#include "timer.h"

struct Timer *timers[MAX_TIMERS];
int timerCount = 0;

void initTimer(struct Timer *timer, int count)
{

    timer->count = count;
    timer->initialCount = count;
    timer->isRunning = false;
    timer->isFinished = false;
    timer->callback = NULL;

    timers[timerCount] = timer;
    timerCount++;
}

void startTimer(struct Timer *timer)
{
    timer->isRunning = true;
}

void stopTimer(struct Timer *timer)
{
    timer->isRunning = false;
}

void resetTimer(struct Timer *timer)
{
    timer->count = timer->initialCount;
    timer->isRunning = false;
    timer->isFinished = false;
}

void updateTimers()
{

    for (int i = 0; i < timerCount; i++)
    {
        struct Timer *timer = timers[i];

        if (!timer->isRunning)
            continue;

        timer->count--;

        if (timer->count <= 0)
        {
            timer->isFinished = true;
            timer->isRunning = false;

            if (timer->callback != NULL)
                timer->callback();
        }

    }
}

void clearTimers()
{
    for (int i = 0; i < timerCount; i++)
    {
        timers[i] = NULL;
    }

    timerCount = 0;
}