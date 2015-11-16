#pragma once

extern wchar_t* eBindStatus_Text[];
extern wchar_t* eBindString_Text[];
extern wchar_t* eBindOptions_Text[];
extern wchar_t* eParseAction_Text[];
extern wchar_t* eQueryOption_Text[];

wstring BSCFToString(DWORD dwFlags);
wstring BINDFToString(DWORD dwFlags);
wstring BINDINFOOPTIONS2String(DWORD dwFlags);
wstring PIFLAGS2String(DWORD dwFlags);


