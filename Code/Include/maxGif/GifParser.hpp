// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAXGIF_PARSING_GIFPARSER_HPP
#define MAXGIF_PARSING_GIFPARSER_HPP

#include <vector>

template< typename CallbackPolicyType >
class GifParser
{
public:

	explicit GifParser( CallbackPolicyType & CallbackPolicy ) noexcept;

	void Parse( const std::vector< uint8_t > & Buffer ) noexcept;

private:

	CallbackPolicyType m_CallbackPolicy;
};

#include <maxGif/GifParser.inl>

#endif // #ifndef MAXGIF_PARSING_GIFPARSER_HPP
