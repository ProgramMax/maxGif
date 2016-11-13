// Copyright 2016, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_TOKEN_HPP
#define MAXGIF_PARSING_TOKEN_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <cstddef>

namespace maxGif
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace Parsing
{

	struct Token
	{
		explicit constexpr Token( const size_t StartOffset ) noexcept
			: StartOffset( StartOffset )
		{}

		size_t StartOffset;
	};

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_TOKEN_HPP
