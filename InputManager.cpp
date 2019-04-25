#include "InputManager.h"

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
        //cout << (SDL_EventType)event.type << endl;
        switch (event.type)
        {
        case SDL_QUIT:
            //game_state = 0; // set game state to done,(do what you want here)
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            string code(SDL_GetKeyName(event.key.keysym.sym));
            keys[code] = (event.type == SDL_KEYDOWN);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            bool press = (event.type == SDL_MOUSEBUTTONDOWN);
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                keys["CLICKLEFT"] = press;
                break;
            case SDL_BUTTON_MIDDLE:
                keys["CLICKMIDDLE"] = press;
                break;
            case SDL_BUTTON_RIGHT:
                keys["CLICKRIGHT"] = press;
                break;
            }
            break;
        }
        case SDL_MOUSEMOTION:
        {
            mouse.x = event.motion.x;
            mouse.y = event.motion.y;
            mouseDelta.x = event.motion.xrel;
            mouseDelta.y = event.motion.yrel;
            break;
        }
        default:
            break;
        }
    }
}
