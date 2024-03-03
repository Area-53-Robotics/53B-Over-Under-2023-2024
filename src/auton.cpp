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
void move_inches(double distance, double velocity_coefficient = 1.0) {
    right_side_motors.tare_position();
    left_side_motors.tare_position();

    double circumference = OMNI_4_IN * M_PI;
    double revolutions = (distance / circumference) * 1.75 * 2;
    double ticks = TICKS_6_1 * revolutions;
    double velocity = VELOCITY_6_1 * velocity_coefficient;

    left_side_motors.move_relative(ticks, velocity);
    right_side_motors.move_relative(ticks, velocity);
}

void turn_pd(float theta, float speed = 127, int timeout = 3000) {
    inertial_sensor.tare_rotation();

    int timer = 0;
    timeout /= 10;

    int direction;

    if (fabs(theta) == theta) {
        direction = 1;
    } else {
        direction = -1;
    }

    float current_angle = inertial_sensor.get_rotation();
    float error = fabs(theta);
    float total_error;
    float output;
    float derivative;
    float prev_error = 0;

    float kp = 10;
    float kd = 30;
    
    while (error > 0.1) {
        current_angle = inertial_sensor.get_rotation();

        error = fabs(theta) - fabs(current_angle);

        derivative = error - prev_error;
        prev_error = error;

        output = error * kp + derivative * kd;

        if (output > speed) {
            output = speed;
        }
        
        //printf("Error: %f, Derivative: %f, Output: %f\n", error, derivative, output);
        controller.print(0,0, "ERROR: %f", error);

        right_side_motors.move(output * -1 * direction);
        left_side_motors.move(output * direction);
        pros::delay(10);

        timer++;

        if (timer > timeout) {
            break;
        }
    }
    right_side_motors.brake();
    left_side_motors.brake();
    pros::delay(100);
}


void skills_autonomous() {

}

void driver_side() {
    right_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    left_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

    lift.set_value(true);
    pros::delay(700);
    lift.set_value(false);
    pros::delay(700);
    turn_pd(-45, 100);
    pros::delay(500);
    move_inches(-14.5, 0.2);
    pros::delay(2500);
    turn_pd(45);
    pros::delay(500);
    move_inches(-4, 0.6);
    pros::delay(500);
    move_inches(5, 0.3);
    pros::delay(500);
    turn_pd(-25, 70);
    pros::delay(700);
    move_inches(8, 0.1);
    pros::delay(1500);
    park.set_value(true);
    move_inches(4.5, 0.2);
    pros::delay(1500);
    turn_pd(-75, 115);
    pros::delay(1000);
    park.set_value(false);
    turn_pd(32);
    pros::delay(1000);
    move_inches(22, 0.4);
    intake.move(-127);
}

void far_side() {
    right_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    left_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

    lift.set_value(true);
    pros::delay(500);
    lift.set_value(false);
    intake.move(127);
    move_inches(5, 0.5);
    pros::delay(750);
    intake.brake();
    move_inches(-24.5, 0.5);
    pros::delay(1600);
    turn_pd(-45, 100);
    pros::delay(700);
    move_inches(-13, 0.5);
    pros::delay(1200);
    turn_pd(-40, 100);
    pros::delay(500);
    move_inches(-6, 0.7);
    pros::delay(1000);
    move_inches(6, 0.3);
    pros::delay(500);
    turn_pd(180, 80);
    pros::delay(1000);
    intake.move(-127);
    pros::delay(500);
    move_inches(6, 0.7);
    pros::delay(500);
    intake.brake();
    move_inches(-6, 0.5);
    pros::delay(500);
    turn_pd(-75, 100);
    pros::delay(700);
    intake.move(127);
    move_inches(25, 1);
    pros::delay(1400);
    turn_pd(125, 120);
    intake.brake();
    pros::delay(700);
    move_inches(16, 1);
    pros::delay(1000);
}

/**
* Runs the user autonomous code. This function will be started in its own task
* with the default priority and stack size whenever the robot is enabled via
* the Field Management System or the VEX Competition Switch in the autonomous
* mode. Alternatively, this function may be called in initialize or opcontrol
* for non-competition testing purposes.time
*
* If the robot is disabled or communications is lost, the autonomous task
* will be stopped. Re-enabling the robot will restart the task, not re-start it
* from where it left off.
*/

void autonomous() {
    // Slot 1
    driver_side();

    // Slot 2
    //far_side();

    // Slot 3
    //skills_autonomous();

}