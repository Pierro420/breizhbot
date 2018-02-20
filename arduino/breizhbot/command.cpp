#include <Servo.h>
#include "command.h"
#include "motors.h"

/*
 * Ajoute cmd à dest
 * Si dernier caractère de dest et premier caractère de cmd est différent de delim on ajoute delim avant cmd
 */
void appendCmd(char** dest, char* cmd, char* delim){
  int length_dest = strlen(*dest) + strlen(cmd) + strlen(delim);
  *dest = (char*) realloc(*dest, sizeof(char) * (length_dest+1) );
  strcat(*dest, delim);
  strcat(*dest, cmd);
}

char* extractFirstElement( char** next_elements, char* delim){
  char* first_element;
  char* tmp_next_elements;
  first_element = strtok_r(*next_elements, delim, &tmp_next_elements);
  *next_elements = (char*) calloc(strlen(tmp_next_elements)+1, sizeof(char));
  strcpy(*next_elements, tmp_next_elements);
  return first_element;
}



void executeCmd(char* cmd, char* delim, boolean debug){
  char* name_cmd;
  name_cmd = extractFirstElement(&cmd, delim); 
  if(strcmp(name_cmd,"B")==0){
    enableMotors(debug);
  }else if(strcmp(name_cmd,"E")==0){
    disableMotors(debug);
  }else if(strcmp(name_cmd,"D")==0){
    char *m, *distance, *speedSPS;
    m = extractFirstElement(&cmd, delim);
    distance = extractFirstElement(&cmd, delim);
    speedSPS = extractFirstElement(&cmd, delim);
    setDistanceToDo(atoi(m), atof(distance), atof(speedSPS), debug);
  }else if(strcmp(name_cmd,"T")==0){
    char *m, *turn, *radius, *angle, *speedSPS;
    m = extractFirstElement(&cmd, delim);
    turn = extractFirstElement(&cmd, delim);
    radius = extractFirstElement(&cmd, delim);
    angle = extractFirstElement(&cmd, delim);
    speedSPS = extractFirstElement(&cmd, delim);
    setTurnToDo(atoi(m), atoi(turn), atof(radius), atof(angle), atof(speedSPS), debug);
  }else if(strcmp(name_cmd,"Up")==0){
    up();
  }else if(strcmp(name_cmd,"Down")==0){
    down();
  }
}



Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
void initServo(){
   myservo.attach(3);  // attaches the servo on pin 9 to the servo object
   down();
}
void up() {
    myservo.write(20);              // tell servo to go to position in variable 'pos'

}
void down(){
    myservo.write(50);              // tell servo to go to position in variable 'pos'

}



/* Constantes pour les broches */
const byte TRIGGER_PIN = 13; // Broche TRIGGER
const byte ECHO_PIN = 12;    // Broche ECHO
 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;


void initUSsensor(){
  
   /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
}

float measure(){

/* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  return distance_mm;
}
