#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <ctime>

#include "../src/coodinate_system.hpp"

class CoodinateSystemTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE( CoodinateSystemTest );
  CPPUNIT_TEST( test_greenwich_sidereal_time );
  CPPUNIT_TEST( test_toRectangular );
  CPPUNIT_TEST( test_toPolar );
//CPPUNIT_TEST( test_toEquatorial );
//CPPUNIT_TEST( test_toGeodetic );
  CPPUNIT_TEST_SUITE_END();

protected:

public:
  void setUp();
  void tearDown();

protected:
  void test_greenwich_sidereal_time();
  void test_toRectangular();
  void test_toPolar();
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
}

void CoodinateSystemTest::test_toPolar()
{
  rectangular r;
  polar p;
  r.X = 11.;
  r.Y = 11.;
  r.Z = 11.;

  p = r.toPolar(10.,8.);
//cout << " " << p.latitude << " " << p.longitude << " " << p.altitude << endl;
}

