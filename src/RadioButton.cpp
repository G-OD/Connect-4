#include "RadioButton.h"

RadioButton::RadioButton(float xPos, float yPos, float size, float outlineSize, std::vector<const char *> optionStrings, int selected, float textRed, float textGreen, float textBlue)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->size = size;
	this->outlineSize = outlineSize;
	this->optionStrings = optionStrings;
	this->selected = selected;

	this->textRed = textRed;
	this->textGreen = textGreen;
	this->textBlue = textBlue;
}

int RadioButton::getValue()
{
	return selected;
}

void RadioButton::setValue(int value)
{
	selected = value;
}

void RadioButton::render()
{
	float xPos = this->xPos;

	for (int i = 0; i < (int)optionStrings.size(); ++i)
	{
		Graphics::drawCircle(xPos, yPos, size, 1.0f, 0.5f, 0.0f);

		if (i == selected)
			Graphics::drawCircle(xPos, yPos, size - outlineSize, 0.0f, 0.0f, 0.0f);
		else
			Graphics::drawCircle(xPos, yPos, size - outlineSize, 1.0f, 1.0f, 1.0f);
		
		xPos += size + outlineSize + outlineSize;
		int len = Graphics::drawText(xPos, yPos, GLUT_BITMAP_8_BY_13, optionStrings[i], false, textRed, textGreen, textBlue);
		xPos += ((size + outlineSize + outlineSize) * 2) + len;
	}
}

bool RadioButton::click(float mouseXPos, float mouseYPos)
{
	mouseXPos = (Game::WINDOW_WIDTH * Graphics::getWindowAspectRatio() * 2) * ((float)mouseXPos / Game::getWindowWidth()) - Game::WINDOW_WIDTH * Graphics::getWindowAspectRatio();
	mouseYPos = (Game::WINDOW_HEIGHT * 2) * ((float)mouseYPos / Game::getWindowHeight()) - Game::WINDOW_HEIGHT;
	mouseYPos *= -1;

	float currentXPos = xPos;
	for (int i = 0; i < (int)optionStrings.size(); ++i)
	{
		if (currentXPos + (size) >= mouseXPos &&
			currentXPos - (size) <= mouseXPos &&
			yPos + (size) >= mouseYPos &&
			yPos - (size) <= mouseYPos)
		{
			selected = i;
			return true;
		}

		const unsigned char *string = reinterpret_cast<const unsigned char*>(optionStrings[i]);
		currentXPos += ((size + outlineSize + outlineSize) * 3) + glutBitmapLength(GLUT_BITMAP_8_BY_13, string);;
	}

	return false;
}