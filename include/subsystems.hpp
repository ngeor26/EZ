#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(6, pros::v5::MotorGears::blue);

inline pros::Motor flipper(7, pros::v5::MotorGears::red);

inline pros::adi::DigitalOut mogo('C');

inline pros::adi::DigitalOut doinker('E');

inline pros::adi::DigitalOut arm('D');

inline pros::adi::Button limit_switch('F');

inline pros::adi::Ultrasonic ultrasonic('G', 'H');

inline pros::Vision vision(15);

inline pros::Imu imu(1);

inline pros::Rotation rotation(-11);