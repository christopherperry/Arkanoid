#include <string>
#include <iostream>
#include <SDL.h>
#include "logger.h"

void Logger::logSDLError(const std::string & message)
{
	std::cout << message << " error: " << SDL_GetError() << std::endl;
}