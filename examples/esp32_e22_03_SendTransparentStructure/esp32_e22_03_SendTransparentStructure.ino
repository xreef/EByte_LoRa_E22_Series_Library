/*
 * EBYTE LoRa E22
 * Send a structured message to all devices that have same ADDH ADDL CHAN
 *
 * Write the int humidity value on serial (or reset device that send default message)
 *
 * Send a transparent message, you must check that the transmitter and receiver have the same
 * CHANNEL ADDL and ADDH
 *
 * Pai attention e22 support RSSI, if you want use that functionality you must enable RSSI on configuration
 * configuration.TRANSMISSION_MODE.enableRSSI = RSSI_ENABLED;
 *
 * and uncomment #define ENABLE_RSSI true in this sketch
 *
 * https://www.mischianti.org
 *
 * E22		  ----- esp32
 * M0         ----- 19 (or GND)
 * M1         ----- 21 (or GND)
 * RX         ----- TX2 (PullUP)
 * TX         ----- RX2 (PullUP)
 * AUX        ----- 18  (PullUP)
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */

//#define ENABLE_RSSI true

#include "Arduino.h"
#include "LoRa_E22.h"

// ---------- esp8266 pins --------------
//LoRa_E22 e22ttl100(RX, TX, AUX, M0, M1);  // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl100(D3, D4, D5, D7, D6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
//LoRa_E22 e22ttl(D2, D3); // Config without connect AUX and M0 M1

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(D2, D3); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl(&mySerial, D5, D7, D6); // AUX M0 M1
// -------------------------------------

// ---------- Arduino pins --------------
//LoRa_E22 e22ttl(4, 5, 3, 7, 6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
//LoRa_E22 e22ttl100(4, 5); // Config without connect AUX and M0 M1

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(4, 5); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl(&mySerial, 3, 7, 6); // AUX M0 M1
// -------------------------------------

// ---------- esp32 pins --------------
LoRa_E22 e22ttl100(&Serial2, 18, 21, 19); //  RX AUX M0 M1

//LoRa_E22 e22ttl100(&Serial2, 22, 4, 18, 21, 19, UART_BPS_RATE_9600); //  esp32 RX <-- e22 TX, esp32 TX --> e22 RX AUX M0 M1
// -------------------------------------

struct Message {
    char type[5] = "HUM";
    char message[8] = "Room";
    byte humidity;
} message;

void setup() {
  Serial.begin(9600);
  delay(500);

  // Startup all pins and UART
  e22ttl100.begin();

  Serial.println("Hi, I'm going to send message!");

	message.humidity = 65;

  // Send message
  ResponseStatus rs = e22ttl100.sendMessage(&message, sizeof(Message));
  // Check If there is some problem of succesfully send
  Serial.println(rs.getResponseDescription());
}

void loop() {
	// If something available
  if (e22ttl100.available()>1) {
	  // read the String message
#ifdef ENABLE_RSSI
		ResponseStructContainer rsc = e22ttl100.receiveMessageRSSI(sizeof(Message));
#else
		ResponseStructContainer rsc = e22ttl100.receiveMessage(sizeof(Message));
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
		Serial.println(message.humidity, DEC);
#ifdef ENABLE_RSSI
			Serial.println(rsc.rssi, DEC);
#endif
	}
  }
  if (Serial.available()) {
	  message.humidity = Serial.parseInt();
	  // Send message
	  ResponseStatus rs = e22ttl100.sendMessage(&message, sizeof(Message));
	  // Check If there is some problem of succesfully send
	  Serial.println(rs.getResponseDescription());
  }
}

