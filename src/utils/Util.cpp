#include "Util.h"

std::vector<int> Util::getDigits(int num)
{
	std::vector<int> res;
	do {
		res.push_back(num % 10);
		num /= 10;
	} while (num > 0);
	std::reverse(res.begin(), res.end());
	return res;
}
