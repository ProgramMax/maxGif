// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <maxGif/Parsing/HeaderBlockToken.hpp>
#include <maxGif/Parsing/ErrorToken.hpp>
#include <maxGif/Parsing/LogicalScreenDescriptorBlockToken.hpp>
#include <maxGif/Parsing/GlobalColorTableBlockToken.hpp>
#include <max/Algorithms/Math.hpp>

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
		}

		return true;
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
}
