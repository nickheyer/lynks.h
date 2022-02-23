#include "lynks.h"

#include <time.h>

int main(void)
{
    clock_t start_time = clock();
//------------------------------------TESTING-ZONE--------------------------------------------------------
    srand(time(NULL));
    lynk *list_1 = NULL;
    printf("loading list_1\n");

    for (int x = 0; x < 10000; x++)
    {
        char tmp[7];
        tmp[0] = (rand() % 65) + 57;
        tmp[1] = (rand() % 65) + 57;
        tmp[2] = (rand() % 65) + 57;
        tmp[3] = (rand() % 65) + 57;
        tmp[4] = (rand() % 65) + 57;
        tmp[5] = (rand() % 65) + 57;
        tmp[7] = '\0';
        lynkback(&list_1, lynkstr(tmp));
    }

    printf("list created\n");
    lynk *test = lynksort(list_1, 's', 'f');

    printf("list sorted\n");
    lynkprint(test, 's');
    printf("list printed\n");
    lynkunload(list_1);
    lynkunload(test);



//--------------------------------------------------------------------------------------------------------
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Done in %f seconds\n", elapsed_time);

    /*
    Benchmarks for the loading and unloading of lynks:
    1. An array of 1000 lynk lists of 1000 lynks, 1M total - 0.152493 seconds
    2. 1M lynk list of integer instantiated lynks. - 0.153707 seconds
    3. 10M lynk list of integer instantiated lynks. - 1.585455 seconds
    4. 50k lynks inserted into middle of 50k lynk list (Index 25k+i), "random access" - Deprecated(13.897690 seconds) - 0.015510 seconds
    5. 5M lynks inserted into middle of 5M lynk list (Index 2.5M+i), "random access" - 1.730934 seconds
    6. 5M lynks inserted into middle of 5M lynk list (Index 2.5M+i), then removed from the middle in the reverse order of insertion, "random access" - 2.021453 seconds
    7. 50k lynks inserted at completely random (rand()%50k) indexes within a 50k lynk list, truly random access, O(n2) unavoidable - Deprecated(22.190919 seconds) - Optimized(18.695469)
    8. 100k lynks w/ random string values inserted into head lynk at front, then sorted in ascending order, and cloned to new link - 156.992965 seconds
    */

    return 0;
}