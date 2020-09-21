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

// with this RECEIVER_ADDL 2 you must set
// FIXED SENDER configuration to the other device and
// FIXED RECEIVER to this device
#define RECEIVER_ADDL 2

// If you want use RSSI uncomment //#define ENABLE_RSSI true
// and use relative configuration with RSSI enabled

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
void printParameters(struct Configuration configuration);
struct Message {
	char type[5] = "TEMP";
	char message[8] = "Kitchen";
	byte temperature[4];
} message;

void setup() {
  Serial.begin(9600);
  delay(500);

  // Startup all pins and UART
  e22ttl100.begin();

  Serial.println("Hi, I'm going to send message!");

	struct Message {
		char type[5] = "TEMP";
		char message[8] = "Kitchen";
		byte temperature[4];
	} message;

	*(float*)(message.temperature) = 19.2;

  // Send message
  ResponseStatus rs = e22ttl100.sendFixedMessage(0, RECEIVER_ADDL, 23, &message, sizeof(Message));
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
		Serial.println(*(float*)(message.temperature));

#ifdef ENABLE_RSSI
		Serial.print("RSSI: "); Serial.println(rsc.rssi, DEC);
#endif
	}
	ResponseStructContainer c;
	c = e22ttl100.getConfiguration();
	// It's important get configuration pointer before all other operation
	Configuration configuration = *(Configuration*) c.data;
	Serial.println(c.status.getResponseDescription());
	Serial.println(c.status.code);

	printParameters(configuration);

  }
  if (Serial.available()) {
		struct Message {
			char type[5] = "TEMP";
			char message[8] = "Kitchen";
			byte temperature[4];
		} message;

		*(float*)(message.temperature) = Serial.parseFloat();
	  // Send message
	  ResponseStatus rs = e22ttl100.sendFixedMessage(0, RECEIVER_ADDL, 23, &message, sizeof(Message));
	  // Check If there is some problem of succesfully send
	  Serial.println(rs.getResponseDescription());


  }
}
void printParameters(struct Configuration configuration) {
	DEBUG_PRINTLN("----------------------------------------");

	DEBUG_PRINT(F("HEAD : "));  DEBUG_PRINT(configuration.COMMAND, HEX);DEBUG_PRINT(" ");DEBUG_PRINT(configuration.STARTING_ADDRESS, HEX);DEBUG_PRINT(" ");DEBUG_PRINTLN(configuration.LENGHT, HEX);
	DEBUG_PRINTLN(F(" "));
	DEBUG_PRINT(F("AddH : "));  DEBUG_PRINTLN(configuration.ADDH, HEX);
	DEBUG_PRINT(F("AddL : "));  DEBUG_PRINTLN(configuration.ADDL, HEX);
	DEBUG_PRINT(F("NetID : "));  DEBUG_PRINTLN(configuration.NETID, HEX);
	DEBUG_PRINTLN(F(" "));
	DEBUG_PRINT(F("Chan : "));  DEBUG_PRINT(configuration.CHAN, DEC); DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.getChannelDescription());
	DEBUG_PRINTLN(F(" "));
	DEBUG_PRINT(F("SpeedParityBit     : "));  DEBUG_PRINT(configuration.SPED.uartParity, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.SPED.getUARTParityDescription());
	DEBUG_PRINT(F("SpeedUARTDatte     : "));  DEBUG_PRINT(configuration.SPED.uartBaudRate, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.SPED.getUARTBaudRateDescription());
	DEBUG_PRINT(F("SpeedAirDataRate   : "));  DEBUG_PRINT(configuration.SPED.airDataRate, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.SPED.getAirDataRateDescription());
	DEBUG_PRINTLN(F(" "));
	DEBUG_PRINT(F("OptionSubPacketSett: "));  DEBUG_PRINT(configuration.OPTION.subPacketSetting, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.OPTION.getSubPacketSetting());
	DEBUG_PRINT(F("OptionTranPower    : "));  DEBUG_PRINT(configuration.OPTION.transmissionPower, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.OPTION.getTransmissionPowerDescription());
	DEBUG_PRINT(F("OptionRSSIAmbientNo: "));  DEBUG_PRINT(configuration.OPTION.RSSIAmbientNoise, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.OPTION.getRSSIAmbientNoiseEnable());
	DEBUG_PRINTLN(F(" "));
	DEBUG_PRINT(F("TransModeWORPeriod : "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.WORPeriod, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getWORPeriodByParamsDescription());
	DEBUG_PRINT(F("TransModeTransContr: "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.WORTransceiverControl, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getWORTransceiverControlDescription());
	DEBUG_PRINT(F("TransModeEnableLBT : "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.enableLBT, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getLBTEnableByteDescription());
	DEBUG_PRINT(F("TransModeEnableRSSI: "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.enableRSSI, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getRSSIEnableByteDescription());
	DEBUG_PRINT(F("TransModeEnabRepeat: "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.enableRepeater, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getRepeaterModeEnableByteDescription());
	DEBUG_PRINT(F("TransModeFixedTrans: "));  DEBUG_PRINT(configuration.TRANSMISSION_MODE.fixedTransmission, BIN);DEBUG_PRINT(" -> "); DEBUG_PRINTLN(configuration.TRANSMISSION_MODE.getFixedTransmissionDescription());


	DEBUG_PRINTLN("----------------------------------------");
}

