#ifndef __TIMER_H__
#define __TIMER_H__

//#include "Defs.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	int Read() const;
	float ReadSec() const;

private:

	int startTime;
};

#endif //__TIMER_H__