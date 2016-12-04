// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_HEADERBLOCKTOKEN_HPP
#define MAXGIF_PARSING_HEADERBLOCKTOKEN_HPP

#include <max/Compiling/CurrentVersionNamespace.hpp>
#include <max/Compiling/NoDefault.hpp>
#include <maxGif/Parsing/Token.hpp>
#include <vector>
#include <stdint.h>

namespace maxGif
{
MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
{
namespace Parsing
{

	class HeaderBlockToken : public Token
	{
	public:

		explicit constexpr HeaderBlockToken( const size_t StartOffset ) noexcept
			: Token( StartOffset )
		{
		}

		static constexpr size_t SizeInBytes() noexcept
		{
			return 6;
		}

		enum class GifStandards
		{
			_87a,
			_89a
		};

		GifStandards Standard( const std::vector< uint8_t > & Buffer ) const noexcept
		{
			switch( Buffer[ StartOffset + 4 ] )
			{
			case uint8_t('7'):
				return GifStandards::_87a;
			case uint8_t('9'):
				return GifStandards::_89a;
			default:
				// This should never be reached.
				//
				// When parsing, a HeaderBlockToken should not be
				// created unless the version is recognized.
				//
				// Intead, the parser would have created an ErrorToken.
				//
				// If the user of the library finds their bug to be here,
				// they probably provided a different Buffer param.
				MAX_NO_DEFAULT;
			}
		}

	};

} // namespace Parsing
} // MAX_CURRENT_VERSION_NAMESPACE_BEGIN( v0 )
MAX_CURRENT_VERSION_NAMESPACE_END( v0 )
} // namespace maxGif

#endif // #ifndef MAXGIF_PARSING_HEADERBLOCKTOKEN_HPP
