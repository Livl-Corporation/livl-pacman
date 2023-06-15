#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_TIMERS 10

typedef void (*TimerCallback)();

struct Timer
{
    int count;
    int initialCount;
    bool isRunning;
    bool isFinished;
    TimerCallback callback;
};

void initTimer(struct Timer *timer, int count);

void startTimer(struct Timer *timer);

void stopTimer(struct Timer *timer);

void resetTimer(struct Timer *timer);

void updateTimers();

#endif // TIMER_H