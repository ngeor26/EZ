#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "pros/rotation.hpp"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(6, pros::v5::MotorGears::blue);

inline pros::Motor flipper(7, pros::v5::MotorGears::red);

inline ez::PID flipperPID{0.45, 0, 0, 0, "Flippa"};

inline pros::Rotation flipperRotation(3);

inline pros::adi::DigitalOut mogo('C');

inline pros::adi::DigitalOut doinker('E');

inline pros::adi::DigitalOut arm('D');

inline pros::adi::DigitalIn limit_switch('F');

inline pros::adi::Ultrasonic ultrasonic('G', 'H');

inline pros::Vision vision(15);

inline pros::Imu imu(1);

inline pros::Rotation rotation(-11);