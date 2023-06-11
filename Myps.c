#include "MyShellFunctions.h"

// figures out the command
void myps(char *tokens[], size_t index, char *command)
{
    if (index == 1)
    {
        psExecute();
        return;
    }

    else if (index == 2)
    {
        if (!strcmp(tokens[1], "-e") || !strcmp(tokens[1], "-A"))
        {
            allprocess();
            return;
        }
        else if (!strcmp(tokens[1], "-d"))
        {
            skipSessionHead();
            return;
        }
        else if (!strcmp(tokens[1], "-a"))
        {
            skipSessAndNull();
            return;
        }
        else if (!strcmp(tokens[1], "-j"))
        {
            showMore();
            return;
        }
        else if (!strcmp(tokens[1], "-ej"))
        {
            allProcessMoreInfo();
            return;
        }
        else
        {
            printf("myps : '%s' doesn't exist\n", command);
            return;
        }
    }

    else
    {
        printf("myps : '%s' doesn't exist\n", command);
        return;
    }
}

// executes ps
void psExecute()
{
    // getting the tty of self process
    const char *selfTty = ttyname(STDIN_FILENO);
    char selfTtyCopy[MAX];
    if (selfTty == NULL)
    {
        puts("myps : cannot access self TTY");
        return;
    }

    // making a copy of selftty
    strcpy(selfTtyCopy, selfTty);

    // opening the proc directory
    DIR *procPtr = opendir("/proc");
    if (procPtr == NULL)
    {
        puts("myps : entry denied to proc directory");
        return;
    }

    // to read the proc directory
    dirent *directEntry;

    // heading
    printf("%8s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");

    // reading the proc directory
    while ((directEntry = readdir(procPtr)) != NULL)
    {
        // if the file is not a process id
        if (!checkString(directEntry->d_name))
            continue;

        // getting the tty of this process
        char tty[MAX];
        giveTTY(directEntry->d_name, tty);
        if (strcmp(tty, selfTtyCopy))
            continue;

        // stores the data related to the process
        pInfo relatedData;

        if (extractPInfo(directEntry->d_name, &relatedData))
            return;

        // print the data
        printf("%8d %s\t", relatedData.pid, tty + 5);
        // convert utime stime to cpu time
        printTimeps((double)(relatedData.utime + relatedData.stime) / sysconf(_SC_CLK_TCK));
        relatedData.comm[strlen(relatedData.comm) - 1] = '\0';
        printf(" %s\n", relatedData.comm + 1);
    }

    closedir(procPtr);
}

// executes ps -e
void allprocess()
{
    // getting the tty of self process
    const char *selfTty = ttyname(STDIN_FILENO);
    char selfTtyCopy[MAX];
    if (selfTty == NULL)
    {
        puts("myps : cannot access self TTY");
        return;
    }

    // making a copy of selftty
    strcpy(selfTtyCopy, selfTty);

    // opening the proc directory
    DIR *procPtr = opendir("/proc");
    if (procPtr == NULL)
    {
        puts("myps : entry denied to proc directory");
        return;
    }

    // to read the proc directory
    dirent *directEntry;

    // heading
    printf("%8s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");

    // reading the proc directory
    while ((directEntry = readdir(procPtr)) != NULL)
    {
        // if the file is not a process id
        if (!checkString(directEntry->d_name))
            continue;

        // getting the tty of this process
        char tty[MAX];
        giveTTY(directEntry->d_name, tty);

        // stores the data related to the process
        pInfo relatedData;

        if (extractPInfo(directEntry->d_name, &relatedData))
            return;

        // print the data
        printf("%8d %s\t", relatedData.pid, tty + 5);
        // convert utime stime to cpu time
        printTimeps((double)(relatedData.utime + relatedData.stime) / sysconf(_SC_CLK_TCK));
        relatedData.comm[strlen(relatedData.comm) - 1] = '\0';
        printf(" %s\n", relatedData.comm + 1);
    }

    closedir(procPtr);
}

