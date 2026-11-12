/*
 * Name: Nick Erdmann
 * Date: 11/10/26
 * File: finfo.c
 * Retrieves and displays information about the file
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    struct stat fileInfo;

    //check filename was provided
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./finfo <filename>\n");
        return 1;
    }

    //retrieve file information
    if (lstat(argv[1], &fileInfo) == -1)
    {
        perror("Error retrieving file information");
        return 1;
    }

    //display filename
    printf("File Name: %s\n", argv[1]);

    //determine and print file type
    printf("File Type: ");

    if (S_ISREG(fileInfo.st_mode))
        printf("Regular File\n");

    else if (S_ISDIR(fileInfo.st_mode))
        printf("Directory\n");

    else if (S_ISLNK(fileInfo.st_mode))
        printf("Symbolic Link\n");

    else if (S_ISCHR(fileInfo.st_mode))
        printf("Character Device\n");

    else if (S_ISBLK(fileInfo.st_mode))
        printf("Block Device\n");

    else if (S_ISFIFO(fileInfo.st_mode))
        printf("FIFO/Pipe\n");

    else if (S_ISSOCK(fileInfo.st_mode))
        printf("Socket\n");

    else
        printf("Unknown File Type\n");

    //display file permissions
    printf("Permissions: ");

    printf("%c", (fileInfo.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (fileInfo.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (fileInfo.st_mode & S_IXUSR) ? 'x' : '-');

    printf("%c", (fileInfo.st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (fileInfo.st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (fileInfo.st_mode & S_IXGRP) ? 'x' : '-');

    printf("%c", (fileInfo.st_mode & S_IROTH) ? 'r' : '-');
    printf("%c", (fileInfo.st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c\n", (fileInfo.st_mode & S_IXOTH) ? 'x' : '-');

    //display the numeric owner ID
    printf("Owner UID: %u\n", (unsigned int)fileInfo.st_uid);

    //display file size in bytes
    printf("File Size: %lld bytes\n", (long long)fileInfo.st_size);

    //convert modification time into readable format
    char timeString[100];

    struct tm *modificationTime = localtime(&fileInfo.st_mtime);

    if (modificationTime != NULL)
    {
        if (strftime(timeString, sizeof(timeString),
                     "%Y-%m-%d %H:%M:%S", modificationTime) > 0)
        {
            printf("Last Modified: %s\n", timeString);
        }
        else
        {
            fprintf(stderr, "Error formatting modification time.\n");
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Error retrieving modification time.\n");
        return 1;
    }

    return 0;
}