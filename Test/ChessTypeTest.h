#pragma once
#include<CppUnitTest.h>
namespace ChessPosTest {
	TEST_CLASS(ChessPosTest) {
public:
	TEST_METHOD_INITIALIZE(tSetup);
	TEST_METHOD_CLEANUP(tCleanup);
	TEST_METHOD(tChessX);
	TEST_METHOD(tChessY);
	TEST_METHOD(tChessPos);
	};
}