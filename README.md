# ESP32 FreeRTOS Temperature Monitor

Embedded firmware project built with ESP-IDF.

## Features

- ESP32
- C programming
- FreeRTOS
- Task scheduling
- Inter-task communication using Queue
- Git version control

## Architecture

sensor_task → Queue → logger_task

- **sensor_task** generates temperature data
- Data is sent through a FreeRTOS Queue
- **logger_task** receives the data and logs it

## Technologies

- ESP-IDF
- FreeRTOS
- C
- Git
- Visual Studio Code

## Build

```bash
idf.py build