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
    CPPUNIT_TEST(TestInitS3);
    CPPUNIT_TEST(TestAddNewFile);
    CPPUNIT_TEST(TestAddModifiedFile);
    CPPUNIT_TEST_SUITE_END();
    public:
    void setUp(void);
    void tearDown(void);
    protected:
    void TestInitS3(void);
    void TestAddNewFile(void);
    void TestAddModifiedFile(void);
    private:
    std::vector<std::string> uuids;
};

void GitBinTest::setUp(void)
{
}

void GitBinTest::tearDown(void)
{
}

void GitBinTest::TestInitS3(void)
{
    Plugin* p = new Plugin();
    p->handleInit("--init", "s3://somepath");
    std::vector<std::string> files;
    files.push_back(".git-bin");
    files.push_back(".git/keshig");
    files.push_back(".git/bin-cache");
    for (auto it = files.begin(); it != files.end(); it++)
    {
        File f((*it));
        CPPUNIT_ASSERT(f.exists() == true);
    }
    delete p;
}

void GitBinTest::TestAddNewFile(void)
{
    File f("test-file");
    if (!f.exists()) f.createFile();
    Plugin* p = new Plugin();
    p->addFile("test-file");
    auto index = p->getIndex();
    CPPUNIT_ASSERT(index != nullptr);
    for (auto it = index->begin(); it != index->end(); it++)
    {
        std::cout << "Index entry:" << std::endl;
        std::cout << "\t\tFilepath: " << (*it).filepath << std::endl;
        std::cout << "\t\tMD5: " << (*it).md5 << std::endl;
        std::cout << "\t\tUUID: " << (*it).uuid << std::endl;
    }
    delete p;
}

void GitBinTest::TestAddModifiedFile(void)
{
    Poco::FileOutputStream ostr("test-file");
    ostr << "This is a test" << std::endl;
    Plugin* p = new Plugin();
    p->addFile("test-file");
    delete p;
}

void TestWorkFlow(void)
{
    return;
    // Remove everything before tests
    std::vector<std::string> files;
    files.push_back(".git-bin");
    files.push_back(".git/keshig");
    files.push_back(".git/bin-cache");
    for (auto it = files.begin(); it != files.end(); it++) 
    {
        File f((*it));
        if (f.exists()) f.remove(true);
    }
    Process::Args args;
    args.push_back("bin");
    args.push_back("--init");
    args.push_back("s3://somepath");
    ProcessHandle pr = Process::launch("git", args, 0, 0, 0);
    CPPUNIT_ASSERT(pr.wait() == 0);
}

CPPUNIT_TEST_SUITE_REGISTRATION(GitBinTest);
int main(int argc, char* argv[])
{
    File gitdir(".git");
    bool gitDirCreated = false;
    if (!gitdir.exists()) 
    {
        gitDirCreated = true;
        gitdir.createDirectory();
    }
    // CppUnit
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
    if (gitDirCreated) 
    {
//        gitdir.remove(true);
    }
    File index(".git-bin");
//    index.remove();
    // Clear after tests
    return collectedResults.wasSuccessful() ? 0 : 1;
}
