#include "main.h"
#include "globals.hpp"

// Team 5225A drive curve function
double calc_drive_curve(double joy_stick_position, float drive_curve_scale) {
  if (drive_curve_scale != 0) {
    return (powf(2.718, -(drive_curve_scale / 10)) +
            powf(2.718, (fabs(joy_stick_position) - 127) / 10) *
                (1 - powf(2.718, -(drive_curve_scale / 10)))) *
           joy_stick_position;
  }
  return joy_stick_position;
}

double drive_temp;

void opcontrol() {
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	right_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    left_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		// Drive
		int forward = calc_drive_curve(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 3.5);		
		int turn = calc_drive_curve(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 3.5);
		chassis.arcade(forward, turn);

		// Intake
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intake.move(127);
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake.move(-127);
		} else {
			intake.brake();
		}

		// Flywheel
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) { 
			flywheel_active = !flywheel_active;
		}

		if (flywheel_active) {
			flywheel.set_velocity(450);
		} else {
			flywheel.set_velocity(0);
		}
		
		// Lift
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			lift.set_value(!lift_state);
			lift_state = !lift_state;
		}

		// Park
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			park.set_value(!park_state);
			park_state = !park_state;
		}

		drive_temp = 0.0;
		
		drive_temp += 
			left_front_motor.get_temperature() +
			left_rear_motor.get_temperature() +
			left_upper_motor.get_temperature() +
			right_front_motor.get_temperature() +
			right_rear_motor.get_temperature() +
			right_upper_motor.get_temperature();
		drive_temp /= 6.0;
		//drive_temp *= 1.8;
		//drive_temp += 32.0;

		controller.print(0, 0, "TEMP: %.2f°C      ", drive_temp);

		pros::delay(20);
	}
} 