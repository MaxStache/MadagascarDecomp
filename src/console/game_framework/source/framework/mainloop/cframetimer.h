#ifndef __MAINLOOP_CFRAMETIMER_H__
#define __MAINLOOP_CFRAMETIMER_H__

class CFrameTimer
{
public:
    CFrameTimer(float maxRate, float minRate); // FUNCTION: GAME 0x464e80
    void Notify();                             // FUNCTION: GAME 0x464f00
    float Tick();                              // FUNCTION: GAME 0x464f40
    void Pause();                              // FUNCTION: GAME 0x465090
    void Resume();                             // FUNCTION: GAME 0x4650d0

    __int64 m_freq;
    __int64 m_lastCounter;
    __int64 m_pauseStart;
    unsigned m_tickDiv;
    unsigned m_lastTick;
    unsigned m_pauseTick;
    int m_hasQpc;
    float m_maxRate;
    float m_minRate;
    float m_minStep;
    float m_maxStep;
    unsigned char m_waited;
    float m_realTime;
    float m_stepTime;
    int m_steps;
    int m_stepsPrev;
    int m_waits;
    int m_waitsPrev;
};

extern CFrameTimer g_frameTimer; // GLOBAL: GAME 0x62a4b8

#endif
