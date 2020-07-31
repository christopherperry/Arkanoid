#pragma once

#include <string>
#include <vector>
#include "utils/Functions.h"

class TimerTask
{
public:
	TimerTask(int timeout, functions::Func task) : timeout{ timeout }, task{ task } {};
	void update(float deltaTime);
	bool isFinished();
	static void update(std::vector<TimerTask*>& tasks, float deltaTime);
	static void removeFinished(std::vector<TimerTask*>& tasks);
private:
	functions::Func task;
	int timeout;
	int totalTime{ 0 };
	bool finished{ false };
};