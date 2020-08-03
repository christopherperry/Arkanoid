#include "GameWinPanel.h"
#include "TextRenderer.h"
#include "sprites/Sprite.h"

enum WinPanelText
{
	CONGRATULATIONS,
	YOU_WIN
};

enum WinPanelSprites
{
	LOGO
};

GameWinPanel::GameWinPanel(SDL_Texture* texture, SDL_Renderer* renderer, TTF_Font* font, SDL_Rect panelRect)
{
	this->panelRect = panelRect;

	SDL_Color white{ 255, 255, 255, 255 };

	text = {
		{WinPanelText::CONGRATULATIONS, new Text(renderer, font, "CONGRATULATIONS", white) },
		{WinPanelText::YOU_WIN, new Text(renderer, font, "You Win!", white) },
	};

	sprites = {
		{ LOGO, new Sprite{ texture, SDL_Rect{289, 193, 190, 94} } }
	};
}

void GameWinPanel::render(SDL_Renderer* renderer)
{
	//////////////////
	// LOGO
	/////////////////
	Sprite* logoSprite = sprites[LOGO];
	int logoWidth = logoSprite->rect.w;
	int logoHeight = logoSprite->rect.h;
	int logoPositionX = (panelRect.w * 0.5f) - (logoWidth * 0.5f);
	int logoPositionY = 31;
	SDL_Rect logoLocation{ logoPositionX, logoPositionY, logoWidth, logoHeight };
	SDL_RenderCopy(renderer, logoSprite->texture, &logoSprite->rect, &logoLocation);

	//////////////////
	// TEXT
	/////////////////
	Text* congratsText = text[WinPanelText::CONGRATULATIONS];
	int textWidth = congratsText->getWidth();
	int textHeight = congratsText->getHeight();
	int positionX = (panelRect.w * 0.5f) - (textWidth * 0.5f);
	int positionY = (panelRect.h * 0.5f) - (textHeight * 0.5f);
	SDL_Rect congratsTextLocation{ positionX, positionY, textWidth, textHeight };
	TextRenderer::render(renderer, congratsText, congratsTextLocation);

	Text* winText = text[WinPanelText::YOU_WIN];
	textWidth = winText->getWidth();
	textHeight = winText->getHeight();
	positionX = (panelRect.w * 0.5f) - (textWidth * 0.5f);
	positionY = congratsTextLocation.y + congratsTextLocation.h;
	SDL_Rect winTextLocation{ positionX, positionY, textWidth, textHeight };
	TextRenderer::render(renderer, winText, winTextLocation);
}