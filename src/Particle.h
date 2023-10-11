// #ifndef PARTICLE_H
// #define PARTICLE_H
// #include "Color.h"
// #include <iostream>

// // Particle type - The specific particle in question
// enum Type {
// 	EMPTY,
// 	SAND,
// 	WATER,
// 	SELECTION,
// 	ROCK
// };
// // Particle state - The state of matter the particle is in
// enum State {
// 	NONPHYSICAL,
// 	SOLID,
// 	LIQUID,
// 	GAS,
// 	POWDER
// };

// class Particle {
// public:
// 	Type type;
// 	State state;
// 	float density;

// 	// update - Updates the particle based on the particles around it
// 	virtual void update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right) = 0;

// 	// getTypeName - Returns the name of the particle type as a string
// 	std::string getTypeName() const;

// 	// make particle print out with cout
// 	friend std::ostream &operator<<(std::ostream &os, const Particle &particle);

// 	// Color - Returns the color of the particle based on its type
// 	Color getColor() const;

// 	// Destructor
// 	virtual ~Particle();
// };

// // Empty - A lack of a particle
// class Empty : public Particle {
// public:
// 	Empty();
// 	void update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right);
// };

// // Sand - A particle that falls down and to the left or right
// class Sand : public Particle {
// public:
// 	Sand();
// 	void update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right);
// };

// // Water - A particle that falls down and also flows left and right
// class Water : public Particle {
// public:
// 	Water();
// 	void update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right);
// };

// // Rock - A particle that does not move.
// class Rock : public Particle {
// public:
// 	Rock();
// 	void update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right);
// };

// // Selection - A particle that is used to show the user's selection
// class Selection : public Particle {
// public:
// 	Selection();
// 	void update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right);
// };

// #endif // !PARTICLE_H