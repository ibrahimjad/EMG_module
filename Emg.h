#include "Arduino.h"

#ifndef EMGXBEE_H_
#define EMGXBEE_H_

class Emg {
public:
	void begin(HardwareSerial &Serial, uint32_t baudRate);		//establishes the connection between microcontroller and XBee
	void updateData();		//update the value of accelerometer and emg channel if checksum is verified
	virtual ~Emg();

	uint16_t getAccZ();		//return acceleration in z-axis
	uint16_t getAccY();		//return acceleration in y-axis
	uint16_t getAccX();		//return acceleration in x-axis
	uint16_t getEmg1();		//return emg channel 1 value
	uint16_t getEmg2();		//return emg channel 2 value

private:
	struct {
		uint16_t x, y, z;
		uint16_t emg1, emg2;
	} _sData;
	HardwareSerial *_pSerial;

	uint8_t arr[21];
};

#endif
