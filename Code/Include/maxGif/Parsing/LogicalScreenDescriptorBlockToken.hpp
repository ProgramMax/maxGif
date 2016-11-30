// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_LOGICALSCREENDESCRIPTORBLOCKTOKEN_HPP
#define MAXGIF_PARSING_LOGICALSCREENDESCRIPTORBLOCKTOKEN_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <maxGif/Parsing/Token.hpp>
#include <vector>
#include <max/Algorithms/SwapEndian.hpp>
#include <max/Compiling/Configuration.hpp>

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
		{}

		static constexpr size_t Size() noexcept
		{
			return 7;
		}

		uint16_t CanvasWidth( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t CanvasWidthOffset = 0;

			return Get16Bits( Buffer, CanvasWidthOffset );
		}

		uint16_t CanvasHeight( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t CanvasHeightOffset = 2;

			return Get16Bits( Buffer, CanvasHeightOffset );
		}

		bool GlobalColorTableFlag( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr uint8_t GlobalColorTableFlagMask = 0b1000'0000;

			return GetFlag( Buffer, PackedFieldOffset, GlobalColorTableFlagMask );
		}

		uint8_t ColorResolution( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr uint8_t ColorResolutionMask  = 0b0111'0000;
			constexpr uint8_t ColorResolutionShift = 4;

			return Get8Bits( Buffer, PackedFieldOffset, ColorResolutionMask, ColorResolutionShift );
		}

		bool SortFlag( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr uint8_t SortFlagMask = 0b0000'1000;

			return GetFlag( Buffer, PackedFieldOffset, SortFlagMask );
		}

		uint8_t SizeOfGlobalColorTable( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr uint8_t SizeOfGlobalColorTableMask  = 0b0000'0111;
			constexpr uint8_t SizeOfGlobalColorTableShift = 0;

			return Get8Bits( Buffer, PackedFieldOffset, SizeOfGlobalColorTableMask, SizeOfGlobalColorTableShift );
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


	private:

		bool GetFlag( const std::vector< uint8_t > & Buffer, const size_t AdditionalOffset, const uint8_t Mask ) const noexcept
		{
			return ( Buffer[ StartOffset + AdditionalOffset ] & Mask ) != 0;
		}

		uint8_t Get8Bits( const std::vector< uint8_t > & Buffer, const size_t AdditionalOffset, const uint8_t Mask, const uint8_t Shift ) const noexcept
		{
			uint8_t EightBits = Buffer[ StartOffset + AdditionalOffset ];

			int MaskedValue = EightBits & Mask;
			int ShiftedValue = MaskedValue >> Shift;

			return static_cast< uint8_t >( ShiftedValue );
		}

		uint16_t Get16Bits( const std::vector< uint8_t > & Buffer, const size_t AdditionalOffset ) const noexcept
		{
			// The value is stored as little-endian
			uint8_t First8Bits  = Buffer[ StartOffset + AdditionalOffset + 0 ];
			uint8_t Second8Bits = Buffer[ StartOffset + AdditionalOffset + 1 ];

			uint16_t CombinedValues = max::Algorithms::CombinePieces( First8Bits, Second8Bits );

			return max::Algorithms::LittleEndianToHost( CombinedValues );
		}

		static constexpr size_t PackedFieldOffset = 4;

	};

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_LOGICALSCREENDESCRIPTORBLOCKTOKEN_HPP
