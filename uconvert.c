/* uconvert.c - Unicode conversion utilities implementation */

#include "precomp.h"

/*
 * IsUnicodeFile - Check if file starts with Unicode BOM
 */
BOOL IsUnicodeFile(LPVOID lpBuffer, DWORD dwSize)
{
    LPBYTE lpBytes = (LPBYTE)lpBuffer;
    
    if (dwSize < 2) {
        return FALSE;
    }
    
    return (lpBytes[0] == 0xFF && lpBytes[1] == 0xFE);
}

/*
 * IsUnicodeBEFile - Check if file starts with Unicode Big Endian BOM
 */
BOOL IsUnicodeBEFile(LPVOID lpBuffer, DWORD dwSize)
{
    LPBYTE lpBytes = (LPBYTE)lpBuffer;
    
    if (dwSize < 2) {
        return FALSE;
    }
    
    return (lpBytes[0] == 0xFE && lpBytes[1] == 0xFF);
}

/*
 * IsUTF8File - Check if file starts with UTF-8 BOM
 */
BOOL IsUTF8File(LPVOID lpBuffer, DWORD dwSize)
{
    LPBYTE lpBytes = (LPBYTE)lpBuffer;
    
    if (dwSize < 3) {
        return FALSE;
    }
    
    return (lpBytes[0] == 0xEF && lpBytes[1] == 0xBB && lpBytes[2] == 0xBF);
}

/*
 * AnsiToUnicode - Convert ANSI string to Unicode
 */
LPWSTR AnsiToUnicode(LPCSTR lpszAnsi, UINT uCodePage)
{
    LPWSTR lpszUnicode;
    INT nLen;
    
    if (!lpszAnsi) {
        return NULL;
    }
    
    // Get required buffer size
    nLen = MultiByteToWideChar(uCodePage, 0, lpszAnsi, -1, NULL, 0);
    if (nLen <= 0) {
        return NULL;
    }
    
    // Allocate buffer
    lpszUnicode = ALLOC_WCHAR(nLen);
    if (!lpszUnicode) {
        return NULL;
    }
    
    // Convert
    if (MultiByteToWideChar(uCodePage, 0, lpszAnsi, -1, lpszUnicode, nLen) == 0) {
        LocalFree(lpszUnicode);
        return NULL;
    }
    
    return lpszUnicode;
}

/*
 * UnicodeToAnsi - Convert Unicode string to ANSI
 */
LPSTR UnicodeToAnsi(LPCWSTR lpszUnicode, UINT uCodePage)
{
    LPSTR lpszAnsi;
    INT nLen;
    
    if (!lpszUnicode) {
        return NULL;
    }
    
    // Get required buffer size
    nLen = WideCharToMultiByte(uCodePage, 0, lpszUnicode, -1, NULL, 0, NULL, NULL);
    if (nLen <= 0) {
        return NULL;
    }
    
    // Allocate buffer
    lpszAnsi = ALLOC_CHAR(nLen);
    if (!lpszAnsi) {
        return NULL;
    }
    
    // Convert
    if (WideCharToMultiByte(uCodePage, 0, lpszUnicode, -1, lpszAnsi, nLen, NULL, NULL) == 0) {
        LocalFree(lpszAnsi);
        return NULL;
    }
    
    return lpszAnsi;
}

/*
 * UTF8ToUnicode - Convert UTF-8 string to Unicode
 */
LPWSTR UTF8ToUnicode(LPCSTR lpszUTF8)
{
    return AnsiToUnicode(lpszUTF8, CP_UTF8);
}

/*
 * UnicodeToUTF8 - Convert Unicode string to UTF-8
 */
LPSTR UnicodeToUTF8(LPCWSTR lpszUnicode)
{
    return UnicodeToAnsi(lpszUnicode, CP_UTF8);
}

/*
 * FreeConvertedString - Free memory allocated by conversion functions
 */
VOID FreeConvertedString(LPVOID lpString)
{
    if (lpString) {
        LocalFree(lpString);
    }
}
