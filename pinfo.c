/*
 * Name: Nick Erdmann
 * Date: 11/10/26
 * File: pinfo.c
 * Retrieves and displays information about the process
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>
#include <signal.h>

int main(int argc, char* argv[])
{
    pid_t pid;

    //check PID
    if (argc > 2)
    {
        fprintf(stderr, "Error: too many arguments\n");
        return 1;
    }

    // else use current
    if (argc == 1)
    {
        pid = getpid();
    }
    else
    {
        char *endptr;

        long inputPID = strtol(argv[1], &endptr, 10);

        if (*argv[1] == '\0' || *endptr != '\0' ||
            inputPID <= 0 || inputPID > 2147483647)
        {
            fprintf(stderr, "Error: Invalid process ID.\n");
            return 1;
        }

        pid = (pid_t)inputPID;
    }

    //check for existance
    if (kill(pid, 0) == -1 && errno != EPERM)
    {
        perror("Error: Process does not exist");
        return 1;
    }

    //retrieve the process priority
    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);

    if (priority == -1 && errno != 0)
    {
        perror("Error retrieving process priority");
        return 1;
    }

    //retrieve the scheduling policy
    int schedulingMethod = sched_getscheduler(pid);

    if (schedulingMethod == -1)
    {
        perror("Error retrieving scheduling method");
        return 1;
    }

    //print process information
    printf("Process ID: %d\n", pid);
    printf("Process Priority: %d\n", priority);

    //convert schedual into text
    printf("Scheduling Method: ");

    switch (schedulingMethod)
    {
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;

        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;

        case SCHED_RR:
            printf("SCHED_RR\n");
            break;

        case SCHED_BATCH:
            printf("SCHED_BATCH\n");
            break;

        case SCHED_IDLE:
            printf("SCHED_IDLE\n");
            break;

        default:
            printf("Unknown Scheduling Method\n");
            break;
    }

    return 0;
}