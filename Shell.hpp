#ifndef _SHELL_HPP
#define _SHELL_HPP

#include <vector>
#include "Job.hpp"

class Shell
{
public:
    int fgJobPID;
    vector<Job> jobs; // This represents the list of jobs. Please change to a preferred type (e.g array of char*)
    string pwd;
    string lastPwd;
};

#endif