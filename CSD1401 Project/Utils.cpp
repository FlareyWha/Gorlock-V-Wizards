#include "Utils.h"
#include "cprocessing.h"
int Utils::isRectClicked(float height, float width, float rectX, float rectY, float mouseX, float mouseY)
{
    float paddingX = width / 2.0f;
    float paddingY = height / 2.0f;
    if (mouseX >= rectX - paddingX && mouseX <= rectX + paddingX && mouseY >= rectY - paddingY && mouseY <= rectY + paddingY)
        return 1;
    else
        return 0;
}

int Utils::isMouseWithinArea(float top, float bottom, float left, float right,float mouseX,float mouseY)
{
    return 0;
}

