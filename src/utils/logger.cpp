#include "logger.h"
#include <string>
#include <iostream>
#include <SDL.h>

void Logger::logSDLError(const std::string & message)
{
	std::cout << message << " error: " << SDL_GetError() << std::endl;
}

void Logger::log(const std::string & message)
{
	std::cout << message << std::endl;
}
