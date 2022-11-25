#ifndef _JOB_HPP
#define _JOB_HPP

#include "Job.hpp"
#include <string>

using namespace std;

Job::Job()
{
    this->PID = EMPTY;
    this->jobID = EMPTY;
    this->command = "";
    this->status = bgRunning;
    this->secondElapsed = 0;
}

Job::Job(int PID, int jobID, string command, jobStatus status)
{
    this->PID = PID;
    this->jobID = jobID;
    this->command = command;
    this->status = status;
    this->secondElapsed = 0;
}

#endif