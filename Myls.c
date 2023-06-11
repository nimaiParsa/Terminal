/*
 *   CS1023 Assignment Q2    *Main file*
 *   author : Nimai Parsa
 */

#include "MyShellFunctions.h"
#define COLUMNS 10

// struct used to store the data
typedef struct full
{
    char name[MAX];
    stats attributes;
} fullStats;

// array of struct used to store the data and size of the array
fullStats allEntries[MAX];
size_t size = 0;

// myls function
void myls(char *tokens[], size_t index, char *command)
{
    // extracting entries
    if (index == 2)
    {
        if (tokens[1][0] != '-')
        {
            if (extractEntries(tokens[1]))
                return;
        }

        else
        {
            if (extractEntries("."))
                return;
        }
    }

    else if (index == 3)
    {
        if (extractEntries(tokens[2]))
            return;
    }

    if (index == 1)
    {
        extractEntries(".");
        ls();
        return;
    }

    else if (index == 2 || index == 3)
    {
        if (!strcmp(tokens[1], "-l") && index == 2)
        {
            printList();
            return;
        }

        else if (!strcmp(tokens[1], "-a"))
        {
            printAllData();
            return;
        }

        else if (!strcmp(tokens[1], "-S") && index == 2)
        {
            sizeSort();
            return;
        }

        else if (!strcmp(tokens[1], "-g") && index == 2)
        {
            printListNoOwner();
            return;
        }

        else if (!strcmp(tokens[1], "-U"))
        {
            printData();
            return;
        }

        else if (!strcmp(tokens[1], "-1"))
        {
            printInNewLine();
            return;
        }

        else if (index == 2)
        {
            ls();
            return;
        }

        else
        {
            printf("myls : command '%s' doesn't exist\n", command);
            return;
        }
    }

    else
    {
        printf("myls : command '%s' doesn't exist\n", command);
        return;
    }
}

// get all the entries
int extractEntries(char *path)
{
    // opening the directory
    DIR *directory = opendir(path);
    if (directory == NULL)
    {
        printf("myls : cannot open '%s'\n", path);
        return 1;
    }

    // reading the directory
    dirent *entry = readdir(directory);
    int index = 0;

    while (entry != NULL)
    {
        strcpy(allEntries[index].name, entry->d_name);
        stat(entry->d_name, &allEntries[index++].attributes);

        entry = readdir(directory);
    }

    closedir(directory);
    size = index;

    return 0;
}

// function to print the total blocks
void getBlocks()
{
    // printing the number of blocks
    size_t totalBlocks = 0;

    for (int i = 0; i < size; i++)
        if (allEntries[i].name[0] != '.')
            totalBlocks += allEntries[i].attributes.st_blocks;

    printf("total %ld\n", totalBlocks / 2);
}

// function to print names of files ignoring files starting with '.'
// function to implement ls -U
void printData()
{
    for (int i = 0; i < size; i++)
    {
        if (allEntries[i].name[0] != '.')
            printf("%s%s", allEntries[i].name, (i % COLUMNS) ? "  " : "\n");
    }
    puts("");
}

// function to sort the data in alphabetical order of name
void alphaSort()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            char string1[MAX];
            char string2[MAX];

            strcpy(string1, allEntries[i].name);
            strcpy(string2, allEntries[j].name);

            convertLower(string1);
            convertLower(string2);

            if (strcmp(string1, string2) > 0)
            {
                fullStats temp = allEntries[i];
                allEntries[i] = allEntries[j];
                allEntries[j] = temp;
            }
        }
    }
}

// function to implement ls -S
void sizeSort()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (allEntries[i].attributes.st_size < allEntries[j].attributes.st_size)
            {
                fullStats temp = allEntries[i];
                allEntries[i] = allEntries[j];
                allEntries[j] = temp;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (allEntries[i].name[0] == '.')
            continue;

        printf("%s ", allEntries[i].name);
    }
    puts("");
}

// function to implement ls -a
void printAllData()
{
    alphaSort();
    for (int i = 0; i < size; i++)
        printf("%s%s", allEntries[i].name, (i % COLUMNS) ? "  " : "\n");
    puts("");
}

// function to implement ls
void ls()
{
    alphaSort();
    printData();
}

// function to convert permission from binary to rwx format
void printPermission(mode_t mode)
{
    // type of file, user, group, others
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");

    printf(" ");
}

// function that prints the user name
void printUser(uid_t uid)
{
    struct passwd *pwsPtr;
    pwsPtr = getpwuid(uid);

    if (pwsPtr != NULL)
        printf("%s ", pwsPtr->pw_name);
    else
        puts("ERROR!");
}

// function that prints the group name
void printGroup(gid_t gid)
{
    struct group *gPtr;
    gPtr = getgrgid(gid);

    if (gPtr != NULL)
        printf("%s ", gPtr->gr_name);
    else
        puts("ERROR!");
}

// print last access time
void printLastTime(time_t time)
{
    char buf[MAX];

    struct tm forTime;
    forTime = *localtime(&time);

    strftime(buf, sizeof(buf), "%b %d %H:%M", &forTime);

    printf("%s ", buf);
}

// function to implement ls -l
void printList()
{
    alphaSort();
    getBlocks();

    for (int i = 0; i < size; i++)
    {
        if (allEntries[i].name[0] == '.')
            continue;

        // printing the permissions in rwx format
        printPermission(allEntries[i].attributes.st_mode);

        // printing the number of links
        printf("%2lu ", allEntries[i].attributes.st_nlink);

        // printing the user
        printUser(allEntries[i].attributes.st_uid);

        // printing the group name
        printGroup(allEntries[i].attributes.st_gid);

        // printing the size of the file
        printf("%8lu ", allEntries[i].attributes.st_size);

        // printing the date of creation
        printLastTime(allEntries[i].attributes.st_mtime);

        // printing the name of the file
        printf("%s ", allEntries[i].name);

        // newline
        puts("");
    }
}

// function to implement ls -g
void printListNoOwner()
{
    alphaSort();
    getBlocks();

    for (int i = 0; i < size; i++)
    {
        if (allEntries[i].name[0] == '.')
            continue;

        // printing the permissions in rwx format
        printPermission(allEntries[i].attributes.st_mode);

        // printing the number of links
        printf("%lu ", allEntries[i].attributes.st_nlink);

        // printing the group name
        printGroup(allEntries[i].attributes.st_gid);

        // printing the size of the file
        printf("%5lu ", allEntries[i].attributes.st_size);

        // printing the date of creation
        printLastTime(allEntries[i].attributes.st_atime);

        // printing the name of the file
        printf("%s ", allEntries[i].name);

        // newline
        puts("");
    }
}

// function to implement ls -1
void printInNewLine()
{
    alphaSort();
    for (int i = 0; i < size; i++)
    {
        if (allEntries[i].name[0] != '.')
            printf("%s\n", allEntries[i].name);
    }
}
