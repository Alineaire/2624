#ifndef ARDUINOMANAGER_H
#define ARDUINOMANAGER_H

#include <string>

using namespace std;

class ArduinoManager
{
    public:
        ArduinoManager();
        virtual ~ArduinoManager();
        static ArduinoManager* Instance()
        {
            if (ArduinoManager::m_instance == nullptr)
            {
                ArduinoManager::m_instance = new ArduinoManager();
            }
            return ArduinoManager::m_instance;
        }

        void init();
        void send(string _text);

    protected:

    private:
        static ArduinoManager* m_instance;
        int comport_number = 25;    /* /dev/ttyACM1 */
        int baudrate = 9600;        /* 9600 baud */
};

#endif // ARDUINOMANAGER_H
