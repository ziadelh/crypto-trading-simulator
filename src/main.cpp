#include "MerkelMain.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    // let the Windows console show the colours used by the candlestick plot
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(console, &mode))
    {
        SetConsoleMode(console, mode | 0x0004); // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    }
#endif

    MerkelMain app{};
    app.init();
}