// to implement ps -d
void skipSessionHead()
{
    // getting the tty of self process
    const char *selfTty = ttyname(STDIN_FILENO);
    char selfTtyCopy[MAX];
    if (selfTty == NULL)
    {
        puts("myps : cannot access self TTY");
        return;
    }

    // making a copy of selftty
    strcpy(selfTtyCopy, selfTty);

    // opening the proc directory
    DIR *procPtr = opendir("/proc");
    if (procPtr == NULL)
    {
        puts("myps : entry denied to proc directory");
        return;
    }

    // to read the proc directory
    dirent *directEntry;

    // heading
    printf("%8s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");

    // reading the proc directory
    while ((directEntry = readdir(procPtr)) != NULL)
    {
        // if the file is not a process id
        if (!checkString(directEntry->d_name))
            continue;

        // getting the tty of this process
        char tty[MAX];
        giveTTY(directEntry->d_name, tty);

        // stores the data related to the process
        pInfo relatedData;

        if (extractPInfo(directEntry->d_name, &relatedData))
            return;

        // print the data
        printf("%8d %s\t", relatedData.pid, tty + 5);
        // convert utime stime to cpu time
        printTimeps((double)(relatedData.utime + relatedData.stime) / sysconf(_SC_CLK_TCK));
        relatedData.comm[strlen(relatedData.comm) - 1] = '\0';
        printf(" %s\n", relatedData.comm + 1);
    }

    closedir(procPtr);
}

// to implement ps -a
void skipSessAndNull()
{
    // getting the tty of self process
    const char *selfTty = ttyname(STDIN_FILENO);
    char selfTtyCopy[MAX];
    if (selfTty == NULL)
    {
        puts("myps : cannot access self TTY");
        return;
    }

    // making a copy of selftty
    strcpy(selfTtyCopy, selfTty);

    // opening the proc directory
    DIR *procPtr = opendir("/proc");
    if (procPtr == NULL)
    {
        puts("myps : entry denied to proc directory");
        return;
    }

    // to read the proc directory
    dirent *directEntry;

    // heading
    printf("%8s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");

    // reading the proc directory
    while ((directEntry = readdir(procPtr)) != NULL)
    {
        // if the file is not a process id
        if (!checkString(directEntry->d_name))
            continue;

        // getting the tty of this process
        char tty[MAX];
        giveTTY(directEntry->d_name, tty);
        if (!strcmp(tty, "??????"))
            continue;

        // stores the data related to the process
        pInfo relatedData;

        if (extractPInfo(directEntry->d_name, &relatedData))
            return;
        // print the data
        printf("%8d %s\t", relatedData.pid, tty + 5);
        // convert utime stime to cpu time
        printTimeps((double)(relatedData.utime + relatedData.stime) / sysconf(_SC_CLK_TCK));
        relatedData.comm[strlen(relatedData.comm) - 1] = '\0';
        printf(" %s\n", relatedData.comm + 1);
    }

    closedir(procPtr);
}

// to implement ps -j
void showMore()
{
    // getting the tty of self process
    const char *selfTty = ttyname(STDIN_FILENO);
    char selfTtyCopy[MAX];
    if (selfTty == NULL)
    {
        puts("myps : cannot access self TTY");
        return;
    }

    // making a copy of selftty
    strcpy(selfTtyCopy, selfTty);

    // opening the proc directory
    DIR *procPtr = opendir("/proc");
    if (procPtr == NULL)
    {
        puts("myps : entry denied to proc directory");
        return;
    }

    // to read the proc directory
    dirent *directEntry;

    // heading
    printf("%8s\t%8s\t%8s %s\t\t%8s %s\n", "PID", "PGID", "SID", "TTY", "TIME", "CMD");

    // reading the proc directory
    while ((directEntry = readdir(procPtr)) != NULL)
    {
        // if the file is not a process id
        if (!checkString(directEntry->d_name))
            continue;

        // getting the tty of this process
        char tty[MAX];
        giveTTY(directEntry->d_name, tty);
        if (strcmp(tty, selfTtyCopy))
            continue;

        // stores the data related to the process
        pInfo relatedData;

        if (extractPInfo(directEntry->d_name, &relatedData))
            return;

        // print the data
        printf("%8d\t%8d\t%8d %s\t\t", relatedData.pid, relatedData.pgid, relatedData.sid, tty + 5);
        // convert utime stime to cpu time
        printTimeps((double)(relatedData.utime + relatedData.stime) / sysconf(_SC_CLK_TCK));
        relatedData.comm[strlen(relatedData.comm) - 1] = '\0';
        printf(" %s\n", relatedData.comm + 1);
    }

    closedir(procPtr);
}

