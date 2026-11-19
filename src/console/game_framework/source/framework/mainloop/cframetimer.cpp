/*****************************************************************************
 *
 * File :     cframetimer.cpp
 *
 * Abstract : Real-time frame pacing for the main loop. See cframetimer.h.
 *
 *****************************************************************************/
#include "precomp.h"

#include <windows.h>

#include "cframetimer.h"

CFrameTimer g_frameTimer(60.0f, 60.0f);

// FUNCTION: GAME 0x464e80
CFrameTimer::CFrameTimer(float maxRate, float minRate)
{
    int q = QueryPerformanceFrequency((LARGE_INTEGER *)&m_freq);
    m_minStep = 1.0f / maxRate;
    m_tickDiv = 1000;
    m_maxRate = maxRate;
    m_minRate = minRate;
    m_hasQpc = q;
    m_lastCounter = 0;
    m_pauseStart = 0;
    m_lastTick = 0;
    m_pauseTick = 0;
    m_realTime = 0;
    m_stepTime = 0;
    m_steps = 0;
    m_stepsPrev = 0;
    m_waits = 0;
    m_waitsPrev = 0;
    m_waited = 1;
    m_maxStep = 1.0f / minRate;
}

// FUNCTION: GAME 0x464f00
void CFrameTimer::Notify()
{
    if (m_hasQpc)
    {
        QueryPerformanceCounter((LARGE_INTEGER *)&m_lastCounter);
        m_realTime = 0;
        m_stepTime = 0;
        m_steps = 0;
        m_waits = 0;
    }
    else
    {
        unsigned t = GetTickCount();
        m_realTime = 0;
        m_stepTime = 0;
        m_steps = 0;
        m_waits = 0;
        m_lastTick = t;
    }
}

// FUNCTION: GAME 0x464f40
float CFrameTimer::Tick()
{
    if (m_hasQpc)
    {
        if (m_pauseStart != 0)
            return 0.0f;
    }
    else if (m_pauseTick != 0)
    {
        return 0.0f;
    }

    double dt;
    if (m_hasQpc)
    {
        __int64 now;
        QueryPerformanceCounter((LARGE_INTEGER *)&now);
        __int64 d = now - m_lastCounter;
        m_lastCounter += d;
        dt = (double)d / (double)m_freq;
    }
    else
    {
        unsigned d = GetTickCount();
        d -= m_lastTick;
        m_lastTick += d;
        dt = (double)d / (double)m_tickDiv;
    }

    m_realTime = (float)(dt + m_realTime);
    if (m_realTime >= 1.0f)
    {
        m_realTime -= 1.0f;
        m_stepsPrev = m_steps;
        m_steps = 0;
        m_waitsPrev = m_waits;
        m_waits = 0;
        m_stepTime -= 1.0f;
    }

    if (m_maxStep + m_stepTime <= m_realTime)
    {
        m_stepTime = m_stepTime + m_maxStep;
        m_steps++;
        m_waited = 0;
        return m_maxStep;
    }
    if (m_minStep + m_stepTime <= m_realTime)
    {
        float d = m_realTime - m_stepTime;
        m_steps++;
        m_waited = 0;
        m_stepTime = d + m_stepTime;
        return d;
    }
    if (!m_waited)
    {
        m_waited = 1;
        m_waits++;
        return -1.0f;
    }
    return 0.0f;
}

// FUNCTION: GAME 0x465090
void CFrameTimer::Pause()
{
    if (m_hasQpc)
    {
        if (m_pauseStart == 0)
            QueryPerformanceCounter((LARGE_INTEGER *)&m_pauseStart);
    }
    else if (m_pauseTick == 0)
    {
        m_pauseTick = GetTickCount();
    }
}

// FUNCTION: GAME 0x4650d0
void CFrameTimer::Resume()
{
    if (m_hasQpc)
    {
        if (m_pauseStart != 0)
        {
            __int64 now = 0;
            QueryPerformanceCounter((LARGE_INTEGER *)&now);
            m_lastCounter += now - m_pauseStart;
            m_pauseStart = 0;
        }
    }
    else if (m_pauseTick != 0)
    {
        m_lastTick += GetTickCount() - m_pauseTick;
        m_pauseTick = 0;
    }
}
