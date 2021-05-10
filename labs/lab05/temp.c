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
        if (TimeCmp(floor, t_sub) > 0) {  // adding to a tree with no right subtree
            TreeInsert(s->times, t);
            s->count++;
            return true;
        }
    } else {
        if (TimeCmp(t_add, ceiling) < 0 && TimeCmp(floor, t_sub) > 0) { // more than 10 min apart 
            TreeInsert(s->times, t);
            s->count++;
            return true;
        }
    }
    return false;
}