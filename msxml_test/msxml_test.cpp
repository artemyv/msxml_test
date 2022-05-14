// msxml_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "XmlUtils.h"

static int DoTheWork();

class CoInitializeWraper
{
	HRESULT hr;
public:
	CoInitializeWraper()
	{
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			
		}
	}
	~CoInitializeWraper()
	{
		if (SUCCEEDED(hr)) {
			CoUninitialize();
		}
	}
	operator bool() const
	{
		return SUCCEEDED(hr);
	}

	std::string what() {
		return fmt::format("CoInitialize failed {:#x}", hr);
	}
};

int main() {
	CoInitializeWraper co;
	if (!co) {
		fmt::print("{}\n", co.what());
		return -1;
	}
	fmt::print("Initialized\n");

	DoTheWork();

	fmt::print("Finished\n");

	return 0;
}

int DoTheWork()
{
	auto xml = msxml_util::createDomObject();
	if (!xml) {
		return -1;
	}

	auto hr = msxml_util::loadXmlFromFile(xml, L"stocks.xml");
	if (FAILED(hr)) {
		return -2;
	}

	fmt::print(L"XML DOM loaded from stocks.xml:\n{}\n", std::wstring_view((const wchar_t*)xml->xml, xml->xml.length()));

	auto xsl = msxml_util::createDomObject();
	if (!xml) {
		return -1;
	}

	hr = msxml_util::loadXmlFromFile(xsl, L"stocks.xsl");
	if (FAILED(hr)) {
		return -2;
	}

	fmt::print(L"XML DOM loaded from stocks.xsl:\n{}\n", std::wstring_view((const wchar_t*)xsl->xml, xsl->xml.length()));

	const auto res = msxml_util::transformXmlToString(xml, xsl);
	if (res.length() == 0) {
		return -3;
	}
	fmt::print(L"Transformation result:\n{}\n", std::wstring_view((const wchar_t*)res, res.length()));

	auto res_dom = msxml_util::transformXmlToObject(xml, xsl);
	if (!res_dom) {
		return -4;
	}
	fmt::print(L"XML DOM transformed to object:\n{}\n", std::wstring_view((const wchar_t*)res_dom->xml, res_dom->xml.length()));

	hr = msxml_util::saveXmlToFile(res_dom, L"stocks.html");
	if (FAILED(hr)) {
		return -3;
	}
	fmt::print(L"transformation result saved to stocks.html\n");
	return 0;
}
