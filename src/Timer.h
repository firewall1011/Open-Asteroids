#pragma once
#include <functional>

class Timer
{
	float countdown = 0.0f;
	float timeRemaining = 0.0f;
	bool shouldAlarm;
public:

	Timer(float countTime);

	bool Tick(float timeElapsed);
	void Reset();
};

