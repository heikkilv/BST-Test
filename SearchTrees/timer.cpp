#include "timer.hh"

Timer::Timer() :
    start_{ clock_::now() }
{
}

void Timer::reset()
{
    start_ = clock_::now();
}

double Timer::elapsed() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (clock_::now() - start_).count();
}
