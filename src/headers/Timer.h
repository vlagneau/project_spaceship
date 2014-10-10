/* 
 * File:   Timer.h
 * Author: Vincent
 *
 * Created on 7 octobre 2014, 19:02
 */

#ifndef TIMER_H
#define	TIMER_H

class Timer {
    
private:
    int _startTicks; // Clock time when the timer started
    int _pausedTicks; // Clock time when the timer was paused
    bool _paused;
    bool _started;
    
public:
    Timer();

    // Actions of the timer
    void start();
    void stop();
    void pause();
    void unpause();
    
    // Function getting the timer's time
    int get_ticks();
    
    // Functions checking the status of the timer
    bool is_started();
    bool is_paused();
};

#endif	/* TIMER_H */