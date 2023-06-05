#include "Tile.h"
#include <iostream>

//Default constructor
Tile::Tile() {
  x = 0;
  y = 0;

  textureClip = {0, 0, 0, 0};
  texture;
}

//Create Texture for texture member
void Tile::createTexture(std::string path, SDL_Renderer* renderer) {
  texture.createTexture(path, renderer);
}

//Renders texture member at (x,y)
void Tile::render(SDL_Renderer* renderer, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
  texture.render(renderer, x, y, &textureClip, angle, center, flip);
}

//Set the position of the given Tile
//Should be done before rendering, or else it will need to be rendered again to be in the correct location
void Tile::setPosition(int newX, int newY) {
  x = newX;
  y = newY;
}

//Set the clip rectangle of the tileset for the texture member
//Should be done before creatingTexture() method called, or else it will need to be created again with the new clip
void Tile::setClipRect(SDL_Rect* clip) {
  textureClip = *clip;
}

//Print a given tile's information
void Tile::printTile() {
  std::cout << "Tile (" << x << "," << y << ") with clip {" << textureClip.x << "," << textureClip.y << "," << textureClip.w << "," << textureClip.h << "}" << std::endl;
}
