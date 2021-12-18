#include "NumberSelector.h"

NumberSelector::NumberSelector(float xPos, float yPos, float width, float height, float outlineSize, int number, float textRed, float textGreen, float textBlue, float bgRed, float bgGreen, float bgBlue)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->width = width;
	this->height = height;
	this->outlineSize = outlineSize;
	this->number = number;

	this->textRed = textRed;
	this->textGreen = textGreen;
	this->textBlue = textBlue;
	this->bgRed = bgRed;
	this->bgGreen = bgGreen;
	this->bgBlue = bgBlue;
}

int NumberSelector::getValue()
{
	return number;
}

void NumberSelector::setValue(int value)
{
	number = value;
}

void NumberSelector::increase()
{
	++number;
}

void NumberSelector::decrease()
{
	--number;
}

void NumberSelector::render()
{
	float maxInnerWidth = width - outlineSize;
	float maxInnerHeight = height - outlineSize;
	float maxInnerWidth4th = maxInnerWidth / 4;

	Graphics::drawRect(xPos, yPos, width, height, 0.0f, 0.0f, 0.0f);
	Graphics::drawRect(xPos - maxInnerWidth4th, yPos, maxInnerWidth - maxInnerWidth4th, height - outlineSize, bgRed, bgGreen, bgBlue);
	Graphics::drawRect(xPos + (maxInnerWidth4th * 3), yPos, maxInnerWidth - (maxInnerWidth4th * 3), height - outlineSize, 0.0f, 1.0f, 0.0f);

	Graphics::drawRect(xPos + (maxInnerWidth4th * 3), yPos, maxInnerWidth4th, 3.0, 0.0f, 0.0f, 0.0f);

	// Top arrow
	Graphics::drawLine(xPos + maxInnerWidth4th * 3, yPos + 3.0f + 5.0f,
						xPos + maxInnerWidth4th * 3, yPos + maxInnerHeight - 5.0f,
						0.0f, 0.0f, 0.0f);

	Graphics::drawLine(xPos + (maxInnerWidth4th * 3), yPos + maxInnerHeight - 5.0f,
						(xPos + maxInnerWidth4th * 3) - 10.0f, yPos + (maxInnerHeight / 2.0f),
						0.0f, 0.0f, 0.0f);
	Graphics::drawLine(xPos + (maxInnerWidth4th * 3), yPos + maxInnerHeight - 5.0f,
						(xPos + maxInnerWidth4th * 3) + 10.0f, yPos + (maxInnerHeight / 2.0f),
						0.0f, 0.0f, 0.0f);

	// Bottom arrow
	Graphics::drawLine(xPos + maxInnerWidth4th * 3, yPos - 3.0f - 5.0f,
						xPos + maxInnerWidth4th * 3, yPos - (maxInnerHeight - 5.0f),
						0.0f, 0.0f, 0.0f);

	Graphics::drawLine(xPos + (maxInnerWidth4th * 3), yPos - (maxInnerHeight - 5.0f),
						(xPos + maxInnerWidth4th * 3) - 10.0f, yPos - (maxInnerHeight / 2.0f),
						0.0f, 0.0f, 0.0f);
	Graphics::drawLine(xPos + (maxInnerWidth4th * 3), yPos - (maxInnerHeight - 5.0f),
						(xPos + maxInnerWidth4th * 3) + 10.0f, yPos - (maxInnerHeight / 2.0f),
						0.0f, 0.0f, 0.0f);

	std::string number = std::to_string(this->number);
	Graphics::drawText(xPos - 25.0f, yPos, GLUT_BITMAP_8_BY_13, number.c_str(), true, textRed, textGreen, textBlue);
}

bool NumberSelector::click(float mouseXPos, float mouseYPos)
{
	mouseXPos = (Game::WINDOW_WIDTH * Graphics::getWindowAspectRatio() * 2) * ((float)mouseXPos / Game::getWindowWidth()) - Game::WINDOW_WIDTH * Graphics::getWindowAspectRatio();
	mouseYPos = (Game::WINDOW_HEIGHT * 2) * ((float)mouseYPos / Game::getWindowHeight()) - Game::WINDOW_HEIGHT;
	mouseYPos *= -1;

	if (mouseXPos >= xPos - width && mouseXPos <= xPos + width &&
		mouseYPos >= yPos - height && mouseYPos <= yPos + height)
	{
		if (mouseYPos > yPos)
		{
			if (number < 999)
			{
				++number;
				return true;
			}
		}
		else
		{
			if (number > 0)
			{
				--number;
				return true;
			}
		}
	}

	return false;
}