#pragma once
#include "cprocessing.h"

class Slider
{
private:
	CP_Image tracker;
	CP_Image thumb;

	CP_Vector trackerPosition;
	CP_Vector thumbPosition;
	
	float trackerWidth;
	float trackerHeight;

	float thumbWidth;
	float thumbHeight;

	//This is the value that will be changed by the slider. e.g volume in settings
	float sliderValue;

public:
	Slider();
	Slider(CP_Vector position, float value);
	~Slider();

	void loadImages(void);

	void updateThumbPositionBasedOnPosition(CP_Vector newPosition);

	void updateThumbPositionBasedOnValue(void);

	void clampThumbPosition(void);

	float getSliderValue(void);

	CP_Vector getThumbPosition(void);

	float getThumbWidth(void);

	float getThumbHeight(void);

	void renderSlider(CP_POSITION_MODE previousMode);
};