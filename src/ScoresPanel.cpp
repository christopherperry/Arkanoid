#include <vector>
#include "ScoresPanel.h"
#include "Text.h"
#include "TextRenderer.h"
#include "utils/Util.h"

enum ScoresPanelText
{
	// Digits for rendering the actual score
	DIGIT_0,
	DIGIT_1,
	DIGIT_2,
	DIGIT_3,
	DIGIT_4,
	DIGIT_5,
	DIGIT_6,
	DIGIT_7,
	DIGIT_8,
	DIGIT_9,

	// "Score: "
	SCORE,

	// "High Score: "
	HIGH_SCORE,

	// "Lives: "
	LIVES
};

ScoresPanel::ScoresPanel(SDL_Renderer* renderer, TTF_Font* font, Vector2 position)
{
	this->position = position;

	SDL_Color white{ 255, 255, 255, 255 };
	SDL_Color red{ 188, 25, 0, 255 };

	text = {
		{ScoresPanelText::LIVES, new Text(renderer, font, "Lives:", red) },
		{ScoresPanelText::SCORE, new Text(renderer, font, "Score:", red) },
		{ScoresPanelText::HIGH_SCORE, new Text(renderer, font, "High Score:", red) },
		{ScoresPanelText::DIGIT_0, new Text(renderer, font, "0", white) },
		{ScoresPanelText::DIGIT_1, new Text(renderer, font, "1", white) },
		{ScoresPanelText::DIGIT_2, new Text(renderer, font, "2", white) },
		{ScoresPanelText::DIGIT_3, new Text(renderer, font, "3", white) },
		{ScoresPanelText::DIGIT_4, new Text(renderer, font, "4", white) },
		{ScoresPanelText::DIGIT_5, new Text(renderer, font, "5", white) },
		{ScoresPanelText::DIGIT_6, new Text(renderer, font, "6", white) },
		{ScoresPanelText::DIGIT_7, new Text(renderer, font, "7", white) },
		{ScoresPanelText::DIGIT_8, new Text(renderer, font, "8", white) },
		{ScoresPanelText::DIGIT_9, new Text(renderer, font, "9", white) },
	};
}

void ScoresPanel::render(SDL_Renderer* renderer, int totalLives, int currentScore)
{
	// Left edge to align all the text to
	int startX = position.x;

	//////////////////////////////////////
	// Score Title
	//////////////////////////////////////
	Text* scoreTitle = text[ScoresPanelText::SCORE];
	SDL_Rect scoreTitleLocation{ startX, 31, scoreTitle->getWidth(), scoreTitle->getHeight() };
	TextRenderer::render(renderer, scoreTitle, scoreTitleLocation);

	//////////////////////////////////////
	// Score Digits
	//////////////////////////////////////
	int nextDigitLocationX = startX;
	std::vector<int> scoreDigits = Util::getDigits(currentScore);
	for (int i = 0; i < scoreDigits.size(); i++)
	{
		int digit = scoreDigits[i];
		Text* t = text[digit];
		TextRenderer::render(renderer, t, SDL_Rect{ nextDigitLocationX, scoreTitleLocation.y + scoreTitle->getHeight(), t->getWidth(), t->getHeight() });

		// Update for the next digit
		nextDigitLocationX += t->getWidth();
	}

	//////////////////////////////////////
	// Lives Title
	//////////////////////////////////////
	Text* livesTitle = text[ScoresPanelText::LIVES];
	SDL_Rect livesTitleLocation{ startX, 150, livesTitle->getWidth(), livesTitle->getHeight() };
	TextRenderer::render(renderer, livesTitle, livesTitleLocation);

	//////////////////////////////////////
	// Lives Digits
	//////////////////////////////////////
	nextDigitLocationX = startX;
	std::vector<int> livesDigits = Util::getDigits(totalLives);
	for (int i = 0; i < livesDigits.size(); i++)
	{
		int digit = livesDigits[i];
		Text* t = text[digit];
		TextRenderer::render(renderer, t, SDL_Rect{ nextDigitLocationX, livesTitleLocation.y + livesTitle->getHeight(), t->getWidth(), t->getHeight() });

		// Update for the next digit
		nextDigitLocationX += t->getWidth();
	}
}