
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
