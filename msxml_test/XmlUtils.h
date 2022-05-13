#pragma once

#pragma warning(disable:4192 4471)
#import <msxml6.dll>
#pragma warning(default:4192 4471)

#pragma warning(disable:4189)
#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include <fmt/xchar.h>
#pragma warning(pop)
#include <string_view>

namespace msxml_util {
	MSXML2::IXMLDOMDocumentPtr createDomObject();
	HRESULT loadXmlFromFile(MSXML2::IXMLDOMDocumentPtr pXMLDom, const wchar_t* path);
	HRESULT loadXmlFromString(MSXML2::IXMLDOMDocumentPtr pXMLDom, const wchar_t* xml);
	HRESULT saveXmlToFile(MSXML2::IXMLDOMDocumentPtr pXMLDom, const wchar_t* path);

}