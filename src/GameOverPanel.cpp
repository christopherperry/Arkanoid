#include "GameOverPanel.h"
#include "TextRenderer.h"

enum GameOverPanelText
{
	GAME_OVER
};

GameOverPanel::GameOverPanel(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect panelRect) : panelRect{ panelRect }
{
	SDL_Color red{ 188, 25, 0, 255 };

	text = {
		{GameOverPanelText::GAME_OVER, new Text(renderer, font, "Game Over", red) },
	};
}

void GameOverPanel::render(SDL_Renderer* renderer)
{
	// Center the start text for now.
	// After we add power ups etc we'll add instructions to this screen.
	Text* gameOverText = text[GameOverPanelText::GAME_OVER];

	int textWidth = gameOverText->getWidth();
	int textHeight = gameOverText->getHeight();
	int positionX = (panelRect.w * 0.5f) - (textWidth * 0.5f);
	int positionY = (panelRect.h * 0.5f) - (textHeight * 0.5f);
	SDL_Rect gameOverTextLocation{ positionX, positionY, textWidth, textHeight };
	TextRenderer::render(renderer, gameOverText, gameOverTextLocation);
}