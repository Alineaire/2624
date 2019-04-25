#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <string>
#include <map>

using namespace std;

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        static InputManager* Instance()
        {
            if (InputManager::m_instance == nullptr)
            {
                InputManager::m_instance = new InputManager();
            }
            return InputManager::m_instance;
        }

        void update();
        bool keyPress(string _key);

    protected:

    private:
        static InputManager* m_instance;
        map<string, bool> keys;
};

#endif // INPUTMANAGER_H
