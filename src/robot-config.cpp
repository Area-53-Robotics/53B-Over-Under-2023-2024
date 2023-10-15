#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor TOP_RIGHT = motor(PORT1, ratio6_1, true);
motor BOTTOM_RIGHT = motor(PORT2, ratio6_1, false);
motor FOWARD_RIGHT = motor(PORT3, ratio6_1, false);
motor TOP_LEFT = motor(PORT10, ratio6_1, false);
motor BOTTOM_LEFT = motor(PORT8, ratio6_1, true);
motor FOWARD_LEFT = motor(PORT7, ratio6_1, true);
motor INTAKE1 = motor(PORT19, ratio18_1, true);
motor INTAKE2 = motor(PORT16, ratio18_1, true);
motor CATA = motor(PORT11, ratio36_1, false);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}