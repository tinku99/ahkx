#ifndef wineheaders_h
#define wineheaders_h
#include <wine/library.h>
#include <windows.h>


void * WineLoadLibrary(const char *dll) {
        return(LoadLibraryA(dll));
}

void WineFreeLibrary(void *handle) {
        FreeLibrary(handle);
}

void * WineGetProcAddress(void *handle, const char *function) {
        return(GetProcAddress(handle, function));
}

#endif
