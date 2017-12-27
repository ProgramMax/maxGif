// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <maxGif/Parsing/HeaderBlockToken.hpp>
#include <maxGif/Parsing/ErrorToken.hpp>
#include <maxGif/Parsing/LogicalScreenDescriptorBlockToken.hpp>
#include <maxGif/Parsing/GlobalColorTableBlockToken.hpp>
#include <max/Algorithms/Math.hpp>
#include <maxGif/Parsing/TrailerBlockToken.hpp>
#include <maxGif/Parsing/GraphicControlExtensionBlockToken.hpp>
#include <maxGif/Parsing/ImageDescriptorBlockToken.hpp>
#include <maxGif/Parsing/PlainTextExtensionBlockToken.hpp>
#include <maxGif/Parsing/ApplicationExtensionBlockToken.hpp>
#include <maxGif/Parsing/CommentExtensionBlockToken.hpp>

namespace
{

	class GifParserState
	{
	public:

		GifParserState() noexcept
			: m_CurrentOffset( 0 )
			, m_GlobalColorTableSizeExponent( 0 )
			, m_HasGlobalColorTable( false )
		{
		}

		size_t  m_CurrentOffset;
		uint8_t m_GlobalColorTableSizeExponent;
		bool    m_HasGlobalColorTable;

	};

	template< typename CallbackPolicyType >
	bool BufferHasEnoughSpaceForToken( GifParserState & ParserState,
	                                   CallbackPolicyType & CallbackPolicy,
	                                   const std::vector< uint8_t > & Buffer,
	                                   const size_t ExpectedTokenSize ) noexcept;

	template< typename CallbackPolicyType >
	bool DoesBufferStartWithGIF( GifParserState & ParserState,
	                             CallbackPolicyType & CallbackPolicy,
	                             const std::vector< uint8_t > & Buffer ) noexcept;

	template< typename CallbackPolicyType >
	bool IsGifVersionKnown( GifParserState & ParserState,
	                        CallbackPolicyType & CallbackPolicy,
	                        const std::vector< uint8_t > & Buffer ) noexcept;

	template< typename CallbackPolicyType >
	bool ReadHeaderBlock( GifParserState & ParserState,
	                      CallbackPolicyType & CallbackPolicy,
	                      const std::vector< uint8_t > & Buffer ) noexcept
	{
		if( BufferHasEnoughSpaceForToken( ParserState,
		                                  CallbackPolicy,
		                                  Buffer,
		                                  maxGif::Parsing::HeaderBlockToken::SizeInBytes() ) )
		{
			// Gif files all start with "GIF",
			if( DoesBufferStartWithGIF( ParserState,
			                            CallbackPolicy,
			                            Buffer ) )
			{
				// followed by the specification version.
				// The only specifications published as of
				// this writing is 87a and 89a
				if( IsGifVersionKnown( ParserState,
				                       CallbackPolicy,
				                       Buffer ) )
				{
					CallbackPolicy.OnHeaderBlockEncountered( maxGif::Parsing::HeaderBlockToken( ParserState.m_CurrentOffset ), Buffer );
					ParserState.m_CurrentOffset += maxGif::Parsing::HeaderBlockToken::SizeInBytes();
				}
			}
		}

		return true;
	}

	template< typename CallbackPolicyType >
	bool ReadLogicalScreenDescriptorBlock( GifParserState & ParserState,
	                                       CallbackPolicyType & CallbackPolicy,
	                                       const std::vector< uint8_t > & Buffer ) noexcept
	{
		if( BufferHasEnoughSpaceForToken( ParserState,
		                                  CallbackPolicy,
		                                  Buffer,
		                                  maxGif::Parsing::LogicalScreenDescriptorBlockToken::SizeInBytes() ) )
		{
			auto Token = maxGif::Parsing::LogicalScreenDescriptorBlockToken{ ParserState.m_CurrentOffset };

			ParserState.m_HasGlobalColorTable = Token.GlobalColorTableFlag( Buffer );
			ParserState.m_GlobalColorTableSizeExponent = Token.ColorResolution( Buffer );

			CallbackPolicy.OnLogicalScreenDescriptorBlockEncountered( Token, Buffer );
			ParserState.m_CurrentOffset += maxGif::Parsing::LogicalScreenDescriptorBlockToken::SizeInBytes();
			return true;
		} else {
			return false;
		}
	}

