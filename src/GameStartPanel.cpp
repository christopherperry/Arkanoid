#include "GameStartPanel.h"
#include "TextRenderer.h"

enum StartPanelText
{
	PRESS_ENTER_TO_START
};

GameStartPanel::GameStartPanel(SDL_Renderer * renderer, TTF_Font * font, SDL_Rect panelRect)
{
	this->panelRect = panelRect;

	SDL_Color red{ 188, 25, 0, 255 };

	text = {
		{StartPanelText::PRESS_ENTER_TO_START, new Text(renderer, font, "Press ENTER to Start", red) },
	};
}

void GameStartPanel::render(SDL_Renderer* renderer)
{
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
