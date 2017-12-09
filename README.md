
SmartHomie
==========

A sensor node implementation based on the [homie-esp8266
](https://github.com/marvinroger/homie-esp8266) project. The connected sensors are made available through MQTT for integration
in the smart home platform of your choice.

Features
--------

Supported sensors / actuators:

* HTU21D temperature and humidity sensor (Sensor connected through I2C)
* PIR infrared motion sensor (Sensor connected to a digital input pin)
* Infrared LED to control TVs, etc. (Connected to a digital output pin)

Currently, the following ESP8266 boards are supported:

* Sparkfun thing
* WEMOS D1
* others can easily be added through modifications in hardware.h

Usage
-----

* Download the repository and open the sketch in Arduino IDE
* Add the following libraries:
  * ArduinoJson (version 5.10.1)
  * Bounce2 (version 2.3.0)
  * Homie (version 1.5.0)
  * PubSubClient (version 2.6.0)
  * IRRemoteESP8266 (version 2.2.1)
* Select your hardware, compile and upload
* Follow the [homie documentation](http://marvinroger.github.io/homie-esp8266/docs/1.5.0/6.-Configuration-API/) for configuration of the device