	template< typename CallbackPolicyType >
	bool ReadOptionalGlobalColorTableBlock( GifParserState & ParserState,
	                                        CallbackPolicyType & CallbackPolicy,
	                                        const std::vector< uint8_t > & Buffer )
	{
		if( ! ParserState.m_HasGlobalColorTable )
		{
			return true;
		} else {
			// When reading the logical screen descriptor,
			// we encountered the global color table size exponent.
			// It tells us the number of colors in the global
			// color table.
			// It is N in the equation 2^(N+1).
			size_t GlobalColorTableEntryCount = max::Algorithms::TwoToThePowerOf( static_cast< size_t >( ParserState.m_GlobalColorTableSizeExponent + 1 ) );

			// Each color table entry is 3 bytes.
			size_t GlobalColorTableSizeInBytes = GlobalColorTableEntryCount * 3;

			if( BufferHasEnoughSpaceForToken( ParserState,
			                                  CallbackPolicy,
			                                  Buffer,
			                                  GlobalColorTableSizeInBytes ) )
			{
				CallbackPolicy.OnGlobalColorTableBlockEncountered( maxGif::Parsing::GlobalColorTableBlockToken{ ParserState.m_CurrentOffset, GlobalColorTableSizeInBytes }, Buffer );
				ParserState.m_CurrentOffset += GlobalColorTableSizeInBytes;
				return true;
			} else {
				return false;
			}
		}
	}

	template< typename CallbackPolicyType >
	bool ReadGraphicControlExtensionBlock( GifParserState & ParserState,
	                                       CallbackPolicyType & CallbackPolicy,
	                                       const std::vector< uint8_t > & Buffer ) noexcept
	{
		if( BufferHasEnoughSpaceForToken( ParserState,
		                                  CallbackPolicy,
		                                  Buffer,
		                                  3 ) )
		{
			auto ExtensionSize = Buffer[ ParserState.m_CurrentOffset ];
			if (ExtensionSize != 4)
			{
				CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken{ ParserState.m_CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::UnexpectedBlockSize }, Buffer );
				return false;
			}

			if (BufferHasEnoughSpaceForToken( ParserState,
			                                  CallbackPolicy,
			                                  Buffer,
			                                  maxGif::v0::Parsing::GraphicControlExtensionBlockToken::SizeInBytes()  ) )
			{
				auto BlockTerminator = Buffer[ ParserState.m_CurrentOffset + maxGif::v0::Parsing::GraphicControlExtensionBlockToken::SizeInBytes() - 1 ];
				if( BlockTerminator != 0x00 )
				{
					CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken( ParserState.m_CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::BlockTerminatorNotPresent ), Buffer );
					return false;
				}
				CallbackPolicy.OnGraphicControlExtensionBlockEncountered( maxGif::v0::Parsing::GraphicControlExtensionBlockToken{ ParserState.m_CurrentOffset }, Buffer );
				ParserState.m_CurrentOffset += maxGif::v0::Parsing::GraphicControlExtensionBlockToken::SizeInBytes();
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}

