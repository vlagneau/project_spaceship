/* 
 * File:   Timer.cpp
 * Author: Vincent
 * 
 * Created on 7 octobre 2014, 19:02
 */

#include "SDL/SDL.h"
#include "headers/Timer.h"

/*
 * Constructor
 */
Timer::Timer() {
    this->_startTicks = 0;
    this->_started = false;
    this->_pausedTicks = 0;
    this->_paused = false;
}

/*
 * Function starting the Timer
 */
void Timer::start(){
    // Update the Timer status
    this->_started = true;
    this->_paused = false;
    
    // Get the current clock time
    this->_startTicks = SDL_GetTicks();
}

/*
 * Function stopping the Timer
 */
void Timer::stop(){
    // Update the Timer Status
    this->_started = false;
    this->_paused = false;
}

/*
 * Function that pause the Timer
 */
void Timer::pause(){
    if (this->_started && !this->_paused) {
        this->_paused = true;
        this->_pausedTicks = SDL_GetTicks() - this->_startTicks;
    }
}

/*
 * Function that unpause the Timer
 */
void Timer::unpause(){
    if(this->_paused){
        this->_paused = false;
        
        // Reset of the starting time
        this->_startTicks = SDL_GetTicks() - this->_pausedTicks;
        this->_pausedTicks = 0;
    }
}

/*
 * Function returning the current time of the Timer
 */
int Timer::get_ticks(){
    int ticks = 0;
    
    if(this->_started){
        // If the timer is paused, the function returns the time when the timer was paused
        if(this->_paused){
            ticks = this->_pausedTicks;
        }
        
        // Else, it returns the difference between the current time and the time the Timer started
        else{
            ticks = SDL_GetTicks() - this->_startTicks;
        }
    }
    
    return ticks;
}

bool Timer::is_started(){
    return this->_started;
}

bool Timer::is_paused(){
    return this->_paused;
}