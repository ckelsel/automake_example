#include "win-png.h"
#include <wincodec.h>
#include <iostream>
#include <fstream>

HRESULT WINAPI WICConvertBitmapSource(
    REFWICPixelFormatGUID dstFormat,
    IWICBitmapSource *pISrc,
    IWICBitmapSource **ppIDst);

// Creates a stream object initialized with the data from an executable resource.
IStream * CreateStreamFromFile(LPCTSTR lpName)
{
    return NULL;
} 

// Loads a PNG image from the specified stream (using Windows Imaging Component).
IWICBitmapSource * LoadBitmapFromStream(IStream * ipImageStream)
{
    typedef HRESULT (WINAPI *PWICConvertBitmapSource)(
        REFWICPixelFormatGUID, IWICBitmapSource *, IWICBitmapSource **);

    HMODULE hDll = LoadLibrary("WindowsCodecs.dll");
    PWICConvertBitmapSource pFunc =
        (PWICConvertBitmapSource)GetProcAddress(hDll, "WICConvertBitmapSource");
    printf("WICConvertBitmapSource: 0x%p.\n", pFunc);

    // initialize return value
    IWICBitmapSource * ipBitmap = NULL;
    UINT nFrameCount = 0;
    IWICBitmapFrameDecode * ipFrame = NULL;
 
    // load WIC's PNG decoder
    IWICBitmapDecoder * ipDecoder = NULL;
    if (FAILED(CoCreateInstance(CLSID_WICPngDecoder, NULL, CLSCTX_INPROC_SERVER, __uuidof(ipDecoder), reinterpret_cast<void**>(&ipDecoder))))
        goto Return;
 
    // load the PNG
    if (FAILED(ipDecoder->Initialize(ipImageStream, WICDecodeMetadataCacheOnLoad)))
        goto ReleaseDecoder;
 
    // check for the presence of the first frame in the bitmap
    if (FAILED(ipDecoder->GetFrameCount(&nFrameCount)) || nFrameCount != 1)
        goto ReleaseDecoder;
 
    // load the first frame (i.e., the image)
    if (FAILED(ipDecoder->GetFrame(0, &ipFrame)))
        goto ReleaseDecoder;
 
    // convert the image to 32bpp BGRA format with pre-multiplied alpha
    //   (it may not be stored in that format natively in the PNG resource,
    //   but we need this format to create the DIB to use on-screen)
    //WICConvertBitmapSource(GUID_WICPixelFormat32bppPBGRA, ipFrame, &ipBitmap);
    pFunc(GUID_WICPixelFormat32bppPBGRA, ipFrame, &ipBitmap);
    ipFrame->Release();
 
ReleaseDecoder:
    ipDecoder->Release();
Return:
    FreeLibrary(hDll);

    return ipBitmap;
}

// 32-bit DIB from the specified WIC bitmap.
HBITMAP CreateHBITMAP(IWICBitmapSource * ipBitmap)
{
    // initialize return value
    HBITMAP hbmp = NULL;
    void * pvImageBits = NULL;
    HDC hdcScreen = GetDC(NULL);
    UINT cbStride = 0;
    UINT cbImage = 0;
 
    // get image attributes and check for valid image
    UINT width = 0;
    UINT height = 0;
    if (FAILED(ipBitmap->GetSize(&width, &height)) || width == 0 || height == 0)
        goto Return;
 
    // prepare structure giving bitmap information (negative height indicates a top-down DIB)
    BITMAPINFO bminfo;
    ZeroMemory(&bminfo, sizeof(bminfo));
    bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bminfo.bmiHeader.biWidth = width;
    bminfo.bmiHeader.biHeight = -((LONG) height);
    bminfo.bmiHeader.biPlanes = 1;
    bminfo.bmiHeader.biBitCount = 32;
    bminfo.bmiHeader.biCompression = BI_RGB;
 
    // create a DIB section that can hold the image
    hbmp = CreateDIBSection(hdcScreen, &bminfo, DIB_RGB_COLORS, &pvImageBits, NULL, 0);
    ReleaseDC(NULL, hdcScreen);
    if (hbmp == NULL)
        goto Return;
 
    // extract the image into the HBITMAP
    cbStride = width * 4;
    cbImage = cbStride * height;
    if (FAILED(ipBitmap->CopyPixels(NULL, cbStride, cbImage, static_cast<BYTE *>(pvImageBits))))
    {
        // couldn't extract image; delete HBITMAP
        DeleteObject(hbmp);
        hbmp = NULL;
    }
 
Return:
    return hbmp;
}

// Loads the PNG containing the splash image into a HBITMAP.
HBITMAP LoadPng(LPCTSTR png)
{
    HBITMAP hbmpSplash = NULL;
    IWICBitmapSource * ipBitmap = NULL;
 
    // load the PNG image data into a stream
    IStream * ipImageStream = CreateStreamFromFile(png);
    if (ipImageStream == NULL)
        goto Return;
 
    // load the bitmap with WIC
    ipBitmap = LoadBitmapFromStream(ipImageStream);
    if (ipBitmap == NULL)
        goto ReleaseStream;
 
    // create a HBITMAP containing the image
    hbmpSplash = CreateHBITMAP(ipBitmap);
    ipBitmap->Release();
 
ReleaseStream:
    ipImageStream->Release();
Return:
    return hbmpSplash;
}
