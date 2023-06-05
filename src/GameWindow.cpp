/* CSCI 200: Final Project
 *
 * Author: Jack Baer
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Wrapper for SDL window rendering functionality, to provide a single standard interface to the renderer and window
 */

#include "GameWindow.h"

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
  window = SDL_CreateWindow("Final Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

//Access window width member
int GameWindow::getWidth() {
  return windowWidth;
}

//Access window height member
int GameWindow::getHeight() {
  return windowHeight;
}

//Render to window
void GameWindow::render() {
  SDL_RenderPresent(renderer);
}

//Clear window contents
void GameWindow::clear() {
  //Set background to white
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
}
