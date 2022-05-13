#include "XmlUtils.h"



MSXML2::IXMLDOMDocumentPtr msxml_util::loadDOMsmart(const wchar_t* path)
{
    MSXML2::IXMLDOMDocumentPtr pXMLDom;
    HRESULT hr = pXMLDom.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
    if (FAILED(hr))
    {
        fmt::print("Failed to instantiate an XML DOM. Err {}\n", hr);
        return {};
    }

    try
    {
        pXMLDom->async = VARIANT_FALSE;
        pXMLDom->validateOnParse = VARIANT_TRUE;
        pXMLDom->resolveExternals = VARIANT_FALSE;

        if (pXMLDom->load(path) == VARIANT_TRUE)
        {
            return pXMLDom;
        }
        else
        {
            // Failed to load xml
            const auto error = pXMLDom->parseError;
            if (error) {
                const auto reason = pXMLDom->parseError->Getreason();
                fmt::print(L"Failed to load DOM from {}. {}\n", path,
                    std::wstring_view((const wchar_t*)reason, reason.length()));
            }
            else
            {
                fmt::print(L"Failed to load DOM from {}.\n", path);
            }
            return {};
        }
    }
    catch (const _com_error& errorObject)
    {
        fmt::print("Exception thrown, HRESULT: {}", errorObject.Error());
        return {};
    }
}