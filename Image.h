#pragma once

#include <vector>

struct Color {
	double r, g, b;

	Color();
	Color(double r, double g, double b);
	~Color();
};

class Image
{
public:
	Image();

	Image(long long int width, long long int height);
	~Image();
	
	Color GetColor(long long int x, long long int y) const;
	void SetColor(const Color& color, long long int x, long long int y);
	void FillImage(const Color& color);

	void Read(const char* path);
	void Export(const char* path) const;

	unsigned long long int m_width;
	unsigned long long int m_height;

private:
	std::vector<Color> m_colors;
};

