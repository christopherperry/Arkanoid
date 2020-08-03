#include <vector>
#include "RoundStartPanel.h"
#include "TextRenderer.h"
#include "utils/Util.h"

enum RoundStartPanelText
{
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
	ROUND_NUMBER,
};

RoundStartPanel::RoundStartPanel(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect panelRect) : panelRect{ panelRect }
{
	SDL_Color red{ 188, 25, 0, 255 };

	text = {
		{RoundStartPanelText::ROUND_NUMBER, new Text(renderer, font, "Round ", red) },
		{RoundStartPanelText::DIGIT_0, new Text(renderer, font, "0", red) },
		{RoundStartPanelText::DIGIT_1, new Text(renderer, font, "1", red) },
		{RoundStartPanelText::DIGIT_2, new Text(renderer, font, "2", red) },
		{RoundStartPanelText::DIGIT_3, new Text(renderer, font, "3", red) },
		{RoundStartPanelText::DIGIT_4, new Text(renderer, font, "4", red) },
		{RoundStartPanelText::DIGIT_5, new Text(renderer, font, "5", red) },
		{RoundStartPanelText::DIGIT_6, new Text(renderer, font, "6", red) },
		{RoundStartPanelText::DIGIT_7, new Text(renderer, font, "7", red) },
		{RoundStartPanelText::DIGIT_8, new Text(renderer, font, "8", red) },
		{RoundStartPanelText::DIGIT_9, new Text(renderer, font, "9", red) },
	};
}

void RoundStartPanel::render(SDL_Renderer* renderer, int roundNumber)
{
	// Center the start text for now.
	Text* roundNumberText = text[RoundStartPanelText::ROUND_NUMBER];

	int textWidth = roundNumberText->getWidth();
	int textHeight = roundNumberText->getHeight();
	int positionX = (panelRect.w * 0.5f) - (textWidth * 0.5f);
	int positionY = (panelRect.h * 0.5f) - (textHeight * 0.5f);
	SDL_Rect roundNumberTextLocation{ positionX, positionY, textWidth, textHeight };
	TextRenderer::render(renderer, roundNumberText, roundNumberTextLocation);

	//////////////////////////////////////
	// Round Number Digits
	//////////////////////////////////////
	int nextDigitLocationX = roundNumberTextLocation.x + roundNumberText->getWidth();
	std::vector<int> roundDigits = Util::getDigits(roundNumber);
	for (int i = 0; i < roundDigits.size(); i++)
	{
		int digit = roundDigits[i];
		Text* t = text[digit];
		TextRenderer::render(renderer, t, SDL_Rect{ nextDigitLocationX, roundNumberTextLocation.y, t->getWidth(), t->getHeight() });

		// Update for the next digit
		nextDigitLocationX += t->getWidth();
	}
}