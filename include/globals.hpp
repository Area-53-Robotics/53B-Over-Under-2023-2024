#pragma once

#include "lemlib/api.hpp"
#include "sylib/sylib.hpp"

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Left Drive
inline pros::Motor left_front_motor(7, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor left_rear_motor(8, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor left_upper_motor(10, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

inline pros::MotorGroup left_side_motors({left_front_motor, left_rear_motor, left_upper_motor});

// Right Drive
inline pros::Motor right_front_motor(3, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor right_rear_motor(2, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor right_upper_motor(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

inline pros::MotorGroup right_side_motors({right_front_motor, right_rear_motor, right_upper_motor});

//Drivetrain
inline pros::MotorGroup drive({right_front_motor, right_rear_motor, right_upper_motor, left_front_motor, left_rear_motor, left_upper_motor}); // Basic drive motor group for other functions

inline lemlib::Drivetrain drivetrain(
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    12.6, // track width
    lemlib::Omniwheel::NEW_4, // wheel diameter
    343, // wheel rpm,
    2 // chase power
);

// Odometry
inline pros::Imu inertial_sensor(20); //set this to sensor port when wire is fixed

inline lemlib::OdomSensors sensors(
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor //set to &intertial_sensor when wire is fixed   
);

// lateral motion controller
inline lemlib::ControllerSettings linearController(
    10, // proportional gain (kP)
    30, // derivative gain (kD)
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
);

// angular motion controller
inline lemlib::ControllerSettings angularController(
    2, // proportional gain (kP)
    10, // derivative gain (kD)
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
);

// Cata
inline sylib::Motor flywheel(11, 600, false);
inline bool flywheel_active = false;
inline bool flywheel_direction = true;

// Lift
inline pros::ADIDigitalOut lift('G');
inline bool lift_state = false;

// Park
inline pros::ADIDigitalOut park('E');
inline bool park_state = false;

// Wings
inline pros::ADIDigitalOut wings('H');
inline bool wing_state = false;

// Intake
inline pros::Motor intake(9, pros::E_MOTOR_GEARSET_06, true);

// Create the chassis
inline lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);