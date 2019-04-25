#ifndef WINDOW_H
#define WINDOW_H

#include <exception>
#include <string>
#include <SDL.h>

using namespace std;

class InitError : public exception
{
    string msg;
public:
    InitError();
    InitError( const string & _message);
    virtual ~InitError() throw();
    virtual const char * what() const throw();
};

class window
{
    public:
        window();
        virtual ~window();
        void draw();

    protected:

    private:
        SDL_Window * m_window;
        SDL_Renderer * m_renderer;
};

#endif // WINDOW_H
