/* tchar_fixes.h - Manual TCHAR function mappings for linking */

#ifndef _TCHAR_FIXES_H_
#define _TCHAR_FIXES_H_

#ifdef UNICODE
#ifndef _sntprintf
#define _sntprintf _snwprintf
#endif
#ifndef _ttol
#define _ttol _wtol
#endif
#ifndef _istdigit
#define _istdigit iswdigit
#endif
#else
#ifndef _sntprintf
#define _sntprintf _snprintf
#endif
#ifndef _ttol
#define _ttol atol
#endif
#ifndef _istdigit
#define _istdigit isdigit
#endif
#endif

#endif /* _TCHAR_FIXES_H_ */
