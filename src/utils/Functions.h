#pragma once

#include <functional>

namespace functions
{
	template <typename T>
	using Func1 = std::function<void(T)>;

	using Func = std::function<void()>;
}