/* 
 * File:   functions.h
 * Author: Vincent
 *
 * Created on 14 mars 2014, 19:12
 */

#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

/**
 * Function loading an optimized image using the path/filename of the image
 * @param _filename name of the image to load (must contain the path if not in the current directory)
 * @return a pointer on the SDL_Surface representing the optimized image
 */
SDL_Surface *load_image(std::string _filename);

void apply_surface(int _x, int _y, SDL_Surface* _source, SDL_Surface* _destination, SDL_Rect* _clip = NULL);

#endif	/* FUNCTIONS_H */