	template< typename CallbackPolicyType >
	bool ReadFirstBodyBlock( GifParserState & ParserState,
	                         CallbackPolicyType & CallbackPolicy,
	                         const std::vector< uint8_t > & Buffer ) noexcept
	{
		if( BufferHasEnoughSpaceForToken( ParserState,
		                                  CallbackPolicy,
		                                  Buffer,
		                                  1 ) )
		{
			switch( Buffer[ ParserState.m_CurrentOffset ] )
			{
			case 0x21: // Extension introducer
				{
					if( BufferHasEnoughSpaceForToken( ParserState,
					                                  CallbackPolicy,
					                                  Buffer,
					                                  2 ) )
					{
						switch( Buffer[ ParserState.m_CurrentOffset ] )
						{
						case 0xf9: // Graphics control label
							CallbackPolicy.OnGraphicControlExtensionBlockEncountered( maxGif::v0::Parsing::GraphicControlExtensionBlockToken{ ParserState.m_CurrentOffset }, Buffer );
							return ReadGraphicControlExtensionBlock( ParserState,
							                                         CallbackPolicy,
                                                                     Buffer );
							break;
						case 0x01: // Plain text label
							CallbackPolicy.OnPlainTextExtensionBlockEncountered( maxGif::v0::Parsing::PlainTextExtensionBlockToken{ ParserState.m_CurrentOffset }, Buffer );
							break;
						case 0xff: // Application label
							if( BufferHasEnoughSpaceForToken( ParserState,
							                                  CallbackPolicy,
							                                  Buffer,
							                                  1 ) )
							{
								uint8_t LabelLength = Buffer[ ParserState.m_CurrentOffset + 1 ];
								CallbackPolicy.OnApplicationExtensionBlockEncountered( maxGif::v0::Parsing::ApplicationExtensionBlockToken{ ParserState.m_CurrentOffset, LabelLength }, Buffer );
							}
							break;
						case 0xfe: // Comment label
							CallbackPolicy.OnCommentExtensionBlockEncountered( maxGif::v0::Parsing::CommentExtensionBlockToken{ ParserState.m_CurrentOffset }, Buffer );
							break;
						default:
							CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken{ ParserState.m_CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::UnknownBlock }, Buffer );
							return false;
						}
					}
				}
				return true;
				break;
			case 0x2c: // Image descriptor
				CallbackPolicy.OnImageDescriptorBlockEncountered( maxGif::v0::Parsing::ImageDescriptorBlockToken{ ParserState.m_CurrentOffset }, Buffer );
				return true;
				break;
			case 0x3b: // Trailer
				CallbackPolicy.OnTrailerBlockEncountered( maxGif::v0::Parsing::TrailerBlockToken{ ParserState.m_CurrentOffset }, Buffer );
				ParserState.m_CurrentOffset += maxGif::v0::Parsing::TrailerBlockToken::SizeInBytes();
				return true;
				break;
			default:
				CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken{ ParserState.m_CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::UnknownBlock }, Buffer );
				return false;
			}
		} else {
			return false;
		}
	}

	template< typename CallbackPolicyType >
	bool BufferHasEnoughSpaceForToken( GifParserState & ParserState,
	                                   CallbackPolicyType & CallbackPolicy,
	                                   const std::vector< uint8_t > & Buffer,
	                                   const size_t ExpectedTokenSize ) noexcept
	{
		if( Buffer.size() >= ParserState.m_CurrentOffset + ExpectedTokenSize )
		{
			return true;
		} else {
			// Not enough space for a header block
			CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken{ ParserState.m_CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::BufferTooSmallForToken }, Buffer );
			return false;
		}
	}

	template< typename CallbackPolicyType >
	bool DoesBufferStartWithGIF( GifParserState & ParserState,
	                             CallbackPolicyType & CallbackPolicy,
	                             const std::vector< uint8_t > & Buffer ) noexcept
	{
		// Gif files all start with "GIF",
		if( Buffer[ ParserState.m_CurrentOffset + 0 ] == 'G' &&
		    Buffer[ ParserState.m_CurrentOffset + 1 ] == 'I' &&
		    Buffer[ ParserState.m_CurrentOffset + 2 ] == 'F' )
		{
			return true;
		} else {
			CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken( ParserState.m_CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::InvalidHeader ), Buffer );
			return false;
		}
	}

	template< typename CallbackPolicyType >
	bool IsGifVersionKnown( GifParserState & ParserState,
	                        CallbackPolicyType & CallbackPolicy,
	                        const std::vector< uint8_t > & Buffer ) noexcept
	{
		if( Buffer[ ParserState.m_CurrentOffset + 3 ] == '8' &&
		    ( Buffer[ ParserState.m_CurrentOffset + 4 ] == '7' ||
		      Buffer[ ParserState.m_CurrentOffset + 4 ] == '9' ) &&
		    Buffer[ ParserState.m_CurrentOffset + 5 ] == 'a' )
		{
			return true;
		} else {
			CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken( ParserState.m_CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::UnknownGifVersion ), Buffer );
			return false;
		}
	}

} // anonymous namespace





template< typename CallbackPolicyType >
GifParser< CallbackPolicyType >::GifParser( CallbackPolicyType & CallbackPolicy ) noexcept
	: m_CallbackPolicy( CallbackPolicy )
{
}

template< typename CallbackPolicyType >
void GifParser< CallbackPolicyType >::Parse( const std::vector< uint8_t > & Buffer ) noexcept
{
	GifParserState ParserState;

	ReadHeaderBlock( ParserState, m_CallbackPolicy, Buffer );

	ReadLogicalScreenDescriptorBlock( ParserState, m_CallbackPolicy, Buffer );

	ReadOptionalGlobalColorTableBlock( ParserState, m_CallbackPolicy, Buffer );

	ReadFirstBodyBlock( ParserState, m_CallbackPolicy, Buffer );
}
