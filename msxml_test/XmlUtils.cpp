#include "XmlUtils.h"

static void showError(const std::wstring description, MSXML2::IXMLDOMDocumentPtr pXMLDom)
{
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
        const auto reason = error->Getreason();
        fmt::print(L"{}. {} at {}:{}\n", description,
            std::wstring_view((const wchar_t*)reason, reason.length()), error->Getline(), error->Getlinepos());
    }
    else
    {
        fmt::print(L"{}.\n", description);
    }
}

MSXML2::IXMLDOMDocumentPtr msxml_util::createDomObject()
{
    MSXML2::IXMLDOMDocumentPtr pXMLDom;
    HRESULT hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
    if (FAILED(hr))
    {
        fmt::print("Failed to instantiate an XML DOM. Err {}\n", hr);
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
        fmt::print(L"Exception thrown, HRESULT: {} {}", errorObject.Error(), errorObject.ErrorMessage());
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
        fmt::print(L"Exception thrown, HRESULT: {} {}", errorObject.Error(), errorObject.ErrorMessage());
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
            fmt::print(L"XML saving failed. Reason={}.\n", hr);
            return hr;
        }
    }
    catch (const _com_error& errorObject)
    {
        fmt::print(L"Exception thrown, HRESULT: {} {}", errorObject.Error(), errorObject.ErrorMessage());
        return errorObject.Error();
    }
}
