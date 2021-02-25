/*
 * LoRa E22-TTL-100
 * Get configuration.
 * https://www.mischianti.org
 *
 * E22		  ----- Arduino
 * M0         ----- 7 (or GND)
 * M1         ----- 6 (or HIGH)
 * RX         ----- 4 (PullUP)
 * TX         ----- 5 (PullUP)
 * AUX        ----- 3  (PullUP)
 * VCC        ----- 3.3v/5v
 * GND        ----- GND
 *
 */
#include "Arduino.h"
#include "LoRa_E22.h"

#define M1 D5
#define M0 D6
#define AUX D3

#define RX D2
#define TX D1

// ---------- esp8266 pins --------------
//LoRa_E22 e22ttl100(RX, TX, AUX, M0, M1);  // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl100(D3, D4, D5, D7, D6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
//LoRa_E22 e22ttl(D2, D3); // Config without connect AUX and M0 M1

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(D2, D3); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl(&mySerial, D5, D7, D6); // AUX M0 M1
// -------------------------------------

// ---------- Arduino pins --------------
LoRa_E22 e22ttl100(4, 5, 3, 7, 6); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX AUX M0 M1
//LoRa_E22 e22ttl100(4, 5); // Config without connect AUX and M0 M1

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(4, 5); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
//LoRa_E22 e22ttl(&mySerial, 3, 7, 6); // AUX M0 M1
// -------------------------------------

// ---------- esp32 pins --------------
//LoRa_E22 e22ttl100(&Serial2, 18, 21, 19); //  RX AUX M0 M1

//LoRa_E22 e22ttl100(&Serial2, 22, 4, 18, 21, 19, UART_BPS_RATE_9600); //  esp32 RX <-- e22 TX, esp32 TX --> e22 RX AUX M0 M1
// -------------------------------------

void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);

