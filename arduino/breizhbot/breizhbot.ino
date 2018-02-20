
#include "motors.h"
#include "command.h"

boolean debug = false;
boolean current_cmd_is_finished = true;
char* current_cmd;
char* next_cmds;
char* delimCmd = (char*) "|";
char* delimParams = (char*) ":";



unsigned long previousMillis = 0;
const long interval = 500; 










void setup()
{ 
  Serial.begin(9600);
//*
  next_cmds = (char*) calloc(1, sizeof(char)); 
  if(next_cmds == NULL) Serial.println("calloc next_cmd failed");
  current_cmd = (char*) calloc(1, sizeof(char)); 
  if(next_cmds == NULL) Serial.println("calloc current_cmd failed");
//*/
  
  initMotors(debug);

  initServo();


  initUSsensor();
}

void loop()
{
//*
//   
//     Utilisateur entre des nouvelles commandes
//     On ajoute les nouvelles commandes à la liste des commandes à executer
//
  while(Serial.available()) { 
    String input = Serial.readString();
    appendCmd(&next_cmds, input.c_str(), delimCmd);
    if(debug){    
      Serial.print("input:");
      Serial.println(input);
      Serial.print("next_cmds:");
      Serial.println(next_cmds);
    }
  }
  
//  
//    S'il n'y a pas de commande en cours et qu'il y a une liste de commande à exécuter 
//    On récupère la première commande à exécuter, on l'enlève de la liste
//    Et on exécute la commande
//* 
  if(current_cmd_is_finished && strlen(next_cmds) > 0){ 
    current_cmd = extractFirstElement(&next_cmds, delimCmd);
    if(debug){   
      Serial.print("current_cmd:");
      Serial.println(current_cmd);
      Serial.print("next_cmds:");
      Serial.println(next_cmds);
    }
    executeCmd(current_cmd, delimParams, debug);
    current_cmd_is_finished = false;
  }
  
//  
//    Si la commande en cours n'est pas finie 
//    On exécute un pas sur les moteurs
//   
  if(!current_cmd_is_finished){
    current_cmd_is_finished = perform_one_step();
    
  }
//  
//    Si la commande en cours est finie 
//    On libère current_cmd
//   
  if(current_cmd_is_finished){
    free(current_cmd);
  }

  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.print(measure());
    Serial.print("|");
  }
 //*/
}
