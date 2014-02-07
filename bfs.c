#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(){
    int array_group[10] = {5, 2, 12, 10, 43, 25, 41, 7, 13, 15};
    queue *qitem;
    qinfo *q;
    qinit(&q);
}

/* 
enqueue(&q, item);

    enqueue(&q, item);

    qitem = (queue *)dequeue(&q);
    item = (inode *)qitem->items;
    qitem = (queue *)dequeue(&q);
    item = (inode *)qitem->items;
    printf("Items are %d, %s, %s", item->i, item->lname, item->fname);


}*/
