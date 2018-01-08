// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_GLOBALCOLORTABLEBLOCKTOKEN_HPP
#define MAXGIF_PARSING_GLOBALCOLORTABLEBLOCKTOKEN_HPP

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

	class GlobalColorTableBlockToken : public VariableSizedToken
	{
	public:

		constexpr GlobalColorTableBlockToken( const size_t StartOffset, const uint8_t Size ) noexcept
			: VariableSizedToken( StartOffset, Size )
		{
		}

		size_t SizeInBytes() const noexcept
		{
			return VariableSizedToken::SizeInBytes;
		}

	};

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_GLOBALCOLORTABLEBLOCKTOKEN_HPP
