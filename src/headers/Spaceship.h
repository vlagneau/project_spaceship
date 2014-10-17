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
//    virtual ~Spaceship();
private:
    // Position of the spaceship
    int _x;
    int _y;
    
    // Velocity of the spaceship
    int _xVel;
    int _yVel;
    
    // Size of the spaceship
    int _width;
    int _height;
    
    // surface of the spaceship
    SDL_Surface* _surface;
    // sprites of the spaceship
    SDL_Rect _sprites[2];
    
    // function initializing the spaceship (sprites, ...)
    void init();
    
public:
    // constructors
    Spaceship();
    Spaceship(int x, int y);
    Spaceship(const Spaceship& orig);
    
    // events handler
    void handle_events(SDL_Event event);
    
    // display of the spaceship
    void show(SDL_Surface* screen);
    
    // clean of the components
    void clean();
    
    // change the position of the spaceship
    void move();
};

#endif	/* SPACESHIP_H */

