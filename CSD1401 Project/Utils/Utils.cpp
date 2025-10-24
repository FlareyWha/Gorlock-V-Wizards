#include "Utils.h"

bool isAreaClicked(CP_Vector areaPos, float areaWidth, float areaHeight, CP_Vector mousePos)
{
	CP_Vector xLimits = CP_Vector_Set(areaPos.x - areaWidth / 2, areaPos.x + areaWidth / 2);
	CP_Vector yLimits = CP_Vector_Set(areaPos.y - areaHeight / 2, areaPos.y + areaHeight / 2);

	if (mousePos.x >= xLimits.x && mousePos.x <= xLimits.y && mousePos.y >= yLimits.x && mousePos.y <= yLimits.y)
	{
		return true;
	}

	return false;
}

bool isCircleClicked(CP_Vector circlePos, float radius, CP_Vector mousePos)
{
	float distance = CP_Vector_Distance(circlePos, mousePos);

	float distanceSquared = distance * distance;
	float radiusSquared = radius * radius;

	if (distanceSquared < radiusSquared)
	{
		return true;
	}

	return false;
}

bool areCirclesIntersecting(CP_Vector circle1Pos, float circle1Radius, CP_Vector circle2Pos, float circle2Radius)
{
	float distance = CP_Vector_Distance(circle1Pos, circle2Pos);
	float distanceSquared = distance * distance;

	float combinedRadius = circle1Radius + circle2Radius;
	float combinedRadiusSquared = combinedRadius * combinedRadius;

	if (distanceSquared < combinedRadiusSquared)
	{
		return true;
	}

	return false;
}
