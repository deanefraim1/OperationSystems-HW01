#ifndef _JOB_HPP
#define _JOB_HPP

#include "Job.hpp"
#include <string>

using namespace std;

Job::Job()
{
    this->PID = EMPTY;
    this->jobID = EMPTY;
    this->prompt = "";
    this->command = "";
    this->status = bgRunning;
    this->timeStamp = EMPTY;
}

Job::Job(int PID, int jobID, string prompt, string command, jobStatus status)
{
    this->PID = PID;
    this->jobID = jobID;
    this->prompt = prompt;
    this->command = command;
    this->status = status;
    time(&(this->timeStamp));
}

double Job::getRunningTime()
{
    if(status == stopped)
        return timeStamp;
    else //running
    {
        time_t start = this->timeStamp;
        time_t end;
        time(&end);
        return difftime(end, start);
    }
}

#endif