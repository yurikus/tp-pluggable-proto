#pragma once

#define STRICT
#define ISOLATION_AWARE_ENABLED 1
#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "targetver.h"

// ATL
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlwin.h>
#include <atlutil.h>
using namespace ATL;

// WTL
#include <atlapp.h>
#include <atlmisc.h>
#include <atldlgs.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlctrlw.h>
#include <atlcrack.h>
#include <atlframe.h>
using namespace WTL;

// STL
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <map>
#include <list>
#include <algorithm>
using namespace std;

// Shell/IE
#include <msxml6.h>
#include <ShlGuid.h>
#include <strsafe.h>
#include <comdef.h>
#include <Wininet.h>

#define LOG(msg, ...) ATLTRACE2(L"[CIE][%04lu]%s[" __FUNCTIONW__ L"] " msg, ::GetCurrentThreadId(), _AtlModule.offset().c_str(), __VA_ARGS__)
#define LOGNF(msg, ...) ATLTRACE2(L"[CIE][%04lu]%s  " msg, ::GetCurrentThreadId(), _AtlModule.offset().c_str(), __VA_ARGS__)
