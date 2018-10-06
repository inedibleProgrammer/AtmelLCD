/*
    Main
    Testing an added comment
*/

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>

bool occurOnce = true;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if(occurOnce)
    {
        occurOnce = false;
        Serial.println("This is a test");
    }
}
