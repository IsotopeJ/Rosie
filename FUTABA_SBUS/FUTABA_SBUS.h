
#ifndef FUTABA_SBUS_h
#define FUTABA_SBUS_h

#include <Arduino.h>


#define SBUS_SIGNAL_OK          0x00
#define SBUS_SIGNAL_LOST        0x01
#define SBUS_SIGNAL_FAILSAFE    0x03
#define BAUDRATE 100000
//#define port Serial1
#define port Serial

//#define ALL_CHANNELS


class FUTABA_SBUS
{
  public:
    uint8_t mFailsafeStatus;
    bool mSbusPassthrough;
    int mToChannels;

    void begin(void);
    int16_t Channel(uint8_t ch);
    uint8_t DigiChannel(uint8_t ch);
    void Servo(uint8_t ch, int16_t position);
    void DigiServo(uint8_t ch, uint8_t position);
    uint8_t Failsafe(void);
    void UpdateServos(void);
    void UpdateChannels(void);
    void FeedLine(void);

  private:
    uint8_t mSbusData[25];
    int16_t mChannels[18];
    int16_t mServos[18];
    int mBufferIndex;
    int mFeedState;
};

#endif
