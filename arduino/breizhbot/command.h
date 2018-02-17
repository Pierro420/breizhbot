#include <Arduino.h>

void appendCmd(char** dest, char* cmd, char* delim);
char* extractFirstElement(char** src, char* delim);
void executeCmd(char* cmd, char* delim, boolean debug);
void up();
void down();
void initServo();
void initUSsensor();
float measure();
