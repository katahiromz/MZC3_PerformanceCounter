////////////////////////////////////////////////////////////////////////////
// PerformanceCounter.cpp -- Win32 performance counter wrapper
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef MZC_NO_INLINING
    #undef MZC_INLINE
    #define MZC_INLINE  /*empty*/
    #include "PerformanceCounter_inl.h"
#endif

////////////////////////////////////////////////////////////////////////////

/*static*/ LARGE_INTEGER MPerformanceCounter::s_freq;
/*static*/ BOOL MPerformanceCounter::s_available = FALSE;

////////////////////////////////////////////////////////////////////////////

struct MPerformanceCounterInitializer_
{
    MPerformanceCounterInitializer_()
    {
        MPerformanceCounter::s_available =
            ::QueryPerformanceFrequency(&MPerformanceCounter::s_freq);
    }
};

// NOTE: MPerformanceCounter is initialized before main/WinMain/wWinMain.
MPerformanceCounterInitializer_ mzcPerformanceCounterInitializer;

////////////////////////////////////////////////////////////////////////////

#ifdef UNITTEST
    // unit test and example
    #include <cstdio>
    using namespace std;
    int main(void)
    {
        MPerformanceCounter counter;
        if (!counter.IsAvailable())
        {
            printf("ERROR: Not available\n");
            return 1;
        }

        counter.Start();
        Sleep(1000);
        printf("%lu\n", counter.CheckTimeInMilliSeconds());
        Sleep(1000);
        printf("%f\n", counter.CheckTimeInSeconds());

        counter.Restart();
        Sleep(1000);
        printf("%f\n", counter.CheckTimeInSeconds());
        Sleep(1000);
        printf("%lu\n", counter.CheckTimeInMilliSeconds());
        return 0;
    }
#endif

////////////////////////////////////////////////////////////////////////////
