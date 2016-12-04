// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_APPLICATIONEXTENSIONBLOCKTOKEN_HPP
#define MAXGIF_PARSING_APPLICATIONEXTENSIONBLOCKTOKEN_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <maxGif/Parsing/Token.hpp>
#include <vector>

namespace maxGif
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace Parsing
{

	class ApplicationExtensionBlockToken : public Token
	{
	public:

		explicit constexpr ApplicationExtensionBlockToken( const size_t StartOffset ) noexcept
			: Token( StartOffset )
		{
		}

		static constexpr size_t SizeInBytes() noexcept
		{
			return 0;
		}

	};

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_APPLICATIONEXTENSIONBLOCKTOKEN_HPP
