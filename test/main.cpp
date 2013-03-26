#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

int main( int argc, char* argv[] ) {
  // イベント・マネージャとテスト・コントローラを生成する
  CPPUNIT_NS::TestResult controller;

  // テスト結果収集リスナをコントローラにアタッチする
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );

  // 「.」で進行状況を出力するリスナをアタッチする
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );

  // テスト・ランナーにテスト群を与え、テストする
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( controller );

  // テスト結果を標準出力に吐き出す
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write();

  return result.wasSuccessful() ? 0 : 1;

}

