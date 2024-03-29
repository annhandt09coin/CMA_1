#include <stdlib.h>
#include "Arduino.h"
#include "pins_arduino.h"
//#include "esp32-hal-uart.h"
#define ALL_GOOD 0
#define ERROR_COMMAND_RESPONSE_TIMEOUT 1
#define ERROR_CORRUPT_RESPONSE 2
#define ERROR_WRONG_OPCODE_RESPONSE 3
#define RESPONSE_SUCCESS 11
#define RESPONSE_FAIL 12

#define MAX_MSG_SIZE 255
#define COMMAND_TIME_OUT 2000 
class RFID
{
public:
	RFID(void);
	bool begin(Stream &serialPort = Serial2);
	unsigned char RFID::calculateCRC (unsigned char * uBuff, unsigned char uBuffLen);  
	uint8_t msg[MAX_MSG_SIZE];
	void sendMessage(uint8_t opcode, uint8_t *data = 0, uint8_t size = 0, uint16_t timeOut = COMMAND_TIME_OUT, boolean waitForResponse = true);
	void sendCommand(uint16_t timeOut = COMMAND_TIME_OUT, boolean waitForResponse = true);
	void set_mode_timming(uint8_t mode);
	void set_timing_message(uint8_t mode);
	void set_reset)reader();
	void set_link_selec(uint8_t mode);
	uint8_t RFID::readData(uint8_t bank, uint32_t address, uint8_t *dataRead, uint8_t &dataLengthRead, uint16_t timeOut);
	uint8_t RFID::readTagEPC(uint8_t *epc, uint8_t &epcLength, uint16_t timeOut);
	bool RFID::check();
	uint8_t RFID::parseResponse(void);
	uint8_t RFID::readData(uint8_t bank, uint32_t address, uint8_t *dataRead, uint8_t &dataLengthRead, uint16_t timeOut);
private:
	Stream *_RFIDSERIAL;
	uint8_t _head = 0;
};