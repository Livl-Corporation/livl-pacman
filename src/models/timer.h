#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_TIMERS 10

typedef void (*TimerCallback)();
typedef bool (*TimerRunCondition)();

struct Timer
{
    int count;
    int initialCount;
    bool isRunning;
    bool isFinished;
    TimerCallback callback;
    TimerRunCondition runCondition;
};

void initTimer(struct Timer *timer, int count);

void startTimer(struct Timer *timer);

void stopTimer(struct Timer *timer);

void resetTimer(struct Timer *timer);

void setDuration(struct Timer *timer, int duration);

void setTimerCallback(struct Timer *timer, TimerCallback callback);

void setTimerRunCondition(struct Timer *timer, TimerRunCondition runCondition);

void updateTimers();

void clearTimers();

#endif // TIMER_H