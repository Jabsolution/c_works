/*
 *
 * This function detects a cycle in a link list
 *
 * It uses tortoise & hare algorithm
 *
 * i.e tortoise is a slow pointer runs one step at a time 
 * while hare is fast pointer runs 2 steps at a time
 *
 */
void cycle_detect(node *list) {
    node *first;
    node *second;

    if (!list)
        return false;

    first = second = list;

    while (first->next && first->next->next) {
        first = first->next;
        second = second->next->next;

        if (first == second)
            return 1;
        else 
            return 0;
    }
    return 0;
}
