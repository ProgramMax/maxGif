// Copyright 2015, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_ALGORITHMS_SWAPENDIAN_HPP
#define MAX_ALGORITHMS_SWAPENDIAN_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <max/Compiling/AliasingOptimizations.hpp>
#include <cstdint>
#include <max/Compiling/ThrowSpecification.hpp>

namespace max
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace Algorithms
{

	MAX_PURE_DECLARATION( constexpr inline uint64_t SwapEndian( const uint64_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint32_t SwapEndian( const uint32_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint16_t SwapEndian( const uint16_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int64_t  SwapEndian( const int64_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int32_t  SwapEndian( const int32_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int16_t  SwapEndian( const int16_t  Value ) MAX_DOES_NOT_THROW );

	MAX_PURE_DECLARATION( constexpr inline uint64_t LittleEndianToHost( const uint64_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint32_t LittleEndianToHost( const uint32_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint16_t LittleEndianToHost( const uint16_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int64_t  LittleEndianToHost( const int64_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int32_t  LittleEndianToHost( const int32_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int16_t  LittleEndianToHost( const int16_t  Value ) MAX_DOES_NOT_THROW );

	MAX_PURE_DECLARATION( constexpr inline uint64_t BigEndianToHost( const uint64_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint32_t BigEndianToHost( const uint32_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint16_t BigEndianToHost( const uint16_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int64_t  BigEndianToHost( const int64_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int32_t  BigEndianToHost( const int32_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int16_t  BigEndianToHost( const int16_t  Value ) MAX_DOES_NOT_THROW );

	MAX_PURE_DECLARATION( constexpr inline uint64_t HostToLittleEndian( const uint64_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint32_t HostToLittleEndian( const uint32_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint16_t HostToLittleEndian( const uint16_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int64_t  HostToLittleEndian( const int64_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int32_t  HostToLittleEndian( const int32_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int16_t  HostToLittleEndian( const int16_t  Value ) MAX_DOES_NOT_THROW );

	MAX_PURE_DECLARATION( constexpr inline uint64_t HostToBigEndian( const uint64_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint32_t HostToBigEndian( const uint32_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline uint16_t HostToBigEndian( const uint16_t Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int64_t  HostToBigEndian( const int64_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int32_t  HostToBigEndian( const int32_t  Value ) MAX_DOES_NOT_THROW );
	MAX_PURE_DECLARATION( constexpr inline int16_t  HosttoBigEndian( const int16_t  Value ) MAX_DOES_NOT_THROW );

} // namespace Algorithms
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace max

#include <max/Algorithms/SwapEndian.inl>

#endif // #ifndef MAX_ALGORITHMS_SWAPENDIAN_HPP
