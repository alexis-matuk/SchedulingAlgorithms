//
//  Functions.h
//  RoundRobin
//
//  Created by alexis matuk on 10/11/15.
//  Copyright (c) 2015 alexis matuk. All rights reserved.
//

#ifndef __RoundRobin__Functions__
#define __RoundRobin__Functions__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "FileReader.h"
#include "Process.h"
#include <deque>
#include "Functions.h"
struct Log{
    std::deque<Process*> queueStates;
    float currentTime;
};
int getProcPos(Process* proc, std::vector<Process*> processes);
void checkProcessToQueue(int procPos, std::vector<Process*> processes, Process * copy,std::deque<Process*> & RequestQueue, float timeElapsed, bool & checkedAllProcs);
void updateWaitingTime(std::vector<Process*> processes, Process* copy, int procPos, float startingTime);
void terminateProgram(std::vector<Log*> & log, std::vector<Process*> & processes, std::vector<Process*> & result);
void terminateProgram(std::vector<Process*> & processes, std::vector<Process*> & result);
void roundRobin(std::deque<Process*> & RequestQueue, std::vector<Process*> & processes, std::vector<Log*> & log, std::vector<Process*> & result, float quantum);
bool myfunction (Process* i,Process* j);
void updateAvailableProcs(std::vector<Process*> processes, std::vector<Process*> & availableProcs, float timeElapsed, float startingTime, int procPos, Process* proc);
void updateCurrentProcess(Process* & proc, Process* & checkProc, std::vector<Process*> availableProcs, std::vector<Process*> processes, bool & checkedAllProcs);
bool insideAvailableProcs(Process* proc, std::vector<Process*>availableProcs);
bool sortQueue(Process* i, Process* j);
void SJF(std::vector<Process*> & availableProcs, std::vector<Process*> & processes,std::vector<Process*> & result,bool & checkedAllProcs, Process* & checkProc, int & procPos, float & startingTime, float & timeElapsed, Process* & proc);
void printVector(std::vector<Process*> procs);
#endif /* defined(__RoundRobin__Functions__) */
