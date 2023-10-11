// #include "Particle.h"

// ///////////////////////////////////////////////////////////////////
// // Main Particle Abstract Class
// ///////////////////////////////////////////////////////////////////

// // getTypeName - Returns the name of the particle type as a string
// std::string Particle::getTypeName() const {
// 	switch (type) {
// 	case SAND:
// 		return "Sand";
// 	case WATER:
// 		return "Water";
// 	case ROCK:
// 		return "Rock";
// 	case SELECTION:
// 		return "Selection";
// 	default:
// 		return "Empty";
// 	}
// }

// // operator<< - make particle print out with cout
// std::ostream &operator<<(std::ostream &os, const Particle &particle) {
// 	os << "Particle of Type " << particle.getTypeName() << " with color " << particle.getColor() << std::endl;
// 	return os;
// }

// // getColor - Returns the color of the particle based on its type
// Color Particle::getColor() const {
// 	switch (type) {
// 	case SAND:
// 		return Color(1.0f, 0.8f, 0.0f); // Yellow - Hex #FFFF00
// 	case WATER:
// 		return Color(0.0f, 0.0f, 1.0f); // Blue - Hex #0000FF
// 	case ROCK:
// 		return Color(0.5f, 0.5f, 0.5f); // Gray - Hex #7F7F7F
// 	case SELECTION:
// 		return Color(0.5f, 1.0f, 0.5f); // Green - Hex #7FFF7F
// 	default:
// 		return Color(1.0f, 0.0f, 0.0f); // red - Hex #FF0000
// 	}
// }

// // Destructor
// Particle::~Particle() {}

// ///////////////////////////////////////////////////////////////////
// // Particle Subclasses
// ///////////////////////////////////////////////////////////////////

// // 🍃 Empty - A lack of a particle
// Empty::Empty() {
// 	type = EMPTY;
// 	state = NONPHYSICAL;
// 	density = 0.0f;
// }
// // Empty Update - An empty particle does not move so it does not need to be updated
// void Empty::update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right) {}

// // ⌛ Sand - A particle that falls down and to the left or right
// Sand::Sand() {
// 	type = SAND;
// 	state = POWDER;
// 	density = 1.0f;
// }
// // Sand Update - A sand particle falls down and to the left or right
// void Sand::update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right) {
// 	Particle *temp;
// 	// If there is nothing below, there is liquid, or there is a powder that is less dense than this sand particle, then fall down
// 	if (below->type == EMPTY || below->state == LIQUID || (below->state == POWDER && below->density < self->density)) {
// 		*temp = *below;
// 		*below = *self;
// 		*self = *temp;
// 	} else if (left->type == EMPTY || left->state == LIQUID || (left->state == POWDER && left->density < self->density)) {
// 		*temp = *left;
// 		*left = *self;
// 		*self = *temp;
// 	} else if (right->type == EMPTY || right->state == LIQUID || (right->state == POWDER && right->density < self->density)) {
// 		*temp = *right;
// 		*right = *self;
// 		*self = *temp;
// 	}
// 	// TESTME: Does this work?
// }

// // 💦 Water - A particle that falls down and also flows left and right
// Water::Water() {
// 	type = WATER;
// 	state = LIQUID;
// 	density = 0.5f;
// }
// // Water Update - A water particle falls down and also flows left and right
// void Water::update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right) {
// 	Particle *temp;
// 	// If there is nothing below or there is a liquid that is less dense than this water particle, then fall down
// 	if (below->type == EMPTY || (below->state == LIQUID && below->density < self->density)) {
// 		*temp = *below;
// 		*below = *self;
// 		*self = *temp;
// 	} else if (left->type == EMPTY || (left->state == LIQUID && left->density < self->density)) {
// 		*temp = *left;
// 		*left = *self;
// 		*self = *temp;
// 	} else if (right->type == EMPTY || (right->state == LIQUID && right->density < self->density)) {
// 		*temp = *right;
// 		*right = *self;
// 		*self = *temp;
// 	}
// }

// // 🪨 Rock - A particle that does not move.
// Rock::Rock() {
// 	type = ROCK;
// 	state = SOLID;
// 	density = 10.0f;
// }
// // Rock Update - A rock does not move so it does not need to be updated
// void Rock::update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right) {}

// // 🎯 Selection - A particle that is used to show the user's selection
// Selection::Selection() {
// 	type = SELECTION;
// 	state = NONPHYSICAL;
// 	density = 0.0f;
// }
// // Selection Update - A selection particle does is not a real particle so it does not need to be updated
// void Selection::update(Particle *self, Particle *above, Particle *below, Particle *left, Particle *right) {}