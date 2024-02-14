#include "main.h"
#include "globals.hpp"

#define M_PI 3.14159265358979323846

/*  TICKS TO REVOLUTIONS  CHEATSHEAT
1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears */

#define TICKS_36_1 1800.0
#define TICKS_18_1 900.0
#define TICKS_6_1 300.0

#define VELOCITY_36_1 100.0
#define VELOCITY_18_1 200.0
#define VELOCITY_6_1 600.0

#define OMNI_4_IN 4.0
#define OMNI_3_IN 3.0

// Drive function in inches
void move_inches(double distance, double velocity_coefficient = 1) {
    right_side_motors.tare_position();
    left_side_motors.tare_position();

    double circumference = OMNI_4_IN * M_PI;
    double revolutions = (distance / circumference) * 1.75 * 2;
    double ticks = TICKS_6_1 * revolutions;
    double velocity = VELOCITY_6_1 * velocity_coefficient;

    left_side_motors.move_relative(ticks, velocity);
    right_side_motors.move_relative(ticks, velocity);
    
    // Add stall
    /*
    while (moving) {
        pros::delay(10);
    }
    
    */
}

void turn_imu(double theta, double speed = 75) {
    inertial_sensor.tare_rotation();

    if (fabs(theta) != theta) {
        while (fabs(inertial_sensor.get_rotation()-theta) > 1) {
            right_side_motors.move(speed);
            left_side_motors.move(speed*-1);
        }
    } else {
        while (fabs(inertial_sensor.get_rotation()-theta > 1))
        right_side_motors.move(speed*-1) ;
        left_side_motors.move(speed);
    }   
    left_side_motors.brake();
    right_side_motors.brake(); 
}


void skills_autonomous() {

}

void driver_side_score() {

}

void driver_side_awp() {

}

void far_side() {
    move_inches(-20);
    move_inches(10);
}

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

}