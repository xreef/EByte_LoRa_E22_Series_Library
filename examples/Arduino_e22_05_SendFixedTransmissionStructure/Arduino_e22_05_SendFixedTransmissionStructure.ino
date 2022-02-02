/*
 * EBYTE LoRa E22
 * send a structured message to all devices that have same addh addl chan
 *
 * write the int humidity value on serial (or reset device that send default message)
 *
 * Send a transparent message, you must check that the transmitter and receiver have the same
 * CHANNEL ADDL and ADDH
 *
 * Pai attention e22 support RSSI, if you want use that functionality you must enable RSSI on configuration
 * configuration.TRANSMISSION_MODE.enableRSSI = RSSI_ENABLED;
 *
 * and uncomment #define ENABLE_RSSI true in this sketch
 *
 * Renzo Mischianti <https://www.mischianti.org>
 * https://www.mischianti.org/category/my-libraries/ebyte-lora-e22-devices/
 *
 * E22		  ----- Arduino
 * M0         ----- 7 (or GND)
 * M1         ----- 6 (or GND)
 * RX         ----- 4 (PullUP)
 * TX         ----- 5 (PullUP)
 * AUX        ----- 3  (PullUP)
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */

// with this RECEIVER_ADDL 2 you must set
// FIXED SENDER configuration to the other device and
// FIXED RECEIVER to this device

// with this RECEIVER_ADDL 3 you must set
// FIXED RECEIVERconfiguration to the other device and
// FIXED SENDER  to this device
#define RECEIVER_ADDL 3

// If you want use RSSI uncomment //#define ENABLE_RSSI true
// and use relative configuration with RSSI enabled
//#define ENABLE_RSSI true

#include "Arduino.h"
#include "LoRa_E22.h"

// ---------- esp8266 pins --------------
//LoRa_E22 e22ttl(RX, TX, AUX, M0, M1);  // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
// LoRa_E22 e22ttl(D3, D4, D5, D7, D6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
//LoRa_E22 e22ttl(D2, D3); // Config without connect AUX and M0 M1

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(D2, D3); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl(&mySerial, D5, D7, D6); // AUX M0 M1
// -------------------------------------

// ---------- Arduino pins --------------
LoRa_E22 e22ttl(4, 5, 3, 7, 6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
//LoRa_E22 e22ttl(4, 5); // Config without connect AUX and M0 M1

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(4, 5); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl(&mySerial, 3, 7, 6); // AUX M0 M1
// -------------------------------------

// ------------- Arduino Nano 33 IoT -------------
// LoRa_E22 e22ttl(&Serial1, 2, 4, 6); //  RX AUX M0 M1
// -------------------------------------------------

// ------------- Arduino MKR WiFi 1010 -------------
// LoRa_E22 e22ttl(&Serial1, 2, 4, 6); //  RX AUX M0 M1
// -------------------------------------------------

// ---------- esp32 pins --------------
//LoRa_E22 e22ttl(&Serial2, 18, 21, 19); //  RX AUX M0 M1

//LoRa_E22 e22ttl(&Serial2, 22, 4, 18, 21, 19, UART_BPS_RATE_9600); //  esp32 RX <-- e22 TX, esp32 TX --> e22 RX AUX M0 M1
// -------------------------------------

struct Message {
	char type[5] = "TEMP";
	char message[8] = "Kitchen";
	byte temperature[4];
} message;

void setup() {
  Serial.begin(9600);
  delay(500);

  // Startup all pins and UART
  e22ttl.begin();

  Serial.println("Hi, I'm going to send message!");

	struct Message {
		char type[5] = "TEMP";
		char message[8] = "Kitchen";
		byte temperature[4];
	} message;

	*(float*)(message.temperature) = 19.2;

  // Send message
  ResponseStatus rs = e22ttl.sendFixedMessage(0, RECEIVER_ADDL, 23, &message, sizeof(Message));
  // Check If there is some problem of succesfully send
  Serial.println(rs.getResponseDescription());
}

void loop() {
	// If something available
  if (e22ttl.available()>1) {
	  // read the String message
#ifdef ENABLE_RSSI
		ResponseStructContainer rsc = e22ttl.receiveMessageRSSI(sizeof(Message));
#else
		ResponseStructContainer rsc = e22ttl.receiveMessage(sizeof(Message));
#endif

	// Is something goes wrong print error
	if (rsc.status.code!=1){
		Serial.println(rsc.status.getResponseDescription());
	}else{
		// Print the data received
		Serial.println(rsc.status.getResponseDescription());
		struct Message message = *(Message*) rsc.data;
		Serial.println(message.type);
		Serial.println(message.message);
		Serial.println(*(float*)(message.temperature));

#ifdef ENABLE_RSSI
		Serial.print("RSSI: "); Serial.println(rsc.rssi, DEC);
#endif
	}
  }
  if (Serial.available()) {
		struct Message {
			char type[5] = "TEMP";
			char message[8] = "Kitchen";
			byte temperature[4];
		} message;

		*(float*)(message.temperature) = Serial.parseFloat();
	  // Send message
	  ResponseStatus rs = e22ttl.sendFixedMessage(0, RECEIVER_ADDL, 23, &message, sizeof(Message));
	  // Check If there is some problem of succesfully send
	  Serial.println(rs.getResponseDescription());
  }
}

