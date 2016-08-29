# RFID Card Reader

## About

This is a small and simple desktop application for reading the ID of RFID cards. It was built for Helios Makerspace's member management system (MSYS).

For the moment the only target platform is OS X with an Adafruit PN532 reader over UART. However there should't be much in the way of supporting other platforms with other hardware.

## Requirements

 * Qt 4.x
 * libnfc

## Installation

### libnfc

For libnfc to detect the PN532 over UART, enable the library to use intrusive scanning by either adding to the config file

```
allow_intrusive_scan = true
```

or using the environment variable:

```
LIBNFC_INTRUSIVE_SCAN=true
```

See [this page](http://nfc-tools.org/index.php?title=Libnfc:configuration) for more details on configuring libnfc


## Dev Roadmap

* Add configuration fields
* Config file
* Icon
* Deploy to service desk