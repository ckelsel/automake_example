#include "del.h"
#include "mycxx.h"
#include "win-png.h"
#include "win-floatbar.h"

int del(int a, int b)
{
    wf_floatbar_free(NULL);
    LoadPng(NULL);
    cxx_func();
    return a - b;
}
