// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include <fstream>
#include <vector>
#include <maxGif/GifParser.hpp>
#include <maxGif/Parsing/Tokens.hpp>

class Callbacks
{
public:

	static void OnApplicationExtensionBlockEncountered( const maxGif::Parsing::ApplicationExtensionBlockToken & /*Token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
		std::cout << "Application extension block:" << std::endl;
	}

	static void OnCommentExtensionBlockEncountered( const maxGif::Parsing::CommentExtensionBlockToken & /*Token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
		std::cout << "Comment extension block:" << std::endl;
	}

	static void OnErrorEncountered( const maxGif::Parsing::ErrorToken & Token, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
		std::cout << "Error:" << std::endl;

		switch( Token.ErrorCode )
		{
		case maxGif::Parsing::ErrorToken::ErrorCodes::BufferTooSmallForToken:
			std::cout << "\tBuffer too small for token" << std::endl;
			break;
		case maxGif::Parsing::ErrorToken::ErrorCodes::InvalidHeader:
			std::cout << "\tInvalid header" << std::endl;
			break;
		case maxGif::Parsing::ErrorToken::ErrorCodes::UnknownGifVersion:
			std::cout << "\tUnknown gif version" << std::endl;
			break;
		case maxGif::Parsing::ErrorToken::ErrorCodes::UnknownBlock:
			std::cout << "\tUnknown block" << std::endl;
			break;
		case maxGif::Parsing::ErrorToken::ErrorCodes::UnexpectedBlockSize:
			std::cout << "\tUnexpected block size" << std::endl;
			break;
		default:
			std::cout << "\tUnknown error" << std::endl;
		}
	}

	static void OnGlobalColorTableBlockEncountered( const maxGif::Parsing::GlobalColorTableBlockToken & Token, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
		std::cout << "Global color table block:" << std::endl;

		std::cout << "\tSize in bytes: " << Token.SizeInBytes() << std::endl;
	}

	static void OnGraphicControlExtensionBlockEncountered( const maxGif::Parsing::GraphicControlExtensionBlockToken & Token, const std::vector< uint8_t > & Buffer ) noexcept
	{
		std::cout << "Graphics control extension block:" << std::endl;

		std::cout << "\tRaw Disposal Method: "     << std::to_string( Token.RawDisposalMethod( Buffer ) )     << std::endl;
		std::cout << "\tUser Input Flag: "         << std::to_string( Token.UserInputFlag( Buffer ) )         << std::endl;
		std::cout << "\tTransparent Color Flag: "  << std::to_string( Token.TransparentColorFlag( Buffer ) )  << std::endl;
		std::cout << "\tDelay Time: "              << std::to_string( Token.DelayTime( Buffer ) )             << std::endl;
		std::cout << "\tTransparent Color Index: " << std::to_string( Token.TransparentColorIndex( Buffer ) ) << std::endl;
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

	static void OnImageDataBlockEncountered( const maxGif::Parsing::ImageDataBlockToken & /*Token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

	static void OnImageDescriptorBlockEncountered( const maxGif::Parsing::ImageDescriptorBlockToken & /*Token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
		std::cout << "Image descriptor block:" << std::endl;
	}

	static void OnLocalColorTableBlockEncountered( const maxGif::Parsing::LocalColorTableBlockToken & /*Token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
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

	static void OnPlainTextExtensionBlockEncountered( const maxGif::Parsing::PlainTextExtensionBlockToken & /*Token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
		std::cout << "Plain text extension:" << std::endl;
	}

	static void OnTrailerBlockEncountered( const maxGif::Parsing::TrailerBlockToken & /*Token*/, const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
		std::cout << "Trailer:" << std::endl;
	}

	static void OnBufferDone( const std::vector< uint8_t > & /*Buffer*/ ) noexcept
	{
	}

};

int main()
{
	std::ifstream in( R"(../../corrupt_example.gif)", std::ios::binary | std::ios::ate );
	size_t fileSize = (size_t)in.tellg();
	in.seekg( 0 );

	std::vector< uint8_t > Buffer;
	Buffer.resize( fileSize );

	Buffer.assign( std::istreambuf_iterator< char >( in ), std::istreambuf_iterator< char >() );


	Callbacks CallbackHandler;
	auto Parser = GifParser< Callbacks >{ CallbackHandler };
	Parser.Parse( Buffer );

	return 0;
}