// to implement ps -ej
void allProcessMoreInfo()
{
    // getting the tty of self process
    const char *selfTty = ttyname(STDIN_FILENO);
    char selfTtyCopy[MAX];
    if (selfTty == NULL)
    {
        puts("myps : cannot access self TTY");
        return;
    }

    // making a copy of selftty
    strcpy(selfTtyCopy, selfTty);

    // opening the proc directory
    DIR *procPtr = opendir("/proc");
    if (procPtr == NULL)
    {
        puts("myps : entry denied to proc directory");
        return;
    }

    // to read the proc directory
    dirent *directEntry;

    // heading
    printf("%8s\t%8s\t%8s %s\t\t%8s %s\n", "PID", "PGID", "SID", "TTY", "TIME", "CMD");

    // reading the proc directory
    while ((directEntry = readdir(procPtr)) != NULL)
    {
        // if the file is not a process id
        if (!checkString(directEntry->d_name))
            continue;

        // getting the tty of this process
        char tty[MAX];
        giveTTY(directEntry->d_name, tty);
    
        // stores the data related to the process
        pInfo relatedData;

        if (extractPInfo(directEntry->d_name, &relatedData))
            return;

        // print the data
        printf("%8d\t%8d\t%8d %s\t\t", relatedData.pid, relatedData.pgid, relatedData.sid, tty + 5);
        // convert utime stime to cpu time
        printTimeps((double)(relatedData.utime + relatedData.stime) / sysconf(_SC_CLK_TCK));
        relatedData.comm[strlen(relatedData.comm) - 1] = '\0';
        printf(" %s\n", relatedData.comm + 1);
    }

    closedir(procPtr);
}

// prints time in H:M:S format
void printTimeps(time_t time)
{
    time_t sec, min, hour;
    sec = time % 60;
    min = (time / 60) % 60;
    hour = (time / 3600) % 3600;

    printf("%02lu:%02lu:%02lu", hour, min, sec);
}

// gives the tty of process name
void giveTTY(char *name, char tty[])
{
    char path[MAX];
    sprintf(path, "/proc/%s/fd/0", name);

    int temp = open(path, O_RDONLY);
    char *tempTTY = ttyname(temp);
    if (tempTTY != NULL)
        strcpy(tty, tempTTY);
    else
        strcpy(tty, "??????");

    close(temp);
}

// checks if a string is a valid number
bool checkString(char *string)
{
    int i = 0;
    while (string[i] != '\0' && string[i] != '\n')
    {
        if (string[i] < '0' || string[i] > '9')
            return false;
        i++;
    }

    return true;
}

// extracts process info of name
int extractPInfo(char *name, pInfo *relatedData)
{
    // path of stat file
    char statPath[MAX];
    sprintf(statPath, "/proc/%s/stat", name);

    // reading the stat file
    FILE *statPtr = fopen(statPath, "r");
    if (statPtr == NULL)
    {
        puts("myps : permission denied");
        fclose(statPtr);
        return 1;
    }

    // extracting the data
    fscanf(statPtr, "%d %s %*s %d %d %d", &relatedData->pid, relatedData->comm, &relatedData->ppid, &relatedData->pgid, &relatedData->sid);
    for (int i = 0; i < 6; i++)
        fscanf(statPtr, "%*s");
    fscanf(statPtr, "%ld %ld", &relatedData->utime, &relatedData->stime);

    for (int i = 0; i < 8; i++)
        fscanf(statPtr, "%*s");

    fscanf(statPtr, "%ld", &relatedData->rss);

    for (int i = 0; i < 14; i++)
        fscanf(statPtr, "%*s");

    fscanf(statPtr, "%ld", &relatedData->psr);
    fclose(statPtr);

    return 0;
}