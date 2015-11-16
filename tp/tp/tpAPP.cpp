#include "stdafx.h"
#include "tpAPP.h"
#include <regex>
#include "dllmain.h"

#define SIZEOF_ARRAY(x) ((sizeof(x))/(sizeof(x[0])))

wstring Win32ErrorMsg(HRESULT hr)
{
    _com_error err(hr);
    return err.ErrorMessage();
}


/////////////////////////////////////////////////////////////////////////////////////////
// IInternetProtocolEx
/////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CtpAPP::StartEx(IUri *pUri, IInternetProtocolSink *pOIProtSink, IInternetBindInfo *pOIBindInfo, DWORD grfPI, HANDLE_PTR dwReserved)
{

    AUTOOFF

    m_spSink = pOIProtSink;
    m_spBI = pOIBindInfo;

    m_bi.cbSize = sizeof(BINDINFO);
    m_spBI->GetBindInfo(&m_grf, &m_bi);

    CComBSTR bsUri; pUri->GetAbsoluteUri(&bsUri);
    CComBSTR bsPath; pUri->GetPath(&bsPath);
    CComBSTR bsQuery; pUri->GetQuery(&bsQuery);

    LOG(L"Abs: %s", bsUri.m_str);
    LOG(L"P&Q: %s%s", bsPath.m_str, bsQuery.m_str);
    LOG(L"grf: %s", BINDFToString(m_grf).c_str());
    LOG(L"BOP: %s", BINDINFOOPTIONS2String(m_bi.dwOptions).c_str());
    LOG(L"PIf: %s", PIFLAGS2String(grfPI).c_str());

    if (m_bi.szExtraInfo)
        LOG(L"ext: %s", m_bi.szExtraInfo);

    size_t sz = readFile(bsPath.m_str);
    if (!sz)
    {
        m_spSink->ReportResult(INET_E_RESOURCE_NOT_FOUND, 404, nullptr);
        return E_FAIL;
    }

    struct { wchar_t *rex, *mime; }
    mimes[] =
    {
        { L"\\.html",  L"text/html" },
        { L"\\.js",  L"text/javascript" },
        { L"\\.css",  L"text/css" }
    };

    for (int i=0; i < SIZEOF_ARRAY(mimes); ++i)
        if (testRex(mimes[i].rex, bsPath.m_str))
        {
            LOG(L"Mime: %s", mimes[i].mime);
            m_spSink->ReportProgress(BINDSTATUS_VERIFIEDMIMETYPEAVAILABLE, mimes[i].mime);
            break;
        }
    
    m_spSink->ReportData(BSCF_FIRSTDATANOTIFICATION, 0, sz);

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////
// IInternetProtocolRoot
/////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CtpAPP::Start(LPCWSTR szUrl, IInternetProtocolSink *pOIProtSink, IInternetBindInfo *pOIBindInfo, DWORD grfPI, HANDLE_PTR dwReserved)
{
    AUTOOFF

    ATLASSERT(m_spSink == nullptr);
    m_spSink = pOIProtSink;
    m_spBI = pOIBindInfo;
    m_spBI->GetBindInfo(&m_grf, &m_bi);

    LOG(L"Abs: %s", szUrl);
    LOG(L"grf: %s", BINDFToString(m_grf).c_str());
    LOG(L"BOP: %s", BINDINFOOPTIONS2String(m_bi.dwOptions).c_str());
    LOG(L"PIf: %s", PIFLAGS2String(grfPI).c_str());

    return S_OK;
}

STDMETHODIMP CtpAPP::Continue(PROTOCOLDATA *pProtocolData)
{
    AUTOOFF
    return S_OK;
}

STDMETHODIMP CtpAPP::Abort(HRESULT hrReason, DWORD dwOptions)
{
    AUTOOFF
    return m_spSink->ReportResult(E_ABORT, 0, nullptr);
}

STDMETHODIMP CtpAPP::Terminate(DWORD dwOptions)
{
    AUTOOFF
    m_spSink.Release();
    m_spBI.Release();
    ReleaseBindInfo(&m_bi);
    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////
// IInternetProtocol
/////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CtpAPP::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
    AUTOOFF

    size_t len = m_data.size();
    if (!len || (len && m_szPos >= len))
        return S_FALSE;

    size_t bytes = min<size_t>(min<size_t>(cb, len), len - m_szPos);
    memcpy(pv, m_data.data() + m_szPos, bytes);

//     LOG(L"cb: %d, *pcbRead: %d", cb, bytes);

    *pcbRead = bytes;
    m_szPos += bytes;

    if (m_szPos >= len)
    {
        m_spSink->ReportData(BSCF_DATAFULLYAVAILABLE, len, len);
        m_spSink->ReportResult(S_OK, 0, nullptr);
        return S_FALSE;
    }

    m_spSink->ReportData(BSCF_INTERMEDIATEDATANOTIFICATION, m_szPos, len);
    return S_OK;
}

STDMETHODIMP CtpAPP::LockRequest(DWORD dwOptions)
{
    AUTOOFF

//     LOG(L"");
    return S_OK;
}

STDMETHODIMP CtpAPP::UnlockRequest()
{
    AUTOOFF
    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////
// IInternetProtocolInfo
/////////////////////////////////////////////////////////////////////////////////////////
HRESULT CtpAPP::ParseUrl(LPCWSTR pwzUrl, PARSEACTION ParseAction, DWORD dwParseFlags, LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved)
{
    AUTOOFF

    LOG(L"%s", pwzUrl);
    LOG(L"sz: %d, %s", cchResult, eParseAction_Text[ParseAction]);
        
    wstring wsSecUrl(L"tp://localhost"), wsDomain(L"tp:localhost"), wsSchema(L"tp");
    int len;

    switch (ParseAction)
    {
        case PARSE_SECURITY_URL:
            len = wsSecUrl.length();
            if (cchResult < len) { return S_FALSE; }
            StringCchCopy(pwzResult, len+1, wsSecUrl.c_str());
            *pcchResult = len;
            LOG(L"[-] '%s'", pwzResult);
            return S_OK;

        case PARSE_SECURITY_DOMAIN:
            if (cchResult < wsDomain.length()) { return S_FALSE; }
            StringCchCopy(pwzResult, wsDomain.length()+1, wsDomain.c_str());
            *pcchResult = wsDomain.length();
            LOG(L"[-] '%s'", pwzResult);
            return S_OK;

        case PARSE_CANONICALIZE:
            len = lstrlen(pwzUrl);
            if (cchResult < len) { return S_FALSE; }
            StringCchCopy(pwzResult, len+1, pwzUrl);
            *pcchResult = len;
            LOG(L"[-] '%s'", pwzResult);
            return S_OK;

        case PARSE_SCHEMA:
            if (cchResult < wsSchema.length()) { return S_FALSE; }
            StringCchCopy(pwzResult, wsSchema.length()+1, wsSchema.c_str());
            *pcchResult = wsSchema.length();
            LOG(L"[-] '%s'", pwzResult);
            return S_OK;
    }

    return INET_E_DEFAULT_ACTION;
}



HRESULT CtpAPP::QueryInfo(LPCWSTR pwzUrl, QUERYOPTION QueryOption, DWORD dwQueryFlags, LPVOID pBuffer, DWORD cbBuffer, DWORD *pcbBuf, DWORD dwReserved)
{
    AUTOOFF

    LOG(L"%s", pwzUrl);
    LOG(L"sz: %d, %s", cbBuffer, eQueryOption_Text[QueryOption]);

    *pcbBuf = sizeof(BOOL);
    if (cbBuffer < sizeof(BOOL))
        return S_FALSE;

    switch (QueryOption)
    {
        case QUERY_USES_NETWORK:
        case QUERY_CAN_NAVIGATE:
        case QUERY_IS_SAFE:
        {
            *(reinterpret_cast<DWORD*>(pBuffer)) = TRUE;
            return S_OK;
        }

        case QUERY_IS_SECURE:
        case QUERY_USES_CACHE:
        {
            *(reinterpret_cast<DWORD*>(pBuffer)) = FALSE;
            return S_OK;
        }

    }

    return INET_E_DEFAULT_ACTION;
}

HRESULT CtpAPP::CompareUrl(LPCWSTR pwzUrl1, LPCWSTR pwzUrl2, DWORD dwCompareFlags)
{
    AUTOOFF
    return E_NOTIMPL;
}

HRESULT CtpAPP::CombineUrl(LPCWSTR pwzBaseUrl, LPCWSTR pwzRelativeUrl, DWORD dwCombineFlags, LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved)
{
    AUTOOFF

    LOG(L"Base: '%s'", pwzBaseUrl);
    LOG(L"Relt: '%s'", pwzRelativeUrl);
    LOG(L"sz: %d", cchResult);

    wchar_t buf[2048] = {0};
    DWORD ret = 2048;

    UrlCombine(pwzBaseUrl, pwzRelativeUrl, buf, &ret, 0);
    StringCchCopy(pwzResult, ret+1, buf);
    *pcchResult = ret+1;

    LOG(L"Result: %s", pwzResult);
    return S_OK;
}

size_t CtpAPP::readFile(const wstring& wsPath)
{
    AUTOOFF

    wstringstream wss;
    wss << L"C:\\src\\app\\test\\" << wsPath;

    FILE *pf = nullptr;
    if (_wfopen_s(&pf, wss.str().c_str(), L"rb") != 0)
        return 0;

    fseek(pf, 0, SEEK_END);
    size_t szSize = ftell(pf);
    m_data.clear();
    m_data.resize(szSize);
    fseek(pf, 0, SEEK_SET);
    fread(const_cast<BYTE*>(m_data.data()), szSize, 1, pf);    
    fclose(pf);

    return szSize;
}

bool CtpAPP::testRex(const wstring& wsRex, const wstring& wsPath)
{
    AUTOOFF

    tr1::wregex rex(wsRex.c_str());
    return regex_search(wsPath.begin(), wsPath.end(), rex);
}

/////////////////////////////////////////////////////////////////////////////////////////
// IInternetProtocolInfo
/////////////////////////////////////////////////////////////////////////////////////////
HRESULT CtpAPP::QueryService(REFGUID guidService, REFIID riid, void **ppvObject)
{
    AUTOOFF;

    HRESULT hr = S_OK;
    CComPtr<IServiceProvider> sp;

    *ppvObject = NULL;

    hr = m_spSink->QueryInterface(IID_IServiceProvider, (void**) &sp);
    if (SUCCEEDED(hr))
        hr = sp->QueryService(guidService, riid, ppvObject);

    return hr;
}
