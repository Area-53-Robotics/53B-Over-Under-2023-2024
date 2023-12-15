	#include "main.h"
	#include "globals.hpp"

	/**
	* A callback function for LLEMU's center button.
	*
	* When this callback is fired, it will toggle line 2 of the LCD text between
	* "I was pressed!" and nothing.
	*/
	void on_center_button() {
		static bool pressed = false;
		pressed = !pressed;
		if (pressed) {
			pros::lcd::set_text(2, "I was pressed!");
		} else {
			pros::lcd::clear_line(2);
		}
	}

	/**
	* Runs initialization code. This occurs as soon as the program is started.
	*
	* All other competition modes are blocked by initialize; it is recommended
	* to keep execution time for this mode under a few seconds.
	*/
	void initialize() {
		pros::lcd::initialize();
		pros::lcd::set_text(1, "Hello World");

		pros::lcd::register_btn1_cb(on_center_button);

		//wings.set_value(false);
	}

	/**
	* Runs while the robot is in the disabled state of Field Management System or
	* the VEX Competition Switch, following either autonomous or opcontrol. When
	* the robot is enabled, this task will exit.
	*/
	void disabled() {}

	/**
	* Runs after initialize(), and before autonomous when connected to the Field
	* Management System or the VEX Competition Switch. This is intended for
	* competition-specific initialization routines, such as an autonomous selector
	* on the LCD.
	*
	* This task will exit when the robot is enabled and autonomous or opcontrol
	* starts.
	*/
	void competition_initialize() {}

	/**
	* Runs the user autonomous code. This function will be started in its own task
	* with the default priority and stack size whenever the robot is enabled via
	* the Field Management System or the VEX Competition Switch in the autonomous
	* mode. Alternatively, this function may be called in initialize or opcontrol
	* for non-competition testing purposes.
	*
	* If the robot is disabled or communications is lost, the autonomous task
	* will be stopped. Re-enabling the robot will restart the task, not re-start it
	* from where it left off.
	*/
	void autonomous() {
		right_side_motors.move(-120);
		left_side_motors.move(-120);

		pros::delay(1500);

		right_side_motors.brake();
		left_side_motors.brake();

		right_side_motors.move(80);
		left_side_motors.move(80);

		pros::delay(750);

		right_side_motors.brake();
		left_side_motors.brake();

		pros::delay(1500);


		/*
		// movee forward
		chassis.moveTo(
			0.0, // x
			-10.0, // y
			0.0, // angle
			4000 // timeout
		);

		chassis.moveTo(
			0.0, // x
			-5.0, // y
			0.0, // angle
			4000 // timeout
		);

		/*
		// move forward
		chassis.moveTo(
			0.0, // x
			12.0, // y
			0.0, // angle
			4000 // timeout
		);

		// turn left
		chassis.moveTo(
			0, // x
			12, // y
			-90, // angle
			4000 // timeout
		);

		// move forward
		chassis.moveTo(
			-3, // x
			12, // y
			-90, // angle
			4000 // timeout
		);

		// spin intake
		intake.move(-127);
		pros::delay(1000);
		intake.brake();
		*/
		
	}

	void opcontrol() {
		cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		//cata_rotation.reset();

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

			if (!limit_switch.get_value()) {
				cata.move(80);
			} else {
				if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
					cata.move(80);
					pros::delay(500);
				} else {
					cata.brake();
				}
			}

			
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
			
			controller.print(0,0, "CataPos: %d", limit_switch.get_value());
			//pros::screen::print(TEXT_SMALL, 3, "Cata Position: %f", limit_switch.get_value());

			pros::delay(20);
		}
	} 
