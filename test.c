#include "lynks.h"

int main(void)
{
    // lynk *list_1 = lynkint(30000);


    // for (int x = 0; x < 30000; x++)
    // {
    //     lynkfront(&list_1, lynkint(69));
    // }


    lynk *list_2 = lynkarr(400000);

    printf("loaded\n");
    printf("Size of array: %i\n", list_2->size);
    printf("Amount of count: %i\n", lynkcount(list_2));
    lynkunload(list_2);
    printf("Done!\n");

    return 0;
}