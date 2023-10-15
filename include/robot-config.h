using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor TOP_RIGHT;
extern motor BOTTOM_RIGHT;
extern motor FOWARD_RIGHT;
extern motor TOP_LEFT;
extern motor BOTTOM_LEFT;
extern motor FOWARD_LEFT;
extern controller Controller1;
extern motor INTAKE1;
extern motor INTAKE2;
extern motor CATA;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );