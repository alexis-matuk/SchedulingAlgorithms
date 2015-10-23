//
//  FileReader.h
//  RoundRobin
//
//  Created by alexis matuk on 10/10/15.
//  Copyright (c) 2015 alexis matuk. All rights reserved.
//

#ifndef __RoundRobin__FileReader__
#define __RoundRobin__FileReader__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "Process.h"
class FileReader{
    std::ifstream file;
    std::string route;
public:
    FileReader(std::string _route):route(_route){}
    ~FileReader();
    bool openFile();
    void closeFile();
    void readProcesses(std::vector<Process*> & _processes);
    float readQuantum();
};
#endif /* defined(__RoundRobin__FileReader__) */
