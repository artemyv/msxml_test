// msxml_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning(disable:4189)
#include <fmt/core.h>
#pragma warning(default:4189)

#pragma warning(disable:4471)
#import <msxml6.dll>
#include <msxml6.tlh> //already done by previous import - but for easier browsing
#pragma warning(default:4471)

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
	//TBD

	return 0;
}
