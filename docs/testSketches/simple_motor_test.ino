// Sparkfun monster shield


#include <Arduino.h>

///Left Motor  Pins
#define INA_1 5
#define INB_1 6
#define PWM_1 7

///Right Motor Pins
#define INA_2 8
#define INB_2 9
#define PWM_2 10



int speed = 80;

void move_forward(int speed);
void stop(bool slowDown);

void setup()
{
    Serial.begin(115200);
    //Setting Left Motor pin as OUTPUT
    pinMode(INA_1, OUTPUT);
    pinMode(INB_1, OUTPUT);

    //Setting Right Motor pin as OUTPUT
    pinMode(INA_2, OUTPUT);
    pinMode(INB_2, OUTPUT);

    delay(100);

    // move_forward(speed);
}

void loop()
{
    move_forward(speed);

    delay(5000);

  stop(false);

    delay(3000);
    move_backward(speed);

    delay(5000);

    stop(false);
    delay(3000);
}

void move_forward(int speed)
{
    // Serial.println("Move forward");

    //Setting CW rotation to and Left Motor  and CCW to Right Motor
    //Left Motor
    digitalWrite(INA_1, HIGH);
    digitalWrite(INB_1, LOW);
    analogWrite(PWM_1, speed);

    //Right Motor
    digitalWrite(INA_2, LOW);
    digitalWrite(INB_2, HIGH);
    analogWrite(PWM_2, speed);
}

void stop(bool slowDown)
{
    if (slowDown)
    {
        ; // ramp down speed
    }
    else
    {
        digitalWrite(INA_1, HIGH);
        digitalWrite(INB_1, HIGH);
        analogWrite(PWM_1, 0);

        digitalWrite(INA_2, HIGH);
        digitalWrite(INB_2, HIGH);
        analogWrite(PWM_2, 0);
    }
}


void move_backward(int speed)
{
    // Serial.println("Move forward");

    //Setting CW rotation to and Left Motor  and CCW to Right Motor
    //Left Motor
    digitalWrite(INA_1, LOW);
    digitalWrite(INB_1, HIGH);
    analogWrite(PWM_1, speed);

    //Right Motor
    digitalWrite(INA_2, HIGH);
    digitalWrite(INB_2, LOW);
    analogWrite(PWM_2, speed);
}
