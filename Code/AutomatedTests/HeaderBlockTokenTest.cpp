// Copyright 2016, Chris Blume. All rights reserved.

#include <max/Testing/TestSuite.hpp>

int main() {
	auto TestSuite = max::Testing::TestSuite( "HeaderBlockToken" );
	TestSuite.AddTest( max::Testing::Test( "constructor",
		[]( max::Testing::Test & CurrentTest ) {
			auto const StartOffset = size_t{ 0 };
			auto       TestObject = maxGif::v0::Parsing::HeaderBlockToken{};

			CurrentTest.MAX_TESTING_ASSERT( TestObject.StartOffset == StartOffset );
		}
	));

	TestSuite.RunTests();
}
