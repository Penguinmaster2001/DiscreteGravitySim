#include "Background.h"

Image image;

Background::Background(std::string &backgroundPath)
{
	image.Read(backgroundPath.c_str());

	backgroundWidth = image.m_width;
	backgroundHeight = image.m_height;

	//init background pixels vector of vectors (dynamic 2d array)
	backgroundPixels.resize(backgroundWidth);

	for (int i = 0; i < backgroundWidth; ++i)
	{
		backgroundPixels[i].resize(backgroundHeight);
	}

	for (int x = 0; x < image.m_width; x++)
	{
		for (int y = 0; y < image.m_height; y++)
		{
			Color pixelColor = image.GetColor(x, y);

			backgroundPixels[x][y] = Vector3(pixelColor.r, pixelColor.g, pixelColor.b);
		}
		//std::cout << "bg pixel at " << x << ", 0: " << backgroundPixels[x][10] << "\n";
	}
}

Background::Background()
{//succ
	backgroundHeight = 0;
	backgroundWidth  = 0;
}

Vector3 Background::GetPixel(int x, int y, int outputWidth, int outputHeight)
{
	int scaledX = (double)x / (double)outputWidth * (backgroundWidth - 1);
	int scaledY = (double)y / (double)outputHeight * (backgroundHeight - 1);

	//std::cout << "bg pixel at: " << scaledX << ", " << scaledY << ": " <<  backgroundPixels[scaledX][scaledY] << " || ";

	double intensity = 1.0;

	Vector3 output = Vector3(1.0, 1.0, 0.0);

	try
	{
		if (scaledX > 1920 || scaledX < 0 || scaledY > 1080 || scaledY < 0)
		{
			std::cout << "";
		}

		output = intensity * backgroundPixels[scaledX][scaledY];
	}
	catch(...) //when ur a good programmer
	{
		std::string error = "Background error" + std::to_string(x) + " " + std::to_string(outputWidth) + " " + std::to_string(backgroundWidth) + " " + std::to_string(scaledX) + "\n" +
			std::to_string(y) + " " + std::to_string(outputHeight) + " " + std::to_string(backgroundHeight) + " " + std::to_string(scaledY) + "\n\n";

		std::cout << error;

		output = Vector3(0.0, 1.0, 1.0);
	}

	return output;

	//return Vector3(0.0);
}
