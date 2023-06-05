/* CSCI 200: Final Project
 *
 * Author: Jack Baer
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity)
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Wraps SDL_Texture to read in png/jpg files and render to provided SDL_Renderer
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

class Texture {
  private:
    //As this is a wrapper class for SDL_Texture, one of the members is of type SDL_Texture
    SDL_Texture *texture;

    //Width/height properties to keep track of texture size
    int width;
    int height; 

  public:
    //Default constructor and destructor
    Texture();
    ~Texture();

    //Handles deallocation of a Texture object, to be called in destructor
    void free();
  
    //Create SDL_Texture from filepath
    void createTexture(std::string path, SDL_Renderer* renderer);
    
    void setClipRect(SDL_Rect rect);

    //Render SDL_Texture member to given renderer and position
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

    //Access to width and height members
    int getWidth();
    int getHeight();
};

#endif
