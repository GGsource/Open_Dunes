#define GLFW_INCLUDE_NONE
// #include "Color.h"
// #include "Particle.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <random>

using namespace std;

// Window dimensions
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
// this resolution is 16:9

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Particle Class - Represents a single particle, size of 1 pixel
class Prtcl {
public:
	// Particle types
	enum Type { EMPTY,
				SAND,
				WATER,
				SELECTION,
				ROCK };

	// Color struct - Represents a color with RGB values
	struct Color {
		float r, g, b;
		Color(float r, float g, float b) : r(r), g(g), b(b) {
		}
		// print with cout
		friend ostream &operator<<(ostream &os, const Color &color) {
			os << "(" << color.r << ", " << color.g << ", " << color.b << ")";
			return os;
		}
	};

	// Constructor - Sets the type of the particle to empty by default, otherwise sets the type to the given type
	Prtcl(Type type = EMPTY) : type(type) {
	}

	void update(Prtcl *north, Prtcl *south, Prtcl *left, Prtcl *east, Prtcl *northWest, Prtcl *northEast, Prtcl *southWest, Prtcl *southEast) {
		// TODO:
		// std::cout << "Particle is updating!" << std::endl;
		//  Update the particle based on what kind of particle it is
		if (type == SAND) {
			// Randomize the direction the sand falls in
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, 1);
			Prtcl *sandDirections[3];
			sandDirections[0] = south;
			sandDirections[1] = (dis(gen) == 0) ? southWest : southEast;
			sandDirections[2] = (dis(gen) == 0) ? southEast : southWest;
			for (Prtcl *direction : sandDirections) {
				if (direction != nullptr && (direction->type == EMPTY || direction->type == WATER)) {
					// std::cout << "Sand is falling!" << std::endl;
					// Fall down
					Prtcl temp = *direction;
					*direction = *this;
					*this = temp;
					break;
					// DONE: This crashes if the sand reaches the bottom of the screen.
				}
			}
		}
	}

	// make particle print out with cout
	friend ostream &operator<<(ostream &os, const Prtcl &particle) {
		os << "Particle of Type " << particle.getTypeName() << " with color " << particle.getColor() << std::endl;
		return os;
	}

	Color getColor() const {
		switch (type) {
		case SAND:
			return Color(1.0f, 0.8f, 0.0f); // Yellow - Hex #FFFF00
		case WATER:
			return Color(0.0f, 0.0f, 1.0f); // Blue - Hex #0000FF
		case ROCK:
			return Color(0.5f, 0.5f, 0.5f); // Gray - Hex #7F7F7F
		case SELECTION:
			return Color(0.5f, 1.0f, 0.5f); // Green - Hex #7FFF7F
		default:
			return Color(1.0f, 0.0f, 0.0f); // red - Hex #FF0000
		}
	}

	Type getType() const {
		return type;
	}

	string getTypeName() const {
		switch (type) {
		case SAND:
			return "Sand";
		case WATER:
			return "Water";
		case ROCK:
			return "Rock";
		case SELECTION:
			return "Selection";
		default:
			return "Empty";
		}
	}

private:
	Type type;
};

