#include "main.h"
#include "globals.hpp"

void opcontrol() {
	cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	while (true) {
		// Drive
		int forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(forward, turn);

		// Intake
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intake.move(127);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake.move(-127);
		} else {
			intake.brake();
		}

		// Cata
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !cataPressed) {
			cataPressed = true;
		}

		if (!limit_switch.get_value() && cataPressed) {
			cata.move(80);
		} else {
			if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
				cata.move(80);
				pros::delay(500);
			} else {
				cata.brake();
			}
		}

		/*
		// Wings
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			if (wingstate) {
				wings.set_value(false);
				wingstate = false;
				pros::delay(500);
			} else {
				wings.set_value(true);
				wingstate = true;
				pros::delay(500);
			}
		}
		*/
		
		controller.print(0,0, "CataPos: %d", limit_switch.get_value());
		//pros::screen::print(TEXT_SMALL, 3, "Cata Position: %f", limit_switch.get_value());

		pros::delay(20);
	}
} 
