#pragma once

#include <string>

class Logger
{
public:
	static void logSDLError(const std::string& message);
	static void log(const std::string& message);
};