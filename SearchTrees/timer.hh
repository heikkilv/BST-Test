#ifndef TIMER_HH
#define TIMER_HH

#include <chrono>

class Timer
{
public:
    Timer();

    // Resets the timer
    void reset();
    // Returns the elapsed time in milliseconds
    double elapsed() const;

private:
    using clock_ = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock_> start_;
};

#endif // TIMER_HH
