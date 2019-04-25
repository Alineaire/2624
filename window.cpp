#include "window.h"

InitError::InitError() :
    exception(),
    msg( SDL_GetError() )
{
}

InitError::InitError( const std::string & _message) :
    exception(),
    msg( _message )
{
}

InitError::~InitError() throw()
{
}

const char * InitError::what() const throw()
{
    return msg.c_str();
}

window::window()
{
    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0)
        throw InitError();

    //m_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
    //if (m_window == NULL)
    if ( SDL_CreateWindowAndRenderer( 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS,
                                      &m_window, &m_renderer) != 0 )
        throw InitError();
    //m_screenSurface = SDL_GetWindowSurface( m_window );
}

window::~window()
{
    SDL_DestroyWindow( m_window );
    //SDL_DestroyRenderer( m_renderer );
    SDL_Quit();
}

void window::draw()
{
    // Clear the window with a black background
    /*SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );

    // Show the window
    SDL_RenderPresent( m_renderer );

    int rgb[] = { 203, 203, 203, // Gray
                  254, 254,  31, // Yellow
                    0, 255, 255, // Cyan
                    0, 254,  30, // Green
                  255,  16, 253, // Magenta
                  253,   3,   2, // Red
                   18,  14, 252, // Blue
                    0,   0,   0  // Black
                };

    SDL_Rect colorBar;
    colorBar.x = 0; colorBar.y = 0; colorBar.w = 90; colorBar.h = 480;
    SDL_SetRenderDrawColor( m_renderer, rgb[0], rgb[1], rgb[2], 255 );
    SDL_RenderFillRect( m_renderer, &colorBar );
    SDL_RenderPresent( m_renderer );*/

    //Apply the current image
    //SDL_BlitSurface( NULL, NULL, m_screenSurface, NULL );

    //Update the surface
    //SDL_UpdateWindowSurface( m_window );
}
