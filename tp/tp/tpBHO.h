// tpBHO.h : Declaration of the CtpBHO

#pragma once
#include "resource.h"       // main symbols
#include "tp_i.h"

class ATL_NO_VTABLE CtpBHO :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CtpBHO, &CLSID_tpBHO>,
	public IObjectWithSiteImpl<CtpBHO>,
	public IDispatchImpl<ItpBHO, &IID_ItpBHO, &LIBID_tpLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CtpBHO()
	{
	}

    DECLARE_REGISTRY_RESOURCEID(IDR_TPBHO)
    DECLARE_NOT_AGGREGATABLE(CtpBHO)

    BEGIN_COM_MAP(CtpBHO)
	    COM_INTERFACE_ENTRY(ItpBHO)
	    COM_INTERFACE_ENTRY(IDispatch)
	    COM_INTERFACE_ENTRY(IObjectWithSite)
    END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

public:
    STDMETHOD(SetSite)(IUnknown* pUnkSite);
};

OBJECT_ENTRY_AUTO(__uuidof(tpBHO), CtpBHO)
