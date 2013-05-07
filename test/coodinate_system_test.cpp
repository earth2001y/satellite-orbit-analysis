#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <ctime>

#include "../src/coodinate_system.hpp"

class CoodinateSystemTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE( CoodinateSystemTest );
  CPPUNIT_TEST( test_greenwich_sidereal_time );
  CPPUNIT_TEST( test_toRectangular );
  CPPUNIT_TEST( test_toGeodetic );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
  void setUp();
  void tearDown();

protected:
  void test_greenwich_sidereal_time();
  void test_toRectangular();
  void test_toGeodetic();
};

CPPUNIT_TEST_SUITE_REGISTRATION( CoodinateSystemTest );

// 各テスト・ケースの実行直前に呼ばれる
void CoodinateSystemTest::setUp() {
}

// 各テスト・ケースの実行直後に呼ばれる
void CoodinateSystemTest::tearDown() {
}

void CoodinateSystemTest::test_greenwich_sidereal_time() {
  time_t t;
  time(&t);
//cout << endl << greenwich_sidereal_time(&t) << endl;
}

void CoodinateSystemTest::test_toRectangular()
{
  geodetic g0, g1;
  g0.latitude  = 0.;
  g0.longitude = PI;
  g0.altitude  = 0.;

  g1 = g0.toRectangular().toGeodetic();

  CPPUNIT_ASSERT_DOUBLES_EQUAL(g0.latitude,  g1.latitude,  .001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(g0.longitude, g1.longitude, .001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(g0.altitude,  g1.altitude,  .100);
}

void CoodinateSystemTest::test_toGeodetic()
{
  rectangular r0;
  geodetic g;

  r0.X = -GRS80::a;
  r0.Y = 0.;
  r0.Z = 0.;
  g  = r0.toGeodetic();

  CPPUNIT_ASSERT_DOUBLES_EQUAL(g.latitude,  0., .1);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(g.longitude, PI, .1);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(g.altitude,  0., .1);
}

