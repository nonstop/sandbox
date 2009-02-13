#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <cppunit/extensions/HelperMacros.h>

class MoneyTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( MoneyTest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp()
  {}
  void tearDown()
  {}

  void testConstructor()
  {
      CPPUNIT_FAIL( "not implemented" );
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MoneyTest );

int main(int argc, char* argv[])
{
  // Get the top level suite from the registry
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

  // Adds the test to the list of test to run
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( suite );

  // Change the default outputter to a compiler error format outputter
  runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                       std::cerr ) );
  // Run the tests.
  bool wasSucessful = runner.run();

  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;
}
