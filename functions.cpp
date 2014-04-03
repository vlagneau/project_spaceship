/* 
 * File:   functions.cpp
 * Author: Vincent
 *
 * Created on 14 mars 2014, 19:12
 */

#include "functions.h"

/**
 * Function loading an optimized image using the path/filename of the image
 * @param _filename name of the image to load (must contain the path if not in the current directory)
 * @return a pointer on the SDL_Surface representing the optimized image
 */
SDL_Surface *load_image(std::string _filename){
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(_filename.c_str());

    //If the image loaded
    if(loadedImage != NULL){
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old surface
        SDL_FreeSurface(loadedImage);

        //If the surface was optimized
        if(optimizedImage != NULL){
            //Color key surface
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

/**
 * Function applying a source surface onto a destination surface using the coordonates given
 * @param _x
 * @param _y
 * @param _source
 * @param _destination
 * @param _clip
 */
void apply_surface(int _x, int _y, SDL_Surface* _source, SDL_Surface* _destination, SDL_Rect* _clip){
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = _x;
    offset.y = _y;

    //Blit
    SDL_BlitSurface(_source, _clip, _destination, &offset);
}