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
    this->secondElapsed = EMPTY;
}

Job::Job(int PID, int jobID, string command, jobStatus status)
{
    this->PID = PID;
    this->jobID = jobID;
    this->command = command;
    this->status = status;
    time(&(this->secondElapsed));
}

double Job::getCurrentRunningTime()
{
    time_t start = this->secondElapsed;
    time_t end;
    time(&end);
    return difftime(end, start);
}

#endif