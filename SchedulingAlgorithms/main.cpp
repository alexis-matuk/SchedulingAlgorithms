//
//  main.cpp
//  RoundRobin
//
//  Created by alexis matuk on 10/10/15.
//  Copyright (c) 2015 alexis matuk. All rights reserved.
//

#include "Functions.h"

int main(int argc, const char * argv[])
{
    int choice;
    bool done = false;
    while(!done)
    {
        std::cout << "===== Scheduling Algorithms ===== " << std::endl;
        std::cout << "1) Preemptive Shortest Job First" << std::endl;
        std::cout << "2) Round Robin" << std::endl;
        std::cout << "3) Salir" << std::endl;
        std::cout << "Elige una opción: ";
        while(!(std::cin >> choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida, intenta otra vez: ";
        }
        switch(choice)
        {
            case 1:{
                std::vector<Process*> availableProcs;
                std::vector<Process*> processes;
                std::vector<Process*> result;
                std::cout << "Ruta del archivo a leer (relativa o absoluta) con extensión: ";
                std::string route;
                std::cin.ignore();
                getline(std::cin, route);
                FileReader reader(route);
                if(!reader.openFile())
                    break;
                reader.readProcesses(processes);
                std::cout << "Los procesos leídos son: " << std::endl;
                printVector(processes);
                std::sort(processes.begin(), processes.end(), myfunction);
                Process* proc = processes[0];
                float timeElapsed = processes[0]->getArrivalTime();
                int procPos = 0;
                bool checkedAllProcs = false;
                Process* checkProc;
                float startingTime = 0.0;
                availableProcs.push_back(proc);
                SJF(availableProcs,processes,result,checkedAllProcs,checkProc,procPos,startingTime,timeElapsed,proc);
                terminateProgram(processes, result);
                break;}
            case 2:{
                std::deque<Process*> RequestQueue;
                std::vector<Process*> processes;
                std::vector<Log*> log;
                std::vector<Process*> result;
                std::string route;
                std::cout << "Ruta del archivo a leer (relativa o absoluta) con extensión: ";
                std::cin.ignore();
                getline(std::cin, route);
                FileReader reader(route);
                if(!reader.openFile())
                    break;
                reader.readProcesses(processes);
                std::cout << "Los procesos leídos son: " << std::endl;
                printVector(processes);
                float quantum = reader.readQuantum();
                std::cout << "El quantum es: " << quantum << std::endl;
                std::sort(processes.begin(), processes.end(), myfunction);
                RequestQueue.push_back(processes[0]);
                roundRobin(RequestQueue, processes, log, result, quantum);
                terminateProgram(log, processes, result);
                break;}
            case 3:{
                std::cout << "Adios!" << std::endl;
                done = true;
                break;}
            default:
                std::cout << "Opción inválida, elige otra" << std::endl;
                break;
        }
    }
    return 0;
}
