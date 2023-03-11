#ifdef _WIN32
//  For Windows (32- and 64-bit)
#   include <windows.h>
#   define SLEEP(msecs) Sleep(msecs)
#elif __unix
//  For linux, OSX, and other unixes
#   define _POSIX_C_SOURCE 199309L // or greater
#   include <time.h>
#   define SLEEP(msecs) do {            \
        struct timespec ts;             \
        ts.tv_sec = msecs/1000;         \
        ts.tv_nsec = msecs%1000*1000;   \
        nanosleep(&ts, NULL);           \
        } while (0)
#else
#   error "Unknown system"
#endif

#include <stdio.h>

int main() {
    printf("I'm sleepy...\n");
    SLEEP(2000);
    printf("Not anymore.");

    return 0;
}
