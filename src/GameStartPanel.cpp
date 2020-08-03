#include "GameStartPanel.h"
#include "TextRenderer.h"
#include "sprites/Sprite.h"

enum StartPanelText
{
	PRESS_ENTER_TO_START
};

enum StartPanelSprites
{
	LOGO
};

GameStartPanel::GameStartPanel(SDL_Texture* texture, SDL_Renderer* renderer, TTF_Font* font, SDL_Rect panelRect)
{
	this->panelRect = panelRect;

	SDL_Color red{ 188, 25, 0, 255 };

	text = {
		{StartPanelText::PRESS_ENTER_TO_START, new Text(renderer, font, "Press ENTER to Start", red) },
	};

	sprites = {
		{ LOGO, new Sprite{ texture, SDL_Rect{289, 193, 190, 94} } }
	};
}

void GameStartPanel::render(SDL_Renderer* renderer)
{
	Sprite* logoSprite = sprites[LOGO];
	int logoWidth = logoSprite->rect.w;
	int logoHeight = logoSprite->rect.h;
	int logoPositionX = (panelRect.w * 0.5f) - (logoWidth * 0.5f);
	int logoPositionY = 31;
	SDL_Rect logoLocation{ logoPositionX, logoPositionY, logoWidth, logoHeight };
	SDL_RenderCopy(renderer, logoSprite->texture, &logoSprite->rect, &logoLocation);

	// Center the start text for now.
	// After we add power ups etc we'll add instructions to this screen.
	Text* gameStartText = text[StartPanelText::PRESS_ENTER_TO_START];

	int textWidth = gameStartText->getWidth();
	int textHeight = gameStartText->getHeight();
	int positionX = (panelRect.w * 0.5f) - (textWidth * 0.5f);
	int positionY = (panelRect.h * 0.5f) - (textHeight * 0.5f);
	SDL_Rect gameStartTextLocation{ positionX, positionY, textWidth, textHeight };
	TextRenderer::render(renderer, gameStartText, gameStartTextLocation);
}
