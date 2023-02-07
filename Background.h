#pragma once

#include <vector>

#include <string>
#include <cmath>

#include "core.h"
#include "Vector3.h"
#include "Image.h"

struct Background
{
	int backgroundWidth;
	int backgroundHeight;

	Background(std::string &backgroundPath);
	Background();

	Vector3 GetPixel(int x, int y, int outputWidth, int outputHeight);

	std::vector< std::vector< Vector3 > > backgroundPixels;
};