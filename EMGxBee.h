#include "Arduino.h"

#ifndef EMGXBEE_H_
#define EMGXBEE_H_

class EMGxBee {
public:
	~EMGxBee();

	void begin(HardwareSerial &Serial, uint32_t baudRate);
	void getData();

	struct{
		uint16_t x,y,z;
		uint16_t emg1, emg2;
	} data;

private:
	HardwareSerial *xBeeSerial;
	uint8_t arr[21];
};

#endif
