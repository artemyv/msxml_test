#include "XmlUtils.h"

static void showError(const std::wstring description, MSXML2::IXMLDOMDocumentPtr pXMLDom)
{
    if (!description.empty()) {
        fmt::print(L"{}. ", description);
    }
    // Failed to load xml
    const auto error = pXMLDom->parseError;
    if (error) {
        /*
            long GeterrorCode ( );
            _bstr_t Getreason ( );
            _bstr_t GetsrcText ( );
            long Getline ( );
            long Getlinepos ( );
            long Getfilepos ( );
        */
        if (error->Getline() > 0) {
            fmt::print(L"line {}: pos {}: ", error->Getline(), error->Getlinepos());
        }
        if (error->GeterrorCode() != 0) {
            fmt::print(L"error {:#x} ", error->GeterrorCode());
        }
        const auto reason = error->Getreason();
        if (reason.length() > 0) {
            fmt::print(L"{} ", std::wstring_view((const wchar_t*)reason, reason.length()));
        }
    }
    fmt::print("\n");
}

MSXML2::IXMLDOMDocumentPtr msxml_util::createDomObject()
{
    MSXML2::IXMLDOMDocumentPtr pXMLDom;
    HRESULT hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
    if (FAILED(hr))
    {
        fmt::print("Failed to instantiate an XML DOM. Err {:#x}\n", hr);
        return {};
    }
    return pXMLDom;
}

HRESULT msxml_util::loadXmlFromFile(MSXML2::IXMLDOMDocumentPtr pXMLDom, const wchar_t* path)
{
    try
    {
        pXMLDom->async = VARIANT_FALSE;
        pXMLDom->validateOnParse = VARIANT_TRUE;
        pXMLDom->resolveExternals = VARIANT_FALSE;

        if (pXMLDom->load(path) == VARIANT_TRUE)
        {
            return S_OK;
        }
        else
        {
            showError(fmt::format(L"Failed to load DOM from {}", path), pXMLDom);
            return E_FAIL;
        }
    }
    catch (const _com_error& errorObject)
    {
        fmt::print(L"Failed to load DOM from {} Exception: {:#x} {}\n", path,  errorObject.Error(), errorObject.ErrorMessage());
        return errorObject.Error();
    }
}

HRESULT msxml_util::loadXmlFromString(MSXML2::IXMLDOMDocumentPtr pXMLDom, const wchar_t* xml)
{

    try
    {
        pXMLDom->async = VARIANT_FALSE;
        pXMLDom->validateOnParse = VARIANT_FALSE;
        pXMLDom->resolveExternals = VARIANT_FALSE;

        if (pXMLDom->loadXML(xml) != VARIANT_TRUE)
        {
            showError(fmt::format(L"Failed to load DOM from {}", xml), pXMLDom);
            return E_FAIL;
        }
        return S_OK;
    }
    catch (const _com_error& errorObject)
    {
        fmt::print(L"Failed to load DOM from {}. Exception: {:#x} {}\n", xml,  errorObject.Error(), errorObject.ErrorMessage());
        return errorObject.Error();
    }
}

HRESULT msxml_util::saveXmlToFile(MSXML2::IXMLDOMDocumentPtr pXMLDom,  const wchar_t* path)
{

    try
    {
        const auto hr = pXMLDom->save(path);
        if(SUCCEEDED(hr)){
            fmt::print(L"XML saved to {}.\n", path);
            return S_OK;
        }
        else
        {
            fmt::print(L"XML saving failed. Reason={:#x}.\n", hr);
            return hr;
        }
    }
    catch (const _com_error& errorObject)
    {
        fmt::print(L"XML saving failed. Exception: {:#x} {}\n", errorObject.Error(), errorObject.ErrorMessage());
        return errorObject.Error();
    }
}

_bstr_t msxml_util::transformXmlToString(MSXML2::IXMLDOMDocumentPtr pXMLDom, MSXML2::IXMLDOMDocumentPtr pXSLDoc)
{
    try
    {
        // Transform the XSLT to an XML string.
        const auto result = pXMLDom->transformNode(pXSLDoc);
        return result;
    }
    catch (const _com_error& errorObject)
    {
        fmt::print(L"transformNode failed. Exception: {:#x} {}\n", errorObject.Error(), errorObject.ErrorMessage());
        return {};
    }
}

MSXML2::IXMLDOMDocumentPtr msxml_util::transformXmlToObject(MSXML2::IXMLDOMDocumentPtr pXMLDom, MSXML2::IXMLDOMDocumentPtr pXSLDoc)
{
    auto pXMLOut = msxml_util::createDomObject();

    if (!pXMLOut)
        return {};
    try {
        // Transform the XSLT to a DOM object.
        const auto hr = pXMLDom->transformNodeToObject(pXSLDoc, pXMLOut.GetInterfacePtr());
        if (FAILED(hr)) {
            fmt::print(L"transformNodeToObject failed, HRESULT: {:#x}\n", hr);
            return {};

        }
        return pXMLOut;
    }
    catch (const _com_error& errorObject)
    {
        fmt::print(L"transformNodeToObject failed. Exception: {:#x} {}\n", errorObject.Error(), errorObject.ErrorMessage());
        return {};
    }
}
