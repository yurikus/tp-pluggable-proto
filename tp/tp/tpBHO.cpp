// tpBHO.cpp : Implementation of CtpBHO

#include "stdafx.h"
#include "tpBHO.h"
#include "dllmain.h"

// CtpBHO

HRESULT CtpBHO::FinalConstruct()
{
    AUTOOFF
    return S_OK;
}

void CtpBHO:: FinalRelease()
{
    AUTOOFF
}

STDMETHODIMP CtpBHO::SetSite(IUnknown* pUnkSite)
{
    AUTOOFF

    HRESULT hr = IObjectWithSiteImpl<CtpBHO>::SetSite(pUnkSite);

    CComPtr<IInternetSession> spIS;
    hr = CoInternetGetSession(0, &spIS, 0);
    if (FAILED(hr)) return hr;

    CComPtr<IClassFactory> spCF;
    hr = _AtlModule.DllGetClassObject(__uuidof(tpAPP), IID_IClassFactory, (void**) &spCF);
    if (FAILED(hr))
    {
        ATLASSERT(false);
        return hr;
    }

    wchar_t* proto = L"tp";

    if (pUnkSite)
    {
        hr = spIS->RegisterNameSpace(spCF, __uuidof(tpAPP), proto, 0, nullptr, 0);
        if (FAILED(hr))
        {
            ATLASSERT(false);
            return hr;
        }
        return hr;
    }
    else
    {
        ATLASSERT(spCF.p);
        spIS->UnregisterNameSpace(spCF, proto);
        return S_OK;
    }
}
