// clang tests\hello_win64.cpp -o out\hello_win64.exe
#include "../src/tinylibc_win64.h"

int WinMain(HINSTANCE app, HINSTANCE prev_app, LPSTR command, int window_options) {
    print("Hello world\n\0");
    print(tprint(123));
    return 0;
}
