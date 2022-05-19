#include <stdio.h>


int main()
{

    int a[3] = {1,2,3};

    int *p;

    p = &a;

    printf("%d",p[0]);

    return 0;
}
