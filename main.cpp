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
SDL_Surface *debug = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *debugFont = NULL;

//The color of the font
SDL_Color debugTextColor = {0xF0, 0xFF, 0xF0};

/**
 * Initialization function for the SDL, title and window
 * @return TRUE if everything is okay, FALSE otherwise
 */
bool init() {
    //Initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        return false;
    }

    // Initialize the TTF library
    if (TTF_Init() == -1) {
        return false;
    }

    // Open the debug font
    debugFont = TTF_OpenFont("ressources/PixelScreen.ttf", 18);

    //Set up the screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    //If there was an error in setting up the screen
    if (screen == NULL) {
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
void clean_up() {
    // Close the debug font
    TTF_CloseFont(debugFont);

    // Quitting the SDL modules
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char** argv) {
    // boolean indicating that the user wants to quit
    bool quit = false;

    // FRAME RATE
    int frames = 0; // current number of frames
    bool fpsCap = true; // boolean indicating that the frame rate is capped
    Timer fpsTimer;
    Timer timerTemp;
    int frame_rate = 0;

    // initialization
    if (init() == false) {
        return 1;
    }

    //Fill the screen black
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

    // Creation of a spaceship
    Spaceship hero;

    // Creation of the array of keystates
    Uint8* keyStates = SDL_GetKeyState(NULL);

    // Starting of the timer used to cap the frame rate
    fpsTimer.start();

    //While the user hasn't quit
    while (quit == false) {
        timerTemp.start();

        // ---- EVENTS HANDLERS ----
        //If there's an event to handle
        if (SDL_PollEvent(&event)) {
            hero.handle_events(event);
            
            if (event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }
        }
        
        
        /*
        if (keyStates[SDLK_UP]) {
            hero.move(0, -15, screen);
        }

        if (keyStates[SDLK_DOWN]) {
            hero.move(0, 15, screen);
        }

        if (keyStates[SDLK_LEFT]) {
            hero.move(-15, 0, screen);
        }

        if (keyStates[SDLK_RIGHT]) {
            hero.move(15, 0, screen);
        }
        //*/
        // -------------------------
        
        // ---- GAME LOGIC ----
        hero.move();
        // --------------------
        
        // ---- RENDERING ----
        // Increment of the frame counter
        frames++;

        // In the case of the cap of frame rate, we wait for the time to be 
        // 1 second / number of frames per seconds required for the total time 
        // of the frame
        if (fpsCap && timerTemp.get_ticks() < (1000 / SETTING_FRAMES_PER_SECOND)) {
            SDL_Delay((1000 / SETTING_FRAMES_PER_SECOND) - timerTemp.get_ticks());
        }

        // Reset the screen in black
        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
        
        // displaying the items
        hero.show(screen);
        
        // Calculation of the frame rate
        frame_rate = frames / (fpsTimer.get_ticks() / 1000.f);

        // Creation of the debug data
        std::stringstream debugDataStream;
        debugDataStream << "FPS : " << frame_rate;

        //Render the time surface
        debug = TTF_RenderText_Solid(debugFont, debugDataStream.str().c_str(), debugTextColor);
        apply_surface(0, 0, debug, screen);
        //Free the time surface
        SDL_FreeSurface(debug);

        //Update the screen
        if (SDL_Flip(screen) == -1) {
            return 1;
        }
        // -------------------
    }

    timerTemp.stop();
    fpsTimer.stop();

    //Free the images and quit SDL
    hero.clean();
    clean_up();

    return 0;
}