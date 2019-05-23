#include "ArduinoManager.h"
#include "rs232.h"

ArduinoManager::ArduinoManager()
{
}

ArduinoManager::~ArduinoManager()
{
    RS232_CloseComport(comport_number);
}

void ArduinoManager::init()
{
    char mode[] = {'8','N','1',0}; // 8 data bits, no parity, 1 stop bit

    if(RS232_OpenComport(comport_number, baudrate, mode))
    {
        printf("Can not open comport\n");
        return;
    }
}

void ArduinoManager::send(string _text)
{
    string format = _text + "$";
    RS232_cputs(comport_number, format.c_str());
}
