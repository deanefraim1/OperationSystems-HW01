#include "Shell.hpp"
#include "Job.hpp"
#include <vector>

#define NOT_EXCIST -1
#define MAX_LINE_SIZE 80
#define SIGEXCIST 0
#define EXCIST 0


Shell::Shell()
{
    char buffer[MAX_LINE_SIZE];
    getcwd(buffer, MAX_LINE_SIZE);
    pwd = buffer;
}

/// @brief search for a job with a given job id in the jobs vector of the shell
/// @param id the wanted job id
/// @return the index of the wanted job in the vector or -1 if not excist.
int Shell::GetJobIndexByJobID(int id)
{
    for (int i = 0; i < jobs.size(); i++)
    {
        if(jobs[i].jobID == id)
            return i;
    }
    return NOT_EXCIST;
}

/// @brief search for a job with a given job id in the jobs vector of the shell
/// @param pid the wanted job pid
/// @return the index of the wanted job in the vector or -1 if not excist.
int Shell::GetJobIndexByPID(int pid)
{
    for (int i = 0; i < jobs.size(); i++)
    {
        if(jobs[i].PID == pid)
            return i;
    }
    return NOT_EXCIST;
}

/// @brief insert the given job to the jobs vector in a sorted order by the job id and gives it a waiting status
/// @param job the given job to insert the vector
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
		jobs[i].status = bgRunning;
        inserted = true;
    }
}

/// @brief swap between the fg job and the given job and give the new fg job a runing status and the old fg job a waiting status
/// @param jobIteratorToFg 
void Shell::MoveJobToFg(vector<Job>::iterator jobIteratorToFg)
{
    Job jobToFg = *jobIteratorToFg.base();
    jobs.erase(jobIteratorToFg);

    if(fgJob.jobID != EMPTY)
        InsertJobSorted(fgJob);

    if(jobToFg.status == stopped)
    {
        time_t currentTime;
        time(&currentTime);
        jobToFg.timeStamp = currentTime - jobToFg.timeStamp; //timeStamo equals to runTime so far (for stopped jobs)
        fgJob.status = fgRunning;
    }   
    fgJob = jobToFg;
}

/// @brief search for a stopped job in the jobs vector with the max job id
/// @return the index of the job if excist or -1 if no stopped job in the job vector
int Shell::GetStoppedJobPIDWithMaxJobID()
{
    for (int i = jobs.size()-1; i >= 0; i++)
    {
        if(jobs[i].status == stopped)
            return jobs[i].PID;
    }
    return NOT_EXCIST;
}

/// @brief 
/// @param job 
void Shell::InsertJobToFg(Job job)
{
    if(fgJob.PID != NOT_EXCIST) 
        InsertJobSorted(fgJob);
    fgJob = job;
}

/// @brief 
void Shell::UpdateJobsList()
{
    for (int i = 0; i < jobs.size(); i++)
    {
        if(kill(jobs[i].PID, SIGEXCIST) != EXCIST)
            jobs.erase(jobs.begin() + i);
    }
}