#include "StdAfx.h"
#include "InterceptHelpers.h"

wchar_t* eBindStatus_Text[] =
{
    L"BINDSTATUS Entry Zero (invalid)",
    L"BINDSTATUS_FINDINGRESOURCE",
    L"BINDSTATUS_CONNECTING",
    L"BINDSTATUS_REDIRECTING",
    L"BINDSTATUS_BEGINDOWNLOADDATA",
    L"BINDSTATUS_DOWNLOADINGDATA",
    L"BINDSTATUS_ENDDOWNLOADDATA",
    L"BINDSTATUS_BEGINDOWNLOADCOMPONENTS",
    L"BINDSTATUS_INSTALLINGCOMPONENTS",
    L"BINDSTATUS_ENDDOWNLOADCOMPONENTS",
    L"BINDSTATUS_USINGCACHEDCOPY",
    L"BINDSTATUS_SENDINGREQUEST",
    L"BINDSTATUS_CLASSIDAVAILABLE",
    L"BINDSTATUS_MIMETYPEAVAILABLE",
    L"BINDSTATUS_CACHEFILENAMEAVAILABLE",
    L"BINDSTATUS_BEGINSYNCOPERATION",
    L"BINDSTATUS_ENDSYNCOPERATION",
    L"BINDSTATUS_BEGINUPLOADDATA",
    L"BINDSTATUS_UPLOADINGDATA",
    L"BINDSTATUS_ENDUPLOADDATA",
    L"BINDSTATUS_PROTOCOLCLASSID",
    L"BINDSTATUS_ENCODING",
    L"BINDSTATUS_VERIFIEDMIMETYPEAVAILABLE",
    L"BINDSTATUS_CLASSINSTALLLOCATION",
    L"BINDSTATUS_DECODING",
    L"BINDSTATUS_LOADINGMIMEHANDLER",
    L"BINDSTATUS_CONTENTDISPOSITIONATTACH",
    L"BINDSTATUS_FILTERREPORTMIMETYPE",
    L"BINDSTATUS_CLSIDCANINSTANTIATE",
    L"BINDSTATUS_IUNKNOWNAVAILABLE",
    L"BINDSTATUS_DIRECTBIND",
    L"BINDSTATUS_RAWMIMETYPE",
    L"BINDSTATUS_PROXYDETECTING",
    L"BINDSTATUS_ACCEPTRANGES",
    L"BINDSTATUS_COOKIE_SENT",
    L"BINDSTATUS_COMPACT_POLICY_RECEIVED",
    L"BINDSTATUS_COOKIE_SUPPRESSED",
    L"BINDSTATUS_COOKIE_STATE_UNKNOWN",
    L"BINDSTATUS_COOKIE_STATE_ACCEPT",
    L"BINDSTATUS_COOKIE_STATE_REJECT",
    L"BINDSTATUS_COOKIE_STATE_PROMPT",
    L"BINDSTATUS_COOKIE_STATE_LEASH",
    L"BINDSTATUS_COOKIE_STATE_DOWNGRADE",
    L"BINDSTATUS_POLICY_HREF",
    L"BINDSTATUS_P3P_HEADER",
    L"BINDSTATUS_SESSION_COOKIE_RECEIVED",
    L"BINDSTATUS_PERSISTENT_COOKIE_RECEIVED",
    L"BINDSTATUS_SESSION_COOKIES_ALLOWED",
    L"BINDSTATUS_CACHECONTROL",
    L"BINDSTATUS_CONTENTDISPOSITIONFILENAME",
    L"BINDSTATUS_MIMETEXTPLAINMISMATCH",
    L"BINDSTATUS_PUBLISHERAVAILABLE",
    L"BINDSTATUS_DISPLAYNAMEAVAILABLE",
    L"BINDSTATUS_SSLUX_NAVBLOCKED",
    L"BINDSTATUS_SERVER_MIMETYPEAVAILABLE",
    L"BINDSTATUS_SNIFFED_CLASSIDAVAILABLE",
    L"BINDSTATUS_64BIT_PROGRESS"
};

