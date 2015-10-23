//
//  Process.h
//  RoundRobin
//
//  Created by alexis matuk on 10/10/15.
//  Copyright (c) 2015 alexis matuk. All rights reserved.
//

#ifndef __RoundRobin__Process__
#define __RoundRobin__Process__

#include <stdio.h>
#include <iostream>
class Process{
    std::string name = "";
    float arrivalTime = 0.0;
    float burstTime = 0.0;
    float timeLeft = 0.0;
    float waitingTime = 0.0;
    float startingTime = 0.0;
    float endingTime = 0.0;
    bool firstSum = false;
public:
    /* Constructor */
    Process(){}
    /* Constructor */
    Process(std::string _name, float _arrivalTime, float _burstTime, float _timeLeft, float _waitingTime, float _startingTime, float _endingTime):name(_name), arrivalTime(_arrivalTime), burstTime(_burstTime), timeLeft(_timeLeft), waitingTime(_waitingTime), startingTime(_startingTime), endingTime(_endingTime){}
    Process(std::string _name, float _arrivalTime, float _burstTime):name(_name), arrivalTime(_arrivalTime), burstTime(_burstTime), timeLeft(_burstTime), waitingTime(0.0), startingTime(0.0), endingTime(0.0){}
    Process(Process* copy);
    std::string getName();
    void addToWaitingTime(float t);
    float getBurstTime();
    bool getFirstSum();
    void setFirstSum(bool s);
    float getArrivalTime();
    void setTimeLeft(float t);
    float getTimeLeft();
    void setWaitingTime(float t);
    float getWaitingTime();
    void setStartingTime(float t);
    float getStartingTime();
    void setEndingTime(float t);
    float getEndingTime();
    bool operator < (Process & proc);
    bool operator > (Process & proc);
    bool operator != (Process & proc);
    bool operator == (Process & proc);
    friend std::ostream & operator << ( std::ostream & os, Process & proc);
};
#endif /* defined(__RoundRobin__Process__) */
