/* 
 * File:   Spaceship.h
 * Author: Vincent
 *
 * Created on 6 mars 2014, 10:33
 */

#ifndef SPACESHIP_H
#define	SPACESHIP_H

#include "SDL/SDL.h"
#include "functions.h"

class Spaceship {
public:
    // constructors
    Spaceship();
    Spaceship(int _x, int _y);
    Spaceship(const Spaceship& orig);
    
    // events handler
    void handle_events();
    
    // display of the spaceship
    void show(SDL_Surface* _screen);
    
    // clean of the components
    void clean();
    
    // change the position of the spaceship
    void move(int _x_variation, int _y_variation, SDL_Surface* _screen);
    
//    virtual ~Spaceship();
private:
    // position of the spaceship
    SDL_Rect _position;
    // surface of the spaceship
    SDL_Surface* _surface;
    // sprites of the spaceship
    SDL_Rect _sprites[2];
    
    // function initializing the spaceship (sprites, ...)
    void init();
};

#endif	/* SPACESHIP_H */