wchar_t* eBindString_Text[] =
{
    L"BINDSTRING Entry Zero (invalid)",
    L"BINDSTRING_HEADERS",
    L"BINDSTRING_ACCEPT_MIMES",
    L"BINDSTRING_EXTRA_URL",
    L"BINDSTRING_LANGUAGE",
    L"BINDSTRING_USERNAME",
    L"BINDSTRING_PASSWORD",
    L"BINDSTRING_UA_PIXELS",
    L"BINDSTRING_UA_COLOR",
    L"BINDSTRING_OS",
    L"BINDSTRING_USERAGENT",
    L"BINDSTRING_ACCEPT_ENCODINGS",
    L"BINDSTRING_POST_COOKIE",
    L"BINDSTRING_POST_DATA_MIME",
    L"BINDSTRING_URL",
    L"BINDSTRING_IID",
    L"BINDSTRING_FLAG_BIND_TO_OBJECT",
    L"BINDSTRING_PTR_BIND_CONTEXT",
    L"BINDSTRING_XDR_ORIGIN",
    L"BINDSTRING_DOWNLOADPATH",
    L"BINDSTRING_ROOTDOC_URL"
};


wchar_t *eParseAction_Text[] =
{
    L"PARSE Entry Zero (invalid)",
    L"PARSE_CANONICALIZE",
    L"PARSE_FRIENDLY",
    L"PARSE_SECURITY_URL",
    L"PARSE_ROOTDOCUMENT",
    L"PARSE_DOCUMENT",
    L"PARSE_ANCHOR",
    L"PARSE_ENCODE",
    L"PARSE_DECODE",
    L"PARSE_PATH_FROM_URL",
    L"PARSE_URL_FROM_PATH",
    L"PARSE_MIME",
    L"PARSE_SERVER",
    L"PARSE_SCHEMA",
    L"PARSE_SITE",
    L"PARSE_DOMAIN",
    L"PARSE_LOCATION",
    L"PARSE_SECURITY_DOMAIN",
    L"PARSE_ESCAPE",
    L"PARSE_UNESCAPE"
};

wchar_t* eQueryOption_Text[] =
{
    L"QUERY Entry Zero (invalid)",
    L"QUERY_EXPIRATION_DATE",
    L"QUERY_TIME_OF_LAST_CHANGE",
    L"QUERY_CONTENT_ENCODING",
    L"QUERY_CONTENT_TYPE",
    L"QUERY_REFRESH",
    L"QUERY_RECOMBINE",
    L"QUERY_CAN_NAVIGATE",
    L"QUERY_USES_NETWORK",
    L"QUERY_IS_CACHED",
    L"QUERY_IS_INSTALLEDENTRY",
    L"QUERY_IS_CACHED_OR_MAPPED",
    L"QUERY_USES_CACHE",
    L"QUERY_IS_SECURE",
    L"QUERY_IS_SAFE",
    L"QUERY_USES_HISTORYFOLDER",
    L"QUERY_IS_CACHED_AND_USABLE_OFFLINE"
};


wstring BSCFToString(DWORD dwFlags)
{
/*
    typedef enum {
        BSCF_FIRSTDATANOTIFICATION = 0x00000001,
        BSCF_INTERMEDIATEDATANOTIFICATION = 0x00000002,
        BSCF_LASTDATANOTIFICATION = 0x00000004,
        BSCF_DATAFULLYAVAILABLE = 0x00000008,
        BSCF_AVAILABLEDATASIZEUNKNOWN = 0x00000010,
        BSCF_SKIPDRAINDATAFORFILEURLS = 0x00000020,
        BSCF_64BITLENGTHDOWNLOAD = 0x00000040
    } BSCF;
*/

    if (!dwFlags)
        return L"";

    wstringstream wss;
    if (dwFlags & BSCF_FIRSTDATANOTIFICATION) wss << L" BSCF_FIRSTDATANOTIFICATION";
    if (dwFlags & BSCF_INTERMEDIATEDATANOTIFICATION) wss << L" BSCF_INTERMEDIATEDATANOTIFICATION";
    if (dwFlags & BSCF_LASTDATANOTIFICATION) wss << L" BSCF_LASTDATANOTIFICATION";
    if (dwFlags & BSCF_DATAFULLYAVAILABLE) wss << L" BSCF_DATAFULLYAVAILABLE";
    if (dwFlags & BSCF_AVAILABLEDATASIZEUNKNOWN) wss << L" BSCF_AVAILABLEDATASIZEUNKNOWN";
    if (dwFlags & BSCF_SKIPDRAINDATAFORFILEURLS) wss << L" BSCF_SKIPDRAINDATAFORFILEURLS";
    if (dwFlags & BSCF_64BITLENGTHDOWNLOAD) wss << L" BSCF_64BITLENGTHDOWNLOAD";

    return wss.str().substr(1);
}


