#include "main.h"
#include "globals.hpp"

double calc_drive_curve(double joy_stick_position, float drive_curve_scale) {
  if (drive_curve_scale != 0) {
    return (powf(2.718, -(drive_curve_scale / 10)) +
            powf(2.718, (fabs(joy_stick_position) - 127) / 10) *
                (1 - powf(2.718, -(drive_curve_scale / 10)))) *
           joy_stick_position;
  }
  return joy_stick_position;
}

void opcontrol() {
	cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	right_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    left_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		// Drive
		int forward = calc_drive_curve(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 3.5); // Gain is arbitrarily set to 3.5
		//int forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		
		int turn = calc_drive_curve(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 3.5);
		//int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.arcade(forward, turn);

		// Intake
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intake.move(100);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake.move(-100);
		} else {
			intake.brake();
		}

		// Flywheel
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			cata.move(127);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			cata.move(-127);
		} else {
			cata.brake();
		}
		
		// Lift
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			front_piston.set_value(!frontPiston);
			frontPiston = !frontPiston;
			pros::delay(500);
		}

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			front_piston.set_value(!frontPiston);
			frontPiston = !frontPiston;
			back_piston.set_value(!backPiston);
			backPiston = !backPiston;
			pros::delay(500);
		}

		// Park
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			park.set_value(!parkPos);
			parkPos = !parkPos;
			pros::delay(500);
		}
		
		//controller.print(0,0, "CataPos: %d", limit_switch.get_value());
		//pros::screen::print(TEXT_SMALL, 3, "Cata Position: %f", limit_switch.get_value());

		pros::delay(20);
	}
} 
