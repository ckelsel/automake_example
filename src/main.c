
#include <stdio.h>
#include "add.h"
#include "del.h"
#include "usage.h"

int main(int argc, char **argv)
{

    if (argc > 1)

    {

        usage();

        return -1;
    }

    int a = 1;

    int b = -1;

    int c;

    c = add(a, b);

    printf("c = %d\n", c);

    c = del(a, b);

    printf("c = %d\n", c);

    return 0;
}
