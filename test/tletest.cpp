#include <cppunit/extensions/HelperMacros.h>
#include "../src/tle.hpp"

class TLETest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE( TLETest );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
  void setUp();
  void tearDown();

protected:
  void test_validation();
  void test_set();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TLETest );

// 各テスト・ケースの実行直前に呼ばれる
void TLETest::setUp() {
}

// 各テスト・ケースの実行直後に呼ばれる
void TLETest::tearDown() {
}


