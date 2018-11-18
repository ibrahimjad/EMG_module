#include "EMGxBee.h"

void EMGxBee::begin(HardwareSerial &serial, uint32_t baudRate) {
	xBeeSerial = &serial;
	xBeeSerial->begin(baudRate);
}

uint16_t EMGxBee::getAccX(){
	return s_data.x;
}

uint16_t EMGxBee::getAccY(){
	return s_data.y;
}

uint16_t EMGxBee::getAccZ(){
	return s_data.z;
}

uint16_t EMGxBee::getEMG1(){
	return s_data.emg1;
}

uint16_t EMGxBee::getEMG2(){
	return s_data.emg2;
}

void EMGxBee::updateData(){
	uint16_t checkSum = 0;

	while(xBeeSerial->available()){
		if (xBeeSerial->read() == 0x7E)
		  if (xBeeSerial->read() == 0x00 && xBeeSerial->read() == 0x14){
				for (int i=0; i<21; i++){
					arr[i] = xBeeSerial->read();
					checkSum = checkSum + arr[i];
				}

				if ((checkSum & 0xFF) == 0xFF){
					uint16_t tmpData = arr[10];
					s_data.z = (tmpData << 8) | arr[11];
					tmpData = arr[12];
					s_data.y = (tmpData << 8) | arr[13];
					tmpData = arr[14];
					s_data.x = (tmpData << 8) | arr[15];
					tmpData = arr[16];
					s_data.emg1 = (tmpData << 8) | arr[17];
					tmpData = arr[18];
					s_data.emg2 = (tmpData << 8) | arr[19];
				}
			}
	}
}

EMGxBee::~EMGxBee() {
	xBeeSerial->end();
}
