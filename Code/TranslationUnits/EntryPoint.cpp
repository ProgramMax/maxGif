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

	static void OnCommentExtensionBlockEncountered( const maxGif::Parsing::CommentExtensionBlockToken & /*token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnErrorEncountered( const maxGif::Parsing::ErrorToken & /*token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnGlobalColorTableBlockEncountered( const maxGif::Parsing::GlobalColorTableBlockToken & /*token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnGraphicControlExtensionBlockEncounered( const maxGif::Parsing::GraphicControlExtensionBlockToken & /*token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnHeaderBlockEncountered( const maxGif::Parsing::HeaderBlockToken & Token, const std::vector< uint8_t > & Buffer ) noexcept
	{
		std::cout << "Header block:" << std::endl;

		switch( Token.Standard( Buffer ) )
		{
		case maxGif::Parsing::HeaderBlockToken::GifStandards::_87a:
			std::cout << "\tGif standard 87a" << std::endl;
			break;
		case maxGif::Parsing::HeaderBlockToken::GifStandards::_89a:
			std::cout << "\tGif standard 89a" << std::endl;
			break;
		}
	}

	static void OnImageDataBlockEncountered( const maxGif::Parsing::ImageDataBlockToken & /*token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnImageDescriptorBlockEncounered( const maxGif::Parsing::ImageDescriptorBlockToken & /*token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnLocalColorTableBlockEncountered( const maxGif::Parsing::LocalColorTableBlockToken & /*token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnLogicalScreenDescriptorBlockEncountered( const maxGif::Parsing::LogicalScreenDescriptorBlockToken & Token, const std::vector< uint8_t > & Buffer ) noexcept
	{
		std::cout << "Logical Screen Descriptor block:" << std::endl;

		std::cout << "\tCanvas Width: "               << std::to_string( Token.CanvasWidth(            Buffer ) ) << std::endl;
		std::cout << "\tCanvas Height: "              << std::to_string( Token.CanvasHeight(           Buffer ) ) << std::endl;
		std::cout << "\tGlobal Color Table Flag: "    << std::to_string( Token.GlobalColorTableFlag(   Buffer ) ) << std::endl;
		std::cout << "\tColor Resolution: "           << std::to_string( Token.ColorResolution(        Buffer ) ) << std::endl;
		std::cout << "\tSort Flag: "                  << std::to_string( Token.SortFlag(               Buffer ) ) << std::endl;
		std::cout << "\tSize Of Global Color Table: " << std::to_string( Token.SizeOfGlobalColorTable( Buffer ) ) << std::endl;
		std::cout << "\tBackground Color Index: "     << std::to_string( Token.BackgroundColorIndex(   Buffer ) ) << std::endl;
		std::cout << "\tPixel Aspect Ratio: "         << std::to_string( Token.PixelAspectRatio(       Buffer ) ) << std::endl;
	}

	static void OnPlainTextExtensionBlockEncountered( const maxGif::Parsing::PlainTextExtensionBlockToken & /*token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnTrailerBlockEncountered( const maxGif::Parsing::TrailerBlockToken & /*token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnBufferDone( const std::vector< uint8_t > & /*Buffer*/ ) noexcept
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
