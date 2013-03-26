#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "../src/tle.hpp"

class TLETest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE( TLETest );
  CPPUNIT_TEST( test_validation );
  CPPUNIT_TEST( test_set );
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

  CPPUNIT_ASSERT(tle.validation("1 23455U 94089A   97320.90946019  .00000140  00000-0  10191-3 0  2621"));
  CPPUNIT_ASSERT(tle.validation("2 23455  99.0090 272.6745 0008546 223.1686 136.8816 14.11711747148495"));

  CPPUNIT_ASSERT(tle.validation("1 24277U 96046A   09116.47337938 -.00000023  00000-0  73445-5 0   432"));
  CPPUNIT_ASSERT(tle.validation("2 24277  98.3597  83.2073 0002090  64.7512 295.3886 14.28595439661547"));

  CPPUNIT_ASSERT(tle.validation("1 25112U 97084A   09116.51259343  .00000203  00000-0  12112-3 0  2154"));
  CPPUNIT_ASSERT(tle.validation("2 25112  45.0199 241.1109 0010042 194.4473 165.6089 14.34380830592834"));
}

// TLE::setのテスト・ケース
void TLETest::test_set() {
  TLE tle;
  std::string line1,line2;
/*
1 23455U 94089A   97320.90946019  .00000140  00000-0  10191-3 0  2621
2 23455  99.0090 272.6745 0008546 223.1686 136.8816 14.11711747148495
*/
  line1 = "1 23455U 94089A   97320.90946019  .00000140  00000-0  10191-3 0  2621";
  line2 = "2 23455  99.0090 272.6745 0008546 223.1686 136.8816 14.11711747148495";

  CPPUNIT_ASSERT(tle.set(line1,line2));
  CPPUNIT_ASSERT_EQUAL(23455,tle.number);
  CPPUNIT_ASSERT_EQUAL('U',tle.classification);
  CPPUNIT_ASSERT_EQUAL(94,tle.IDYY);
  CPPUNIT_ASSERT_EQUAL(89,tle.IDNY);
  CPPUNIT_ASSERT(std::string("A  ") == tle.IDPL);
  CPPUNIT_ASSERT_EQUAL(97,tle.epoch_year);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(320.90946019,tle.epoch_day,10e-8);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.00000280,tle.dmotion,10e-8);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.00000000,tle.ddmotion,10e-8);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.10191e-3,tle.BSTAR,10e-8);
  CPPUNIT_ASSERT_EQUAL('0',tle.ephemeris);
  CPPUNIT_ASSERT_EQUAL(262,tle.elemnum);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(99.0090,tle.inclination,10e-4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(272.6745,tle.ascension,10e-4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(.0008546,tle.eccentricity,10e-7);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(223.1686,tle.perigee,10e-4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(136.8816,tle.anomaly,10e-4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(14.11711747,tle.motion,10e-8);
  CPPUNIT_ASSERT_EQUAL(14849,tle.revolution);

/*
1 24277U 96046A   09116.47337938 -.00000023  00000-0  73445-5 0   432
2 24277  98.3597  83.2073 0002090  64.7512 295.3886 14.28595439661547
*/
  line1 = "1 24277U 96046A   09116.47337938 -.00000023  00000-0  73445-5 0   432";
  line2 = "2 24277  98.3597  83.2073 0002090  64.7512 295.3886 14.28595439661547";

  CPPUNIT_ASSERT(tle.set(line1,line2));
  CPPUNIT_ASSERT_EQUAL(24277,tle.number);
  CPPUNIT_ASSERT_EQUAL('U',tle.classification);
  CPPUNIT_ASSERT_EQUAL(96,tle.IDYY);
  CPPUNIT_ASSERT_EQUAL(46,tle.IDNY);
  CPPUNIT_ASSERT(std::string("A  ") == tle.IDPL);
  CPPUNIT_ASSERT_EQUAL(9,tle.epoch_year);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(116.47337938,tle.epoch_day,10e-8);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.00000046,tle.dmotion,10e-8);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.00000000,tle.ddmotion,10e-8);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.73445e-5,tle.BSTAR,1e-10);
  CPPUNIT_ASSERT_EQUAL('0',tle.ephemeris);
  CPPUNIT_ASSERT_EQUAL(43,tle.elemnum);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(98.3597,tle.inclination,10e-4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(83.2073,tle.ascension,10e-4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(.0002090,tle.eccentricity,10e-7);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(64.7512,tle.perigee,10e-4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(295.3886,tle.anomaly,10e-4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(14.28595439,tle.motion,10e-8);
  CPPUNIT_ASSERT_EQUAL(66154,tle.revolution);
}

