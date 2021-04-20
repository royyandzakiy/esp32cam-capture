# esp32cam-capture

captures image by pressing push button, then uploads to server

## Getting Started
### Preparing ESP32-Cam Firmware
- Download & install Arduino IDE
- open folder `esp32cam-capture`
- create empty file `credentials.h`
- edit `WIFI_SSID` & `WIFI_PASS` with current WiFi configurations
- edit `serverName` by inserting target IP address or domain
- edit `serverPath` if needed (for example if placed files in a different directory or with a different file name)
- Connect ESP32-Cam with proper pinout connections with an FTDI or other programmer

```
ESP32-Cam       FTDI Programmer
5V -------------- 5V
GND ------------- GND
UOR ------------- TX
UOT ------------- RX
IO0 to GND (for flashing mode, release if not flashing mode)

ESP32-Cam       Push Button
12 -------------- +
GND ------------- -
```

- Verify & Upload

### Preparing Server
- Install xampp or other alternatives
- Insert `webserver/upload.php` to `public_html` or `htdocs` or main page alternative. optionally you can also insert `gallery.php`
- Create folder `uploads` in the same location
- start server

---

Inspired from project by Rui Santos https://RandomNerdTutorials.com/esp32-cam-post-image-photo-server/
