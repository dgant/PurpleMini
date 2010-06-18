#include "TestModule.h"
using namespace std;
using namespace BWAPI;
TestModule::TestModule() : currentTestCase(NULL)
{
}

TestModule::~TestModule()
{
  for(std::list<TestCase*>::iterator i=testCases.begin();i!=testCases.end();i++)
  {
    delete *i;
  }
  testCases.clear();
}

void TestModule::onFrame()
{
  if (Broodwar->isPaused()) return;
  if (Broodwar->getFrameCount()==0) return;
  Broodwar->drawTextScreen(0,0,"Assert success count: %d",assert_success_count);
  Broodwar->drawTextScreen(0,20,"Assert failed count: %d",assert_fail_count);
  runTestCases();
}

void TestModule::runTestCases()
{
  if (currentTestCase==NULL && testCases.empty()==false)
  {
    currentTestCase = *testCases.begin();
    currentTestCase->start();
  }
  if (currentTestCase!=NULL)
  {
    if (currentTestCase->isRunning())
      currentTestCase->update();
    else
    {
      currentTestCase->stop();
      delete currentTestCase;
      currentTestCase = NULL;
      testCases.erase(testCases.begin());
    }
  }
}

void TestModule::addTestCase(TestCase* testCase)
{
  testCases.push_back(testCase);
}

TestCase* TestModule::getCurrentTestCase() const
{
  return currentTestCase;
}