/* uconvert.h - Unicode conversion utilities for Notepad */

#ifndef _UCONVERT_H_
#define _UCONVERT_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Unicode conversion macros */
#define UNICODE_NULL        ((WCHAR)0)

/* Memory allocation macros for Unicode strings */
#define ALLOC_WCHAR(count)  ((WCHAR*)LocalAlloc(LPTR, (count) * sizeof(WCHAR)))
#define ALLOC_CHAR(count)   ((CHAR*)LocalAlloc(LPTR, (count) * sizeof(CHAR)))

/* String length calculation macros */
#define WCHAR_LENGTH(wstr)  (wstr ? wcslen(wstr) : 0)
#define CHAR_LENGTH(str)    (str ? strlen(str) : 0)

/* Unicode file detection helpers */
BOOL IsUnicodeFile(LPVOID lpBuffer, DWORD dwSize);
BOOL IsUnicodeBEFile(LPVOID lpBuffer, DWORD dwSize);
BOOL IsUTF8File(LPVOID lpBuffer, DWORD dwSize);

/* Conversion functions */
LPWSTR AnsiToUnicode(LPCSTR lpszAnsi, UINT uCodePage);
LPSTR UnicodeToAnsi(LPCWSTR lpszUnicode, UINT uCodePage);
LPWSTR UTF8ToUnicode(LPCSTR lpszUTF8);
LPSTR UnicodeToUTF8(LPCWSTR lpszUnicode);

/* Memory cleanup */
VOID FreeConvertedString(LPVOID lpString);

#ifdef __cplusplus
}
#endif

#endif /* _UCONVERT_H_ */
