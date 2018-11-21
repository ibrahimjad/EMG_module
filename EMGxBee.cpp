#include "EMGxBee.h"

void EMGxBee::begin(HardwareSerial &serial, uint32_t baudRate) {
	_pSerial = &serial;
	_pSerial->begin(baudRate);
}

uint16_t EMGxBee::getAccZ() {
	return _sData.z;
}

uint16_t EMGxBee::getAccY() {
	return _sData.y;
}

uint16_t EMGxBee::getAccX() {
	return _sData.x;
}

uint16_t EMGxBee::getEmg1() {
	return _sData.emg1;
}

uint16_t EMGxBee::getEmg2() {
	return _sData.emg2;
}

void EMGxBee::updateData() {
	while (_pSerial->available()) {
		if (_pSerial->read() == 0x7E)
			if (_pSerial->read() == 0x00 && _pSerial->read() == 0x14) {
				uint16_t checkSum = 0;

				for (int i = 0; i < 21; i++) {
					arr[i] = _pSerial->read();
					checkSum = checkSum + arr[i];
				}

				if ((checkSum & 0xFF) == 0xFF) {
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

EMGxBee::~EMGxBee() {
	_pSerial->end();
}
