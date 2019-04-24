#include "Emg.h"

void Emg::begin(HardwareSerial &serial, uint32_t baudRate) {		//establishes the connection between microcontroller and XBee
	_pSerial = &serial;
	_pSerial->begin(baudRate);
}

uint16_t Emg::getAccZ() {		//returns acceleration in z-axis
	return _sData.z;
}

uint16_t Emg::getAccY() {		//returns acceleration in y-axis
	return _sData.y;
}

uint16_t Emg::getAccX() {		//returns acceleration in x-axis
	return _sData.x;
}

uint16_t Emg::getEmg1() {		//returns emg channel 1 value
	return _sData.emg1;
}

uint16_t Emg::getEmg2() {		//returns emg channel 2 value
	return _sData.emg2;
}

void Emg::updateData() {		//updates data when a new package is received
	while (_pSerial->available()) {		//check incoming data
		if (_pSerial->read() == 0x7E)		//check the start of new packet
			if (_pSerial->read() == 0x00 && _pSerial->read() == 0x14) {		//check that 14 bytes are being received
				uint16_t checkSum = 0;

				for (int i = 0; i < 21; i++) {		//read data from serial and store it in array
					arr[i] = _pSerial->read();
					checkSum = checkSum + arr[i];		//calculate checksum
				}

				if ((checkSum & 0xFF) == 0xFF) {		//verify checksum, if true, update the values of the accelerometer and emg channels.
					uint16_t tmpData = arr[10];
					_sData.z = (tmpData << 8) | arr[11];
					tmpData = arr[12];
					_sData.y = (tmpData << 8) | arr[13];
					tmpData = arr[14];
					_sData.x = (tmpData << 8) | arr[15];
					tmpData = arr[16];
					_sData.emg1 = (tmpData << 8) | arr[17];
					tmpData = arr[18];
					_sData.emg2 = (tmpData << 8) | arr[19];
				}
			}
	}
}

Emg::~Emg() {
	_pSerial->end();
}
