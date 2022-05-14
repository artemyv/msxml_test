#include "pch.h"
#include "../msxml_test/XmlUtils.cpp"

namespace msxml_test
{
    // The fixture for testing class Foo.
    class XmlTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if their bodies would
        // be empty.

         // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        void SetUp() override {
            // Code here will be called immediately after the constructor (right
            // before each test).
            hr = CoInitialize(NULL);
        }

        void TearDown() override {
            // Code here will be called immediately after each test (right
            // before the destructor).
            if (SUCCEEDED(hr)) {
                CoUninitialize();
                hr = E_NOT_SET;
            }
        }
        HRESULT hr = E_NOT_SET;
        // Class members declared here can be used by all tests in the test suite
        // for Foo.
    };
TEST_F(XmlTest, loadXmlFile_FileNotFound) {
    auto dom = msxml_util::createDomObject();
    bool bSuccess = dom;
    EXPECT_TRUE(bSuccess);

	const auto res = msxml_util::loadXmlFromFile(dom, L"dummy.xml");
    EXPECT_TRUE(FAILED(res));
}
TEST_F(XmlTest, loadXmlFile_Stocks) {
    auto dom = msxml_util::createDomObject();
    bool bSuccess = dom;
    EXPECT_TRUE(bSuccess);

    const auto res = msxml_util::loadXmlFromFile(dom, L"stocks.xml");
    EXPECT_TRUE(SUCCEEDED(res));
}
TEST_F(XmlTest, loadXmlString) {
    auto dom = msxml_util::createDomObject();
    bool bSuccess = dom;
    EXPECT_TRUE(bSuccess);

    const auto res = msxml_util::loadXmlFromString(dom, L"<stocks><stock attr=\"val1\">val2</stock></stocks>");
    EXPECT_TRUE(SUCCEEDED(res));
}
TEST_F(XmlTest, loadXmlString_bad) {
    auto dom = msxml_util::createDomObject();
    bool bSuccess = dom;
    EXPECT_TRUE(bSuccess);

    const auto res = msxml_util::loadXmlFromString(dom, L"<stocks><stock attr=\"val1\">val2</stock2></stocks>");
    EXPECT_TRUE(FAILED(res));
}
TEST_F(XmlTest, saveFile) {
    auto dom = msxml_util::createDomObject();
    bool bSuccess = dom;
    EXPECT_TRUE(bSuccess);

    auto res = msxml_util::loadXmlFromString(dom, L"<stocks><stock attr=\"val1\">val2</stock></stocks>");
    EXPECT_TRUE(SUCCEEDED(res));

    res = msxml_util::saveXmlToFile(dom, L"ut_file1.xml");
    EXPECT_TRUE(SUCCEEDED(res));

    //Todo - check file exists and contains valid xml
}

TEST_F(XmlTest, tansform_positive) {
    auto dom = msxml_util::createDomObject();
    bool bSuccess = dom;
    EXPECT_TRUE(bSuccess);

    const auto res = msxml_util::loadXmlFromFile(dom, L"stocks.xml");
    EXPECT_TRUE(SUCCEEDED(res));

    auto dom2 = msxml_util::createDomObject();
    bool bSuccess2 = dom2;
    EXPECT_TRUE(bSuccess2);

    const auto res2 = msxml_util::loadXmlFromFile(dom2, L"stocks.xsl");
    EXPECT_TRUE(SUCCEEDED(res2));

    const auto ret = msxml_util::transformXmlToString(dom, dom2);
    EXPECT_TRUE(ret.length() > 0);

}
TEST_F(XmlTest, tansformobj_positive) {
    auto dom = msxml_util::createDomObject();
    bool bSuccess = dom;
    EXPECT_TRUE(bSuccess);

    const auto res = msxml_util::loadXmlFromFile(dom, L"stocks.xml");
    EXPECT_TRUE(SUCCEEDED(res));

    auto dom2 = msxml_util::createDomObject();
    bool bSuccess2 = dom2;
    EXPECT_TRUE(bSuccess2);

    const auto res2 = msxml_util::loadXmlFromFile(dom2, L"stocks.xsl");
    EXPECT_TRUE(SUCCEEDED(res2));

    const auto ret = msxml_util::transformXmlToObject(dom, dom2);
    bool bret = ret;
    EXPECT_TRUE(bret);
    EXPECT_TRUE(ret->xml.length() > 0);

}

TEST_F(XmlTest, tansformobj_negative) {
    auto dom = msxml_util::createDomObject();
    bool bSuccess = dom;
    EXPECT_TRUE(bSuccess);

    const auto res = msxml_util::loadXmlFromFile(dom, L"stocks.xml");
    EXPECT_TRUE(SUCCEEDED(res));

    auto dom2 = msxml_util::createDomObject();
    bool bSuccess2 = dom2;
    EXPECT_TRUE(bSuccess2);

    const auto res2 = msxml_util::loadXmlFromFile(dom2, L"stocks2.xsl");
    EXPECT_TRUE(SUCCEEDED(res2));

    const auto ret = msxml_util::transformXmlToObject(dom, dom2);
    bool bret = ret;
    EXPECT_FALSE(bret);
}
}