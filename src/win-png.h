#ifndef _WIN_PNG_H_
#define _WIN_PNG_H_
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

HBITMAP LoadPng(LPCTSTR png);

#ifdef __cplusplus
};
#endif

#endif // _WIN_PNG_H_
