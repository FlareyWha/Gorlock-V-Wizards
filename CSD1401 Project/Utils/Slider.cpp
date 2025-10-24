#include "Slider.h"
#include "cprocessing.h"

Slider::Slider()
{
	loadImages();
	trackerPosition = thumbPosition = CP_Vector_Zero();
	sliderValue = 0;
}

Slider::Slider(CP_Vector position, float value)
{
	loadImages();
	trackerPosition = thumbPosition = position;
	sliderValue = value;
}

Slider::~Slider()
{
	CP_Image_Free(tracker);
	CP_Image_Free(thumb);
}

void Slider::loadImages(void)
{
	tracker = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
	thumb = CP_Image_Load("Assets/Main/bar_round_gloss_large.png");
}

void Slider::updateThumbPositionBasedOnPosition(CP_Vector newPosition)
{
	//sliderValue = newPosition.x - (trackerPosition.x - trackerWidth / 2);

	thumbPosition = newPosition;

	clampThumbPosition();

	sliderValue = 100 - thumbPosition.x - (trackerPosition.x - trackerWidth / 2) / trackerWidth;
}

void Slider::updateThumbPositionBasedOnValue(void)
{
	float newXPos = trackerPosition.x - trackerWidth / 2;

	newXPos += trackerWidth * (sliderValue / 100);

	thumbPosition = CP_Vector_Set(newXPos, thumbPosition.y);
}

void Slider::clampThumbPosition(void)
{
	CP_Math_ClampFloat(thumbPosition.x, trackerPosition.x - trackerWidth / 2, trackerPosition.x + trackerWidth / 2);

	thumbPosition.y = trackerPosition.y;
}

float Slider::getSliderValue(void)
{
	return sliderValue;
}

void Slider::renderSlider(CP_POSITION_MODE previousMode)
{
	CP_Settings_ImageMode(CP_POSITION_CENTER);

	CP_Image_Draw(tracker, trackerPosition.x, trackerPosition.y, trackerWidth, trackerHeight, 255);

	CP_Image_Draw(thumb, thumbPosition.x, thumbPosition.y, thumbWidth, thumbHeight, 255);

	CP_Settings_ImageMode(previousMode);
}
