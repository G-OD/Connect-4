#ifndef NUMBERSELECTOR_H
#define NUMBERSELECTOR_H

#include "Graphics.h"

class NumberSelector
{
	private:
		float xPos;
		float yPos;
		float width;
		float height;
		float outlineSize;
		int number;

		float textRed;
		float textGreen;
		float textBlue;
		float bgRed;
		float bgGreen;
		float bgBlue;

	public:
		NumberSelector(float xPos, float yPos, float width, float height, float outlineSize, int number, float textRed, float textGreen, float textBlue, float bgRed, float bgGreen, float bgBlue);

		~NumberSelector() {}

		int getValue();
		void setValue(int value);

		void increase();
		void decrease();

		void render();

		bool click(float mouseXPos, float mouseYPos);
};

#endif