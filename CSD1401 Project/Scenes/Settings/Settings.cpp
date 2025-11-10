#include "cprocessing.h"
#include "Settings.h"
#include "../Game/Game.h"
#include "../../Utils/Slider.h"
#include "../../Utils/Utils.h"
#include "../../System/SettingsManager.h"
#include "../../System/SoundManager.h"
#include "../../System/SceneManager.h"
#include <iostream>
#include <stdlib.h>

CP_Font myFont;


//Volume and SFX slider
Slider slider[2];
int currentActiveSliderIndex = -1;
SceneManager* scenes;
SettingsManager* settings;
SoundManager* sound;

void settingsInit(void)
{
	myFont = CP_Font_Load("./Assets/Fonts/KenneyFonts/Kenney Mini.ttf");

	settings = SettingsManager::GetInstance();
	sound = SoundManager::GetInstance();

	//0 is BGM
	slider[0] = Slider(CP_Vector_Set(800, 300), settings->getBGMVolume());

	//1 is SFX
	slider[1] = Slider(CP_Vector_Set(800, 600), settings->getSFXVolume());
}

void settingsUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Font_Set(myFont);
	CP_Font_DrawText("Settings", 100, 100);

	if (CP_Input_KeyReleased(KEY_Q))
	{
		scenes->ChangeScenes(Scenes::MAIN_MENU_SCENE);
	}
	for (int i = 0; i < 2; i++)
	{
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
		{
			CP_Vector mousePos = CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY());

			if (currentActiveSliderIndex == -1 && isAreaClicked(slider[i].getThumbPosition(), slider[i].getThumbWidth(), slider[i].getThumbHeight(), mousePos))
			{
				currentActiveSliderIndex = i;
			}

			if (currentActiveSliderIndex == i)
			{
				slider[i].updateThumbPositionBasedOnPosition(mousePos);
				
				switch (i)
				{
				case 0:
					settings->setBGMVolume(slider[i].getSliderValue());
					std::cout << "Volume: " << settings->getBGMVolumeLerp() << std::endl;
					sound->refreshBGMVolume(settings->getBGMVolumeLerp());
					break;

				case 1:
					settings->setSFXVolume(slider[i].getSliderValue());
					sound->refreshSFXVolume(settings->getSFXVolumeLerp());
					break;

				default:
					break;
				}
			}
		}
		else
		{
			currentActiveSliderIndex = -1;
		}

		slider[i].renderSlider(CP_POSITION_CENTER);
	}

	//Draw text for sliders
	char buffer[50] = { 0 };

	sprintf_s(buffer, 50, "BGM: %i", settings->getBGMVolume());
	CP_Font_DrawText(buffer, 800, 200);

	sprintf_s(buffer, 50, "SFX: %i", settings->getSFXVolume());
	CP_Font_DrawText(buffer, 800, 500);
}

void settingsExit(void)
{
	CP_Font_Free(myFont);
	
	for (int i = 0; i < 2; i++)
	{
		slider[i].freeResources();
	}
}
