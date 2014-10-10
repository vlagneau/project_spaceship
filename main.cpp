/* 
 * File:   main.cpp
 * Author: Vincent
 *
 * Created on 3 mars 2014, 23:26
 */

#include <cstdlib>
#include <sstream>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "src/headers/Spaceship.h"
#include "src/headers/const.h"
#include "src/headers/Timer.h"

using namespace std;

// The screen of the game
SDL_Surface *screen = NULL;
SDL_Surface *seconds = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *debugFont = NULL;

//The color of the font
SDL_Color debugTextColor = {0xF0, 0xFF, 0xF0};

// Setting for the number of frames per second
const int SETTING_FRAMES_PER_SECOND = 24;

/**
 * Initialization function for the SDL, title and window
 * @return TRUE if everything is okay, FALSE otherwise
 */
bool init(){
    //Initialize all SDL subsystems
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        return false;
    }
    
    // Initialize the TTF library
    if(TTF_Init() == -1){
        return false;
    }
    
    // Open the debug font
    debugFont = TTF_OpenFont("ressources/PixelScreen.ttf", 14);

    //Set up the screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    //If there was an error in setting up the screen
    if(screen == NULL){
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption("Project Spaceship", NULL);

    //If everything initialized fine
    return true;
}

/**
 * Function shutting down the SDL
 */
void clean_up(){
    // Close the debug font
    TTF_CloseFont(debugFont);

    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char** argv) {
    // boolean indicating that the user wants to quit
    bool quit = false;
    
    Timer timerTest;
    timerTest.start();
    
    // FRAME RATE
    // Current number of frames
    int frames = 0;
    bool lock_fps = false;
    Timer fps_timer;
    
    // initialization
    if(init() == false){
        return 1;
    }
    
    //Fill the screen black
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
    
    // Creation of a spaceship and displaying
    Spaceship hero;
    hero.show(screen);
    
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
            hero.move(0, -1, screen);
        }
        
        if(keyStates[SDLK_DOWN]){
            hero.move(0, 1, screen);
        }
        
        if(keyStates[SDLK_LEFT]){
            hero.move(-1, 0, screen);
        }
        
        if(keyStates[SDLK_RIGHT]){
            hero.move(1, 0, screen);
        }
        
        // Timer tests
        //*
        std::stringstream time;
        time << "Timer: " << timerTest.get_ticks() / 1000.f;
        //Render the time surface
        seconds = TTF_RenderText_Solid(debugFont, time.str().c_str(), debugTextColor);
        //Apply the time surface
        apply_surface(0, 0, seconds, screen);
        //Free the time surface
        SDL_FreeSurface(seconds);
        //Update the screen
        if(SDL_Flip(screen) == -1){
            return 1;
        }
        //*/
    }
    
    timerTest.stop();
    
    //Free the images and quit SDL
    hero.clean();
    clean_up();
    
    return 0;
}