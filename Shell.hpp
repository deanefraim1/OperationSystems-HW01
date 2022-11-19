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

    /// @brief search for a job with a given job id in the jobs vector of the shell
    /// @param id the wanted job id
    /// @return the index of the wanted job in the vector or -1 if not excist.
    int GetJobByJobID(int id);

    /// @brief search for a job with a given job id in the jobs vector of the shell
    /// @param pid the wanted job pid
    /// @return the index of the wanted job in the vector or -1 if not excist.
    int GetJobByPID(int pid);

    /// @brief insert the given job to the jobs vector in a sorted order by the job id
    /// @param job the given job to insert the vector
    void InsertJobSorted(Job job);

    /// @brief swap between the fg job and the given job and give the new fg job a runing status and the old fg job a waiting status
    /// @param jobIteratorToFg 
    void SwapFgJobSortedWith(vector<Job>::iterator jobIteratorToFg);
};

#endif