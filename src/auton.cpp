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

void move_pid(double target, int timeout, int max_speed) {
    inertial_sensor.tare();
    drive.tare_position();
    const float WHEEL_RADIUS = OMNI_4_IN / 2;  // Inches
    float delay_time = 20;
    double time_elapsed = 0;
    int start_time = pros::millis();
    int end_time = start_time + 1000 * timeout;
    int time_at_target = 0;
    double power, left_power, right_power, power_theta;

    double dist_traveled;
    double error;
    double prev_error = error;

    double error_theta;
    double prev_error_theta = error_theta;

    double integral;
    double integral_theta;

    double derivative;
    double derivative_theta;

    const float kp = 11;
    const float ki = 0;
    const float kd = 30;

    const float kp_theta = 2;
    const float ki_theta = 0;
    const float kd_theta = 10;

    std::vector<double> positions;

    while (true) {
        // Calculate PID values for distance distance traveled
        positions = drive.get_positions();
        dist_traveled = positions[0] * ((2 * M_PI / 360) * WHEEL_RADIUS);
        error = target - dist_traveled;
        integral = integral + error * delay_time;
        derivative = error - prev_error;
        prev_error = error;

        // Calculate PID values for rotation
        error_theta = inertial_sensor.get_rotation();
        integral_theta = integral_theta + error_theta * delay_time;
        derivative_theta = error_theta - prev_error_theta;
        prev_error_theta = error_theta;
        power_theta = (error_theta * kp_theta) + (derivative_theta * kd_theta);

        if (power_theta > max_speed) {
        integral_theta = 0;
        }

        power = (error * kp) + (integral * ki) + (derivative * kd);

        // Correct the power based on rotation (we want to move in a straight line)
        left_power = (power + power_theta);
        right_power = (power - power_theta);

        if (left_power > max_speed) {
            left_power = max_speed;
        }
        if (right_power > max_speed) {
             right_power = max_speed;
        }

        right_side_motors.move(right_power);
        left_side_motors.move(left_power);

        // check exit conditions
        if (error < 0.5 && error > -0.5) {
        // The chassis has to spend time at the target to make sure it doesn't overshoot.
            time_at_target += delay_time;
            if (time_at_target > 500) {  // 500 Milliseconds
                printf("move_pid met the target\n");
                break;
            }
        } else {
            time_at_target = 0;
        }

        // Timeout
        if (pros::millis() > end_time) {
            printf("move_pid timed out\n");
            break;
        }

        printf("%f, %f, %f, %f\n", power, error * kp, integral * ki, derivative * kd);
        // printf("%f, %f, %f, %f\n", power_theta, error_theta * kp_theta, integral_theta * ki_theta, derivative_theta * kd_theta);

    pros::delay(delay_time);
    time_elapsed += delay_time;
  }

  left_side_motors.move(0);
  right_side_motors.move(0);
}

void turn_pid(double target, int timeout, int max_speed) {
    inertial_sensor.tare();
    drive.tare_position();
    const float WHEEL_RADIUS = OMNI_4_IN / 2;  // Inches
    float delay_time = 10;
    double end_time = pros::millis() + timeout * 1000;  // Convert to seconds
    double time_elapsed = 0;
    double time_at_target = 0;
    double power;
    bool is_target_negative = false;

    if (target < 0) {
        is_target_negative = true;
    }

    double dist_traveled;
    double error;
    double prev_error = error;

    double integral;

    double derivative;

    const double kp = 0.8;
    const double ki = 0.0008;
    const double kd = 0.5;

    while (true) {
        // Calculate PID values for distance distance traveled
        dist_traveled = fabs(inertial_sensor.get_rotation());
        error = fabs(target) - dist_traveled;
        integral = integral + error * delay_time;
        derivative = error - prev_error;
        prev_error = error;

        power = (error * kp) + (integral * ki) + (derivative * kd);

        if (power > max_speed) {
            power = max_speed;
        }

        if (power > 50) {
            integral = 0;
        }

        if (!is_target_negative) {
            //move(power, -power);
            left_side_motors.move(power);
            right_side_motors.move(-power);
        } else {
            //move(-power, power);
            left_side_motors.move(power);
            right_side_motors.move(-power);
        }

        // check exit conditions
        if (error < 0.5 && error > -0.5) {
            // The chassis has to spend time at the target to make sure it doesn't
            // overshoot.
            time_at_target += delay_time;
            if (time_at_target > 500) {  // 500 Milliseconds
                printf("turn_pid met the target\n");
                break;
            }
        } else {
            time_at_target = 0;
        }

        // Timeout
        if (pros::millis() > end_time) {
            printf("turn_pid timed out\n");
            break;
        }

        // printf("%f, %f, %f, %f\n", power, error * kp, integral * ki,
        // derivative * kd);

        pros::delay(delay_time);  // Milliseconds
    }

    left_side_motors.move(0);
    right_side_motors.move(0);
}


// Drive a motor group forward in inches
void move_inches(double distance, double ticks_per_revolution = TICKS_6_1, double wheel = OMNI_4_IN, double motor_velocity = VELOCITY_6_1, double velocity_coefficient = 0.5) {
    double circumference = wheel * M_PI;
    double revolutions = distance / circumference;
    double ticks = ticks_per_revolution * revolutions;
    double velocity = motor_velocity * velocity_coefficient;

    left_side_motors.move_relative(ticks, velocity);
    right_side_motors.move_relative(ticks, velocity);
}

void turn_degrees(double theta, double width = 12.75, double ticks_per_revolution = TICKS_6_1, double wheel = OMNI_4_IN, double motor_velocity = VELOCITY_6_1, double velocity_coefficient = 0.5) {
    double distance = width * 2 * M_PI / (360/theta);
    double circumference = wheel * M_PI;
    double revolutions = distance / circumference;
    double ticks = ticks_per_revolution * revolutions;
    double velocity = motor_velocity * velocity_coefficient;
    
    left_side_motors.move_relative(ticks, velocity);
    right_side_motors.move_relative(ticks*-1, velocity);

}

void turn_imu(double theta) {
    while (inertial_sensor.get_heading() < theta) {
        if (!(fabs(theta) == theta)) {
            right_side_motors.move(75);
            left_side_motors.move(-75);
        } else {
            right_side_motors.move(-75);
            left_side_motors.move(75);
        }
    }
}


void skills_autonomous() {
    move_pid(-30, 4, 75);
    turn_pid(-45, 3, 75);
    cata.move(60);
    pros::delay(45000);

}

void driver_side() {
    move_pid(50, 5, 75);
    turn_pid(-90, 3, 75);
    move_pid(12, 3, 127);
    intake.move(-127);
    pros::delay(2000);
    intake.brake();
    move_pid(3, 1, 75);
    move_pid(-12, 3, 75);
}

void far_side() {
    move_inches(50);
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
    // driver side
    /*
    move_inches(110);
    pros::delay(2000);

    turn_degrees(-50);
    pros::delay(2000);

    move_inches(-15);
    pros::delay(2000);

    turn_degrees(-50);
    pros::delay(2000);

    move_inches(12);
    pros::delay(1500);

    intake.move(-127);
    pros::delay(2000);
    intake.brake();

    turn_degrees(-30);
    pros::delay(1500);

    move_inches(10);
    pros::delay(1000);

    move_inches(-20);
    /*
    cata.move(80);
    */

    // far side
    move_inches(-80);
    pros::delay(2000);

    move_inches(40);

}