wstring BINDFToString(DWORD dwFlags)
{
/*
    typedef enum {
        BINDF_ASYNCHRONOUS = 0x00000001,
        BINDF_ASYNCSTORAGE = 0x00000002,
        BINDF_NOPROGRESSIVERENDERING = 0x00000004,
        BINDF_OFFLINEOPERATION = 0x00000008,
        BINDF_GETNEWESTVERSION = 0x00000010,
        BINDF_NOWRITECACHE = 0x00000020,
        BINDF_NEEDFILE = 0x00000040,
        BINDF_PULLDATA = 0x00000080,
        BINDF_IGNORESECURITYPROBLEM = 0x00000100,
        BINDF_RESYNCHRONIZE = 0x00000200,
        BINDF_HYPERLINK = 0x00000400,
        BINDF_NO_UI = 0x00000800,
        BINDF_SILENTOPERATION = 0x00001000,
        BINDF_PRAGMA_NO_CACHE = 0x00002000,
        BINDF_GETCLASSOBJECT = 0x00004000,
        BINDF_RESERVED_1 = 0x00008000,
        BINDF_FREE_THREADED = 0x00010000,
        BINDF_DIRECT_READ = 0x00020000,
        BINDF_FORMS_SUBMIT = 0x00040000,
        BINDF_GETFROMCACHE_IF_NET_FAIL = 0x00080000,
        BINDF_FROMURLMON = 0x00100000,
        BINDF_FWD_BACK = 0x00200000,
        BINDF_PREFERDEFAULTHANDLER = 0x00400000,
        BINDF_ENFORCERESTRICTED = 0x00800000
    } BINDF;
*/

    if (!dwFlags)
        return L"";

    wstringstream wss;
    if (dwFlags & BINDF_ASYNCHRONOUS) wss << L" BINDF_ASYNCHRONOUS";
    if (dwFlags & BINDF_ASYNCSTORAGE) wss << L" BINDF_ASYNCSTORAGE";
    if (dwFlags & BINDF_NOPROGRESSIVERENDERING) wss << L" BINDF_NOPROGRESSIVERENDERING";
    if (dwFlags & BINDF_OFFLINEOPERATION) wss << L" BINDF_OFFLINEOPERATION";
    if (dwFlags & BINDF_GETNEWESTVERSION) wss << L" BINDF_GETNEWESTVERSION";
    if (dwFlags & BINDF_NOWRITECACHE) wss << L" BINDF_NOWRITECACHE";
    if (dwFlags & BINDF_NEEDFILE) wss << L" BINDF_NEEDFILE";
    if (dwFlags & BINDF_PULLDATA) wss << L" BINDF_PULLDATA";
    if (dwFlags & BINDF_IGNORESECURITYPROBLEM) wss << L" BINDF_IGNORESECURITYPROBLEM";
    if (dwFlags & BINDF_RESYNCHRONIZE) wss << L" BINDF_RESYNCHRONIZE";
    if (dwFlags & BINDF_HYPERLINK) wss << L" BINDF_HYPERLINK";
    if (dwFlags & BINDF_NO_UI) wss << L" BINDF_NO_UI";
    if (dwFlags & BINDF_SILENTOPERATION) wss << L" BINDF_SILENTOPERATION";
    if (dwFlags & BINDF_PRAGMA_NO_CACHE) wss << L" BINDF_PRAGMA_NO_CACHE";
    if (dwFlags & BINDF_GETCLASSOBJECT) wss << L" BINDF_GETCLASSOBJECT";
    if (dwFlags & BINDF_RESERVED_1) wss << L" BINDF_RESERVED_1";
    if (dwFlags & BINDF_FREE_THREADED) wss << L" BINDF_FREE_THREADED";
    if (dwFlags & BINDF_DIRECT_READ) wss << L" BINDF_DIRECT_READ";
    if (dwFlags & BINDF_FORMS_SUBMIT) wss << L" BINDF_FORMS_SUBMIT";
    if (dwFlags & BINDF_GETFROMCACHE_IF_NET_FAIL) wss << L" BINDF_GETFROMCACHE_IF_NET_FAIL";
    if (dwFlags & BINDF_FROMURLMON) wss << L" BINDF_FROMURLMON";
    if (dwFlags & BINDF_FWD_BACK) wss << L" BINDF_FWD_BACK";
    if (dwFlags & BINDF_PREFERDEFAULTHANDLER) wss << L" BINDF_PREFERDEFAULTHANDLER";
    if (dwFlags & BINDF_ENFORCERESTRICTED) wss << L" BINDF_ENFORCERESTRICTED";

    return wss.str().substr(1);
}

