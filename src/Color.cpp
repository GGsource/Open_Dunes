// #include "Color.h"

// // Color struct - Represents a color with RGB values
// Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

// // make color print out with cout
// std::ostream &operator<<(std::ostream &os, const Color &color) {
// 	os << "(" << color.r << ", " << color.g << ", " << color.b << ")";
// 	return os;
// }

// // Function to take RGB value that is between 0 and 255 and convert it to a value between 0 and 1
// Color Color::hexToColor(int hex) {
// 	float r = ((hex >> 16) & 0xFF) / 255.0f;
// 	float g = ((hex >> 8) & 0xFF) / 255.0f;
// 	float b = (hex & 0xFF) / 255.0f;
// 	return Color(r, g, b);
// }