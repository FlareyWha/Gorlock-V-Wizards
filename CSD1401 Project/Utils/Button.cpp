#include "Button.h"
#include "cprocessing.h"

void Button1::buttoninit(float x, float y) {
	Button = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
	this->buttonX1 = x;
	this->buttonY1 = y;
}

void Button1::Buttondraw() {

	CP_Image_Draw(Button, buttonX1, buttonY1, buttonWidth, buttonHeight, 255);

}