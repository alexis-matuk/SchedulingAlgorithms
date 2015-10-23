//
//  Functions.cpp
//  RoundRobin
//
//  Created by alexis matuk on 10/11/15.
//  Copyright (c) 2015 alexis matuk. All rights reserved.
//

#include "Functions.h"
int getProcPos(Process* proc, std::vector<Process*> processes)
{
    int pos = 0;
    for (int i = 0; i<processes.size(); i++)
    {
        if(*proc == *processes[i])
        {
            return pos;
        }
        pos++;
    }
    return pos;
}

void printVector(std::vector<Process*> procs)
{
    for(auto i : procs)
    {
        std::cout << i->getName() << " " << i->getArrivalTime() << " " << i->getBurstTime() << std::endl;
    }
    std::cout << std::endl;
}

bool inQueue(Process* proc, std::deque<Process*> _queue)
{
    for(auto i : _queue)
    {
        if( *i == *proc)
            return true;
    }
    return false;
}

void checkProcessToQueue(int procPos, std::vector<Process*> processes, Process * copy,std::deque<Process*> & RequestQueue, float timeElapsed, bool & checkedAllProcs)
{
    for(int i = procPos+1; i < processes.size(); i++)
    {
        if(procPos == processes.size() - 1)
        {
            if(!inQueue(copy, RequestQueue) && copy->getTimeLeft() > 0)
                RequestQueue.push_back(processes[i-1]);
            break;
        }
        else if(processes[i]->getArrivalTime() <= timeElapsed && processes[i]->getTimeLeft() > 0)
        {
            if(!inQueue(processes[i], RequestQueue))
                RequestQueue.push_back(processes[i]);
            if( i == processes.size() - 1 )
                checkedAllProcs = true;
        }
        else
        {
            break;
        }
    }
}

void updateWaitingTime(std::vector<Process*> processes, Process* copy, int procPos, float startingTime)
{
    if(!processes[procPos]->getFirstSum())
    {
        processes[procPos]->addToWaitingTime(startingTime - copy->getArrivalTime());
        processes[procPos]->setFirstSum(true);
    }
    else
    {
        if(startingTime - copy->getEndingTime() < 0)
            processes[procPos]->addToWaitingTime(0);
        else
            processes[procPos]->addToWaitingTime(startingTime - copy->getEndingTime());
    }
}

void terminateProgram(std::vector<Process*> & processes, std::vector<Process*> & result)
{
    std::cout << std::endl;
    std::cout << "=====Processes Gantt Chart====" << std::endl;
    for(auto i : result)
        std::cout << *i;
    std::cout << std::endl;
    std::cout << std::endl;
    float waitingTime = 0;
    std::cout << "=====Waiting Times====" << std::endl;
    for(auto i : processes)
    {
        waitingTime+=i->getWaitingTime();
        std::cout << i->getName() << " - " << i->getWaitingTime() << std::endl;
    }
    std::cout << "Average waiting time: " << (float)waitingTime/(size_t)processes.size() << std::endl;
    std::cout << std::endl;
    for(auto i : processes)
        delete i;
    for(auto i : result)
        delete i;
}

void terminateProgram(std::vector<Log*> & log, std::vector<Process*> & processes, std::vector<Process*> & result)
{
    std::cout << std::endl;
    std::cout << "=====Processes Gantt Chart====" << std::endl;
    for(auto i : result)
        std::cout << *i;
    std::cout << std::endl;
    std::cout << std::endl;
    float waitingTime = 0;
    std::cout << "=====Waiting Times====" << std::endl;
    for(auto i : processes)
    {
        waitingTime+=i->getWaitingTime();
        std::cout << i->getName() << " - " << i->getWaitingTime() << std::endl;
    }
    std::cout << "Average waiting time: " << (float)waitingTime/(size_t)processes.size() << std::endl;
    std::cout << std::endl;
    std::cout << "=====Queue States====" << std::endl;
    for(auto  i : log)
    {
        std::cout << "Time: " << i->currentTime << std::endl;
        if(i->queueStates.empty())
            std::cout << "Request queue empty";
        else
        {
            std::cout << "Queue - ";
            for( auto j : i->queueStates)
            {
                std::cout << *j;
            }
        }
        std::cout << std::endl;
    }
    for(auto i : processes)
        delete i;
    for(auto i : result)
        delete i;
    for(auto  i : log)
        delete i;
}

