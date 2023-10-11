#include <iostream>

// Color struct - Represents a color with RGB values
struct Color {
	float r, g, b;
	Color(float r, float g, float b);
	friend std::ostream &operator<<(std::ostream &os, const Color &color);
};