class Coord2D {
public:
	double x, y;
	Coord2D(double x, double y) : x(x), y(y) {
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Callback function for when the window is resized
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}
// Draw a pixel at the given coordinates with the given color
void drawPixel(int x, int y, Prtcl::Color color) {
	glBegin(GL_POINTS);
	glColor3f(color.r, color.g, color.b);
	glVertex2f(x, y);
	glEnd();
}

// Function to take RGB value that is between 0 and 255 and convert it to a value between 0 and 1
Prtcl::Color hexToColor(int hex) {
	float r = ((hex >> 16) & 0xFF) / 255.0f;
	float g = ((hex >> 8) & 0xFF) / 255.0f;
	float b = (hex & 0xFF) / 255.0f;
	return Prtcl::Color(r, g, b);
}

// BrushStroke - draws particles in a circle around the given coordinates
void brushStroke(Prtcl ***screen, int x, int y, int brushSize, Prtcl::Type type, bool selection = false) {
	int layer = 1;
	if (selection)
		layer = 2;
	// fill the area within 5 pixels of the mouse in a circle - hardcoded for now to test
	for (int brushY = y - brushSize; brushY <= y + brushSize; brushY++) {
		for (int brushX = x - brushSize; brushX <= x + brushSize; brushX++) {
			if (brushX >= 0 && brushX < WINDOW_WIDTH && brushY >= 0 && brushY < WINDOW_HEIGHT) {
				if ((brushX - x) * (brushX - x) + (brushY - y) * (brushY - y) <= brushSize * brushSize)
					screen[brushY][brushX][layer] = Prtcl(type);
			}
		}
	}
}

// clearSelection - clears the selection particle from the given coordinates
void clearSelection(Prtcl ***screen, int x, int y, int brushSize) {
	brushStroke(screen, x, y, brushSize, Prtcl::EMPTY, true);
}

void mouseEvents(GLFWwindow *window, Prtcl ***screen, Coord2D &prevMousePos, Coord2D curMousePos, int brushSize) {
	// Separate the previous and current mouse positions into x and y coordinates
	int prevX = prevMousePos.x;
	int prevY = prevMousePos.y;
	int curX = curMousePos.x;
	int curY = curMousePos.y;
	// Hover - Draws a selection particle where the mouse is, on top of the particles layer
	// First clear the selection particle from the position the mouse was at right before this
	if (prevX >= 0 && prevX < WINDOW_WIDTH && prevY >= 0 && prevY < WINDOW_HEIGHT)
		clearSelection(screen, prevX, prevY, brushSize + 1); // Brush size + 1 to clear the selection particle from the previous mouse position, which could have been larger than the current brush size
	// Then set the selection particle at the current mouse position
	if (curX >= 0 && curX < WINDOW_WIDTH && curY >= 0 && curY < WINDOW_HEIGHT)
		brushStroke(screen, curX, curY, brushSize, Prtcl::SELECTION, true);

	// Left Click - Draws Rock particles where the mouse is. Interpolate between the previous and current mouse positions to draw a line
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		// FIXME: A Left click is not detected when using tablet and drawing pen until the pen has been moved a certain distance.
		// This is because the tablet is not sending mouse events, but rather tablet events. Need to find a way to detect tablet events and react accordingly.
		int dx = curX - prevX;
		int dy = curY - prevY;
		int steps = max(abs(dx), abs(dy));
		for (int i = 0; i <= steps; i++) {
			if (steps == 0)
				break;
			int x = prevX + dx * i / steps;
			int y = prevY + dy * i / steps;
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
				brushStroke(screen, x, y, brushSize, Prtcl::SAND);
			}
		}

	}
	// TODO: Replace this with a system where drawing, erasing, and any other cursor actions happen through left click, we just swap the state of the current cursor tool.
	// Right Click - Erases particles where the mouse is. Interpolate between the previous and current mouse positions to draw a line
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		int dx = curX - prevX;
		int dy = curY - prevY;
		int steps = max(abs(dx), abs(dy));
		for (int i = 0; i <= steps; i++) {
			if (steps == 0)
				break;
			int x = prevX + dx * i / steps;
			int y = prevY + dy * i / steps;
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
				brushStroke(screen, x, y, brushSize, Prtcl::ROCK);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of Helper Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Main function
int main() {
	// Initialize GLFW and create a window
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Open Dunes Project", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Get screen resolution
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	const int SCREEN_WIDTH = mode->width;
	const int SCREEN_HEIGHT = mode->height;
	// Change the position the window is originally placed at to be in the center of the screen
	glfwSetWindowPos(window, (SCREEN_WIDTH - WINDOW_WIDTH) / 2, (SCREEN_HEIGHT - WINDOW_HEIGHT) / 2);

	// Load OpenGL functions using GLAD
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Switch from normalized coordinates to pixel coordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);

	// Create a 3D array of pixels to represent the screen, with a depth of 3 to include a layer over the screen and one behind it
	Prtcl ***screen = new Prtcl **[WINDOW_HEIGHT];
	for (int y = 0; y < WINDOW_HEIGHT; y++) {
		screen[y] = new Prtcl *[WINDOW_WIDTH];
		for (int x = 0; x < WINDOW_WIDTH; x++) {
			screen[y][x] = new Prtcl[3];
			screen[y][x][0] = Prtcl(); // Background layer
			screen[y][x][1] = Prtcl(); // Main Particle layer
			screen[y][x][2] = Prtcl(); // Selection layer
		}
	}

	// Keep track of the previous mouse position
	Coord2D prevMousePos = Coord2D(0, 0);
	int brushSize = 1;	  // Keep track of how big the user wants the brush to be
	int framesPassed = 0; // Keep track of how many frames have passed to limit brush size change rate
	int frameCap = 15;	  // Limit the brush size change rate to once every 15 frames

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Set background color to dark blue
		Prtcl::Color bgColor = hexToColor(0x0b0c1e); // Dark Blue - Hex #0B0C1E
		// Clear the screen
		glClearColor(bgColor.r, bgColor.g, bgColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Get the current mouse position
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		Coord2D curMousePos = Coord2D(mouseX, mouseY);

		// Check if the = key is pressed to increase the brush size, and the - key is pressed to decrease the brush size
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS && framesPassed >= frameCap) {
			// IDEA: Consider making brush size increase/decrease exponentially instead of linearly
			// IDEA: Implement pen pressure sensitivity to change brush size using a drawing tablet
			brushSize++;
			framesPassed = 0;
		} else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS && brushSize > 1 && framesPassed >= frameCap) {
			clearSelection(screen, curMousePos.x, curMousePos.y, brushSize);
			brushSize--;
			framesPassed = 0;
		}

		// Deal with mouse events - left click, right click, hovering, etc.
		mouseEvents(window, screen, prevMousePos, curMousePos, brushSize);

		// Update all particles
		for (int y = WINDOW_HEIGHT - 1; y >= 0; y--) {
			for (int x = WINDOW_WIDTH - 1; x >= 0; x--) {
				if (screen[y][x][1].getType() != Prtcl::EMPTY) {
					// Check if each direction is within the bounds of the screen, if not send a nullptr
					Prtcl *north = (y - 1 >= 0 && y - 1 < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH) ? &screen[y - 1][x][1] : nullptr;
					Prtcl *south = (y + 1 >= 0 && y + 1 < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH) ? &screen[y + 1][x][1] : nullptr;
					Prtcl *left = (y >= 0 && y < WINDOW_HEIGHT && x - 1 >= 0 && x - 1 < WINDOW_WIDTH) ? &screen[y][x - 1][1] : nullptr;
					Prtcl *right = (y >= 0 && y < WINDOW_HEIGHT && x + 1 >= 0 && x + 1 < WINDOW_WIDTH) ? &screen[y][x + 1][1] : nullptr;
					Prtcl *northWest = (y - 1 >= 0 && y - 1 < WINDOW_HEIGHT && x - 1 >= 0 && x - 1 < WINDOW_WIDTH) ? &screen[y - 1][x - 1][1] : nullptr;
					Prtcl *northEast = (y - 1 >= 0 && y - 1 < WINDOW_HEIGHT && x + 1 >= 0 && x + 1 < WINDOW_WIDTH) ? &screen[y - 1][x + 1][1] : nullptr;
					Prtcl *southWest = (y + 1 >= 0 && y + 1 < WINDOW_HEIGHT && x - 1 >= 0 && x - 1 < WINDOW_WIDTH) ? &screen[y + 1][x - 1][1] : nullptr;
					Prtcl *southEast = (y + 1 >= 0 && y + 1 < WINDOW_HEIGHT && x + 1 >= 0 && x + 1 < WINDOW_WIDTH) ? &screen[y + 1][x + 1][1] : nullptr;
					screen[y][x][1].update(north, south, left, right, northWest, northEast, southWest, southEast);
				}
			}
		}

		// Render all non empty particles
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			for (int x = 0; x < WINDOW_WIDTH; x++) {
				for (int z = 0; z < 3; z++) {
					if (screen[y][x][z].getType() != Prtcl::EMPTY) {
						drawPixel(x, y, screen[y][x][z].getColor());
					}
				}
			}
		}

		// Draw UI
		// TODO: Implement UI
		// renderUI(window, brushSize);
		//

		prevMousePos = curMousePos; // Update the previous mouse position
		if (framesPassed < frameCap)
			framesPassed++; // Increment the number of frames passed up to 10

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();
}

// TODO: Improve sand by randomizing the first direction it tries to fall in before trying the opposite. This will make it look more natural.
// TODO: Speed up the rate at which sand falls.