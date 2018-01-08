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
			CurrentTest.MAX_TESTING_ASSERT( maxGif::Parsing::HeaderBlockToken::SizeInBytes() == 6 );
		}
	));

	TestSuite.RunTests();

	return 0;
}
