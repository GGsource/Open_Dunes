#include "Color.h"

// Color struct - Represents a color with RGB values
Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

// make color print out with cout
std::ostream &operator<<(std::ostream &os, const Color &color) {
	os << "(" << color.r << ", " << color.g << ", " << color.b << ")";
	return os;
}