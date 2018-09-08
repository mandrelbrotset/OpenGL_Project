#pragma once

#include "DrawShapes.h"

class Cube: public DrawShapes
{
public:
	Cube(string textureFilePath);
	void drawCube();
	~Cube();
};

