#include "Arduino.h"

#ifndef EMGXBEE_H_
#define EMGXBEE_H_

class EMGxBee {
public:
	void begin(HardwareSerial &Serial, uint32_t baudRate);
	void updateData();
	virtual ~EMGxBee();

	uint16_t getAccZ();
	uint16_t getAccY();
	uint16_t getAccX();
	uint16_t getEmg1();
	uint16_t getEmg2();

private:
	struct {
		uint16_t x, y, z;
		uint16_t emg1, emg2;
	} _sData;
	HardwareSerial *_pSerial;

	uint8_t arr[21];
};

#endif
