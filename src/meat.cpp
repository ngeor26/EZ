#include "main.h"

bool isFlipping = false;

bool isRaised = false;
bool mogoOn = false;
bool doinkerOn = false;

bool canRaise = true;
bool canMogo = true;
bool canDoinker = true;

int autonState = 0;
bool buttonUnpressed = true;

int numRings = 0;
bool hasSecond = false;

std::string colorStack[2] = {"", ""};

void doFlip() {
  isFlipping = true;
  if (((autonState == 0 || autonState == 1 || autonState == 2) && colorStack[0] == "Red") || ((autonState == 3 || autonState == 4 || autonState == 5) && colorStack[0] == "Blue")) {
    flipper.move_absolute(-700, 150);
  } else {
    flipper.move_absolute(-1060, 200);
  }
  pros::delay(500);
  flipper.move_absolute(0, 55);
  pros::delay(800);
  isFlipping = false;
}

void toggleArm() {
  canRaise = false;
  arm.set_value(!isRaised);
  isRaised = !isRaised;
  pros::delay(500);
  canRaise = true;
}

void raiseMacro() {
  canRaise = false;
  if (!isRaised) {
    arm.set_value(!isRaised);
    isRaised = !isRaised;
  }
  isFlipping = true;
  flipper.move_absolute(-1700, 200);
  pros::delay(300);
  isFlipping = false;
  canRaise = true;
}

void toggleMogo() {
  canMogo = false;
  mogo.set_value(!mogoOn);
  mogoOn = !mogoOn;
  if (!mogoOn) {
    master.print(0, 0, "%s", "Mogo on ");
  } else {
    master.print(0, 0, "%s", "Mogo off");
  }

  pros::delay(250);
  canMogo = true;
}

void toggleDoinker() {
  canDoinker = false;
  doinker.set_value(!doinkerOn);
  doinkerOn = !doinkerOn;
  pros::delay(500);
  canDoinker = true;
}

void shaky() {
  isFlipping = true;
  flipper.move_velocity(-35);
  pros::delay(250);
  flipper.move_absolute(0, 55);
  pros::delay(250);
  isFlipping = false;
}

void update_colorStack() {
  // while (true) {
    pros::vision_object_s_t object_arr[3];

    int y1 = 0;
    int y2 = 0;
    std::string color1 = "";
    std::string color2 = "";

    vision.read_by_size(0, 3, object_arr);

    for (int i = 0; i < 3; i++) {
      if (object_arr[i].height > 150 && (object_arr[i].signature == 1 || object_arr[i].signature == 2)) {
        if (y1 != 0) {
          y2 = object_arr[i].y_middle_coord;
          color2 = (object_arr[i].signature == 1) ? "Red" : "Blue";
        } else {
          y1 = object_arr[i].y_middle_coord;
          color1 = (object_arr[i].signature == 1) ? "Red" : "Blue";
        }
      }
      if (y2 < y1) {
        colorStack[1] = color2;
        colorStack[0] = color1;
      } else {
        colorStack[1] = color1;
        colorStack[0] = color2;
      }
    }

    std::cout << "Bottom: " + colorStack[0] << " Top: " + colorStack[1] << std::endl;

    // pros::delay(200);
  // }
}

void insideopcontrol() {
  // while (true) {
    hasSecond = ultrasonic.get_value() > 50;

    if (master.get_digital(DIGITAL_R2) && flipper.get_position() > -50 && (!(colorStack[0] != "" && colorStack[1] != "") || master.get_digital(DIGITAL_Y))) {
      intake.move_velocity(-600);
    } else if (master.get_digital(DIGITAL_L2)) {
      intake.move_velocity(550);
    } else {
      intake.move_velocity(0);
    }

    if (!isFlipping) {
      if (master.get_digital(DIGITAL_RIGHT)) {
        flipper.move(-127);
      } else if (master.get_digital(DIGITAL_DOWN)) {
        flipper.move(50);
      } else {
        flipper.brake();
      }
    }

    if (master.get_digital(DIGITAL_B) && canRaise) {
      pros::Task raise_task(toggleArm);
    }

    if (master.get_digital(DIGITAL_A) && canRaise) {
      pros::Task raise_macro(raiseMacro);
    }

    if (master.get_digital(DIGITAL_L1) && canMogo) {
      pros::Task mogo_task(toggleMogo);
    }

    if (master.get_digital(DIGITAL_X) && canDoinker) {
      pros::Task doinker_task(toggleDoinker);
    }

    if (master.get_digital(DIGITAL_R1) && !isFlipping) {
      pros::Task flip_task(doFlip);
    }

    if (master.get_digital(DIGITAL_LEFT) && !isFlipping) {
      pros::Task shake_task(shaky);
    }
  // }
}