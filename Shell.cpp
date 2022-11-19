#include "Shell.hpp"
#include "Job.hpp"

#define NOT_EXCIST -1

/// @brief search for a job with a given job id in the jobs vector of the shell
/// @param id the wanted job id
/// @return the index of the wanted job in the vector or -1 if not excist.
int Shell::GetJobByJobID(int id)
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
int Shell::GetJobByPID(int pid)
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
    for (int i = 0; i < jobs.size(); i++)
	{
		if(jobs[i].jobID > job.jobID)
		{
			jobs.insert(jobs.begin() + i, job);
			jobs[i].status = waiting;
			break;
		}
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

    fgJob = jobToFg;
    fgJob.status = running;
}