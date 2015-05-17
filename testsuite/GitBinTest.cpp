#include <iostream>
#include <cstdio>
#include <string>
#include <list>
#include <fstream>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

#include <Poco/File.h>
#include <Poco/StreamCopier.h>
#include <Poco/DigestStream.h>
#include <Poco/MD5Engine.h>
#include <Poco/FileStream.h>

#include "Plugin.h"

using namespace CppUnit;

using Poco::DigestOutputStream;
using Poco::DigestEngine;
using Poco::MD5Engine;
using Poco::FileOutputStream;

class GitBinTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(GitBinTest);
    CPPUNIT_TEST(TestIndexCreate);
    CPPUNIT_TEST(TestIndexRead);
    CPPUNIT_TEST_SUITE_END();
    public:
    void setUp(void);
    void tearDown(void);
    protected:
    void TestIndexCreate(void);
    void TestIndexRead(void);
    private:
    std::vector<std::string> uuids;
};

void GitBinTest::setUp(void)
{
    // Create 100 random files
    Poco::File f("tests");
    f.createDirectory();
    UUIDGenerator gen;
    for (int i = 0; i < 100; i++)
    {
        UUID uuid = gen.createRandom();
        std::string filename("tests/");
        filename.append(uuid.toString());
        FileOutputStream ofstr(filename);
        ofstr << uuid.toString();
        uuids.push_back(uuid.toString());
    }
}

void GitBinTest::tearDown(void)
{
    Poco::File f("tests");
    f.remove(true);
}

void GitBinTest::TestIndexCreate(void)
{
    Plugin* p = new Plugin();
    for (auto it = uuids.begin(); it != uuids.end(); it++)
    {
        std::string filepath("tests/");
        p->addFile(filepath.append(*it));
    }    
}

void GitBinTest::TestIndexRead(void)
{

}

CPPUNIT_TEST_SUITE_REGISTRATION(GitBinTest);
int main(int argc, char* argv[])
{
    CPPUNIT_NS::TestResult testResult;
    CPPUNIT_NS::TestResultCollector collectedResults;
    testResult.addListener(&collectedResults);
    CPPUNIT_NS::BriefTestProgressListener progress;
    testResult.addListener(&progress);
    CPPUNIT_NS::TestRunner testRunner;
    testRunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    testRunner.run(testResult);
    CPPUNIT_NS::CompilerOutputter compilerOutputter(&collectedResults, std::cerr);
    compilerOutputter.write();
    return collectedResults.wasSuccessful() ? 0 : 1;
}
