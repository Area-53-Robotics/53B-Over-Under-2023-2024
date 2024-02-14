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

double current_velocity;

double error;
double prev_error;
double total_error;

double integral;
double derivative;
double output;

double kp = 1;
double ki = 1;
double kd = 1;

void flywheel_pid(double target) {
	current_velocity = flywheel.get_velocity();

	error = target - current_velocity;

	integral += error;

	derivative = error - prev_error;
	prev_error = error;

	output = error * kp + integral * ki + derivative * kd;

	flywheel.set_velocity(output);
}

void opcontrol() {
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	right_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    left_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		// Drive
		int forward = calc_drive_curve(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 3.5);
		//int forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		
		int turn = calc_drive_curve(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 3.5);
		//int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
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
			flywheel_pid(500);
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

		// Wings
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
			wings.set_value(!wing_state);
			wing_state = !wing_state;
		}

		pros::delay(20);
	}
} 