bool myfunction (Process* i,Process* j)
{
    return (*i<*j);
}

bool sortQueue(Process* i, Process* j)
{
    if(i->getTimeLeft() == j->getTimeLeft())
        return i->getArrivalTime() < j->getArrivalTime();
    return i->getTimeLeft() < j->getTimeLeft();
}

bool insideAvailableProcs(Process* proc, std::vector<Process*>availableProcs)
{
    std::vector<Process*>::iterator it;
    
    it = std::find (availableProcs.begin(), availableProcs.end(), proc);
    if (it != availableProcs.end())
        return true;
    return false;
}

void updateAvailableProcs(std::vector<Process*> processes, std::vector<Process*> & availableProcs, float timeElapsed, float startingTime, int procPos, Process* proc)
{
    for(int i=procPos; i<processes.size(); i++)
    {
        if(*processes[i] == *proc)
        {
            continue;
        }
        else
        {
            if(processes[i]->getArrivalTime() >= startingTime && processes[i]->getArrivalTime() <= timeElapsed && !insideAvailableProcs(processes[i], availableProcs))
            {
                availableProcs.push_back(processes[i]);
            }
        }
    }
}

void updateCurrentProcess(Process* & proc, Process* & checkProc, std::vector<Process*> availableProcs, std::vector<Process*> processes, bool & checkedAllProcs)
{
    //Si tienen el mismo tieme left que proc, dejas el proc
    std::vector<Process*> copyVector = availableProcs;
    std::sort(copyVector.begin(), copyVector.end(), sortQueue);
    int j = 0;
    while(j < availableProcs.size())
    {
        if(copyVector[j]->getTimeLeft() != 0)
        {
            Process* newProc = copyVector[j];
            float procPos = getProcPos(newProc, availableProcs);
            proc = processes[procPos];
            break;
        }
        j++;
    }
    
    float procPos = getProcPos(proc, processes);
    int i = procPos+1;
    while(i < processes.size())
    {
        if(processes[i]->getArrivalTime() == proc->getArrivalTime())
        {
            i++;
            continue;
        }
        else
        {
            if(!insideAvailableProcs(processes[i], availableProcs))
            {
                checkProc = processes[i];
                break;
            }
        }
        i++;
    }
}

void roundRobin(std::deque<Process*> & RequestQueue, std::vector<Process*> & processes, std::vector<Log*> & log, std::vector<Process*> & result, float quantum)
{
    Process* proc;
    float timeElapsed = processes[0]->getArrivalTime();
    int procPos = 0;
    bool checkedAllProcs = false;
    while (!RequestQueue.empty())
    {
        proc = RequestQueue.front();
        RequestQueue.pop_front();
        Process* copy = new Process(proc);
        procPos = getProcPos(proc, processes);
        if(copy->getTimeLeft() <= quantum)
        {
            float startingTime = timeElapsed;
            timeElapsed += copy->getTimeLeft();
            updateWaitingTime(processes, copy, procPos, startingTime);
            copy->setStartingTime(startingTime);
            copy->setEndingTime(startingTime + copy->getTimeLeft());
            copy->setTimeLeft(0);
            result.push_back(copy);
            if(!checkedAllProcs)
                checkProcessToQueue(procPos, processes, copy, RequestQueue, timeElapsed, checkedAllProcs);
            Log* l = new Log();
            std::deque<Process*>* queueCopy = new std::deque<Process*>(RequestQueue);
            l->queueStates = *queueCopy;
            l->currentTime = timeElapsed;
            log.push_back(l);
        }
        else
        {
            float startingTime = timeElapsed;
            if(copy->getTimeLeft() - quantum < 0)
                copy->setTimeLeft(0);
            else
                copy->setTimeLeft(copy->getTimeLeft() - quantum);
            updateWaitingTime(processes, copy, procPos, startingTime);
            copy->setStartingTime(startingTime);
            copy->setEndingTime(timeElapsed+quantum);
            result.push_back(copy);
            timeElapsed+=quantum;
            if(!checkedAllProcs)
                checkProcessToQueue(procPos, processes, copy, RequestQueue, timeElapsed, checkedAllProcs);
            if(copy->getTimeLeft() > 0)
                RequestQueue.push_back(copy);
            Log* l = new Log();
            std::deque<Process*>* queueCopy = new std::deque<Process*>(RequestQueue);
            l->queueStates = *queueCopy;
            l->currentTime = timeElapsed;
            log.push_back(l);
        }
    }
}

