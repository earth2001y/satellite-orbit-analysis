#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "../src/orbit.hpp"
#include "../src/tle.hpp"

class OrbitTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE( OrbitTest );
  CPPUNIT_TEST( test_setTLE );
  CPPUNIT_TEST( test_sgp );
  CPPUNIT_TEST_SUITE_END();

protected:
  TLE tle;
  orbit orb;

public:
  void setUp();
  void tearDown();

protected:
  void test_setTLE();
  void test_sgp();
};

CPPUNIT_TEST_SUITE_REGISTRATION( OrbitTest );

// 各テスト・ケースの実行直前に呼ばれる
void OrbitTest::setUp() {
  std::string line1,line2;
  line1="1 88888U          80275.98708465  .00073094  13844-3  66816-4 0     9";
  line2="2 88888  72.8435 115.9689 0086731  52.6988 110.5714 16.05824518   103";
  tle.set(line1,line2);
}

// 各テスト・ケースの実行直後に呼ばれる
void OrbitTest::tearDown() {
}

void OrbitTest::test_setTLE() {
  orb.setTLE(&tle);
  CPPUNIT_ASSERT(&tle == orb.tle);
}

void OrbitTest::test_sgp() {
  double r[3],v[3];
  double dr, dv;

  dr = 1.e-2;
  dv = 1.e-2;

  orb.setTLE(&tle);

  orb.sgp(r,v,0.);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2328.96594238,r[0],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-5995.21600342,r[1],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1719.97894287,r[2],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.91110113,v[0],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.98164053,v[1],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-7.09049922,v[2],dv);

  orb.sgp(r,v,360.);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2456.00610352,r[0],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-6071.94232177,r[1],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1222.95977784,r[2],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.67852119,v[0],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.44705850,v[1],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-7.22800565,v[2],dv);

  orb.sgp(r,v,720.);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2567.39477539,r[0],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-6112.49725342,r[1],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(  713.97710419,r[2],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.43952477,v[0],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.09884824,v[1],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-7.31889641,v[2],dv);

  orb.sgp(r,v,1080.);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2663.03179932,r[0],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-6115.37414551,r[1],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(  195.73919105,r[2],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.19531813,v[0],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.65333930,v[1],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-7.36169147,v[2],dv);

  orb.sgp(r,v,1440.);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 2742.85470581,r[0],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-6079.13580322,r[1],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( -328.86091614,r[2],dr);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.94707947,v[0],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.21346101,v[1],dv);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(-7.35499924,v[2],dv);
}

