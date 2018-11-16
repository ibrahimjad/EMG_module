#include "EMGxBee.h"

void EMGxBee::begin(HardwareSerial &serial, uint32_t baudRate) {
	xBeeSerial = &serial;
	xBeeSerial->begin(baudRate);
}

void EMGxBee::getData(){
	uint8_t checkSum = 0;

	while(xBeeSerial->available()){
		if (xBeeSerial->read() == 0x7E)
		  if (xBeeSerial->read() == 0x00 && xBeeSerial->read() == 0x14){
				for (int i=0; i<21; i++){
					arr[i] = xBeeSerial->read();
					checkSum = checkSum + arr[i];
				}

				if (checkSum == 0xFF){
					uint16_t tmpData = arr[10];
					data.z = (tmpData << 8) | arr[11];
					tmpData = arr[12];
					data.y = (tmpData << 8) | arr[13];
					tmpData = arr[14];
					data.x = (tmpData << 8) | arr[15];
					tmpData = arr[16];
					data.emg1 = (tmpData << 8) | arr[17];
					tmpData = arr[18];
					data.emg2 = (tmpData << 8) | arr[19];
				}
			}
	}
}

EMGxBee::~EMGxBee() {
	xBeeSerial->end();
}
