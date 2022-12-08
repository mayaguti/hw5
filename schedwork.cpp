

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool scheduleHelper(
    size_t day,
    size_t workerCount,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched);
bool isValid(
    const unsigned int workerID,
    const size_t maxShifts,
    DailySchedule& sched);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    // Fill schedule
    for(unsigned int i = 0; i < avail.size(); i++){
        vector<Worker_T> temp;
        for(unsigned int j = 0; j < dailyNeed; j++){
            temp.push_back(INVALID_ID);
        }
        sched.push_back(temp);
    }

    return scheduleHelper(0, 0, avail, dailyNeed, maxShifts, sched);
}

bool scheduleHelper(
    size_t day,
    size_t workerCount,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched)
{
    if(day == avail.size() - 1 && workerCount == dailyNeed){
        return true;
    }

    if(workerCount == dailyNeed){
        return scheduleHelper(day+1, 0, avail, dailyNeed, maxShifts, sched);
    }

    if(sched[day][workerCount] == INVALID_ID){
        for(size_t i = 0; i < avail[day].size(); i++){
            if(avail[day][i] == 1){
                sched[day][workerCount] = i;
                if(isValid(i, maxShifts, sched) && scheduleHelper(day, workerCount + 1, avail, dailyNeed, maxShifts, sched)){
                    return true;
                }
            }
        }
        sched[day][workerCount] = INVALID_ID;
    }

    return false;
}

bool isValid(
    const unsigned int workerID,
    const size_t maxShifts,
    DailySchedule& sched)
{
    unsigned int perDay = 0;
    unsigned int perWeek = 0;

    for(size_t i = 0; i < sched.size(); i++){
        for(size_t j = 0; j < sched[i].size(); j++){
            if(sched[i][j] == workerID){
                perDay++;
                perWeek++;
            }
        }
        if(perDay > 1){ // each nurse works no more than 1 shift a day
            return false;
        }
        perDay = 0;
    }
    if(perWeek > maxShifts){ // each nurse works no more than maxShifts a week
        return false;
    }
    return true;
}