wstring BINDINFOOPTIONS2String(DWORD dwFlags)
{
/*
    typedef enum {
        BINDINFO_OPTIONS_WININETFLAG = 0x00010000,
        BINDINFO_OPTIONS_ENABLE_UTF8 = 0x00020000,
        BINDINFO_OPTIONS_DISABLE_UTF8 = 0x00040000,
        BINDINFO_OPTIONS_USE_IE_ENCODING = 0x00080000,
        BINDINFO_OPTIONS_BINDTOOBJECT = 0x00100000,
        BINDINFO_OPTIONS_SECURITYOPTOUT = 0x00200000,
        BINDINFO_OPTIONS_IGNOREMIMETEXTPLAIN = 0x00400000,
        BINDINFO_OPTIONS_USEBINDSTRINGCREDS = 0x00800000,
        BINDINFO_OPTIONS_IGNOREHTTPHTTPSREDIRECTS = 0x01000000,
        BINDINFO_OPTIONS_IGNORE_SSLERRORS_ONCE = 0x02000000,
        BINDINFO_WPC_DOWNLOADBLOCKED = 0x08000000,
        BINDINFO_WPC_LOGGING_ENABLED = 0x10000000,
        BINDINFO_OPTIONS_DISABLEAUTOREDIRECTS = 0x40000000,
        BINDINFO_OPTIONS_SHDOCVW_NAVIGATE = (int) 0x80000000,
        BINDINFO_OPTIONS_ALLOWCONNECTDATA = 0x20000000
    } BINDINFO_OPTIONS;
*/
    if (!dwFlags)
        return L"";

    wstringstream wss;
    if (dwFlags & BINDINFO_OPTIONS_WININETFLAG) wss << L" BINDINFO_OPTIONS_WININETFLAG";
    if (dwFlags & BINDINFO_OPTIONS_ENABLE_UTF8) wss << L" BINDINFO_OPTIONS_ENABLE_UTF8";
    if (dwFlags & BINDINFO_OPTIONS_DISABLE_UTF8) wss << L" BINDINFO_OPTIONS_DISABLE_UTF8";
    if (dwFlags & BINDINFO_OPTIONS_USE_IE_ENCODING) wss << L" BINDINFO_OPTIONS_USE_IE_ENCODING";
    if (dwFlags & BINDINFO_OPTIONS_BINDTOOBJECT) wss << L" BINDINFO_OPTIONS_BINDTOOBJECT";
    if (dwFlags & BINDINFO_OPTIONS_SECURITYOPTOUT) wss << L" BINDINFO_OPTIONS_SECURITYOPTOUT";
    if (dwFlags & BINDINFO_OPTIONS_IGNOREMIMETEXTPLAIN) wss << L" BINDINFO_OPTIONS_IGNOREMIMETEXTPLAIN";
    if (dwFlags & BINDINFO_OPTIONS_USEBINDSTRINGCREDS) wss << L" BINDINFO_OPTIONS_USEBINDSTRINGCREDS";
    if (dwFlags & BINDINFO_OPTIONS_IGNOREHTTPHTTPSREDIRECTS) wss << L" BINDINFO_OPTIONS_IGNOREHTTPHTTPSREDIRECTS";
    if (dwFlags & BINDINFO_OPTIONS_IGNORE_SSLERRORS_ONCE) wss << L" BINDINFO_OPTIONS_IGNORE_SSLERRORS_ONCE";
    if (dwFlags & BINDINFO_WPC_DOWNLOADBLOCKED) wss << L" BINDINFO_WPC_DOWNLOADBLOCKED";
    if (dwFlags & BINDINFO_WPC_LOGGING_ENABLED) wss << L" BINDINFO_WPC_LOGGING_ENABLED";
    if (dwFlags & BINDINFO_OPTIONS_DISABLEAUTOREDIRECTS) wss << L" BINDINFO_OPTIONS_DISABLEAUTOREDIRECTS";
    if (dwFlags & BINDINFO_OPTIONS_SHDOCVW_NAVIGATE) wss << L" BINDINFO_OPTIONS_SHDOCVW_NAVIGATE";
    if (dwFlags & BINDINFO_OPTIONS_ALLOWCONNECTDATA) wss << L" BINDINFO_OPTIONS_ALLOWCONNECTDATA";

    return wss.str().substr(1);
}


