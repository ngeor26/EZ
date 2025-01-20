#pragma once

#include <iostream>
#include <string>

#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/vision.hpp"

// Global variables
extern bool isFlipping;
extern bool isRaised;
extern bool mogoOn;
extern bool doinkerOn;

extern bool canRaise;
extern bool canMogo;
extern bool canDoinker;

extern int autonState;
extern bool buttonUnpressed;

extern int numRings;
extern bool hasSecond;

extern std::string colorStack[2];

// Function declarations
void doFlip();
void toggleArm();
void raiseMacro();
void toggleMogo();
void toggleDoinker();
void shaky();
void update_stack();
void insideopcontrol();