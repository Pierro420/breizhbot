

/*
 * Fichier de déclarations des fonctions liées aux moteurs
 * 
 * Acronymes : 
 *  - MM => millimeter
 *  - SPS => step per second
 *  - RPM => revolution per minute
 */
#include <Arduino.h>
#include <AccelStepper.h>

#define MOTOR1_IN1                      4     // IN1 on the ULN2003 driver 1
#define MOTOR1_IN2                      5     // IN2 on the ULN2003 driver 1
#define MOTOR1_IN3                      6     // IN3 on the ULN2003 driver 1
#define MOTOR1_IN4                      7     // IN4 on the ULN2003 driver 1
#define MOTOR1_DIR                      -1     // Sens de rotation du moteur 1

#define MOTOR2_IN1                      8     // IN1 on the ULN2003 driver 2
#define MOTOR2_IN2                      9     // IN2 on the ULN2003 driver 2
#define MOTOR2_IN3                      10    // IN3 on the ULN2003 driver 2
#define MOTOR2_IN4                      11    // IN4 on the ULN2003 driver 2
#define MOTOR2_DIR                      1     // Sens de rotation du moteur 2


#define MAX_SPEED                       1000     // 1000 valeur conseillée par la documentation 
                                             // Au delà de ≃1300 le moteur PaP décroche en mode HALF STEP / ≃650 en mode FULL STEP (valeurs testées avec un arduino Nano V3)

#define STEEPS_PER_MOTOR_REVOLUTION     4096 // cf documentation (4096 en mode HALF STEP, 2048 en mode FULL STEP)

#define WHEEL_DIAMETER_MM               65 // Diamètre des roues en millimètre
#define WHEEL_SPACING_MM                110 // Entraxe des roues en millimètre

#define STEEPS_FOR_1MM                  STEEPS_PER_MOTOR_REVOLUTION/(PI * WHEEL_DIAMETER_MM)
#define STEEPS_FOR_1DEG                 STEEPS_FOR_1MM * WHEEL_SPACING_MM * (PI / 360)

enum Move {NO_MOVE = 0, FORWARD = 1, BACKWARD = -1};
enum Turn {NO_TURN = 0, RIGHT = 1, LEFT = 2};

void initMotors(boolean debug);
void enableMotors(boolean debug);
void disableMotors(boolean debug);

void setDistanceToDo(Move m, float distMM, float speedSPS, boolean debug); 
void setTurnToDo(Move m, Turn t, float radius, float angle, float speed1, boolean debug);
//void setOrient(float angle, float speedSPS, boolean debug);
//void setCircle(float radius, float angle, float speed1, boolean debug);
boolean perform_one_step();
