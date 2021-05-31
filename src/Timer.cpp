#include "Timer.h"
#include <chrono>
#include <thread>
#include <iostream>


using namespace std::chrono_literals;
using namespace std::chrono;

Timer::Timer(float countTime) : countdown(countTime), timeRemaining(countTime), shouldAlarm(true) {}

void Timer::Reset()
{
	timeRemaining = countdown;
	shouldAlarm = true;
}

bool Timer::Tick(float timeElapsed) 
{
	if (!shouldAlarm)
		return false;
	
	timeRemaining -= timeElapsed;
	if (timeRemaining <= 0.0f) {
		shouldAlarm = false;
		return true;
	}
	return false;
}