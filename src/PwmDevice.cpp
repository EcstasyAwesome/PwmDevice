#include "PwmDevice.h"

/*
 * @param pin
 *        pin number that a device is connected
 * @param min
 *        min pwm level
 * @param max
 *        max pwm level
 */

PwmDevice::PwmDevice(const uint8_t pin, const uint8_t min, const uint8_t max) {
  _pin = pin;
  _min = (min < 1) ? 1 : ((min > 254) ? 254 : min);
  _max = (max < _min) ? _min : ((max > UINT8_MAX) ? UINT8_MAX : max);
  pinMode(_pin, OUTPUT);
}

/*
 * @param value
 *        level in pwm
 * @return true if a value was applied
 */

bool PwmDevice::setPwm(const uint8_t value) {
  if (value == 0) return PwmDevice::off();
  uint8_t temp = (value < _min) ? _min : ((value > _max) ? _max : value);
  if (_pwm != temp) {
    _pwm = temp;
    _percent = map(_pwm, _min, _max, 1, 100);
	_time = millis();
	_state = true;
	analogWrite(_pin, _pwm);
    return true;
  }
  return false;
}

/*
 * @param value
 *        level in percent
 * @return true if a value was applied
 */

bool PwmDevice::setPercent(const uint8_t value) {
  if (value == 0) return PwmDevice::off();
  uint8_t temp = (value < 1) ? 1 : ((value > 100) ? 100 : value);
  if (_percent != temp) {
    _percent = temp;
    _pwm = map(_percent, 1, 100, _min, _max);
    _time = millis();
	_state = true;
	analogWrite(_pin, _pwm);
    return true;
  }
  return false;
}

/*
 * @return true if a device is activated
 */

bool PwmDevice::on() {
  if (!_state) {
    _pwm = _max;
    _percent = 100;
    _time = millis();
	_state = true;
	analogWrite(_pin, _pwm);
    return true;
  }
  return false;
}

/*
 * @return true if a device is deactivated
 */

bool PwmDevice::off() {
  if (_state) {
    _pwm = 0;
    _percent = 0;
    _time = millis();
	_state = false;
	analogWrite(_pin, _pwm);
    return true;
  }
  return false;
}

/*
 * @return level in pwm
 */

uint8_t PwmDevice::getPwm() {
  return _pwm;
}

/*
 * @return level in percent
 */

uint8_t PwmDevice::getPercent() {
  return _percent;
}

/*
 * @return time when a device was changed his state
 */

uint32_t PwmDevice::getTime() {
  return _time;
}

/*
 * @return device state
 */

bool PwmDevice::isActive() {
  return _state;
}