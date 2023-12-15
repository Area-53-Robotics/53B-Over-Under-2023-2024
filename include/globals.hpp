#include "lemlib/api.hpp"

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Left Drive
inline pros::Motor left_front_motor(7, pros::E_MOTOR_GEARSET_06, true);
inline pros::Motor left_rear_motor(8, pros::E_MOTOR_GEARSET_06, true);
inline pros::Motor left_upper_motor(10, pros::E_MOTOR_GEARSET_06, false);

inline pros::MotorGroup left_side_motors({left_front_motor, left_rear_motor, left_upper_motor});

// Right Drive
inline pros::Motor right_front_motor(3, pros::E_MOTOR_GEARSET_06, false);
inline pros::Motor right_rear_motor(2, pros::E_MOTOR_GEARSET_06, false);
inline pros::Motor right_upper_motor(1, pros::E_MOTOR_GEARSET_06, true);

inline pros::MotorGroup right_side_motors({right_front_motor, right_rear_motor, right_upper_motor});

//Drivetrain
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
lemlib::ControllerSettings linearController(
    10, // proportional gain (kP)
    30, // derivative gain (kD)
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(
    2, // proportional gain (kP)
    10, // derivative gain (kD)
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
);

// Cata
inline pros::Motor cata(11, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::ADIDigitalIn limit_switch('G');
inline pros::ADIAnalogIn cata_rotation(9);

// Wings
inline pros::ADIDigitalOut wings('H');
bool wingstate = false;

// Intake
inline pros::Motor intake_right(16, pros::E_MOTOR_GEARSET_18, true);
inline pros::Motor intake_left(19, pros::E_MOTOR_GEARSET_18, false);

inline pros::MotorGroup intake({intake_right, intake_left});

// Create the chassis
inline lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);