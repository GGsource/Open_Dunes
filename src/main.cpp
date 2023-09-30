#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

using namespace std;

// Window dimensions
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
// this resolution is 16:9

// Particle Class - Represents a single particle, size of 1 pixel
class Particle {
public:
	// Particle types
	enum Type { EMPTY,
				SAND,
				WATER,
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
			return Color(1.0f, 0.8f, 0.0f); // Yellow
		case WATER:
			return Color(0.0f, 0.0f, 1.0f); // Blue
		case ROCK:
			return Color(0.5f, 0.5f, 0.5f); // Gray
		default:
			return Color(1.0f, 0.0f, 0.0f); // red
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
		default:
			return "Empty";
		}
	}

private:
	Type type;
};

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

// Main function
int main() {
	// // Initialize GLFW
	// if (!glfwInit()) {
	// 	cout << "Failed to initialize GLFW" << endl;
	// 	return -1;
	// }
	// // Get screen resolution
	// const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	// const int SCREEN_WIDTH = mode->width;
	// const int SCREEN_HEIGHT = mode->height;
	// std::cout << "Screen resolution: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << std::endl;
	// std::cout << "Window resolution: " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << std::endl;
	// // Set GLFW window properties
	// glfwWindowHint(GLFW_SAMPLES, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// GLFWwindow *window;
	// // Create GLFW window
	// window =
	// 	glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Open Dunes", NULL, NULL);
	// if (window == NULL) {
	// 	cout << "Failed to open GLFW window" << endl;
	// 	return -1;
	// }
	// // Make the window's context the current one
	// glfwMakeContextCurrent(window);

	// // Initialize GLAD
	// if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	// 	cout << "Failed to initialize GLAD" << endl;
	// 	return -1;
	// }

	// // Set the viewport
	// glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// // Change the position the window is originally placed at to be in the center of the screen
	// glfwSetWindowPos(window, (SCREEN_WIDTH - WINDOW_WIDTH) / 2, (SCREEN_HEIGHT - WINDOW_HEIGHT) / 2);

	// // // Create a 2D array of pixels to represent the screen
	// // Particle screen[WINDOW_HEIGHT][WINDOW_WIDTH];
	// // // Initialize the screen to be empty
	// // for (int y = 0; y < WINDOW_HEIGHT; y++) {
	// // 	for (int x = 0; x < WINDOW_WIDTH; x++) {
	// // 		screen[y][x] = Particle();
	// // 	}
	// // }

	// // Main loop
	// while (!glfwWindowShouldClose(window)) {
	// 	// // First clear the screen
	// 	// glClear(GL_COLOR_BUFFER_BIT);
	// 	// // First update particle positions
	// 	// for (int y = 0; y < WINDOW_HEIGHT; y++) {
	// 	// 	for (int x = 0; x < WINDOW_WIDTH; x++) {
	// 	// 		Particle *above = y > 0 ? &screen[y - 1][x] : nullptr;
	// 	// 		Particle *below = y < WINDOW_HEIGHT - 1 ? &screen[y + 1][x] : nullptr;
	// 	// 		Particle *left = x > 0 ? &screen[y][x - 1] : nullptr;
	// 	// 		Particle *right = x < WINDOW_WIDTH - 1 ? &screen[y][x + 1] : nullptr;

	// 	// 		screen[y][x].update(above, below, left, right);
	// 	// 	}
	// 	// }

	// 	// // Then render the particles
	// 	// for (int y = 0; y < WINDOW_HEIGHT; y++) {
	// 	// 	for (int x = 0; x < WINDOW_WIDTH; x++) {
	// 	// 		drawPixel(x, y, screen[y][x].getColor());
	// 	// 		std::cout << screen[y][x] << std::endl;
	// 	// 	}
	// 	// }

	// 	// Clear the screen
	// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// 	glClear(GL_COLOR_BUFFER_BIT);

	// 	// Draw a single pixel in the center of the screen
	// 	glBegin(GL_POINTS);
	// 	glColor3f(1.0f, 1.0f, 1.0f); // White color
	// 	glVertex2f(0.0f, 0.0f);		 // Center of the screen in OpenGL's coordinate system
	// 	glEnd();

	// 	glfwSwapBuffers(window);
	// 	glfwPollEvents();
	// }

	// // Terminate GLFW
	// glfwTerminate();
	// return 0;

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

	// Create a 2D array of pixels to represent the screen
	Particle **screen = new Particle *[WINDOW_HEIGHT];
	// Initialize the screen to be empty
	for (int y = 0; y < WINDOW_HEIGHT; y++) {
		screen[y] = new Particle[WINDOW_WIDTH];
		for (int x = 0; x < WINDOW_WIDTH; x++) {
			screen[y][x] = Particle();
		}
	}

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Set background color to dark blue
		Particle::Color bgColor = hexToColor(0x0b0c1e);
		// Clear the screen
		glClearColor(bgColor.r, bgColor.g, bgColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Check if the mouse is currently being left clicked to add particles
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			// Get the mouse position
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			// fill the area within 5 pixels of the mouse in a circle
			for (int y = mouseY - 5; y <= mouseY + 5; y++) {
				for (int x = mouseX - 5; x <= mouseX + 5; x++) {
					if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
						if ((x - mouseX) * (x - mouseX) + (y - mouseY) * (y - mouseY) <= 25) {
							screen[y][x] = Particle(Particle::ROCK);
						}
					}
				}
			}
		}
		// Check if the mouse is currently being right clicked to erase particles
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			// Get the mouse position
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			// erase the area within 5 pixels of the mouse in a circle
			for (int y = mouseY - 5; y <= mouseY + 5; y++) {
				for (int x = mouseX - 5; x <= mouseX + 5; x++) {
					if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
						if ((x - mouseX) * (x - mouseX) + (y - mouseY) * (y - mouseY) <= 25) {
							screen[y][x] = Particle();
						}
					}
				}
			}
		}

		// Render all non empty particles
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			for (int x = 0; x < WINDOW_WIDTH; x++) {
				if (screen[y][x].getType() != Particle::EMPTY) {
					drawPixel(x, y, screen[y][x].getColor());
				}
			}
		}

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();
}