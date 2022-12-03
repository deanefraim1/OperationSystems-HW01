#include "Shell.hpp"
#include "Job.hpp"
#include <vector>
#include <iostream>

#define NOT_EXCIST -1
#define MAX_LINE_SIZE 80
#define SIGEXCIST 0
#define EXCIST 0

using namespace std;

Shell::Shell()
{
    char buffer[MAX_LINE_SIZE];
    getcwd(buffer, MAX_LINE_SIZE);
    pwd = buffer;
}

int Shell::GetJobIndexByJobID(int id)
{
    for (int i = 0; i < jobs.size(); i++)
    {
        if(jobs[i].jobID == id)
            return i;
    }
    return NOT_EXCIST;
}

int Shell::GetJobIndexByPID(int pid)
{
    for (int i = 0; i < jobs.size(); i++)
    {
        if(jobs[i].PID == pid)
            return i;
    }
    return NOT_EXCIST;
}

void Shell::InsertJobSorted(Job job)
{
    int i;
    bool inserted = false;
    for (i = 0; i < jobs.size(); i++)
    {
		if(jobs[i].jobID > job.jobID)
		{
			jobs.insert(jobs.begin() + i, job);
            inserted = true;
            break;
        }
	}
    if(!inserted)
    {
        jobs.insert(jobs.begin() + i, job);
        inserted = true;
    }
}

void Shell::MoveJobToFg(int jobIndexToFg)
{
    Job jobToFg = jobs[jobIndexToFg];
    vector<Job>::iterator jobIteratorToFg = jobs.begin() + jobIndexToFg;
    jobs.erase(jobIteratorToFg);

    if(jobToFg.status == stopped)
    {
        time_t currentTime;
        time(&currentTime);
        jobToFg.timeStamp = currentTime - jobToFg.timeStamp; //timeStamo equals to runTime so far (for stopped jobs)
    }   
    jobToFg.status = fgRunning;
    fgJob = jobToFg;
}

int Shell::GetStoppedJobIndexWithMaxJobID()
{
    for (int i = jobs.size()-1; i >= 0; i++)
    {
        if(jobs[i].status == stopped)
            return i;
    }
    return NOT_EXCIST;
}

void Shell::UpdateJobsList()
{
    for (int i = 0; i < jobs.size(); i++)
    {
        if(kill(jobs[i].PID, SIGEXCIST) != EXCIST)
            jobs.erase(jobs.begin() + i);
    }
}

int Shell::GetNextJobID()
{
    if(jobs.size() > 0)
        return (jobs.end()-1).base()->jobID + 1;
    else
        return 1;
}

void Shell::PrintAllJobsInfo()
{
    for (int i = 0; i < jobs.size(); i++)
	{
		cout << "[" << jobs[i].jobID << "] " << jobs[i].prompt << " : " << jobs[i].PID << " " << jobs[i].getRunningTime() << " secs";
		if(jobs[i].status == stopped)
			cout << " (stopped)";
		cout << endl;
	}
}

void Shell::PrintShellPID()
{
    cout << "smash pid is " << getpid() << endl;
}

void Shell::KillAllJobs()
{
    for (int i = 0; i < jobs.size(); i++)
	{
		cout << "[" << jobs[i].jobID << "] " << jobs[i].prompt << " - Sending SIGTERM...";
		kill(jobs[i].PID, SIGTERM);
		if(!jobs[i].waitUntilTerminated(5, 0.1))
		{
			cout << " (5 sec passed) Sending SIGKILL...";
			kill(jobs[i].PID, SIGKILL);
		}
		cout << " Done." << endl;
	}
}
