#ifndef HID_SERVICE_H
#define HID_SERVICE_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "MicroBitBLEManager.h"
#include "MicroBitBLEService.h"
#include "EventModel.h"


/**
  * Class definition for a MicroBit BLE Accelerometer Service.
  * Provides access to live accelerometer data via Bluetooth, and provides basic configuration options.
  */
class HIDService : public MicroBitBLEService
{
    public:
    /**
     * Constructor.
     * Create a representation of the Bluetooth SIG Battery Service
     * @param _ble The instance of a BLE device that we're running on.
     */
    HIDService( BLEDevice &_ble);

    void setLevel(uint8_t newLevel);

    private:
    /**
      * Invoked when BLE connects.
      */
    void onConnect( const microbit_ble_evt_t *p_ble_evt);

    /**
      * Invoked when BLE disconnects.
      */
    void onDisconnect( const microbit_ble_evt_t *p_ble_evt);

    /**
      * Callback. Invoked when any of our attributes are written via BLE.
      */
    void onDataWritten( const microbit_ble_evt_write_t *params);


    // Actual service data
    uint8_t batteryLevel;  // Battery level (0-100)
    
    // Index for each charactersitic in arrays of handles and UUIDs
    typedef enum mbbs_cIdx
    {
        mbbs_cIdxLEVEL,
        mbbs_cIdxCOUNT
    } mbbs_cIdx;
    
    // UUIDs for our service and characteristics
    static const uint16_t serviceUUID;
    static const uint16_t charUUID[ mbbs_cIdxCOUNT];
    
    // Data for each characteristic when they are held by Soft Device.
    MicroBitBLEChar      chars[ mbbs_cIdxCOUNT];



    public:
    
    int              characteristicCount()          { return mbbs_cIdxCOUNT; };
    MicroBitBLEChar *characteristicPtr( int idx)    { return &chars[ idx]; };

};

#endif
#endif