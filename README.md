# STM32_L152RE_Wi-Fi_MbedOS_6_PlatformIO
Проект для подключения Wi-Fi (idw0xx1) к плате STM32 Nucleo L152RE в IDE PlatformIO

Проект основан на: 
1. https://github.com/maxgerhardt/pio-mbedos-wifi/tree/master
2. https://aiu.susu.ru/iot/wifi - тут также можно посмотреть работу с сокетами
3. https://github.com/ARMmbed/wifi-x-nucleo-idw01m1 - исходная библиотека, тут доработана для использования OS 6

# Если выводит пустоту добавиьт следующий код после инициализации библиотек

 static BufferedSerial serial_port(USBTX, USBRX, 115200);
    FileHandle *mbed::mbed_override_console(int fd) {
        return &serial_port;
    };
