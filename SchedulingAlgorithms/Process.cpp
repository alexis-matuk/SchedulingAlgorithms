//
//  Process.cpp
//  RoundRobin
//
//  Created by alexis matuk on 10/10/15.
//  Copyright (c) 2015 alexis matuk. All rights reserved.
//

#include "Process.h"
/*
 Sobrecarga del operador << para imprimir un proceso
 
 llamada: std::cout << Process;
 */
std::ostream & operator << ( std::ostream & os, Process & proc)
{
    os << "| " << proc.startingTime << " " << proc.name << " " << proc.endingTime << " |";
    return os;
}

Process::Process(Process* copy)
{
    name = copy->name;
    arrivalTime = copy->arrivalTime;
    burstTime = copy->burstTime;
    timeLeft = copy->timeLeft;
    waitingTime = copy->waitingTime;
    startingTime = copy->startingTime;
    endingTime = copy->endingTime;
    firstSum = copy->firstSum;
}

bool Process::operator < (Process & proc)
{
    return arrivalTime < proc.arrivalTime;
}

bool Process::operator > (Process & proc)
{
    return arrivalTime > proc.arrivalTime;
}

bool Process::operator != (Process & proc)
{
    if(name != proc.name && burstTime != proc.burstTime)
        return true;
    return false;
}

bool Process::operator == (Process & proc)
{
    if(name == proc.name && burstTime == proc.burstTime)
        return true;
    return false;
}

std::string Process::getName()
{
    return name;
}

void Process::addToWaitingTime(float t)
{
    waitingTime+=t;
}

bool Process::getFirstSum()
{
    return firstSum;
}

void Process::setFirstSum(bool s)
{
    firstSum = s;
}

float Process::getArrivalTime()
{
    return arrivalTime;
}

void Process::setTimeLeft(float t)
{
    timeLeft = t;
}

float Process::getTimeLeft()
{
    return timeLeft;
}

void Process::setWaitingTime(float t)
{
    waitingTime = t;
}

float Process::getWaitingTime()
{
    return waitingTime;
}

void Process::setStartingTime(float t)
{
    startingTime = t;
}

float Process::getStartingTime()
{
    return startingTime;
}

void Process::setEndingTime(float t)
{
    endingTime = t;
}

float Process::getEndingTime()
{
    return endingTime;
}

float Process:: getBurstTime()
{
    return burstTime;
}