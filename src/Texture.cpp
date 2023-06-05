#include "Texture.h"
#include <iostream>

//Constructor
Texture::Texture() {
  texture = nullptr;

  width = 0;
  height = 0;
}

//Free texture
void Texture::free() {
  if(texture != nullptr) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
    width = 0;
    height = 0;
  }
}

//Destructor
Texture::~Texture() {
  free();
}

//Create SDL_Texture from file at provided file path
void Texture::createTexture(std::string path, SDL_Renderer* renderer) {
  free();

  SDL_Texture* newTexture = nullptr;

  //Using given path, create a surface
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface -> format, 0, 0xFF, 0xFF));

  //Create SDL_Texture from previous surface, attached to provided renderer
  newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

  width = loadedSurface -> w;
  height = loadedSurface -> h;

  //Free surface after texture has been created
  SDL_FreeSurface(loadedSurface);

  //Assign created texture to member
  texture = newTexture;
}

//Render texture to provided renderer with any provided modifiers
void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) {
  SDL_Rect destinationRect = {x, y, width, height};
  if(clip != nullptr) {
    destinationRect.w = clip -> w;
    destinationRect.h = clip -> h;
  }
  SDL_RenderCopyEx(renderer, texture, clip, &destinationRect, angle, center, flip);
}

//Access width member
int Texture::getWidth() {
  return width;
}

//Access height member
int Texture::getHeight() {
  return height;
}
