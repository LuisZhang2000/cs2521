// Schedule ADT implementation

#include <stdio.h>
#include <stdlib.h>

#include "Schedule.h"
#include "Time.h"
#include "Tree.h"

struct schedule {
    Tree times;
    int  count;
};

// Creates a new schedule
Schedule ScheduleNew(void) {
    Schedule s = malloc(sizeof(*s));
    if (s == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    s->times = TreeNew();
    s->count = 0;
    return s;
}

// Frees all memory associated with a given schedule
void ScheduleFree(Schedule s) {
    TreeFree(s->times);
    free(s);
}

// Gets the number of times added to the schedule
int  ScheduleCount(Schedule s) {
    return s->count;
}

// Attempts to schedule a new landing time. Returns true if the time was
// successfully added, and false otherwise.
bool ScheduleAdd(Schedule s, Time t) {
    // check if schedule is within 10 min of other landings
    Time floor = TreeFloor(s->times, t);
    Time ceiling = TreeCeiling(s->times, t);

    Time t_add = TimeAddMinutes(t, 10);
    Time t_sub = TimeSubtractMinutes(t, 10);

    if (ScheduleCount(s) == 0) {    // no schedules yet
        TreeInsert(s->times, t);
        s->count++;
        return true;
    } else if (floor == NULL && ceiling != NULL) {
        if (TimeCmp(t_add, ceiling) < 0) {  // adding to a tree with no left subtree
            TreeInsert(s->times, t);
            s->count++;
            return true;
        }
    } else if (ceiling == NULL && floor != NULL) {
        if (TimeCmp(t_sub, floor) > 0) {  // adding to a tree with no right subtree
            TreeInsert(s->times, t);
            s->count++;
            return true;
        }
    } else {
        if (TimeCmp(t_add, ceiling) < 0 && TimeCmp(t_sub, floor) > 0) { // more than 10 min apart 
            TreeInsert(s->times, t);
            s->count++;
            return true;
        }
    }
    return false;
}

// Shows  all  the landing times in the schedule. If mode is 1, only the
// times are shown. If mode is 2, the underlying data structure is shown
// as well.
void ScheduleShow(Schedule s, int mode) {
    if (mode == 1) {
        TreeList(s->times);
    } else if (mode == 2) {
        TreeShow(s->times);
    }
}
