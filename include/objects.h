//Header Guard
#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


class GameWindow {
  public:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    GameWindow();
    int init();
    void render();
    void clear();
    bool quitRequested();
    void requestQuit();

  private:
    //Member data of window dimensions for resizing
    int windowHeight;
    int windowWidth;

    //Flags for window focus/state
    bool quitFlag;
};


class Texture {
  public:
    
    Texture();
    ~Texture();

    void free();

    void createTexture(std::string path, SDL_Renderer* renderer);

    //void setColor(Uint8 red, Uint8 green, Uint8 blue);
    //void setAlpha(Uint8 alpha);

    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

    int getWidth();
    int getHeight();

  private:
    SDL_Texture* texture;

    int width;
    int height;
};



//End header
#endif
