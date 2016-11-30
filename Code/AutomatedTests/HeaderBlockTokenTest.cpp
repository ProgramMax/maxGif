// Copyright 2016, The maxGif Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <max/Testing/TestSuite.hpp>
#include <maxGif/Parsing/Tokens.hpp>
#include <vector>

int main() {
	auto TestSuite = max::Testing::TestSuite( "HeaderBlockToken" );
	TestSuite.AddTest( max::Testing::Test( "constructor sets the start offset",
		[]( max::Testing::Test & CurrentTest ) {
			auto const StartOffset = size_t{ 0 };
			auto const TestObject = maxGif::Parsing::HeaderBlockToken{ StartOffset };

			CurrentTest.MAX_TESTING_ASSERT( TestObject.StartOffset == StartOffset );
		}
	));

	TestSuite.AddTest( max::Testing::Test( "size is 6",
		[]( max::Testing::Test & CurrentTest ) {
			CurrentTest.MAX_TESTING_ASSERT( maxGif::Parsing::HeaderBlockToken::Size() == 6 );
		}
	));

	TestSuite.AddTest( max::Testing::Test( "standard 87a is parsed",
		[]( max::Testing::Test & CurrentTest ) {
			auto const Buffer = std::vector< uint8_t >{ 'G', 'I', 'F', '8', '7', 'a' };
			auto const TestObject = maxGif::Parsing::HeaderBlockToken{ 0 };

			CurrentTest.MAX_TESTING_ASSERT( TestObject.Standard( Buffer ) == maxGif::Parsing::HeaderBlockToken::GifStandards::_87a );
		}
	));

	TestSuite.AddTest( max::Testing::Test( "standard 89a is parsed",
		[]( max::Testing::Test & CurrentTest ) {
			auto const Buffer = std::vector< uint8_t >{ 'G', 'I', 'F', '8', '9', 'a' };
			auto const TestObject = maxGif::Parsing::HeaderBlockToken{ 0 };

			CurrentTest.MAX_TESTING_ASSERT( TestObject.Standard( Buffer ) == maxGif::Parsing::HeaderBlockToken::GifStandards::_89a );
		}
	));

	TestSuite.RunTests();

	return 0;
}
