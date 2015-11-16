#pragma once

class CtpModule
    : public ATL::CAtlDllModuleT< CtpModule >
{
public :
	DECLARE_LIBID(LIBID_tpLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(101, "{2706197D-520A-468F-A896-894B07FD4946}")

public:
    CtpModule()
        : off(0)
    { }

    int off;
    wstring offset()
    {
        if (off < 0)
            return L"";

        wstring str;
        str.resize(off, L' ');
        return str;
    }
};

extern class CtpModule _AtlModule;


class AutoOffset
{
public:
    AutoOffset() { LOGNF(L"[+]"); _AtlModule.off += 2; }
    ~AutoOffset() { _AtlModule.off -= 2; LOGNF(L"[-]"); }
};

#define AUTOOFF AutoOffset _offset_; LOG(L"");
#define OFF _AtlModule.offset().c_str()

