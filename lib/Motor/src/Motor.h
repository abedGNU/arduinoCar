#ifndef Motor_h
#define Motor_h

#include <Encoder.h>

class Motor
{
public:
	Motor();
	Motor(int pinA, int pinB, int pin_PWM, bool inv_Dir, int encA, int encB);
	Encoder *enc;
	double maxSpeed;						 			// motor shaft
	double gearRatio;						 			// i = 30, 40, 50, .... not tau (1/30, 1/40,....)
	// load pulse per round
	int pulsePerLoadRound = 390; 			// gearbox's output shaft. 

	void setLoadSpeed(double speed); // gearbox's output shaft
	long getLoadSpeed();						 // gearbox's output shaft
	double getLoadAngle();
  //
	long setMotorSpeed();						// motor shaft
	long getMotorSpeed();				 		// motor shaft
	void stop();

private:
	int enA, enB;
	int pinPwm;
	bool invDir;
	double loadAngle ;

	void setDirection(double speed);
};
#endif
