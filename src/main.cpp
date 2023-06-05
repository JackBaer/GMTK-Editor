/* CSCI 200: Final Project
 *
 * Author: Jack Baer
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity)
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Main file, which handles all file I/O and creates a tilemap grid to be rendered to the created SDL_Window
 */

#include <fstream>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameWindow.h"
#include "Tile.h"

//Game Window
GameWindow* window = new GameWindow();

//Create Event Handler
SDL_Event e;

int main(int argc, char **argv) {
  std::string tileData;
  std::ifstream input;

  if(argc == 2) {
    tileData = argv[1];
    std::cout << "Opening file " << "\"" << tileData << "\"" << std::endl;
    input.open(tileData);
    if(input.fail()) {
      std::cout << "File does not exist. Exiting program..." << std::endl;
      return -1;
    }
  }
  else {
    std::cout << "Please give a .map file to read: " << std::endl;
    std::cin >> tileData;
    std::cout << "Opening file " << "\"" << tileData << "\"" << std::endl;
    input.open(tileData);
    if(input.fail()) {
      std::cout << "File does not exist. Exiting program..." << std::endl;
      return -1;
    }
  }
  std::cout << "File opened successfully!" << std::endl << std::endl;
  
  //Tilemap dimensions, to be specified in file
  int rows;
  int columns; 

  //Read first two values in for grid dimensions (rows and columns)
  input >> rows;
  input >> columns;

  //Tilemap to be rendered (the horrifying triple-pointer-2D-array
  Tile*** tilemap = new Tile**[columns];

  //Create 2D array of Tile objects
  for(int i = 0; i < columns; i++) {
    tilemap[i] = new Tile*[rows];
  }

  //Tile width/height
  int tileWidth;
  int tileHeight;
  
  //Read next two values in for the tile dimensions (each rectangle's size to be sliced from provided tileset image)
  input >> tileWidth;
  input >> tileHeight;

  //Tileset width/height
  int setWidth;
  int setHeight;

  //Read next two values in for the image dimensions (full image, to be sliced with tile dimensions)
  input >> setWidth;
  input >> setHeight;

  //Read in the name of the tileset image file
  std::string imgPath;

  input >> imgPath;

  //Generate table of possible texture clips
  int totalTiles = (setWidth / tileWidth) * (setHeight / tileHeight);
  SDL_Rect* tileClips = new SDL_Rect[totalTiles];

  std::cout << "Rows: " << rows << std::endl;
  std::cout << "Columns: " << columns << std::endl;
  std::cout << "Total Tiles in Set: " << totalTiles << std::endl;
  int counter = 0;

  //Iterate through tileset image with given parameters to generate SDL_Rect clips of the tile textures within
  int setColumns = setWidth / tileWidth;
  int setRows = setHeight / tileHeight;
  for(int i = 0; i < setRows; i++) {
    for(int j = 0; j < setColumns; j++) {
      //Create clip rectangle out of current position in tileset image
      SDL_Rect currentClip;
      currentClip.x = (j * tileWidth);
      currentClip.y = (i * tileHeight);
      currentClip.w = tileWidth;
      currentClip.h = tileHeight;

      //std::cout << counter << " {" << currentClip.x << "," << currentClip.y << "," << currentClip.w << "," << currentClip.h << "}" << std::endl;

      //Set clip rectangle at ID equal to current clip
      tileClips[counter] = currentClip;

      counter++;
    }
  }

  window -> init();

  //Read characters from file
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      //Read in integer ID from map data
      int currentID;
      input >> currentID;

      //std::cout << currentID << " ";

      //Construct Tile object from provided information, with texture corresponding to ID number
      //Using tileClips array generated above, Tile ID can be used to immediately access SDL_Rect for texture rendering
      SDL_Rect currentClip = tileClips[currentID];


      Tile* currentTile = new Tile();
      int xPos = j * tileWidth;
      int yPos = i * tileHeight;
      currentTile -> createTexture(imgPath, window -> renderer);
      currentTile -> setClipRect(&currentClip);
      currentTile -> setPosition(xPos, yPos);

      //Add Tile object to array of Tiles
      tilemap[j][i] = currentTile;
    }
    //std::cout << std::endl;
  }

  //Close file now that map data has been read
  input.close();

  //Main window loop, to be run after reading in file data through console
  while(!(window -> quitRequested())) {
    while(SDL_PollEvent(&e) != 0) {
      if(e.type == SDL_QUIT) {
        window -> requestQuit();
      }
    }
    //Clear before drawing
    window -> clear();

    //Draw Commands 
    
    for(int i = 0; i < rows; i++) {
      for(int j = 0; j < columns; j++) {
        tilemap[j][i] -> render(window -> renderer, 0.0, nullptr, SDL_FLIP_NONE);
      }
    }

    //Render to window
    window -> render();
  }  
   
  return 0;
}

