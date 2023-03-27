// clang
#include "common.h"
//#include "common/crt.h"
#include <windows.h>

#if OS_WIN && BITS_64
    #pragma comment(linker, "/defaultlib:user32.lib")
    #pragma comment(linker, "/defaultlib:kernel32.lib")
    #pragma comment(linker, "/subsystem:windows")
    #pragma comment(linker, "/ENTRY:_start")

    struct WinInit {
        HANDLE stdin = 0;
        HANDLE stdout = 0;
        HANDLE stderr = 0;
        void init() {
            AllocConsole();
            this->stdin = GetStdHandle(-10);
            this->stdout = GetStdHandle(-11);
            this->stderr = GetStdHandle(-12);
        }
    };
    global WinInit _win_init = {};

    void osExit(uint return_code) {
        ExitProcess(return_code);
    }
    void osCrash(uint return_code) {
        osExit(return_code);
    }
    void osPrint(const u8* msg, uint count) {
        WriteFile(_win_init.stdout, msg, count, 0, 0);
        MessageBoxA(0, (char*)msg, 0, 0);
    }
    void* osAlloc(void* prev_ptr, uint size) {
        return VirtualAlloc(prev_ptr, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    }
    // TODO: exceptions: AddVectoredExceptionHandler(...) / HandlerRoutine(...)

    int WinMain(HINSTANCE app, HINSTANCE prev_app, LPSTR command, int window_options);
    external int _start() {
        //crtInit();
        _win_init.init();
        int retCode = WinMain(0, 0, 0, 0);
        //_DoExit();
        ExitProcess(retCode);
    }
#else
    static_assert(false, "Must compile on 64-bit Windows!");
#endif
