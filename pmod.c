/*
 * Name: Nick Erdmann
 * Date: 11/10/26
 * File: pmod.c
 * Mod proccess priority
 */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int main(int argc, char* argv[])
{

    errno = 0;

    int newPriority = nice(10);

    if (newPriority == -1 && errno != 0)
    {
        perror("Error modifying process priority");
        return 1;
    }

    printf("Process priority modified\n");
    printf("New nice value: %d\n", newPriority);

    //set the requested sleep duration.

    struct timespec sleepTime;

    sleepTime.tv_sec = 1;
    sleepTime.tv_nsec = 837272638;

    //sleep using nanosleep

    while (nanosleep(&sleepTime, &sleepTime) == -1)
    {
        if (errno != EINTR)
        {
            perror("Error during nanosleep");
            return 1;
        }
    }

    //goodbye message
    printf("Goodbye!\n");

    return 0;
}