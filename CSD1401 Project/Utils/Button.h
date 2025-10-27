#pragma once
#include "cprocessing.h"
class Button1
{
protected:

private:
	CP_Image Button;
	float buttonX1 = 0;
	float buttonY1 = 0;

	float buttonWidth = 250;
	float buttonHeight = 60;

public:

	void Buttondraw();
	void buttoninit(float x, float y);

};

