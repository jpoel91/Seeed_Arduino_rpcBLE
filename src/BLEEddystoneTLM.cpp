/*
 * BLEEddystoneTLM.cpp
 *
 *  Created on: Mar 12, 2018
 *      Author: pcbreflux
 */
#include <string.h>
#include <stdio.h>
#include "BLEEddystoneTLM.h"

static const char LOG_TAG[] = "BLEEddystoneTLM";
#define ENDIAN_CHANGE_U16(x) ((((x)&0xFF00)>>8) + (((x)&0xFF)<<8))
#define ENDIAN_CHANGE_U32(x) ((((x)&0xFF000000)>>24) + (((x)&0x00FF0000)>>8)) + ((((x)&0xFF00)<<8) + (((x)&0xFF)<<24))

BLEEddystoneTLM::BLEEddystoneTLM() {
	beaconUUID = 0xFEAA;
	m_eddystoneData.frameType = EDDYSTONE_TLM_FRAME_TYPE;
	m_eddystoneData.version = 0;
	m_eddystoneData.volt = 3300; // 3300mV = 3.3V
	m_eddystoneData.temp = (uint16_t) ((float) 23.00);
	m_eddystoneData.advCount = 0;
	m_eddystoneData.tmil = 0;
} // BLEEddystoneTLM

std::string BLEEddystoneTLM::getData() {
	return std::string((char*) &m_eddystoneData, sizeof(m_eddystoneData));
} // getData

BLEUUID BLEEddystoneTLM::getUUID() {
	return BLEUUID(beaconUUID);
} // getUUID

uint8_t BLEEddystoneTLM::getVersion() {
	return m_eddystoneData.version;
} // getVersion

uint16_t BLEEddystoneTLM::getVolt() {
	return m_eddystoneData.volt;
} // getVolt

float BLEEddystoneTLM::getTemp() {
	return (float)m_eddystoneData.temp;
} // getTemp

uint32_t BLEEddystoneTLM::getCount() {
	return m_eddystoneData.advCount;
} // getCount

uint32_t BLEEddystoneTLM::getTime() {
	return m_eddystoneData.tmil;
} // getTime

std::string BLEEddystoneTLM::toString() {
  std::string out = "";
  uint32_t rawsec = ENDIAN_CHANGE_U32(m_eddystoneData.tmil);
  char val[6];

  out += "Version " + m_eddystoneData.version;
  out += "\n";
  out += "Battery Voltage " + ENDIAN_CHANGE_U16(m_eddystoneData.volt);
  out += " mV\n";

  out += "Temperature ";
  snprintf(val, sizeof(val), "%d", m_eddystoneData.temp);
  out += val;
  out += ".0 °C\n";

  out += "Adv. Count ";
  snprintf(val, sizeof(val), "%lu", ENDIAN_CHANGE_U32(m_eddystoneData.advCount));
  out += val;
  out += "\n";

  out += "Time ";

  snprintf(val, sizeof(val), "%04lu", rawsec / 864000);
  out += val;
  out += ".";

  snprintf(val, sizeof(val), "%02lu", (rawsec / 36000) % 24);
  out += val;
  out += ":";

  snprintf(val, sizeof(val), "%02lu", (rawsec / 600) % 60);
  out += val;
  out += ":";

  snprintf(val, sizeof(val), "%02lu", (rawsec / 10) % 60);
  out += val;
  out += "\n";

  return out;
} // toString

/**
 * Set the raw data for the beacon record.
 */
void BLEEddystoneTLM::setData(std::string data) {
	if (data.length() != sizeof(m_eddystoneData)) {
		return;
	}
  memcpy(&m_eddystoneData, data.data(), data.length());
} // setData

void BLEEddystoneTLM::setUUID(BLEUUID l_uuid) {
	beaconUUID = l_uuid.getNative()->uuid.uuid16;
} // setUUID

void BLEEddystoneTLM::setVersion(uint8_t version) {
	m_eddystoneData.version = version;
} // setVersion

void BLEEddystoneTLM::setVolt(uint16_t volt) {
	m_eddystoneData.volt = volt;
} // setVolt

void BLEEddystoneTLM::setTemp(float temp) {
	m_eddystoneData.temp = (uint16_t)temp;
} // setTemp

void BLEEddystoneTLM::setCount(uint32_t advCount) {
	m_eddystoneData.advCount = advCount;
} // setCount

void BLEEddystoneTLM::setTime(uint32_t tmil) {
	m_eddystoneData.tmil = tmil;
} // setTime
