// Copyright 2016, Chris Blume. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include <fstream>
#include <vector>
#include <maxGif/Parse.hpp>
#include <maxGif/Parsing/Tokens.hpp>

class Callbacks
{
public:

	static void OnCommentExtensionBlockEncountered( const maxGif::Parsing::CommentExtensionBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnErrorEncountered( const maxGif::Parsing::ErrorToken & /*token*/ ) noexcept
	{
	}

	static void OnGlobalColorTableBlockEncountered( const maxGif::Parsing::GlobalColorTableBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnGraphicControlExtensionBlockEncounered( const maxGif::Parsing::GraphicControlExtensionBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnHeaderBlockEncountered( const maxGif::Parsing::HeaderBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnImageDataBlockEncountered( const maxGif::Parsing::ImageDataBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnImageDescriptorBlockEncounered( const maxGif::Parsing::ImageDescriptorBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnLocalColorTableBlockEncountered( const maxGif::Parsing::LocalColorTableBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnLogicalScreenDescriptorBlockEncountered( const maxGif::Parsing::LogicalScreenDescriptorBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnPlainTextExtensionBlockEncountered( const maxGif::Parsing::PlainTextExtensionBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnTrailerBlockEncountered( const maxGif::Parsing::TrailerBlockToken & /*token*/ ) noexcept
	{
	}

	static void OnBufferDone() noexcept
	{
	}

};

int main()
{
	Callbacks CallbackObject;
	Parse<>( CallbackObject );

	return 0;
}
