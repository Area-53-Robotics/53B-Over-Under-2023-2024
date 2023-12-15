#include "main.h"
#include "globals.hpp"

// pi
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
    imu.tare();
    drive.tare_position();
    const float WHEEL_RADIUS = 4 / 2;  // Inches
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

    while (true) {
        // Calculate PID values for distance distance traveled
        for (int i = 0; i < )
        dist_traveled = left_encoder.get_value() * ((2 * M_PI / 360) * WHEEL_RADIUS);
        error = target - dist_traveled;
        integral = integral + error * delay_time;
        derivative = error - prev_error;
        prev_error = error;
    }
}



// Drive a motor group forward in inches
void move_inches(double distance, double ticks_per_revolution, double wheel = OMNI_4_IN, double motor_velocity = , double velocity_coefficient = 1.0) {
   double circumference = wheel * M_PI;
   double revolutions = distance / circumference;
   double ticks = ticks_per_revolution * revolutions;
   double velocity = motor_velocity * velocity_coefficient;

   drive.move_relative(ticks, velocity);
}

void skills_autonomous() {

}

void driver_side() {

}

void far_side() {

}

void autonomous() {
	driver_side();
    //far_side();
    //skills_autonomous();
}