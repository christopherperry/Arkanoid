#include "Brick.h"

void Brick::render(SDL_Renderer* renderer)
{
	Entity::render(renderer);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, &boundingBox.getBounds());
}
