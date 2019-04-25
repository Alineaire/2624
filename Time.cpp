#include "Time.h"

#include <SDL.h>

Time::Time()
{
    time = 0.0f;
    deltaTime = 0.0f;
}

Time::~Time()
{
}

void Time::init()
{
    time = SDL_GetTicks() / 1000.0f;
    SDL_Delay(1);
    float timeEnd = SDL_GetTicks() / 1000.0f;
    deltaTime = timeEnd - time;
    time = timeEnd;
}

void Time::update()
{
    float timeEnd = SDL_GetTicks() / 1000.0f;
    deltaTime = timeEnd - time;
    time = timeEnd;
}
