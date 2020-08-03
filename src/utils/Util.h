#pragma once

#include <vector>

class Util
{
public:
	static std::vector<int> getDigits(int value);
};

/*
 Use this to safely delete references in your class ~Destructors.
*/
template <class T> void SafeDelete(T* pt)
{
	if (pt != nullptr)
	{
		delete pt;
		pt = nullptr;
	}
}