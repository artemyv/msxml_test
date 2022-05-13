#include "pch.h"
#include "../msxml_test/XmlUtils.cpp"

namespace msxml_test
{
    // The fixture for testing class Foo.
    class XmlTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if their bodies would
        // be empty.

        XmlTest() {
            // You can do set-up work for each test here.
        }

        ~XmlTest() override {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        void SetUp() override {
            // Code here will be called immediately after the constructor (right
            // before each test).
            CoInitialize(NULL);
        }

        void TearDown() override {
            // Code here will be called immediately after each test (right
            // before the destructor).
            CoUninitialize();
        }

        // Class members declared here can be used by all tests in the test suite
        // for Foo.
    };
TEST_F(XmlTest, loadDOMsmart_FileNotFound) {
	const auto res = msxml_util::loadDOMsmart(L"dummy.xml");
	bool bSuccess = res;
  EXPECT_FALSE(bSuccess);
}
}