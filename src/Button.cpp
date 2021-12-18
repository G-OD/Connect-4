#include "Button.h"

// Contstructor
Button::Button(float xPos, float yPos, float width, float height, const char *text, float textRed, float textGreen, float textBlue, float bgRed, float bgGreen, float bgBlue)
{
	// Init variables
	this->xPos = xPos;
	this->yPos = yPos;
	this->width = width;
	this->height = height;
	this->text = text;

	this->textRed = textRed;
	this->textGreen = textGreen;
	this->textBlue = textBlue;
	
	this->bgRed = bgRed;
	this->bgGreen = bgGreen;
	this->bgBlue = bgBlue;
}

void Button::render()
{
	Graphics::drawRect(xPos, yPos, width, height, bgRed, bgGreen, bgBlue); // Draw rectangle according to values in variables
	Graphics::drawText(xPos, yPos, GLUT_BITMAP_8_BY_13, text, true, textRed, textGreen, textBlue); // Same for text set text type to 8 by 3 and center to true
}

// Button click handler
bool Button::click(float mouseXPos, float mouseYPos)
{
	mouseXPos = (Game::WINDOW_WIDTH * Graphics::getWindowAspectRatio() * 2) * ((float)mouseXPos / Game::getWindowWidth()) - Game::WINDOW_WIDTH * Graphics::getWindowAspectRatio(); // Get the mouse position according to the window width and height taking into account the aspect ratio. I then use linear interpolation to find the mouse position
	mouseYPos = (Game::WINDOW_HEIGHT * 2) * ((float)mouseYPos / Game::getWindowHeight()) - Game::WINDOW_HEIGHT;
	mouseYPos *= -1; // Invert Y position

	// Axis aligned bounding box collision detection
	if (xPos + width >= mouseXPos &&
		xPos - width <= mouseXPos &&
		yPos + height >= mouseYPos &&
		yPos - height <= mouseYPos)
	{
		return true;
	}

	return false; // Return false if not clicked
}