// Copyright 2016, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <maxGif/Parsing/HeaderBlockToken.hpp>
#include <maxGif/Parsing/ErrorToken.hpp>
#include <maxGif/Parsing/LogicalScreenDescriptorBlockToken.hpp>
#include <iostream>
#include <vector>

namespace
{

	template< typename CallbackPolicy >
	bool BufferHasEnoughSpaceForToken( const std::vector< uint8_t > & Buffer,
	                                   const size_t CurrentOffset,
	                                   const size_t ExpectedTokenSize ) noexcept;

	template< typename CallbackPolicy >
	bool DoesBufferStartWithGIF( const std::vector< uint8_t > & Buffer,
	                             const size_t CurrentOffset ) noexcept;

	template< typename CallbackPolicy >
	bool IsGifVersionKnown( const std::vector< uint8_t > & Buffer,
	                        const size_t CurrentOffset ) noexcept;

	template< typename CallbackPolicy >
	bool ReadHeaderBlock( const std::vector< uint8_t > & Buffer,
	                      const size_t CurrentOffset ) noexcept
	{
		if( BufferHasEnoughSpaceForToken< CallbackPolicy >( Buffer,
		                                                    CurrentOffset,
		                                                    maxGif::v0::Parsing::HeaderBlockToken::Size() ) )
		{
			// Gif files all start with "GIF",
			if( DoesBufferStartWithGIF< CallbackPolicy >( Buffer,
			                                              CurrentOffset ) )
			{
				// followed by the specification version.
				// The only specifications published as of
				// this writing is 87a and 89a
				if( IsGifVersionKnown< CallbackPolicy >( Buffer,
				                                         CurrentOffset + 3 ) )
				{
					CallbackPolicy.OnHeaderBlockEncountered( maxGif::Parsing::HeaderBlockToken( CurrentOffset ), Buffer );
				}
			}
		}

		return true;
	}

	template< typename CallbackPolicyType >
	bool ReadLogicalScreenDescriptorBlock( CallbackPolicyType & CallbackPolicy,
	                                       const std::vector< uint8_t > & Buffer,
	                                       const size_t CurrentOffset ) noexcept
	{
		if( BufferHasEnoughSpaceForToken( CallbackPolicy,
		                                  Buffer,
		                                  CurrentOffset,
		                                  maxGif::Parsing::LogicalScreenDescriptorBlockToken::Size() ) )
		{
			CallbackPolicy.OnLogicalScreenDescriptorBlockEncountered( maxGif::Parsing::LogicalScreenDescriptorBlockToken( CurrentOffset ), Buffer );
		}

		return true;
	}

	template< typename CallbackPolicyType >
	bool BufferHasEnoughSpaceForToken( CallbackPolicyType & CallbackPolicy,
	                                   const std::vector< uint8_t > & Buffer,
	                                   const size_t CurrentOffset,
	                                   const size_t ExpectedTokenSize ) noexcept
	{
		if( Buffer.size() >= CurrentOffset + ExpectedTokenSize )
		{
			return true;
		} else {
			// Not enough space for a header block
			CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken( CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::BufferTooSmallForToken ), Buffer );
			return false;
		}
	}

	template< typename CallbackPolicy >
	bool DoesBufferStartWithGIF( const std::vector< uint8_t > & Buffer,
	                             const size_t CurrentOffset ) noexcept
	{
		// Gif files all start with "GIF",
		if( Buffer[ CurrentOffset + 0 ] == 'G' &&
		    Buffer[ CurrentOffset + 1 ] == 'I' &&
		    Buffer[ CurrentOffset + 2 ] == 'F' )
		{
			return true;
		} else {
			CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken( CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::InvalidHeader ), Buffer );
			return false;
		}
	}

	template< typename CallbackPolicy >
	bool IsGifVersionKnown( const std::vector< uint8_t > & Buffer,
	                        const size_t CurrentOffset ) noexcept
	{
		if( Buffer[ CurrentOffset + 0 ] == '8' &&
		    ( Buffer[ CurrentOffset + 1 ] == '7' ||
		      Buffer[ CurrentOffset + 1 ] == '9' ) &&
		    Buffer[ CurrentOffset + 2 ] == 'a' )
		{
			return true;
		} else {
			CallbackPolicy.OnErrorEncountered( maxGif::v0::Parsing::ErrorToken( CurrentOffset, maxGif::v0::Parsing::ErrorToken::ErrorCodes::UnknownGifVersion ), Buffer );
			return false;
		}
	}

} // anonymous namespace

template< typename CallbackPolicy >
void Parse() noexcept
{
	std::ifstream in( R"(../../corrupt_example.gif)", std::ios::binary | std::ios::ate );
	size_t fileSize = (size_t)in.tellg();
	in.seekg( 0 );

	std::vector< uint8_t > Buffer;
	Buffer.resize( fileSize );

	Buffer.assign( std::istreambuf_iterator< char >( in ), std::istreambuf_iterator< char >() );



	size_t CurrentOffset = 0;


	ReadHeaderBlock( CallbackPolicy, Buffer, CurrentOffset );
	CurrentOffset += maxGif::Parsing::HeaderBlockToken::Size();

	ReadLogicalScreenDescriptorBlock( CallbackPolicy, Buffer, CurrentOffset );
}
