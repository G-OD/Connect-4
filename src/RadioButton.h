#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <vector>
#include "Graphics.h"

class RadioButton
{
	private:
		float xPos;
		float yPos;
		float size = 20.0f;
		float outlineSize = 8.0f;
		std::vector<const char *> optionStrings;
		int selected;

		float textRed;
		float textGreen;
		float textBlue;

	public:
		RadioButton(float xPos, float yPos, float size, float outlineSize, std::vector<const char *> optionStrings, int selected, float textRed, float textGreen, float textBlue);

		~RadioButton() {}

		int getValue();
		void setValue(int value);

		void render();

		bool click(float mouseXPos, float mouseYPos);
};

#endif