#include <algorithm>
#include "TimerTask.h"

void TimerTask::update(float deltaTime)
{
	if (finished) return;

	totalTime += deltaTime;

	if (totalTime >= timeout)
	{
		finished = true;
		task();
	}
}

bool TimerTask::isFinished()
{
	return finished;
}

void TimerTask::update(std::vector<TimerTask*>& tasks, float deltaTime)
{
	for (TimerTask* task : tasks)
	{
		task->update(deltaTime);
	}
}

void TimerTask::removeFinished(std::vector<TimerTask*>& tasks)
{
	std::vector<TimerTask*>::iterator newEnd = std::partition(tasks.begin(), tasks.end(), [=](TimerTask* e) -> bool { return !e->isFinished(); });
	for (std::vector<TimerTask*>::iterator it = newEnd; it != tasks.end(); ++it)
	{
		delete (*it);
	}
	tasks.erase(newEnd, tasks.end());
}
