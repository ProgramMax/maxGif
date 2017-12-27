// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_ERRORTOKEN_HPP
#define MAXGIF_PARSING_ERRORTOKEN_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <maxGif/Parsing/Token.hpp>

namespace maxGif
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace Parsing
{

	class ErrorToken : public Token
	{
	public:

		enum class ErrorCodes
		{
			BufferTooSmallForToken,
			InvalidHeader,
			UnknownGifVersion,
			UnknownBlock,
			UnexpectedBlockSize,
			BlockTerminatorNotPresent
		};

		constexpr ErrorToken( const size_t StartOffset, const ErrorCodes ErrorCode ) noexcept
			: Token(     StartOffset )
			, ErrorCode( ErrorCode   )
		{
		}

		ErrorCodes ErrorCode;

	};

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_ERRORTOKEN_HPP
