////////////////////////////////////////////////////////////////////////////
// PerformanceCounter.h -- Win32 performance counter wrapper
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef __MZC3_PERFORMANCECOUNTER__
#define __MZC3_PERFORMANCECOUNTER__

////////////////////////////////////////////////////////////////////////////

class MPerformanceCounter EXTENDS_MOBJECT
{
public:
    MPerformanceCounter();
    virtual ~MPerformanceCounter();

    // copyable
    MPerformanceCounter(const MPerformanceCounter& counter);
    void operator=(const MPerformanceCounter& counter);

    BOOL   Start();
    void   Restart();

    // in seconds
    double CheckTimeInSeconds() const;
    double CheckTimeInSecondsAndRestart();
    // in milliseconds
    DWORD  CheckTimeInMilliSeconds() const;
    DWORD  CheckTimeInMilliSecondsAndRestart();

    static BOOL IsAvailable();

protected:
           LARGE_INTEGER    m_past;
    static LARGE_INTEGER    s_freq;
    static BOOL             s_available;

    friend struct MPerformanceCounterInitializer_;
};

////////////////////////////////////////////////////////////////////////////

#ifndef MZC_NO_INLINING
    #undef MZC_INLINE
    #define MZC_INLINE inline
    #include "PerformanceCounter_inl.h"
#endif

#endif  // ndef __MZC3_PERFORMANCECOUNTER__