wstring PIFLAGS2String(DWORD dwFlags)
{
/*
    typedef enum _tagPI_FLAGS {
        PI_PARSE_URL = 0x00000001,
        PI_FILTER_MODE = 0x00000002,
        PI_FORCE_ASYNC = 0x00000004,
        PI_USE_WORKERTHREAD = 0x00000008,
        PI_MIMEVERIFICATION = 0x00000010,
        PI_CLSIDLOOKUP = 0x00000020,
        PI_DATAPROGRESS = 0x00000040,
        PI_SYNCHRONOUS = 0x00000080,
        PI_APARTMENTTHREADED = 0x00000100,
        PI_CLASSINSTALL = 0x00000200,
        PI_PASSONBINDCTX = 0x00002000,
        PI_NOMIMEHANDLER = 0x00008000,
        PI_LOADAPPDIRECT = 0x00004000,
        PD_FORCE_SWITCH = 0x00010000,
        PI_PREFERDEFAULTHANDLER = 0x00020000
    } PI_FLAGS;
*/

    if (!dwFlags)
        return L"";

    wstringstream wss;
    if (dwFlags & PI_PARSE_URL) wss << L" PI_PARSE_URL";
    if (dwFlags & PI_FILTER_MODE) wss << L" PI_FILTER_MODE";
    if (dwFlags & PI_FORCE_ASYNC) wss << L" PI_FORCE_ASYNC";
    if (dwFlags & PI_USE_WORKERTHREAD) wss << L" PI_USE_WORKERTHREAD";
    if (dwFlags & PI_MIMEVERIFICATION) wss << L" PI_MIMEVERIFICATION";
    if (dwFlags & PI_CLSIDLOOKUP) wss << L" PI_CLSIDLOOKUP";
    if (dwFlags & PI_DATAPROGRESS) wss << L" PI_DATAPROGRESS";
    if (dwFlags & PI_SYNCHRONOUS) wss << L" PI_SYNCHRONOUS";
    if (dwFlags & PI_APARTMENTTHREADED) wss << L" PI_APARTMENTTHREADED";
    if (dwFlags & PI_CLASSINSTALL) wss << L" PI_CLASSINSTALL";
    if (dwFlags & PI_PASSONBINDCTX) wss << L" PI_PASSONBINDCTX";
    if (dwFlags & PI_NOMIMEHANDLER) wss << L" PI_NOMIMEHANDLER";
    if (dwFlags & PI_LOADAPPDIRECT) wss << L" PI_LOADAPPDIRECT";
    if (dwFlags & PD_FORCE_SWITCH) wss << L" PD_FORCE_SWITCH";
    if (dwFlags & PI_PREFERDEFAULTHANDLER) wss << L" PI_PREFERDEFAULTHANDLER";

    return wss.str().substr(1);
}
