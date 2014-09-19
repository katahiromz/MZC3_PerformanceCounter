////////////////////////////////////////////////////////////////////////////
// PerformanceCounter_inl.hpp -- Win32 performance counter wrapper
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

MZC_INLINE MPerformanceCounter::MPerformanceCounter()
{
}

MZC_INLINE /*virtual*/ MPerformanceCounter::~MPerformanceCounter()
{
}

MZC_INLINE MPerformanceCounter::MPerformanceCounter(const MPerformanceCounter& counter)
{
    m_past = counter.m_past;
}

MZC_INLINE MPerformanceCounter& MPerformanceCounter::operator=(const MPerformanceCounter& counter)
{
    m_past = counter.m_past;
    return *this;
}

MZC_INLINE BOOL MPerformanceCounter::Start()
{
    return ::QueryPerformanceCounter(&m_past);
}

MZC_INLINE void MPerformanceCounter::Restart()
{
    ::QueryPerformanceCounter(&m_past);
}

MZC_INLINE double MPerformanceCounter::CheckTimeInSeconds() const
{
    LARGE_INTEGER curr;
    ::QueryPerformanceCounter(&curr);
    return (double)(curr.QuadPart - m_past.QuadPart) / s_freq.QuadPart;
}

MZC_INLINE DWORD MPerformanceCounter::CheckTimeInMilliSeconds() const
{
    LARGE_INTEGER curr;
    ::QueryPerformanceCounter(&curr);
    return (DWORD)((curr.QuadPart - m_past.QuadPart) * 1000 / s_freq.QuadPart);
}

MZC_INLINE double MPerformanceCounter::CheckTimeInSecondsAndRestart()
{
    LARGE_INTEGER curr;
    ::QueryPerformanceCounter(&curr);
    double d = (double)(curr.QuadPart - m_past.QuadPart) / s_freq.QuadPart;
    m_past = curr;
    return d;
}

MZC_INLINE DWORD MPerformanceCounter::CheckTimeInMilliSecondsAndRestart()
{
    LARGE_INTEGER curr;
    ::QueryPerformanceCounter(&curr);
    DWORD dw = (curr.QuadPart - m_past.QuadPart) * 1000 / s_freq.QuadPart;
    m_past = curr;
    return dw;
}

MZC_INLINE /*static*/ bool MPerformanceCounter::IsAvailable()
{
    return MPerformanceCounter::s_available;
}
