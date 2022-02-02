/*
 * EBYTE LoRa E22
 * send a structured message to the device that have ADDH ADDL CHAN -> 0 DESTINATION_ADDL 23
 *
 * The receiver read the first part of the packet and undestand the type.
 * If the type is HUMI read the message and the humidity as int
 * else read the temperature as float.
 * I use byte array because some microcontroller can have different size for float
 *
 * You must configure 2 device: one as SENDER (with FIXED SENDER config) and uncomment the relative
 * define with the correct DESTINATION_ADDL, and one as RECEIVER (with FIXED RECEIVER config)
 * and uncomment the relative define with the correct DESTINATION_ADDL.
 *
 * Write a string on serial monitor or reset to resend default value.
 *
 * You must uncommend the correct constructor and set the correct AUX_PIN define.
 *
 * by Renzo Mischianti <https://www.mischianti.org>
 *
 * https://www.mischianti.org
 *
 * E22		  ----- WeMos D1 mini	----- esp32			----- Arduino Nano 33 IoT	----- Arduino MKR	----- ArduinoUNO
 * M0         ----- D7 (or GND)		----- 19 (or GND)	----- 4 (or GND)			----- 2 (or GND)	----- 7 Volt div (or GND)
 * M1         ----- D6 (or GND)		----- 21 (or GND)	----- 6 (or GND)			----- 4 (or GND)	----- 6 Volt div (or GND)
 * TX         ----- D3 (PullUP)		----- TX2 (PullUP)	----- TX1 (PullUP)			----- 14 (PullUP)	----- 4 (PullUP)
 * RX         ----- D4 (PullUP)		----- RX2 (PullUP)	----- RX1 (PullUP)			----- 13 (PullUP)	----- 5 Volt div (PullUP)
 * AUX        ----- D5 (PullUP)		----- 15  (PullUP)	----- 2  (PullUP)			----- 0  (PullUP)	----- 3 (PullUP)
 * VCC        ----- 3.3v/5v			----- 3.3v/5v		----- 3.3v/5v				----- 3.3v/5v		----- 3.3v/5v
 * GND        ----- GND				----- GND			----- GND					----- GND			----- GND
 *
 */

#define MESSAGE_TYPE "HUMI"

// With FIXED SENDER configuration
//#define DESTINATION_ADDL 3
//#define ROOM "Kitchen"

// With FIXED RECEIVER configuration
#define DESTINATION_ADDL 2
#define ROOM "Bathroo"

// If you want use RSSI uncomment //#define ENABLE_RSSI true
// and use relative configuration with RSSI enabled
// #define ENABLE_RSSI true

#include "Arduino.h"
#include "LoRa_E22.h"

// ---------- esp8266 pins --------------
//LoRa_E22 e22ttl(RX, TX, AUX, M0, M1);  // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl(D3, D4, D5, D7, D6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
//LoRa_E22 e22ttl(D2, D3); // Config without connect AUX and M0 M1

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(D2, D3); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl(&mySerial, D5, D7, D6); // AUX M0 M1
// -------------------------------------

// ---------- Arduino pins --------------
//LoRa_E22 e22ttl(4, 5, 3, 7, 6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
//LoRa_E22 e22ttl(4, 5); // Config without connect AUX and M0 M1

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(4, 5); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl(&mySerial, 3, 7, 6); // AUX M0 M1
// -------------------------------------

// ------------- Arduino Nano 33 IoT -------------
// LoRa_E22 e22ttl(&Serial1, 2, 4, 6); //  RX AUX M0 M1
// -------------------------------------------------

// ------------- Arduino MKR WiFi 1010 -------------
// LoRa_E22 e22ttl(&Serial1, 0, 2, 4); //  RX AUX M0 M1
// -------------------------------------------------

// ---------- esp32 pins --------------
 LoRa_E22 e22ttl(&Serial2, 15, 21, 19); //  RX AUX M0 M1

//LoRa_E22 e22ttl(&Serial2, 22, 4, 18, 21, 19, UART_BPS_RATE_9600); //  esp32 RX <-- e22 TX, esp32 TX --> e22 RX AUX M0 M1
// -------------------------------------

struct MessageTemperature {
	char type[5];
	char message[8];
	byte temperature[4];
};

struct MessageHumidity {
	char type[5];
	char message[8];
	byte humidity;
};

void setup() {
	Serial.begin(9600);
	while(!Serial);
	delay(500);

	// Startup all pins and UART
	e22ttl.begin();

	Serial.println("Hi, I'm going to send message!");

	struct MessageHumidity message = { "HUMI", ROOM, 80 };
	// Send message
	ResponseStatus rs = e22ttl.sendFixedMessage(0, DESTINATION_ADDL, 23, &message, sizeof(MessageHumidity));
	// Check If there is some problem of succesfully send
	Serial.println(rs.getResponseDescription());

	delay(1000);

	struct MessageTemperature messageT = { "TEMP", ROOM, 0 };
	*(float*)(messageT.temperature) = 19.2;

	// Send message
	ResponseStatus rsT = e22ttl.sendFixedMessage(0, DESTINATION_ADDL, 23, &messageT, sizeof(MessageTemperature));
	// Check If there is some problem of succesfully send
	Serial.println(rsT.getResponseDescription());
}

void loop() {
	// If something available
	if (e22ttl.available() > 1) {
		// read the String message
		char type[5]; // first part of structure
		ResponseContainer rs = e22ttl.receiveInitialMessage(sizeof(type));
		String typeStr = rs.data;

		// Is something goes wrong print error
		if (rs.status.code != 1) {
			Serial.println(rs.status.getResponseDescription());
		} else {
			Serial.println(typeStr);
			if (typeStr == "TEMP") {
				struct MessageTemperaturePartial {
					char message[8];
					byte temperature[4];
				};

				ResponseStructContainer rsc = e22ttl.receiveMessage( sizeof(MessageTemperaturePartial));
				struct MessageTemperaturePartial message = *(MessageTemperaturePartial*) rsc.data;

				Serial.println(*(float*)(message.temperature));
				Serial.println(message.message);
				rsc.close();
			} else if (typeStr == "HUMI") {
				struct MessageHumidityPartial {
					char message[8];
					byte humidity;
				};

				ResponseStructContainer rsc = e22ttl.receiveMessage(sizeof(MessageHumidityPartial));
				struct MessageHumidityPartial message = *(MessageHumidityPartial*) rsc.data;

				Serial.println(message.humidity);
				Serial.println(message.message);
				rsc.close();
			} else {
				Serial.println("Something goes wrong!!");
			}
		}
	}
 	if (Serial.available()) {
 		if (MESSAGE_TYPE == "HUMI") {
 			struct MessageHumidity message = { "HUMI", ROOM, 0 };
 			message.humidity = Serial.parseInt();

 	 		// Send message
 	 		ResponseStatus rs = e22ttl.sendFixedMessage(0, DESTINATION_ADDL, 23, &message, sizeof(MessageHumidity));
 	 		// Check If there is some problem of succesfully send
 	 		Serial.println(rs.getResponseDescription());
 		} else {
 			struct MessageTemperature message = { "TEMP", ROOM, 0 };
 			*(float*)(message.temperature) = Serial.parseFloat();

 	 		// Send message
 	 		ResponseStatus rs = e22ttl.sendFixedMessage(0, DESTINATION_ADDL, 23, &message, sizeof(MessageTemperature));
 	 		// Check If there is some problem of succesfully send
 	 		Serial.println(rs.getResponseDescription());
 		}
 	}
}
