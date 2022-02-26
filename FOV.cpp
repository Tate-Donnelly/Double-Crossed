#include "FOV.h"

FOV::FOV()
{
	setType("FOV");
	setSolidness(df::SOFT);
}

FOV::FOV(float x_length, float y_length)
{
	setType("FOV");
	setSolidness(df::SOFT);
	setVisionX(x_length);
	setVisionY(y_length);
}

FOV::~FOV()
{
}

float FOV::getVisionX()
{
	return vision_x;
}

void FOV::setVisionX(float new_vision_x)
{
	vision_x = new_vision_x;
}

float FOV::getVisionY()
{
	return vision_y;
}

void FOV::setVisionY(float new_vision_y)
{
	vision_y = new_vision_y;
}
