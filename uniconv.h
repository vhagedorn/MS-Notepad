/* uniconv.h - Unicode conversion macros and functions for Notepad */

#ifndef _UNICONV_H_
#define _UNICONV_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Macros for calculating sizes */
#define CharSizeOf(x)   (sizeof(x)/sizeof(TCHAR))
#define ByteCountOf(x)  ((x)*sizeof(TCHAR))

/* Unicode Byte Order Mark constants */
#define BYTE_ORDER_MARK             0xFEFF
#define REVERSE_BYTE_ORDER_MARK     0xFFFE

/* UTF-8 Byte Order Mark */
#define UTF8_BOM_1                  0xEF
#define UTF8_BOM_2                  0xBB
#define UTF8_BOM_3                  0xBF

/* Function prototypes for Unicode detection and conversion */
INT IsTextUTF8(LPSTR lpstrInputStream, INT iLen);
INT IsInputTextUnicode(LPSTR lpstrInputStream, INT iLen);

#ifdef __cplusplus
}
#endif

#endif /* _UNICONV_H_ */
