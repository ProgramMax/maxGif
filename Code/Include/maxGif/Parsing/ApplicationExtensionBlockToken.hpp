// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_APPLICATIONEXTENSIONBLOCKTOKEN_HPP
#define MAXGIF_PARSING_APPLICATIONEXTENSIONBLOCKTOKEN_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <maxGif/Parsing/VariableSizedToken.hpp>
#include <vector>
#include <cstddef>

namespace maxGif
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace Parsing
{

	class ApplicationExtensionBlockToken : public VariableSizedToken
	{
	public:

		constexpr ApplicationExtensionBlockToken( const size_t StartOffset, const uint8_t SizeInBytes ) noexcept
			: VariableSizedToken( StartOffset, SizeInBytes )
		{
		}

		size_t SizeInBytes() const noexcept
		{
			return VariableSizedToken::SizeInBytes;
		}

		constexpr size_t ApplicationBlockStartOffset() noexcept
		{
			return StartOffset + 3;
		}

		uint8_t ApplicationBlockSizeInBytes( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			return Buffer[ StartOffset + 2 ];
		}

	};

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_APPLICATIONEXTENSIONBLOCKTOKEN_HPP
