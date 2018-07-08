#ifndef Encoder_h
#define Encoder_h

class Encoder
{
public:
	Encoder();
	Encoder(int intPinA, int pin_b, bool inv_dir=false);
	void init();
	void count();

	long getCounter(); 	// motor count, not load
	void resetCounter();
private:
	long counter=0;
	int pinA, pinB;
	bool invDir;
};
#endif
