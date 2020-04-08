#ifndef PwmDevice_h
#define PwmDevice_h
#include <Arduino.h>

class PwmDevice {
  private:
    bool _state;
    uint8_t _pin;
    uint8_t _pwm;
    uint8_t _percent;
    uint8_t _min;
    uint8_t _max;
	uint32_t _time;
  public:
    PwmDevice(const uint8_t pin, const uint8_t min = 1, const uint8_t max = UINT8_MAX);
    bool setPwm(const uint8_t value);
    bool setPercent(const uint8_t value);
	bool on();
	bool off();
	bool isActive();
    uint8_t getPwm();
    uint8_t getPercent();
	uint32_t getTime();
};

#endif