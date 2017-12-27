// Copyright 2017, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_BITMANIPULATION_HPP
#define MAXGIF_PARSING_BITMANIPULATION_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <max/Algorithms/SwapEndian.hpp>

namespace maxGif
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace Parsing
{

	constexpr bool GetFlag( const uint8_t * const Buffer, const size_t Offset, const uint8_t Mask ) noexcept
	{
		return ( Buffer[ Offset ] & Mask ) != 0;
	}

	constexpr uint8_t Get8Bits( const uint8_t * const Buffer, const size_t Offset, const uint8_t Mask, const uint8_t Shift ) noexcept
	{
		const uint8_t EightBits = Buffer[ Offset ];

		const int MaskedValue = EightBits & Mask;
		const int ShiftedValue = MaskedValue >> Shift;

		return static_cast< uint8_t >( ShiftedValue );
	}

	constexpr uint16_t Get16BitsLittleEndian( const uint8_t * const Buffer, const size_t Offset ) noexcept
	{
		// The value is stored as little-endian
		uint8_t First8Bits = Buffer[ Offset + 0 ];
		uint8_t Second8Bits = Buffer[ Offset + 1 ];

		uint16_t CombinedValues = max::Algorithms::CombinePieces( First8Bits, Second8Bits );

		return max::Algorithms::LittleEndianToHost( CombinedValues );
	}

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_BITMANIPULATION_HPP
