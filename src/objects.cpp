#include "objects.h"
#include <iostream>
#include <string>
#include "definitions.h"

//Constructor
GameWindow::GameWindow(void) {
  //Members to hold SDL Window and Renderer for game window
  window = NULL;
  renderer = NULL;

  //Used to determine when user exits window
  quitFlag = NULL;
}

//Initialize main game window
int GameWindow::init() {
  //Initialize desired SDL subsystems
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Init(SDL_INIT_AUDIO);
  SDL_Init(SDL_INIT_TIMER);
  SDL_Init(SDL_INIT_EVENTS);

  //Initialize PNG image support
  IMG_Init(IMG_INIT_PNG);

  //Shouldn't immediately quit upon initialization
  quitFlag = false;

  //Creates generic starting window with SDL flags and screen constants from definitions.h
  window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  return 1;
}

//Check if window needs to be closed, to be checked by main event handling system
bool GameWindow::quitRequested() {
  return quitFlag;
}

//Request window close by setting quit flag
void GameWindow::requestQuit() {
  quitFlag = true;
}

//Render to window
void GameWindow::render() {
  SDL_RenderPresent(renderer);
}

//Clear window contents
void GameWindow::clear() {
  SDL_RenderClear(renderer);
}

/**************************************************/

//Constructor
Texture::Texture() {
  texture = NULL;

  width = 0;
  height = 0;
}

//Free texture
void Texture::free() {
  if(texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
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

  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = IMG_Load(path.c_str());

  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface -> format, 0, 0xFF, 0xFF));

  newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

  width = loadedSurface -> w;
  height = loadedSurface -> h;

  texture = newTexture;
}


//Render texture to provided renderer with any provided modifiers
void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
  SDL_Rect destinationRect = {x, y, width, height};

  if(clip != NULL) {
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

