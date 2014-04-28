/* 
 * File:   main.cpp
 * Author: Vincent
 *
 * Created on 3 mars 2014, 23:26
 */

#include <cstdlib>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"

#include "src/headers/Spaceship.h"
#include "src/headers/const.h"

using namespace std;

// The screen of the game
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

/**
 * Initialization function for the SDL, title and window
 * @return TRUE if everything is okay, FALSE otherwise
 */
bool init(){
    //Initialize all SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    //If there was an error in setting up the screen
    if(screen == NULL){
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption("The flying sausage", NULL);

    //If everything initialized fine
    return true;
}

/**
 * Function shutting down the SDL
 */
void clean_up(){
    //Quit SDL
    SDL_Quit();
}

int main(int argc, char** argv) {
    // boolean indicating that the user wants to quit
    bool quit = false;
    
    // initialization
    if(init() == false){
        return 1;
    }
    
    //Fill the screen black
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
    
    // Creation of a spaceship and displaying
    Spaceship temp;
    temp.show(screen);
    
    // Creation of the array of keystates
    Uint8* keyStates = SDL_GetKeyState(NULL);
    
    //While the user hasn't quit
    while(quit == false){
        //If there's an event to handle
        if(SDL_PollEvent(&event)){
//            //If a key was pressed
//            if(event.type == SDL_KEYDOWN){
//                //Move the spaceship the proper way
//                switch(event.key.keysym.sym){
//                    case SDLK_UP: temp.move(0, -10, screen); break;
//                    case SDLK_DOWN: temp.move(0, 10, screen); break;
//                    case SDLK_LEFT: temp.move(-10, 0, screen); break;
//                    case SDLK_RIGHT: temp.move(10, 0, screen); break;
//                }
//            }

            // If the user wants to quit
            /*else */if(event.type == SDL_QUIT){
                //Quit the program
                quit = true;
            }
        }
        
        if(keyStates[SDLK_UP]){
            temp.move(0, -1, screen);
        }
        
        if(keyStates[SDLK_DOWN]){
            temp.move(0, 1, screen);
        }
        
        if(keyStates[SDLK_LEFT]){
            temp.move(-1, 0, screen);
        }
        
        if(keyStates[SDLK_RIGHT]){
            temp.move(1, 0, screen);
        }
    }
    
    //Free the images and quit SDL
    temp.clean();
    clean_up();
    
    return 0;
}

