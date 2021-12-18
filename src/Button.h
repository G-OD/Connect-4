#ifndef BUTTON_H
#define BUTTON_H

#include <cstring>
#include "Graphics.h"

class Button
{
	private:
		float xPos; // Position
		float yPos;
		float width;
		float height;
		const char *text; // Text to hold

		float textRed; // RGB values for text
		float textGreen;
		float textBlue;
		float bgRed; // Background colour
		float bgGreen;
		float bgBlue;

	public:
		Button(float xPos, float yPos, float width, float height, const char *string, float textRed, float textGreen, float textBlue, float bgRed, float bgGreen, float bgBlue);

		~Button() {}

		void render();

		bool click(float mouseXPos, float mouseYPos);
};

#endif