void setup() {
	Serial.begin(9600);
	while(!Serial){};
	delay(500);

	Serial.println();


	// Startup all pins and UART
	e22ttl100.begin();

	ResponseStructContainer c;
	c = e22ttl100.getConfiguration();
	// It's important get configuration pointer before all other operation
	Configuration configuration = *(Configuration*) c.data;
	Serial.println(c.status.getResponseDescription());
	Serial.println(c.status.code);

	printParameters(configuration);

	configuration.ADDL = 0x03;
	configuration.ADDH = 0x00;
	configuration.NETID = 0x00;

	configuration.CHAN = 23;


	//	----------------------- DEFAULT TRANSPARENT -----------------------
	//	configuration.ADDL = 0x03;
	//	configuration.ADDH = 0x00;
	//	configuration.NETID = 0x00;
	//
	//	configuration.CHAN = 23;
	//
	//	configuration.SPED.uartBaudRate = UART_BPS_9600;
	//	configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
	//	configuration.SPED.uartParity = MODE_00_8N1;
	//
	//	configuration.OPTION.subPacketSetting = SPS_240_00;
	//	configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
	//	configuration.OPTION.transmissionPower = POWER_22;
	//
	//	configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED;
	//	configuration.TRANSMISSION_MODE.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
	//	configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
	//	configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
	//	configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER;
	//	configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
	//	----------------------- DEFAULT TRANSPARENT WITH RSSI -----------------------
	//	configuration.ADDL = 0x03;
	//	configuration.ADDH = 0x00;
	//	configuration.NETID = 0x00;
	//
	//	configuration.CHAN = 23;
	//
	//	configuration.SPED.uartBaudRate = UART_BPS_9600;
	//	configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
	//	configuration.SPED.uartParity = MODE_00_8N1;
	//
	//	configuration.OPTION.subPacketSetting = SPS_240_00;
	//	configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
	//	configuration.OPTION.transmissionPower = POWER_22;
	//
	//	configuration.TRANSMISSION_MODE.enableRSSI = RSSI_ENABLED;
	//	configuration.TRANSMISSION_MODE.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
	//	configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
	//	configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
	//	configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER;
	//	configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
	//	----------------------- FIXED SENDER -----------------------
//			configuration.ADDL = 0x02;
//			configuration.ADDH = 0x00;
//			configuration.NETID = 0x00;
//
//			configuration.CHAN = 23;
//
//			configuration.SPED.uartBaudRate = UART_BPS_9600;
//			configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
//			configuration.SPED.uartParity = MODE_00_8N1;
//
//			configuration.OPTION.subPacketSetting = SPS_240_00;
//			configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
//			configuration.OPTION.transmissionPower = POWER_22;
//
//			configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED;
//			configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
//			configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
//			configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
//			configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_TRANSMITTER;
//			configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
	//
	//	----------------------- FIXED RECEIVER -----------------------
			configuration.ADDL = 0x03;
			configuration.ADDH = 0x00;
			configuration.NETID = 0x00;

			configuration.CHAN = 23;

			configuration.SPED.uartBaudRate = UART_BPS_9600;
			configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
			configuration.SPED.uartParity = MODE_00_8N1;

			configuration.OPTION.subPacketSetting = SPS_240_00;
			configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
			configuration.OPTION.transmissionPower = POWER_22;

			configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED;
			configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
			configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
			configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
			configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER;
			configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
	//	----------------------- FIXED SENDER RSSI -----------------------
	//		configuration.ADDL = 0x02;
	//		configuration.ADDH = 0x00;
	//		configuration.NETID = 0x00;
	//
	//		configuration.CHAN = 23;
	//
	//		configuration.SPED.uartBaudRate = UART_BPS_9600;
	//		configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
	//		configuration.SPED.uartParity = MODE_00_8N1;
	//
	//		configuration.OPTION.subPacketSetting = SPS_240_00;
	//		configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
	//		configuration.OPTION.transmissionPower = POWER_22;
	//
	//		configuration.TRANSMISSION_MODE.enableRSSI = RSSI_ENABLED;
	//		configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
	//		configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
	//		configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
	//		configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_TRANSMITTER;
	//		configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
	//
	//	----------------------- FIXED RECEIVER RSSI -----------------------
	//		configuration.ADDL = 0x03;
	//		configuration.ADDH = 0x00;
	//		configuration.NETID = 0x00;
	//
	//		configuration.CHAN = 23;
	//
	//		configuration.SPED.uartBaudRate = UART_BPS_9600;
	//		configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
	//		configuration.SPED.uartParity = MODE_00_8N1;
	//
	//		configuration.OPTION.subPacketSetting = SPS_240_00;
	//		configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
	//		configuration.OPTION.transmissionPower = POWER_22;
	//
	//		configuration.TRANSMISSION_MODE.enableRSSI = RSSI_ENABLED;
	//		configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
	//		configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
	//		configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
	//		configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER;
	//		configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;

	//	----------------------- WOR SENDER -----------------------
	//		configuration.ADDL = 0x02;
	//		configuration.ADDH = 0x00;
	//		configuration.NETID = 0x00;
	//
	//		configuration.CHAN = 23;
	//
	//		configuration.SPED.uartBaudRate = UART_BPS_9600;
	//		configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
	//		configuration.SPED.uartParity = MODE_00_8N1;
	//
	//		configuration.OPTION.subPacketSetting = SPS_240_00;
	//		configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
	//		configuration.OPTION.transmissionPower = POWER_22;
	//
	//		configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED;
	//		configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
	//		configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
	//		configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
	//		configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_TRANSMITTER;
	//		configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
	//
	//	----------------------- WOR RECEIVER -----------------------
	//		configuration.ADDL = 0x03;
	//		configuration.ADDH = 0x00;
	//		configuration.NETID = 0x00;
	//
	//		configuration.CHAN = 23;
	//
	//		configuration.SPED.uartBaudRate = UART_BPS_9600;
	//		configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
	//		configuration.SPED.uartParity = MODE_00_8N1;
	//
	//		configuration.OPTION.subPacketSetting = SPS_240_00;
	//		configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
	//		configuration.OPTION.transmissionPower = POWER_22;
	//
	//		configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED;
	//		configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
	//		configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
	//		configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
	//		configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER;
	//		configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
	//	----------------------- BROADCAST MESSAGE 1 -----------------------
//			configuration.ADDL = 0x04;
//			configuration.ADDH = 0x00;
//			configuration.NETID = 0x00;
//
//			configuration.CHAN = 23;
//
//			configuration.SPED.uartBaudRate = UART_BPS_9600;
//			configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
//			configuration.SPED.uartParity = MODE_00_8N1;
//
//			configuration.OPTION.subPacketSetting = SPS_240_00;
//			configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
//			configuration.OPTION.transmissionPower = POWER_22;
//
//			configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED;
//			configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
//			configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
//			configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
//			configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER;
//			configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
	//	----------------------- BROADCAST MESSAGE 2 -----------------------
//			configuration.ADDL = 0x05;
//			configuration.ADDH = 0x00;
//			configuration.NETID = 0x00;
//
//			configuration.CHAN = 23;
//
//			configuration.SPED.uartBaudRate = UART_BPS_9600;
//			configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
//			configuration.SPED.uartParity = MODE_00_8N1;
//
//			configuration.OPTION.subPacketSetting = SPS_240_00;
//			configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
//			configuration.OPTION.transmissionPower = POWER_22;
//
//			configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED;
//			configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
//			configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
//			configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
//			configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER;
//			configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;
	//	----------------------- BROADCAST MESSAGE 3 -----------------------
	//		configuration.ADDL = 0x06;
	//		configuration.ADDH = 0x00;
	//		configuration.NETID = 0x00;
	//
	//		configuration.CHAN = 23;
	//
	//		configuration.SPED.uartBaudRate = UART_BPS_9600;
	//		configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
	//		configuration.SPED.uartParity = MODE_00_8N1;
	//
	//		configuration.OPTION.subPacketSetting = SPS_240_00;
	//		configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
	//		configuration.OPTION.transmissionPower = POWER_22;
	//
	//		configuration.TRANSMISSION_MODE.enableRSSI = RSSI_DISABLED;
	//		configuration.TRANSMISSION_MODE.fixedTransmission = FT_FIXED_TRANSMISSION;
	//		configuration.TRANSMISSION_MODE.enableRepeater = REPEATER_DISABLED;
	//		configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
	//		configuration.TRANSMISSION_MODE.WORTransceiverControl = WOR_RECEIVER;
	//		configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;

	// Set configuration changed and set to not hold the configuration
	ResponseStatus rs = e22ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
	Serial.println(rs.getResponseDescription());
	Serial.println(rs.code);

	c = e22ttl100.getConfiguration();
	// It's important get configuration pointer before all other operation
	configuration = *(Configuration*) c.data;
	Serial.println(c.status.getResponseDescription());
	Serial.println(c.status.code);

	printParameters(configuration);
}

void loop() {

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
void printModuleInformation(struct ModuleInformation moduleInformation) {
	Serial.println("----------------------------------------");
	DEBUG_PRINT(F("HEAD: "));  DEBUG_PRINT(moduleInformation.COMMAND, HEX);DEBUG_PRINT(" ");DEBUG_PRINT(moduleInformation.STARTING_ADDRESS, HEX);DEBUG_PRINT(" ");DEBUG_PRINTLN(moduleInformation.LENGHT, DEC);

	Serial.print(F("Model no.: "));  Serial.println(moduleInformation.model, HEX);
	Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
	Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
	Serial.println("----------------------------------------");

}

