#include "main.h"
#include "globals.hpp"

// pi
#define M_PI 3.14159265358979323846

/* GEAR TO TICKS CHEATSHEAT
1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears */
#define TICKS_36_1 = 1800.0;
#define TICKS_18_1 = 300.0;
#define TICKS_6_1 = 900.0;

#define VELOCITY_36_1 = 100.0;
#define VELOCITY_18_1 = 200.0;
#define VELOCITY_6_1 = 600.0;

#define OMNI_4_IN = 4.0;
#define OMNI_3_IN = 3.0;

// 
void drive_forward(pros::MotorGroup drive_group, double distance, double ticks_per_revolution, double wheel, double motor_velocity, double velocity_coefficient = 1.0) {
   double circumference = wheel * M_PI;
   double revolutions = distance / circumference;
   double ticks = ticks_per_revolution * revolutions;
   double velocity = motor_velocity * velocity_coefficient;

   drive_group.move_relative(ticks, velocity);


}

void skills_autonomous() {
    /*
	drive.move_relative(-80);


	cata.move(80);
	pros::delay();
    */

}

void driver_side() {
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
}

void far_side() {}

void autonomous() {

	driver_side();
}