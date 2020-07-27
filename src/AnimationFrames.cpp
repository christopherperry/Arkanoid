#include "AnimationFrames.h"

void AnimationFrames::startAnimation()
{
	isAnimating = true;
}

void AnimationFrames::update(float deltaTimeMillis)
{
	if (isAnimating)
	{
		if (frameTimerMillis >= millisPerFrame)
		{
			currentFrame++;

			if (isLooping)
			{
				if (currentFrame >= totalFrames)
				{
					currentFrame = 0;
				}
			}

			frameTimerMillis = 0.0f;
		}
		else
		{
			frameTimerMillis += deltaTimeMillis;
		}
	}
}

int AnimationFrames::getCurrentFrame()
{
	return currentFrame;
}