void SJF(std::vector<Process*> & availableProcs, std::vector<Process*> & processes,std::vector<Process*> & result,bool & checkedAllProcs, Process* & checkProc, int & procPos, float & startingTime, float & timeElapsed, Process* & proc)
{
    int i = 0;
    while(processes[i]->getArrivalTime() == proc->getArrivalTime())
    {
        i++;
        checkProc = processes[i];
    }
    while(!checkedAllProcs)
    {
        float workingTime = checkProc->getArrivalTime() - timeElapsed;
        if(workingTime < proc->getTimeLeft())
        {
            procPos = getProcPos(proc, processes);
            startingTime = timeElapsed;
            timeElapsed+=workingTime;
            Process* copy = new Process(proc);
            availableProcs[procPos]->setTimeLeft(copy->getTimeLeft() - workingTime);
            processes[procPos]->setTimeLeft(copy->getTimeLeft() - workingTime);
            copy->setEndingTime(timeElapsed);
            copy->setStartingTime(startingTime);
            copy->setTimeLeft(copy->getTimeLeft() - workingTime);
            result.push_back(copy);
            procPos = getProcPos(proc, processes);
            updateAvailableProcs(processes, availableProcs, timeElapsed, startingTime, procPos, proc);
        }
        else
        {
            if(proc->getTimeLeft() == 0)
                continue;
            procPos = getProcPos(proc, processes);
            startingTime = timeElapsed;
            workingTime = proc->getTimeLeft();
            timeElapsed+=workingTime;
            Process* copy = new Process(proc);
            availableProcs[procPos]->setTimeLeft(copy->getTimeLeft() - workingTime);
            processes[procPos]->setTimeLeft(copy->getTimeLeft() - workingTime);
            copy->setEndingTime(timeElapsed);
            copy->setStartingTime(startingTime);
            copy->setTimeLeft(copy->getTimeLeft() - workingTime);
            result.push_back(copy);
            procPos = getProcPos(proc, processes);
            updateAvailableProcs(processes, availableProcs, timeElapsed, startingTime, procPos, proc);
        }
        updateCurrentProcess(proc, checkProc, availableProcs, processes, checkedAllProcs);
        if(availableProcs.size() == processes.size())
            checkedAllProcs = true;
    }
    std::sort(availableProcs.begin(), availableProcs.end(), sortQueue);
    for( int i = 0; i<availableProcs.size(); i++)
    {
        if(availableProcs[i]->getTimeLeft() == 0)
            continue;
        else
        {
            procPos = getProcPos(availableProcs[i], processes);
            startingTime = timeElapsed;
            timeElapsed+=availableProcs[i]->getTimeLeft();
            Process* copy = new Process(availableProcs[i]);
            availableProcs[i]->setTimeLeft(0.0);
            copy->setStartingTime(startingTime);
            copy->setEndingTime(timeElapsed);
            copy->setTimeLeft(0.0);
            result.push_back(copy);
        }
    }
    for(int i=0; i<result.size(); i++)
    {
        float procPos = getProcPos(result[i], processes);
        if(!processes[procPos]->getFirstSum())
        {
            processes[procPos]->addToWaitingTime(result[i]->getStartingTime() - result[i]->getArrivalTime());
            processes[procPos]->setEndingTime(result[i]->getEndingTime());
            processes[procPos]->setFirstSum(true);
        }
        else
        {
            if(result[i]->getStartingTime() - processes[procPos]->getEndingTime() < 0 || result[i]->getName() == result[i-1]->getName())
                processes[procPos]->setEndingTime(result[i]->getEndingTime());
            else
            {
                processes[procPos]->addToWaitingTime(result[i]->getStartingTime() - processes[procPos]->getEndingTime());
                processes[procPos]->setEndingTime(result[i]->getEndingTime());
            }
        }
    }
    
}

