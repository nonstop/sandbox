#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>


#include "confpp.h"

class ConfTest : public CppUnit::TestFixture
{ 
    CPPUNIT_TEST_SUITE( ConfTest );
    CPPUNIT_TEST( simpleReadInt );
    CPPUNIT_TEST( simpleReadDbl );
    CPPUNIT_TEST( simpleReadString );
    CPPUNIT_TEST( arraysReadInts );
    CPPUNIT_TEST( arraysReadDoubles );
    CPPUNIT_TEST( arraysReadStrings );
    CPPUNIT_TEST_SUITE_END();
public: 
    void setUp()
    {
        simple = new confpp::ConfigFile("simple.cfg");
        arrays = new confpp::ConfigFile("arrays.cfg");
    }
    void tearDown()
    {
        delete arrays;
        delete simple;
    }
    
    void simpleReadInt() 
    {
        CPPUNIT_ASSERT(simple->get<int>("intValue") == 124);
    }
    void simpleReadDbl() 
    {
        CPPUNIT_ASSERT(simple->get<double>("dblValue") == 36.5);
    }
    void simpleReadString()
    {
        CPPUNIT_ASSERT(simple->get<std::string>("strValue") == "string value");
    }
    void arraysReadInts() 
    {
        std::vector<int> ints;
        arrays->get("ints", ints);

        CPPUNIT_ASSERT(ints.size() == 3);

        CPPUNIT_ASSERT(ints[0] == 3);
        CPPUNIT_ASSERT(ints[1] == -4);
        CPPUNIT_ASSERT(ints[2] == 5);
    }
    void arraysReadDoubles() 
    {
        std::vector<double> doubles;
        arrays->get("doubles", doubles);

        CPPUNIT_ASSERT(doubles.size() == 5);

        CPPUNIT_ASSERT(doubles[0] == 1);
        CPPUNIT_ASSERT(doubles[1] == 2);
        CPPUNIT_ASSERT(doubles[2] == 3);
        CPPUNIT_ASSERT(doubles[3] == 4.3);
        CPPUNIT_ASSERT(doubles[4] == 43);
    }
//    strings=   str1 str2 str3 "str 4"
    void arraysReadStrings()
    {
        std::vector<std::string> strs;
        arrays->get("strings", strs);

        CPPUNIT_ASSERT(strs.size() == 5);

        CPPUNIT_ASSERT(strs[0] == "str1");
        CPPUNIT_ASSERT(strs[1] == "str 2");
        CPPUNIT_ASSERT(strs[2] == "st\"r\"3");
        CPPUNIT_ASSERT(strs[3] == "str 4");
        CPPUNIT_ASSERT(strs[4] == "str \"5\"");
    }
    bool operator==(const ConfTest &b) const
    { 
        return true; 
    }
private:
    confpp::ConfigFile *simple, *arrays;
};

CPPUNIT_TEST_SUITE_REGISTRATION( ConfTest );

int main(int ac, char *av[])
{
    // Get the top level suite from the registry
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( suite );

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(), std::cerr ) );
    // Run the tests.
    bool wasSucessful = runner.run();

    // Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}

