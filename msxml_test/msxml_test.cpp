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
		return fmt::format("CoInitialize failed {}", hr);
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

	hr = msxml_util::saveXmlToFile(xml, L"stocks2.xml");
	if (FAILED(hr)) {
		return -3;
	}
	fmt::print(L"XML DOM saved to stocks2.xml\n");
	return 0;
}
