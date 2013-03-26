#include <cppunit/extensions/HelperMacros.h>
#include "../src/tle.hpp"

class TLETest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE( TLETest );
  CPPUNIT_TEST( test_validation );
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

// TLE::validationのテスト・ケース
void TLETest::test_validation() {
  TLE tle;

  CPPUNIT_ASSERT_EQUAL(true, tle.validation("1 23455U 94089A   97320.90946019  .00000140  00000-0  10191-3 0  2621"));
  CPPUNIT_ASSERT_EQUAL(true, tle.validation("2 23455  99.0090 272.6745 0008546 223.1686 136.8816 14.11711747148495"));

  CPPUNIT_ASSERT_EQUAL(true, tle.validation("1 24277U 96046A   09116.47337938 -.00000023  00000-0  73445-5 0   432"));
  CPPUNIT_ASSERT_EQUAL(true, tle.validation("2 24277  98.3597  83.2073 0002090  64.7512 295.3886 14.28595439661547"));

  CPPUNIT_ASSERT_EQUAL(true, tle.validation("1 25112U 97084A   09116.51259343  .00000203  00000-0  12112-3 0  2154"));
  CPPUNIT_ASSERT_EQUAL(true, tle.validation("2 25112  45.0199 241.1109 0010042 194.4473 165.6089 14.34380830592834"));
}


