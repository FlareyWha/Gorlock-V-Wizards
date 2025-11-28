/*!
@file       Slider.cpp
@author     Yap Yu Xuan Daevon (yuxuandaevon.yap)
@brief      This file contains definition of functions and variables
			used for the slider class
*//*_______________________________________________________________________*/

#include "Slider.h"
#include "cprocessing.h"

/*!
@brief	Constructor
*//*______________________________________________________________*/
Slider::Slider()
{
	loadImages();
	trackerPosition = thumbPosition = CP_Vector_Zero();
	sliderValue = 0;

	trackerWidth = 400;
	trackerHeight = 25;

	thumbWidth = 40;
	thumbHeight = 50;

	updateThumbPositionBasedOnValue();
}


/*!
@brief	Overloaded constructor
*//*______________________________________________________________*/
Slider::Slider(CP_Vector position, float value)
{
	loadImages();
	trackerPosition = thumbPosition = position;
	sliderValue = value;

	trackerWidth = 400;
	trackerHeight = 25;

	thumbWidth = 40;
	thumbHeight = 50;

	updateThumbPositionBasedOnValue();
}

/*!
@brief	Loads the images used for the slider
@param	void
@return void
*//*______________________________________________________________*/
void Slider::loadImages(void)
{
	thumb = CP_Image_Load("Assets/Slider/thumb.png");
}

/*!
@brief	Updates the thumb position based off a new position (used when dragging the thumb with mouse)
@param	CP_Vector newPosition - the new position to set the thumb to
@return void
*//*______________________________________________________________*/
void Slider::updateThumbPositionBasedOnPosition(CP_Vector newPosition)
{
	thumbPosition = newPosition;

	clampThumbPosition();

	sliderValue = (((thumbPosition.x - trackerWidth / 2) -  trackerWidth) / trackerWidth) * 100;
}

/*!
@brief	Updates the thumb position based off the value attached to the slider (used when initializing slider)
@param	void
@return void
*//*______________________________________________________________*/
void Slider::updateThumbPositionBasedOnValue(void)
{
	float newXPos = trackerPosition.x - trackerWidth / 2;

	newXPos += trackerWidth * (sliderValue / 100);

	thumbPosition = CP_Vector_Set(newXPos, thumbPosition.y);
}

/*!
@brief	Clamp thumb position to the boundaries of the tracker
@param	void
@return void
*//*______________________________________________________________*/
void Slider::clampThumbPosition(void)
{
	thumbPosition.x = CP_Math_ClampFloat(thumbPosition.x, trackerPosition.x - trackerWidth / 2, trackerPosition.x + trackerWidth / 2);

	thumbPosition.y = trackerPosition.y;
}

/*!
@brief	Get value attached to the slider
@param	void
@return float - value attached to the slider
*//*______________________________________________________________*/
float Slider::getSliderValue(void)
{
	return sliderValue;
}

/*!
@brief	Get position of the thumb
@param	void
@return CP_Vector - position of the thumb
*//*______________________________________________________________*/
CP_Vector Slider::getThumbPosition(void)
{
	return thumbPosition;
}

/*!
@brief	Get thumb width
@param	void
@return float - thumb width
*//*______________________________________________________________*/
float Slider::getThumbWidth(void)
{
	return thumbWidth;
}

/*!
@brief	Get thumb height
@param	void
@return float - thumb height
*//*______________________________________________________________*/
float Slider::getThumbHeight(void)
{
	return thumbHeight;
}

/*!
@brief	Render the slider
@param	CP_POSITION_MODE previousMode - the previous rendering mode
@return void
*//*______________________________________________________________*/
void Slider::renderSlider(CP_POSITION_MODE previousMode)
{
	CP_Settings_ImageMode(CP_POSITION_CENTER);

	//Draw tracker
	CP_Settings_Fill(CP_Color_Create(223, 43, 72, 255));
	CP_Graphics_DrawRectAdvanced(trackerPosition.x, trackerPosition.y, trackerWidth, trackerHeight, 0.f, 10.f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Image_Draw(thumb, thumbPosition.x, thumbPosition.y, thumbWidth, thumbHeight, 255);

	CP_Settings_ImageMode(previousMode);
}

/*!
@brief	Free resources
@param	void
@return void
*//*______________________________________________________________*/
void Slider::freeResources(void)
{
	CP_Image_Free(thumb);
}
