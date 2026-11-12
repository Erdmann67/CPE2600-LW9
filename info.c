/*
 * Name: Nick Erdmann
 * Date: 11/10/26
 * File: info.c
 * Retrieves and displays information about the system
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/sysinfo.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    struct timespec currentTime;
    struct utsname systemInfo;
    struct sysinfo memoryInfo;

    char hostname[256];

    //current time
    if (clock_gettime(CLOCK_REALTIME, &currentTime) == 0)
    {
        unsigned long long nanoseconds =
            (unsigned long long)currentTime.tv_sec * 1000000000ULL
            + currentTime.tv_nsec;

        printf("Current Time (nanoseconds): %llu\n", nanoseconds);
    }

    //hostname
    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        if (hostname[0] != '\0')
        {
            printf("Network Name: %s\n", hostname);
        }
    }

    //system info
    if (uname(&systemInfo) == 0)
    {
        if (systemInfo.sysname[0] != '\0')
            printf("Operating System: %s\n", systemInfo.sysname);

        if (systemInfo.release[0] != '\0')
            printf("OS Release: %s\n", systemInfo.release);

        if (systemInfo.version[0] != '\0')
            printf("OS Version: %s\n", systemInfo.version);

        if (systemInfo.machine[0] != '\0')
            printf("Hardware Type: %s\n", systemInfo.machine);
    }

    //available processors
    int cpuCount = get_nprocs();

    if (cpuCount > 0)
    {
        printf("Number of CPUs: %d\n", cpuCount);
    }

    //total mem
    long totalPages = sysconf(_SC_PHYS_PAGES);
    long pageSize = getpagesize();

    if (totalPages > 0 && pageSize > 0)
    {
        unsigned long long totalMemory =
            (unsigned long long)totalPages * pageSize;

        printf("Total Physical Memory: %llu bytes\n", totalMemory);
    }

    //free mem
    if (sysinfo(&memoryInfo) == 0)
    {
        unsigned long long freeMemory =
            (unsigned long long)memoryInfo.freeram * memoryInfo.mem_unit;

        printf("Free Physical Memory: %llu bytes\n", freeMemory);
    }

    return 0;
}