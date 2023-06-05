#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameWindow {
  public:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    GameWindow();
    int init();
    void render();
    void clear();
    void requestQuit();

    bool quitRequested();
    int getHeight();
    int getWidth();

  private:
    //Member data of window dimensions for resizing
    int windowHeight;
    int windowWidth;

    //Flags for window focus/state
    bool quitFlag;
};


#endif
