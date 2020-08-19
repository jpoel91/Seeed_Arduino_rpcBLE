/*
 * BLEScan.h
 *
 *  Created on: Jul 1, 2017
 *      Author: kolban
 */

#ifndef COMPONENTS_CPP_UTILS_BLESCAN_H_
#define COMPONENTS_CPP_UTILS_BLESCAN_H_

// #include <vector>
#include <string>
#include "BLEAdvertisedDevice.h"
#include "FreeRTOS.h"
#include "Seeed_erpcUnified.h"
class BLEScan;
class BLEAdvertisedDeviceCallbacks;
class BLEAdvertisedDevice;
//void beginCentral(uint8_t connCount);
//void start_Scan(uint32_t scanDuration_ms);
//void setupGAPBondManager();

/**
 * @brief The result of having performed a scan.
 * When a scan completes, we have a set of found devices.  Each device is described
 * by a BLEAdvertisedDevice object.  The number of items in the set is given by
 * getCount().  We can retrieve a device by calling getDevice() passing in the
 * index (starting at 0) of the desired device.
 */
class BLEScanResults {
public:
	  int                 getCount();

private:
	friend BLEScan;
	std::map<std::string, BLEAdvertisedDevice*> m_vectorAdvertisedDevices;
};


class BLEScan {
public:
	void           setActiveScan(bool active);
	void           setInterval(uint16_t intervalMSecs);
	void           setWindow(uint16_t windowMSecs);
	void           setAdvertisedDeviceCallbacks(
			              BLEAdvertisedDeviceCallbacks* pAdvertisedDeviceCallbacks,
										bool wantDuplicates = false);
	bool           start(uint32_t duration, void (*scanCompleteCB)(BLEScanResults), bool is_continue = false);
	BLEScanResults start(uint32_t duration, bool is_continue = false);
	void			clearResults();
    static uint8_t                _scanProcessing;	
	BLEScanResults                m_scanResults;
private:
    BLEScan();   // One doesn't create a new instance instead one asks the BLEDevice for the singleton.
	friend class BLEDevice;
	
	bool                          m_wantDuplicates;
	uint16_t _scanInterval = 0x40;              // Duration to wait between starting a scan. Value range: 0x0004 - 0x4000 (2.5ms - 10240ms)(0.625ms/step).
	uint16_t _scanWindow = 0x30;                // Duration to continuously scan for after starting. Value range: 0x0004 - 0x4000 (2.5ms - 10240ms)(0.625ms/step).
//	FreeRTOS::Semaphore           m_semaphoreScanEnd = FreeRTOS::Semaphore("ScanEnd");

    T_APP_RESULT  gapCallbackDefault(uint8_t cb_type, void *p_cb_data);

	void                        (*m_scanCompleteCB)(BLEScanResults scanResults);
	BLEAdvertisedDeviceCallbacks* m_pAdvertisedDeviceCallbacks = nullptr;	
	
};

#endif /* COMPONENTS_CPP_UTILS_BLESCAN_H_ */