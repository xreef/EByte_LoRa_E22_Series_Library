/*
 * EBYTE LoRa E22 Series
 *
 * AUTHOR:  Renzo Mischianti
 * VERSION: 1.0.0
 *
 * https://www.mischianti.org
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Renzo Mischianti www.mischianti.org All right reserved.
 *
 * You may copy, alter and reuse this code in any way you like, but please leave
 * reference to www.mischianti.org in your comments if you redistribute this code.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef LoRa_E22_h
#define LoRa_E22_h

#define M0_PIN	7
#define M1_PIN	8
#define AUX_PIN	A0
#define SOFT_RX_PIN	10
#define SOFT_TX_PIN 11

#if !defined(__STM32F1__) && !defined(ESP32)
#define ACTIVATE_SOFTWARE_SERIAL
#endif
#if defined(ESP32)
#define HARDWARE_SERIAL_SELECTABLE_PIN
#endif

#ifdef ACTIVATE_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
#endif

#include <includes/statesNaming.h>

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Uncomment to enable printing out nice debug messages.
//#define LoRa_E22_DEBUG

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

// Setup debug printing macros.
#ifdef LoRa_E22_DEBUG
#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
#define DEBUG_PRINT(...) {}
#define DEBUG_PRINTLN(...) {}
#endif

enum MODE_TYPE {
	MODE_0_NORMAL = 0,
	MODE_1_WOR = 1,
	MODE_2_CONFIGURATION = 2,
	MODE_2_PROGRAM = 2,
	MODE_3_SLEEP = 3,
	MODE_INIT = 0xFF
};

enum PROGRAM_COMMAND {
	WRITE_CFG_PWR_DWN_SAVE = 0xC0,
	READ_CONFIGURATION = 0xC1,
	WRITE_CFG_PWR_DWN_LOSE = 0xC2,
	WRONG_FORMAT = 0xFF,
	RETURNED_COMMAND = 0xC1,

	SPECIAL_WIFI_CONF_COMMAND = 0xCF

//  , READ_MODULE_VERSION   	= 0xC3,
//  WRITE_RESET_MODULE     	= 0xC4
};

enum REGISTER_ADDRESS {
	REG_ADDRESS_CFG	= 0x00,
	REG_ADDRESS_SPED 		= 0x03,
	REG_ADDRESS_TRANS_MODE 	= 0x04,
	REG_ADDRESS_CHANNEL 	= 0x05,
	REG_ADDRESS_OPTION	 	= 0x06,
	REG_ADDRESS_CRYPT	 	= 0x07,
	REG_ADDRESS_PID		 	= 0x80
};

enum PACKET_LENGHT {
	PL_CONFIGURATION 	= 0x09,

	PL_SPED				= 0x01,
	PL_OPTION			= 0x01,
	PL_TRANSMISSION_MODE= 0x01,
	PL_CHANNEL			= 0x01,
	PL_CRYPT			= 0x02,
	PL_PID				= 7
};

#pragma pack(push, 1)
struct Speed {
	uint8_t airDataRate :3; //bit 0-2
	String getAirDataRateDescription() {
		return getAirDataRateDescriptionByParams(this->airDataRate);
	}

	uint8_t uartParity :2; //bit 3-4
	String getUARTParityDescription() {
		return getUARTParityDescriptionByParams(this->uartParity);
	}

	uint8_t uartBaudRate :3; //bit 5-7
	String getUARTBaudRateDescription() {
		return getUARTBaudRateDescriptionByParams(this->uartBaudRate);
	}

};

struct TransmissionMode {
	byte WORPeriod :3; //bit 2,1,0
	String getWORPeriodByParamsDescription() {
		return getWORPeriodByParams(this->WORPeriod);
	}
	byte WORTransceiverControl :1; //bit 3
	String getWORTransceiverControlDescription() {
		return getWORTransceiverControlByParams(this->WORTransceiverControl);
	}
	byte enableLBT :1; //bit 4
	String getLBTEnableByteDescription() {
		return getLBTEnableByteByParams(this->enableLBT);
	}
	byte enableRepeater :1; //bit 5
	String getRepeaterModeEnableByteDescription() {
		return getRepeaterModeEnableByteByParams(this->enableRepeater);
	}
	byte fixedTransmission :1; //bit 6
	String getFixedTransmissionDescription() {
		return getFixedTransmissionDescriptionByParams(this->fixedTransmission);
	}

	byte enableRSSI :1; //bit 7
	String getRSSIEnableByteDescription() {
		return getRSSIEnableByteByParams(this->enableRSSI);
	}
};

struct Option {
	uint8_t transmissionPower :2; //bit 0-1
	String getTransmissionPowerDescription() {
		return getTransmissionPowerDescriptionByParams(this->transmissionPower);
	}
	uint8_t reserve :3; //bit 2-3
	//	String getAirDataRate() {
	//		return getAirDataRateDescriptionByParams(this->airDataRate);
	//	}
	uint8_t RSSIAmbientNoise :1; //bit 5
	String getRSSIAmbientNoiseEnable() {
		return getRSSIAmbientNoiseEnableByParams(this->RSSIAmbientNoise);
	}

	uint8_t subPacketSetting :2; //bit 6-7
	String getSubPacketSetting() {
		return getSubPacketSettingByParams(this->subPacketSetting);
	}

};

struct Crypt {
	byte CRYPT_H = 0;
	byte CRYPT_L = 0;
};

struct Configuration {
	byte COMMAND = 0;
	byte STARTING_ADDRESS = 0;
	byte LENGHT = 0;

	byte ADDH = 0;
	byte ADDL = 0;
	byte NETID = 0;

	struct Speed SPED;
	struct Option OPTION;

	byte CHAN = 0;
	String getChannelDescription() {
		return String(this->CHAN + OPERATING_FREQUENCY) + F("MHz");
	}

	struct TransmissionMode TRANSMISSION_MODE;

	struct Crypt CRYPT;
};

struct ModuleInformation {
	byte COMMAND = 0;
	byte STARTING_ADDRESS = 0;
	byte LENGHT = 0;

	byte reserved[3] = {0,0,0};

	byte model = 0;
	byte version = 0;
	byte features = 0;
	byte end = 0;
};

struct ResponseStatus {
	Status code;
	String getResponseDescription() {
		return getResponseDescriptionByParams(this->code);
	}
};

struct ResponseStructContainer {
	void *data;
	byte rssi;
	ResponseStatus status;
	void close() {
		free(this->data);
	}
};
struct ResponseContainer {
	String data;
	byte rssi;
	ResponseStatus status;
};

struct ConfigurationMessage
{
	byte specialCommand1 = 0xCF;
	byte specialCommand2 = 0xCF;

	unsigned char message[];
};

//struct FixedStransmission {
//		byte ADDL = 0;
//		byte ADDH = 0;
//		byte CHAN = 0;
//		void *message;
//};
#pragma pack(pop)

class LoRa_E22 {
public:
#ifdef ACTIVATE_SOFTWARE_SERIAL
	LoRa_E22(byte txE32pin, byte rxE32pin,
			UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
	LoRa_E22(byte txE32pin, byte rxE32pin, byte auxPin, UART_BPS_RATE bpsRate =
			UART_BPS_RATE_9600);
	LoRa_E22(byte txE32pin, byte rxE32pin, byte auxPin, byte m0Pin, byte m1Pin,
			UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
#endif

	LoRa_E22(HardwareSerial* serial, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
	LoRa_E22(HardwareSerial* serial, byte auxPin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
	LoRa_E22(HardwareSerial* serial, byte auxPin, byte m0Pin, byte m1Pin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);

#ifdef HARDWARE_SERIAL_SELECTABLE_PIN
	LoRa_E22(byte txE32pin, byte rxE32pin, HardwareSerial* serial, UART_BPS_RATE bpsRate, uint32_t serialConfig = SERIAL_8N1);
	LoRa_E22(byte txE32pin, byte rxE32pin, HardwareSerial* serial, byte auxPin, UART_BPS_RATE bpsRate, uint32_t serialConfig = SERIAL_8N1);
	LoRa_E22(byte txE32pin, byte rxE32pin, HardwareSerial* serial, byte auxPin, byte m0Pin, byte m1Pin, UART_BPS_RATE bpsRate, uint32_t serialConfig = SERIAL_8N1);
#endif

#ifdef ACTIVATE_SOFTWARE_SERIAL
	LoRa_E22(SoftwareSerial* serial,
			UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
	LoRa_E22(SoftwareSerial* serial, byte auxPin, UART_BPS_RATE bpsRate =
			UART_BPS_RATE_9600);
	LoRa_E22(SoftwareSerial* serial, byte auxPin, byte m0Pin, byte m1Pin,
			UART_BPS_RATE bpsRate = UART_BPS_RATE_9600);
#endif

//		LoRa_E22(byte txE32pin, byte rxE32pin, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600, MODE_TYPE mode = MODE_0_NORMAL);
//		LoRa_E22(HardwareSerial* serial = &Serial, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600, MODE_TYPE mode = MODE_0_NORMAL);
//		LoRa_E22(SoftwareSerial* serial, UART_BPS_RATE bpsRate = UART_BPS_RATE_9600, MODE_TYPE mode = MODE_0_NORMAL);

	bool begin();
	Status setMode(uint8_t mode);

	ResponseStructContainer getConfiguration();
	ResponseStatus setConfiguration(Configuration configuration,
			PROGRAM_COMMAND saveType = WRITE_CFG_PWR_DWN_LOSE);

	ResponseStructContainer getModuleInformation();
	ResponseStatus resetModule();

	ResponseStatus sendMessage(const void *message, const uint8_t size);

    ResponseContainer receiveMessageUntil(char delimiter = '\0');
	ResponseStructContainer receiveMessage(const uint8_t size);
	ResponseStructContainer receiveMessageRSSI(const uint8_t size);

	ResponseStructContainer receiveMessageComplete(const uint8_t size, bool enableRSSI);

	ResponseStatus sendMessage(const String message);
	ResponseContainer receiveMessage();
	ResponseContainer receiveMessageRSSI();

	ResponseContainer receiveMessageComplete(bool enableRSSI);

	ResponseStatus sendFixedMessage(byte ADDH, byte ADDL, byte CHAN,
			const String message);

	ResponseStatus sendConfigurationMessage( byte ADDH,byte ADDL, byte CHAN,
			Configuration *configuration, PROGRAM_COMMAND programCommand = WRITE_CFG_PWR_DWN_SAVE);

	ResponseStatus sendBroadcastFixedMessage(byte CHAN, const String message);

	ResponseStatus sendFixedMessage(byte ADDH, byte ADDL, byte CHAN,
			const void *message, const uint8_t size);
	ResponseStatus sendBroadcastFixedMessage(byte CHAN, const void *message,
			const uint8_t size);

	ResponseContainer receiveInitialMessage(const uint8_t size);

//	int available(unsigned long timeout = 1000);
	int available();
private:
	HardwareSerial* hs;

#ifdef ACTIVATE_SOFTWARE_SERIAL
	SoftwareSerial* ss;
#endif

	bool isSoftwareSerial = true;

	int8_t txE32pin = -1;
	int8_t rxE32pin = -1;
	int8_t auxPin = -1;

#ifdef HARDWARE_SERIAL_SELECTABLE_PIN
	uint32_t serialConfig = SERIAL_8N1;
#endif

	int8_t m0Pin = -1;
	int8_t m1Pin = -1;

	unsigned long halfKeyloqKey = 0x06660708;
	unsigned long encrypt(unsigned long data);
	unsigned long decrypt(unsigned long data);

	UART_BPS_RATE bpsRate = UART_BPS_RATE_9600;

	struct NeedsStream {
		template<typename T>
		void begin(T &t, int baud) {
			DEBUG_PRINTLN("Begin ");
			t.setTimeout(500);
			t.begin(baud);
			stream = &t;
		}

#ifdef HARDWARE_SERIAL_SELECTABLE_PIN
//		  template< typename T >
//		  void begin( T &t, int baud, SerialConfig config ){
//			  DEBUG_PRINTLN("Begin ");
//			  t.setTimeout(500);
//			  t.begin(baud, config);
//			  stream = &t;
//		  }
//
		template< typename T >
		void begin( T &t, int baud, uint32_t config ) {
			DEBUG_PRINTLN("Begin ");
			t.setTimeout(500);
			t.begin(baud, config);
			stream = &t;
		}

		template< typename T >
		void begin( T &t, int baud, uint32_t config, int8_t txE32pin, int8_t rxE32pin ) {
			DEBUG_PRINTLN("Begin ");
			t.setTimeout(500);
			t.begin(baud, config, txE32pin, rxE32pin);
			stream = &t;
		}
#endif

		void listen() {

		}

		Stream *stream;
	};
	NeedsStream serialDef;

	MODE_TYPE mode = MODE_0_NORMAL;

	void managedDelay(unsigned long timeout);
	Status waitCompleteResponse(unsigned long timeout = 1000,
			unsigned int waitNoAux = 100);
	void flush();
	void cleanUARTBuffer();

	Status sendStruct(void *structureManaged, uint16_t size_);
	Status receiveStruct(void *structureManaged, uint16_t size_);
	void writeProgramCommand(PROGRAM_COMMAND cmd, REGISTER_ADDRESS addr, PACKET_LENGHT pl);

	RESPONSE_STATUS checkUARTConfiguration(MODE_TYPE mode);

#ifdef LoRa_E22_DEBUG
	void printParameters(struct Configuration *configuration);
#endif
};

#endif
