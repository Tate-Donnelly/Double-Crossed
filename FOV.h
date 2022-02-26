#ifndef __FOV_H__
#define __FOV_H__

#include "Object.h"

class FOV : public df::Object {
public: 
	FOV();
	FOV(float x_length, float y_length);
	~FOV();
	float getVisionX();
	void setVisionX(float new_vision_x);
	float getVisionY();
	void setVisionY(float new_vision_y);
private:
	float vision_x;
	float vision_y;
};

#endif // __FOV_H__
