/* 
 * File:   Spaceship.cpp
 * Author: Vincent
 * 
 * Created on 6 mars 2014, 10:33
 */

#include "Spaceship.h"
#include "const.h"

/**
 * Default constructor
 */
Spaceship::Spaceship() {
    // initialization of the ship
    this->init();
    
    // initiatlization of the position
    this->_position.x = (SCREEN_WIDTH - this->_sprites[0].w) / 2;
    this->_position.y = (SCREEN_HEIGHT - this->_sprites[0].h) / 2;
    this->_position.h = this->_sprites[0].h;
    this->_position.w = this->_sprites[0].w;
}

/**
 * Custom constructor allowing to set the initial position of the ship
 * @param _x position on the x axis
 * @param _y position on the y axis
 */
Spaceship::Spaceship(int _x, int _y) {
    Spaceship();
    
    this->_position.x = _x;
    this->_position.y = _y;
}

Spaceship::Spaceship(const Spaceship& orig) {
}

void Spaceship::handle_events() {
}

/**
 * Method that display the spaceship onto the surface that have been
 * passed in the parameters, by reseting the surface before
 * @param _screen surface that will have the spaceship blitted on
 */
void Spaceship::show(SDL_Surface* _screen){
    SDL_FillRect(_screen, &_screen->clip_rect, SDL_MapRGB(_screen->format, 0, 0, 0));
    apply_surface(this->_position.x, this->_position.y, this->_surface, _screen, &(this->_sprites[0]));
    
    SDL_Flip(_screen);
}

/**
 * Function initializing the spaceship sprites and images
 */
void Spaceship::init() {
    this->_surface = load_image("ressources/spaceship_sprite.png");
    
    //Clip range for the top left
    this->_sprites[0].x = 0;
    this->_sprites[0].y = 0;
    this->_sprites[0].w = 150;
    this->_sprites[0].h = 125;

    //Clip range for the top right
    this->_sprites[1].x = 150;
    this->_sprites[1].y = 0;
    this->_sprites[1].w = 150;
    this->_sprites[1].h = 165;
}

void Spaceship::clean(){
    SDL_FreeSurface(this->_surface);
}


// change the position of the spaceship
void Spaceship::move(int _x_variation, int _y_variation, SDL_Surface* _screen){
    int new_x = this->_position.x + _x_variation;
    int new_y = this->_position.y + _y_variation;
    
    if(new_x < 0){
        this->_position.x = 0;
    }
    else if (new_x <= (SCREEN_WIDTH - this->_position.w)){
        this->_position.x = new_x;
    }
    
    if(new_y < 0){
        this->_position.y = 0;
    }
    else if (new_y <= (SCREEN_HEIGHT - this->_position.h)){
        this->_position.y = new_y;
    }
    
    this->show(_screen);
}

/*
Spaceship::~Spaceship() {
}
//*/
