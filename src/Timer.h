#pragma once

#include <string>

class Timer
{
public:
	Timer(int timeout, std::string tag) : timeout{ timeout }, tag{ tag } {};
	void start() { this->isStarted = true; };
	bool isStarted() { return isStarted; };
	bool isFinished() { return totalTime >= timeout; }
	std::string getTag() { return tag; }
	void update(float deltaTime) { totalTime += deltaTime; };
private:
	int timeout;
	int totalTime;
	bool isStarted{ false };
	std::string tag;
};