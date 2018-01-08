// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_GRAPHICCONTROLEXTENSIONBLOCKTOKEN_HPP
#define MAXGIF_PARSING_GRAPHICCONTROLEXTENSIONBLOCKTOKEN_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <maxGif/Parsing/VariableSizedToken.hpp>
#include <maxGif/Parsing/BitManipulation.hpp>
#include <vector>
#include <cstddef>

namespace maxGif
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace Parsing
{

	class GraphicControlExtensionBlockToken : public VariableSizedToken
	{
	public:

		explicit constexpr GraphicControlExtensionBlockToken( const size_t StartOffset, const uint8_t SizeInBytes ) noexcept
			: VariableSizedToken( StartOffset, SizeInBytes )
		{
		}

		static constexpr size_t MinimumSizeRequiredInBytes() noexcept
		{
			return 8;
		}

		constexpr size_t SizeInBytes() noexcept
		{
			return VariableSizedToken::SizeInBytes;
		}

		enum class DisposalMethods
		{
			Unspecified = 0,
			KeepThisFrame = 1,
			RestoreBackgroundColorFromLogicalScreenDescriptor = 2,
			RestorePreviousBuffer = 3,
		};

		uint8_t RawDisposalMethod( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t Offset = 3;
			constexpr uint8_t Mask = 0b0001'1100;
			constexpr uint8_t Shift = 3;
			return Get8Bits( & Buffer[ 0 ], StartOffset + Offset, Mask, Shift );
		}

		bool UserInputFlag( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t Offset = 3;
			constexpr uint8_t Mask = 0b0000'0010;
			return GetFlag( & Buffer[ 0 ], Offset, Mask );
		}

		bool TransparentColorFlag( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t Offset = 3;
			constexpr uint8_t Mask = 0b0000'0001;
			return GetFlag( & Buffer[ 0 ], Offset, Mask );
		}

		uint16_t DelayTime( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t Offset = 3;
			return Get16BitsLittleEndian( & Buffer[ 0 ], Offset );
		}

		uint8_t TransparentColorIndex( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			constexpr size_t Offset = 4;
			return Buffer[ StartOffset + Offset ];
		}

	};

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_GRAPHICCONTROLEXTENSIONBLOCKTOKEN_HPP
