#include "motors.h"

AccelStepper stepper1(AccelStepper::HALF4WIRE, MOTOR1_IN1, MOTOR1_IN3, MOTOR1_IN2, MOTOR1_IN4);
AccelStepper stepper2(AccelStepper::HALF4WIRE, MOTOR2_IN1, MOTOR2_IN3, MOTOR2_IN2, MOTOR2_IN4);

void initMotors(boolean debug  = false){
  if(debug){
    Serial.println(F("initMotors: set max speed for each motor"));
  }
  stepper1.setMaxSpeed(MAX_SPEED);
  stepper2.setMaxSpeed(MAX_SPEED);
}

void enableMotors(boolean debug) { // not used
  if(debug){
    Serial.println(F("enableMotors: enableOutputs for each motor"));
  }
  stepper1.enableOutputs();
  stepper2.enableOutputs();
}

void disableMotors(boolean debug) { // not used
  if(debug){
    Serial.println(F("disableMotors: disableOutputs for each motor"));
  }
  stepper1.disableOutputs();
  stepper2.disableOutputs();
}


boolean perform_one_step(){
  if(stepper1.distanceToGo() != 0){
    stepper1.runSpeedToPosition();
  }
  if(stepper2.distanceToGo() != 0){
    stepper2.runSpeedToPosition();
  }
  return stepper1.distanceToGo()==0 && stepper2.distanceToGo()==0;
}


void setDistanceToDo(Move m, float distMM, float speedSPS, boolean debug) {
   
  long steps = round(distMM * STEEPS_FOR_1MM); 
  
  if(debug){
    if(m==FORWARD) Serial.println(F("GO FORWARD"));
    else if(m==BACKWARD) Serial.println(F("GO BACKWARD"));
    else Serial.println(F("NO MOVE"));
    Serial.print(F("Desired distance: "));
    Serial.print(distMM);
    Serial.print(F(" mm\nNumber of steps to perform: "));
    Serial.println(steps);
    Serial.print(F("Desired speed: "));
    Serial.print(speedSPS);
    Serial.println(F(" steps per second"));
  }
  if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0){ // si les 2 moteurs n'ont plus de distance à parcourir    
    stepper1.move(m * steps * MOTOR1_DIR);
    stepper1.setSpeed(speedSPS);
    stepper2.move(m * steps * MOTOR2_DIR);
    stepper2.setSpeed(speedSPS);    
  }else{
    if(debug){
      Serial.println("Can't execute the action :");
      Serial.print("Motor 1 still has ");
      Serial.print(stepper1.distanceToGo());
      Serial.println(" steps to perform");
      Serial.print("Motor 2 still has ");
      Serial.print(stepper2.distanceToGo());
      Serial.println(" steps to perform");
    }
  }

  
}

void setTurnToDo(Move m, Turn t, float radius, float angle, float speedSPS, boolean debug){
  float lenght_big_arc, lenght_small_arc;
  float steps_big_arc, steps_small_arc;
  float speed_big_arc, speed_small_arc;

  lenght_big_arc = 2 * PI * (radius + (WHEEL_SPACING_MM/2)) * (angle / 360);
  steps_big_arc = round(lenght_big_arc * STEEPS_FOR_1MM);
  speed_big_arc = speedSPS;

  lenght_small_arc = 2 * PI * (radius - (WHEEL_SPACING_MM/2)) * (angle / 360);
  steps_small_arc = round(lenght_small_arc * STEEPS_FOR_1MM);
  speed_small_arc = abs((steps_small_arc*speed_big_arc)/steps_big_arc);

  if(debug){

    if(t==RIGHT) Serial.println(F("TURN RIGHT"));
    else if(t==LEFT) Serial.println(F("TURN LEFT"));
    else Serial.println(F("NO TURN"));
    
    if(m==FORWARD) Serial.println(F("GO FORWARD"));
    else if(m==BACKWARD) Serial.println(F("GO BACKWARD"));
    else Serial.println(F("NO MOVE"));
    
  }
  

  if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0){
    if(t == RIGHT){
      stepper1.move(m * steps_big_arc * MOTOR1_DIR);
      stepper1.setSpeed(speed_big_arc);
  
      stepper2.move(m * steps_small_arc * MOTOR2_DIR);
      stepper2.setSpeed(speed_small_arc);
    }else if(t == LEFT){
      stepper1.move(m * steps_small_arc * MOTOR1_DIR);
      stepper1.setSpeed(speed_small_arc);

      stepper2.move(m * steps_big_arc * MOTOR2_DIR);
      stepper2.setSpeed(speed_big_arc);
    }else{
      
    }
  }
}

void setCircle(float radius, float angle, float speed1, boolean debug){
  
  float distMM1 = 2 * PI * (radius + WHEEL_SPACING_MM/2) * (angle / 360);
  long steps1 = round(distMM1 * STEEPS_FOR_1MM);

  float distMM2 = 2 * PI * (radius - WHEEL_SPACING_MM/2) * (angle / 360);
  long steps2 = round(distMM2 * STEEPS_FOR_1MM);

  float speed2 = abs((steps2*speed1)/steps1);

  if(debug){
    Serial.print("Desired radius: ");
    Serial.print(radius);
    Serial.print(" mm\nNumber of steps for motor1 to perform: ");
    Serial.println(steps1);
    Serial.print("Desired speed1: ");
    Serial.println(speed1);
    Serial.print("Number of steps for motor2 to perform: ");
    Serial.println(steps2);
    Serial.print("Calculated speed2: ");
    Serial.println(speed2);
  }

   if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0){ // si les 2 moteurs n'ont plus de distance à parcourir
    
    delay(1000);
       
    stepper1.move(steps1 * MOTOR1_DIR);
    stepper1.setSpeed(speed1);

    stepper2.move(steps2 * MOTOR2_DIR);
    stepper2.setSpeed(speed2);
      
  }else{
    if(debug){
      Serial.println("Can't execute the action :");
      Serial.print("Motor 1 still has ");
      Serial.print(stepper1.distanceToGo());
      Serial.println(" steps to perform");
      Serial.print("Motor 2 still has ");
      Serial.print(stepper2.distanceToGo());
      Serial.println(" steps to perform");
    }
  }
}


