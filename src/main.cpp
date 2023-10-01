#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

using namespace std;

// Window dimensions
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
// this resolution is 16:9

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Particle Class - Represents a single particle, size of 1 pixel
class Particle {
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
	Particle(Type type = EMPTY) : type(type) {
	}

	void update(Particle *above, Particle *below, Particle *left, Particle *right) {
		// TODO:
		//  Update the particle based on what kind of particle it is
	}

	// make particle print out with cout
	friend ostream &operator<<(ostream &os, const Particle &particle) {
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

// Draw a pixel at the given coordinates with the given color
void drawPixel(int x, int y, Particle::Color color) {
	glBegin(GL_POINTS);
	glColor3f(color.r, color.g, color.b);
	glVertex2f(x, y);
	glEnd();
}

// Function to take RGB value that is between 0 and 255 and convert it to a value between 0 and 1
Particle::Color hexToColor(int hex) {
	float r = ((hex >> 16) & 0xFF) / 255.0f;
	float g = ((hex >> 8) & 0xFF) / 255.0f;
	float b = (hex & 0xFF) / 255.0f;
	return Particle::Color(r, g, b);
}

// Callback function for when the window is resized
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouseEvents(GLFWwindow *window, Particle ***screen, Coord2D &prevMousePos, Coord2D curMousePos) {
	// Separate the previous and current mouse positions into x and y coordinates
	int prevX = prevMousePos.x;
	int prevY = prevMousePos.y;
	int curX = curMousePos.x;
	int curY = curMousePos.y;
	// Hover - Draws a selection particle where the mouse is, on top of the particles layer
	// First clear the selection particle from the position the mouse was at right before this
	if (prevX >= 0 && prevX < WINDOW_WIDTH && prevY >= 0 && prevY < WINDOW_HEIGHT)
		screen[prevY][prevX][2] = Particle();
	// Then set the selection particle at the current mouse position
	if (curX >= 0 && curX < WINDOW_WIDTH && curY >= 0 && curY < WINDOW_HEIGHT)
		screen[curY][curX][2] = Particle(Particle::SELECTION);

	// Left Click - Draws Rock particles where the mouse is. Interpolate between the previous and current mouse positions to draw a line
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		int dx = curX - prevX;
		int dy = curY - prevY;
		int steps = max(abs(dx), abs(dy));
		for (int i = 0; i <= steps; i++) {
			if (steps == 0)
				break;
			int x = prevX + dx * i / steps;
			int y = prevY + dy * i / steps;
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
				screen[y][x][1] = Particle(Particle::ROCK);
			}
		}

	}
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
				screen[y][x][1] = Particle();
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
	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Window", NULL, NULL);
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
	Particle ***screen = new Particle **[WINDOW_HEIGHT];
	for (int y = 0; y < WINDOW_HEIGHT; y++) {
		screen[y] = new Particle *[WINDOW_WIDTH];
		for (int x = 0; x < WINDOW_WIDTH; x++) {
			screen[y][x] = new Particle[3];
			screen[y][x][0] = Particle();
			screen[y][x][1] = Particle();
			screen[y][x][2] = Particle();
		}
	}

	// Keep track of the previous mouse position
	Coord2D prevMousePos = Coord2D(0, 0);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Set background color to dark blue
		Particle::Color bgColor = hexToColor(0x0b0c1e); // Dark Blue - Hex #0B0C1E
		// Clear the screen
		glClearColor(bgColor.r, bgColor.g, bgColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Get the current mouse position
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		Coord2D curMousePos = Coord2D(mouseX, mouseY);

		// Deal with mouse events - left click, right click, hovering, etc.
		mouseEvents(window, screen, prevMousePos, curMousePos);

		// Render all non empty particles
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			for (int x = 0; x < WINDOW_WIDTH; x++) {
				for (int z = 0; z < 3; z++) {
					if (screen[y][x][z].getType() != Particle::EMPTY) {
						drawPixel(x, y, screen[y][x][z].getColor());
					}
				}
			}
		}

		// Update the previous mouse position
		prevMousePos = curMousePos;

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();
}