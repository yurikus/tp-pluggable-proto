// tpAPP.h : Declaration of the CtpAPP

#pragma once
#include "resource.h"       // main symbols
#include "tp_i.h"
#include "InterceptHelpers.h"

class ATL_NO_VTABLE CtpAPP
    : public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CtpAPP, &CLSID_tpAPP>
    , public IInternetProtocolEx
    , public IInternetProtocolInfo
    , public IServiceProvider
    , public ItpAPP
{
public:

    DECLARE_NOT_AGGREGATABLE(CtpAPP)

    BEGIN_COM_MAP(CtpAPP)
        COM_INTERFACE_ENTRY(IInternetProtocolRoot)
        COM_INTERFACE_ENTRY(IInternetProtocolEx)
        COM_INTERFACE_ENTRY(IInternetProtocol)
        COM_INTERFACE_ENTRY(IInternetProtocolInfo)
        COM_INTERFACE_ENTRY(IServiceProvider)
	    COM_INTERFACE_ENTRY(ItpAPP)
    END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

    CtpAPP()
    {
        m_szPos = 0;

    }

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

    // Dummy, since we don't want to register protocol in the registry
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) { return S_OK; }

public:
    // IInternetProtocolEx
    STDMETHOD(StartEx)(IUri *pUri, IInternetProtocolSink *pOIProtSink, IInternetBindInfo *pOIBindInfo,
        DWORD grfPI, HANDLE_PTR dwReserved);

    // IInternetProtocolRoot
    STDMETHOD(Start)(LPCWSTR szUrl, IInternetProtocolSink *pOIProtSink, IInternetBindInfo *pOIBindInfo,
        DWORD grfPI, HANDLE_PTR dwReserved);
    STDMETHOD(Continue)(PROTOCOLDATA *pProtocolData);
    STDMETHOD(Abort)(HRESULT hrReason, DWORD dwOptions);
    STDMETHOD(Terminate)(DWORD dwOptions);
    STDMETHOD(Suspend)() { return E_NOTIMPL; }
    STDMETHOD(Resume)() { return E_NOTIMPL; }

    // IInternetProtocol
    STDMETHOD(Read)(void *pv, ULONG cb, ULONG *pcbRead);
    STDMETHOD(Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition) { return E_NOTIMPL; }
    STDMETHOD(LockRequest)(DWORD dwOptions);
    STDMETHOD(UnlockRequest)();

    // IInternetProtocolInfo
    STDMETHOD(ParseUrl)(LPCWSTR pwzUrl, PARSEACTION ParseAction, DWORD dwParseFlags, LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved);
    STDMETHOD(QueryInfo)(LPCWSTR pwzUrl, QUERYOPTION OueryOption, DWORD dwQueryFlags, LPVOID pBuffer, DWORD cbBuffer, DWORD *pcbBuf, DWORD dwReserved);
    STDMETHOD(CompareUrl)(LPCWSTR pwzUrl1, LPCWSTR pwzUrl2, DWORD dwCompareFlags);
    STDMETHOD(CombineUrl)(LPCWSTR pwzBaseUrl, LPCWSTR pwzRelativeUrl, DWORD dwCombineFlags, LPWSTR pwzResult, DWORD cchResult, DWORD *pcchResult, DWORD dwReserved);

    // IServiceProvider
    STDMETHOD(QueryService)(REFGUID guidService, REFIID riid, void **ppvObject);

public:
    CComPtr<IInternetProtocolSink> m_spSink;
    CComPtr<IInternetBindInfo> m_spBI;
    BINDINFO m_bi;
    DWORD m_grf;

public:
    size_t m_szPos;
    vector<BYTE> m_data;
    size_t readFile(const wstring& wsPfx);
    bool testRex(const wstring& wsRex, const wstring& wsPath);
};

OBJECT_ENTRY_AUTO(__uuidof(tpAPP), CtpAPP)
