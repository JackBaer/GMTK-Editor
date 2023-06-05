/* CSCI 200: Final Project
 *
 * Author: Jack Baer
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity)
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Wraps the full tileset texture, its clipped tile image, and its position within the window into a single structure
 */

#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Texture.h"

class Tile {
  private:
    //Wrapped texture member, allows for convenient rendering
    Texture texture;
    
    //Texture clip, to specify which tile in tileset object corresponds to
    SDL_Rect textureClip;

    //Position data of texture within tile grid for rendering purposed
    int x;
    int y;

  public:
    Tile();

    //Sets the textureClip member to provided rectangle
    void setClipRect(SDL_Rect* clip);

    //Sets texture member to the image provided at path
    void createTexture(std::string path, SDL_Renderer* renderer);

    //Allows for the movement of Tiles after creation, assuming they are rendered at the new location after the method is called
    void setPosition(int newX, int newY);

    void printTile();

    //Renders Tile texture member at (x, y)
    void render(SDL_Renderer* renderer, double angle, SDL_Point* center, SDL_RendererFlip flip);
};

#endif

