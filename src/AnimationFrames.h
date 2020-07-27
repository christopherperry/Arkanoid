#pragma once

class AnimationFrames
{
private:
	int currentFrame{0};
	int totalFrames;
	bool isAnimating{ false };
	bool isLooping{ true };
	float frameTimerMillis{ 0.0f };

	// 4 frames per second would be 250 / 1000 so 250 millis.
	float millisPerFrame; 
public:
	AnimationFrames(int totalFrames, float millisPerFrame, bool isLooping) : totalFrames{ totalFrames }, millisPerFrame{ millisPerFrame }, isLooping{ isLooping } {};
	void startAnimation();
	void reset();
	bool isFinished();
	void update(float deltaTimeMillis);
	int getCurrentFrame();
};

