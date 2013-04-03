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
  orb.setTLE(&tle);
  orb.sgp(r,v,0.);
  CPPUNIT_ASSERT_EQUAL(2328.,r[0]);
}

