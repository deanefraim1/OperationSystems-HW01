#ifndef _SHELL_HPP
#define _SHELL_HPP

#include <vector>
#include "Job.hpp"

#define NOT_EXCIST -1

class Shell
{
public:
    Job fgJob;
    vector<Job> jobs; // This represents the list of jobs. Please change to a preferred type (e.g array of char*)
    string pwd;
    string lastPwd;

    /// @brief Shell constructor - initiate all the fields.
    Shell();

    /// @brief search for a job with a given job id in the jobs vector of the shell
    /// @param id the wanted job id
    /// @return the index of the wanted job in the vector or -1 if not excist.
    int GetJobIndexByJobID(int id);

    /// @brief search for a job with a given job id in the jobs vector of the shell
    /// @param pid the wanted job pid
    /// @return the index of the wanted job in the vector or -1 if not excist.
    int GetJobIndexByPID(int pid);

    /// @brief insert the given job to the jobs vector in a sorted order by the job id
    /// @param job the given job to insert the vector
    void InsertJobSorted(Job job);

    /// @brief move the given job to the fgJob and updates its data (timeStamp, status)
    /// @param jobIteratorToFg 
    void MoveJobToFg(int jobIndexToFg);

    /// @brief search for a stopped job in the jobs vector with the max job id
    /// @return the index of the job if excist or -1 if no stopped job in the job vector
    int GetStoppedJobIndexWithMaxJobID();

    /// @brief updates the job list and fgJob according to status changed by waitpid
    void UpdateJobs();

    /// @brief find job with highest job id, and calc the next job id to enter the jobs vector
    /// @return the highest job id excist +1
    int GetNextAvailableJobID();

    /// @brief print all jobs in the following format "[<job-id>] <prompt> : <jobPid> <jobRunningTime> secs" and add "(stopped)" at the end if the job is stopped
    void PrintAllJobsInfo();

    /// @brief prints the shell PID
    void PrintShellPID();

    /// @brief kills all jobs excists and if SIGTERM fails, it sends SIGKILL
    void KillAllJobs();

    /// @brief change the fgJob to stopped (handling the time and status) and pass it to the jobs list
    void StopFgJob();

    /// @brief makes the fgJob empty
    void ClearFgJob();
};

#endif