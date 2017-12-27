// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_LOGICALSCREENDESCRIPTORBLOCKTOKEN_HPP
#define MAXGIF_PARSING_LOGICALSCREENDESCRIPTORBLOCKTOKEN_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <maxGif/Parsing/Token.hpp>
#include <vector>
#include <maxGif/Parsing/BitManipulation.hpp>

namespace maxGif
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace Parsing
{

	class LogicalScreenDescriptorBlockToken : public Token
	{
	public:

		explicit constexpr LogicalScreenDescriptorBlockToken( const size_t StartOffset ) noexcept
			: Token( StartOffset )
		{
		}

		static constexpr size_t SizeInBytes() noexcept
		{
			return 7;
		}

		uint16_t CanvasWidth( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t CanvasWidthOffset = 0;

			return Get16BitsLittleEndian( & Buffer[ 0 ], StartOffset + CanvasWidthOffset );
		}

		uint16_t CanvasHeight( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t CanvasHeightOffset = 2;

			return Get16BitsLittleEndian( & Buffer[ 0 ], StartOffset + CanvasHeightOffset );
		}

		bool GlobalColorTableFlag( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr uint8_t GlobalColorTableFlagMask = 0b1000'0000;

			return GetFlag( & Buffer[ 0 ], StartOffset + PackedFieldOffset, GlobalColorTableFlagMask );
		}

		uint8_t ColorResolution( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr uint8_t ColorResolutionMask  = 0b0111'0000;
			constexpr uint8_t ColorResolutionShift = 4;

			return Get8Bits( & Buffer[ 0 ], StartOffset + PackedFieldOffset, ColorResolutionMask, ColorResolutionShift );
		}

		bool SortFlag( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr uint8_t SortFlagMask = 0b0000'1000;

			return GetFlag( & Buffer[ 0 ], StartOffset + PackedFieldOffset, SortFlagMask );
		}

		uint8_t SizeOfGlobalColorTable( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr uint8_t SizeOfGlobalColorTableMask  = 0b0000'0111;
			constexpr uint8_t SizeOfGlobalColorTableShift = 0;

			return Get8Bits( & Buffer[ 0 ], StartOffset + PackedFieldOffset, SizeOfGlobalColorTableMask, SizeOfGlobalColorTableShift );
		}

		uint8_t BackgroundColorIndex( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t BackgroundColorIndexOffset = 5;

			return Buffer[ StartOffset + BackgroundColorIndexOffset ];
		}

		uint8_t PixelAspectRatio( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t PixelAspectRatioOffset = 6;

			return Buffer[ StartOffset + PixelAspectRatioOffset ];
		}

		static constexpr size_t PackedFieldOffset = 4;

	};

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_LOGICALSCREENDESCRIPTORBLOCKTOKEN_HPP
