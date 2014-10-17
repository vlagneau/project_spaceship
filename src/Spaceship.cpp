/* 
 * File:   Spaceship.cpp
 * Author: Vincent
 * 
 * Created on 6 mars 2014, 10:33
 */

#include "headers/Spaceship.h"
#include "headers/const.h"

/**
 * Default constructor
 */
Spaceship::Spaceship() {
    // initialization of the ship
    this->init();
    
    // Initialization of the width and height
    this->_height = this->_sprites[0].h;
    this->_width = this->_sprites[0].w;
    
    // initiatlization of the position
    this->_x = (SCREEN_WIDTH - this->_width) / 2;
    this->_y = (SCREEN_HEIGHT - this->_height) / 2;
    
    // Initialization of the velocity
    this->_xVel = 0;
    this->_yVel = 0;
}

/**
 * Custom constructor allowing to set the initial position of the ship
 * @param _x position on the x axis
 * @param _y position on the y axis
 */
Spaceship::Spaceship(int x, int y) {
    Spaceship();
    
    this->_x = x;
    this->_y = y;
}

Spaceship::Spaceship(const Spaceship& orig) {
}

/**
 * Method that handles all the external events that can happen to the spaceship
 */
void Spaceship::handle_events(SDL_Event event) {
    // If a key is pressed, we adjust the velocity of the spaceship
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym) {
            case SDLK_UP: this->_yVel -= 10;
                break;
            case SDLK_DOWN: this->_yVel += 10;
                break;
            case SDLK_LEFT: this->_xVel -= 10;
                break;
            case SDLK_RIGHT: this->_xVel += 10;
                break;
        }
    }
    
    //*
    // If a key is released, we also adjust the velocity
    else if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym) {
            case SDLK_UP: this->_yVel += 10;
                break;
            case SDLK_DOWN: this->_yVel -= 10;
                break;
            case SDLK_LEFT: this->_xVel += 10;
                break;
            case SDLK_RIGHT: this->_xVel -= 10;
                break;
        }
    } 
    //*/
}

/**
 * Method that display the spaceship onto the surface that have been
 * passed in the parameters, by reseting the surface before
 * @param _screen surface that will have the spaceship blitted on
 */
void Spaceship::show(SDL_Surface* screen){
    apply_surface(this->_x, this->_y, this->_surface, screen, &(this->_sprites[0]));
}

/**
 * Function initializing the spaceship sprites and images
 */
void Spaceship::init() {    
    this->_surface = load_image("ressources/ships.png");
    
    //Clip range for the top left
    this->_sprites[0].x = 62;
    this->_sprites[0].y = 319;
    this->_sprites[0].w = 131;
    this->_sprites[0].h = 134;

}

void Spaceship::clean(){
    SDL_FreeSurface(this->_surface);
}


/*
 * Method that use the current velocity of the ship to move it on
 * the x and y axis and set its new position
 */
void Spaceship::move(){
    int new_x = this->_x;
    int new_y = this->_y;
    
    // Adding the velocity to the current x position
    new_x += this->_xVel;
    
    // Protection against the fact that the spaceship goes out of the screen
    if(new_x < 0){
        new_x = 0;
    }
    else if(new_x > (SCREEN_WIDTH - this->_width)){
        new_x = SCREEN_WIDTH - this->_width;
    }
    
    // Adding the velocity to the current y position
    new_y += this->_yVel;
    
    // Protection against the fact that the spaceship goes out of the screen
    if(new_y < 0){
        new_y = 0;
    }
    else if(new_y > (SCREEN_HEIGHT - this->_height)){
        new_y = SCREEN_HEIGHT - this->_height;
    }
    
    // Ppdating of the current position of the spaceship
    this->_x = new_x;
    this->_y = new_y;
}

/*
Spaceship::~Spaceship() {
}
//*/
