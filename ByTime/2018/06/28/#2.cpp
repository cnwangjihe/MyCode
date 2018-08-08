#include <stdio.h>
#include <sys/sysinfo.h>
 
int main()
{
        struct sysinfo si;
        sysinfo(&si);
        printf("Totalram:       %d\n", si.totalram);
        printf("Available:      %d\n", si.freeram);
        return 0;
}