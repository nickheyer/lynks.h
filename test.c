#include "lynks.h"

#include <time.h>

int main(void)
{
    clock_t start_time = clock();
//------------------------------------TESTING-ZONE--------------------------------------------------------


    lynk *list_1 = lynkarr(50000);

    for (int x = 1; x < 50000; x++)
    {
        lynkinsert(&list_1, 25000, lynkempty());
    }

    lynkunload(list_1);


//--------------------------------------------------------------------------------------------------------
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Done in %f seconds\n", elapsed_time);

    /*
    Benchmarks for the loading and unloading of lynks:
    1. An array of 1000 lynk lists of 1000 lynks, 1M total - 0.152493 seconds
    2. 1M lynk list of integer instantiated lynks. - 0.153707 seconds
    3. 10M lynk list of integer instantiated lynks. - 1.585455 seconds
    4. 50k lynks inserted into middle of 50k lynk list, "random access" - 13.897690 seconds
    */

    return 0;
}