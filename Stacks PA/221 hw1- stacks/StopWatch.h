#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

class StopWatch
{
private:
	/// Timer Resolution
	float			resolution;

	/// Using The Performance Timer?
	bool			performanceTimer;

	/// Start Value
	__int64			begin;
	/// End Value
	__int64			end;

	bool running;

public:
	StopWatch() {
		/// Timer Frequency
		__int64			frequency;

		begin = end = 0;
		running = false;

		// Check to see whether this computer has a performance timer
		if (!QueryPerformanceFrequency((LARGE_INTEGER *)&frequency))
		{
			// no performace counter available
			performanceTimer = false;
			resolution = 1.0f / 1000.0f;
		}
		else
		{
			// there is a performace timer available, so set the resolution
			performanceTimer = true;
			// calculate the resolution of the counter
			resolution = (float)(((double)1.0f) / ((double)frequency));
		}
	}

	// starts the timer
	void start() {
		__int64 time;

		// check if performance timer is used
		if (performanceTimer)
		{
			// get the current time
			QueryPerformanceCounter((LARGE_INTEGER *)&time);
			begin = time;
		}
		else
		{
			// set the last time this function was called to now
			begin = timeGetTime();
		}
		running = true;
	}

	// stops the timer from running
	void stop(void)
	{
		__int64 time;

		// check if performance timer is used
		if (performanceTimer)
		{
			// get the current time
			QueryPerformanceCounter((LARGE_INTEGER *)&time);
			end = time;
		}
		else
		{
			// set the last time this function was called to now
			end = timeGetTime();
		}
		running = false;
	}

	// returns the time in seconds of the timer.  If the timer is running, returns
	// the number of seconds since start was called.
	double seconds(void)
	{
		if (!running)
		{
			return ((double)(end - begin)*resolution);
		}
		__int64 now;

		// check if performance timer is used
		if (performanceTimer)
		{
			// get the current time
			QueryPerformanceCounter((LARGE_INTEGER *)&now);
		}
		else
		{
			// get the current time
			end = timeGetTime();
		}
		return ((double)(now - begin)*resolution);
	}

	// returns the time in milliseconds of the timer.  If the timer is running, returns
	// the number of milliseconds since start was called.
	double ms(void)
	{
		return seconds() * 1000;
	}
};

#endif