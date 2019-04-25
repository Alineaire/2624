#include "InputManager.h"
#include "utils.h"

#include <SDL.h>

#include <iostream>

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        cout << (SDL_EventType)event.type << endl;
        switch (event.type)
        {
        case SDL_QUIT:
            //game_state = 0; // set game state to done,(do what you want here)
            break;
        case SDL_KEYDOWN:
        {
            string keyName(SDL_GetKeyName(event.key.keysym.sym));
            cout << keyName << endl;
            break;
        }
        case SDL_KEYUP:
        {
            string keyName(SDL_GetKeyName(event.key.keysym.sym));
            cout << keyName << endl;
            break;
        }
            /*if (event.key.keysym.sym > 0 && event.key.keysym.sym <= 0x7F)
            {
                string keyName(SDL_GetKeyName(event.key.keysym.sym));
                cout << keyName << endl;
                keys[toUpper(keyName)] = (event.type == SDL_KEYDOWN);
            }
            break;*/
        default:
            break;
        }
    }
}

bool InputManager::keyPress(string _key)
{
    string formatKey = toUpper(_key);
    if (_key.length() == 1)
    {
        return keys[formatKey];
    }

    return false;
}
