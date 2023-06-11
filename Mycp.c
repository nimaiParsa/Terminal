// change the tokens part
#include "MyShellFunctions.h"

// checks which case
void mycp(char *tokens[], size_t index, char *command)
{
    if (index <= 1)
    {
        printf("mycp : '%s' is not valid\n", command);
        return;
    }

    else if (index == 4 && tokens[1][0] == '-')
    {
        if (!strcmp(tokens[1], "-n"))
        {
            dontOverWriteExistingcp(tokens[2], tokens[3]);
            return;
        }

        else if (!strcmp(tokens[1], "-v"))
        {
            verbosecp(tokens[2], tokens[3]);
            return;
        }

        else if (!strcmp(tokens[1], "-i"))
        {
            promptOverWritecp(tokens[2], tokens[3]);
            return;
        }

        else if (!strcmp(tokens[1], "-b"))
        {
            backupcp(tokens[2], tokens[3]);
            return;
        }

        else
        {
            printf("mycp : '%s' is not valid\n", command);
            return;
        }
    }

    else if (index == 3)
    {
        copy(tokens[1], tokens[2]);
        return;
    }

    else if (index >= 4)
    {
        copyMultiple(tokens, index, command);
        return;
    }

    else
    {
        printf("mycp : '%s' is not valid\n", command);
        return;
    }
}

// to implement cp
void copy(char *file1, char *file2)
{
    // to check if file2 is a directory
    char destination[MAX];
    strcpy(destination, file2);

    // getting the file name, if a path is provided for file1
    size_t firstSlash = 0;
    for (int i = strlen(file1) - 2; i >= 0; i--)
    {
        if (file1[i] == '/')
        {
            firstSlash = i + 1;
            break;
        }
    }

    // checking if file2 is a directory
    if (isdir(file2))
    {
        strcat(destination, "/");
        strcat(destination, file1 + firstSlash);
    }

    // checking if file1 is a directory
    if (isdir(file1))
    {
        printf("mycp : SOURCE cannot be a directory\n");
        return;
    }

    // opening file1
    FILE *file1Ptr = fopen(file1, "r");
    if (file1Ptr == NULL)
    {
        printf("mycp: '%s' No such file or directory\n", file1);
        return;
    }

    // opening file2
    FILE *file2Ptr = fopen(destination, "wb");
    if (file2Ptr == NULL)
    {
        printf("mycp : cannot open '%s'\n", destination);
        fclose(file1Ptr);
        return;
    }

    // copying
    char read;
    while ((read = fgetc(file1Ptr)) != EOF)
        fputc(read, file2Ptr);

    fclose(file1Ptr);
    fclose(file2Ptr);

    // copying permissions of file1 to file2
    stats forPermissions;
    stat(file1, &forPermissions);
    mode_t mode = forPermissions.st_mode;

    chmod(destination, mode);
}

// do not overwrite
void dontOverWriteExistingcp(char *file1, char *file2)
{
    char destination[MAX];
    strcpy(destination, file2);

    size_t firstSlash = 0;
    for (int i = strlen(file1) - 2; i >= 0; i--)
    {
        if (file1[i] == '/')
        {
            firstSlash = i + 1;
            break;
        }
    }

    // checking if file2 is a directory
    if (isdir(file2))
    {
        strcat(destination, "/");
        strcat(destination, file1 + firstSlash);
    }

    // checking if destination already exists
    if (!access(destination, F_OK))
        return;

    copy(file1, destination);
}

// to implement cp -i
void promptOverWritecp(char *file1, char *file2)
{
    char destination[MAX];
    strcpy(destination, file2);

    size_t firstSlash = 0;
    for (int i = strlen(file1) - 2; i >= 0; i--)
    {
        if (file1[i] == '/')
        {
            firstSlash = i + 1;
            break;
        }
    }

    // checking if file2 is a directory
    if (isdir(file2))
    {
        strcat(destination, "/");
        strcat(destination, file1 + firstSlash);
    }

    // checking if destination already exists
    char response;
    if (!access(destination, F_OK))
    {
        printf("mycp: overwrite '%s'? ", destination);
        fflush(stdout);
        scanf("%c", &response);
    }

    else
        response = 'y';

    if (response != 'Y' && response != 'y')
        return;

    copy(file1, destination);
}

// to implement cp -v
void verbosecp(char *file1, char *file2)
{
    if (access(file1, F_OK))
    {
        printf("mycp: '%s' No such file or directory\n", file1);
        return;
    }

    char destination[MAX];
    strcpy(destination, file2);

    size_t firstSlash = 0;
    for (int i = strlen(file1) - 2; i >= 0; i--)
    {
        if (file1[i] == '/')
        {
            firstSlash = i + 1;
            break;
        }
    }

    // checking if file2 is a directory
    if (isdir(file2))
    {
        strcat(destination, "/");
        strcat(destination, file1 + firstSlash);
    }

    printf("'%s' -> '%s'\n", file1, destination);
    copy(file1, destination);
}

// to implement cp -b
void backupcp(char *file1, char *file2)
{
    // checking if file1 is a directory
    if (isdir(file1))
    {
        printf("mycp : SOURCE cannot be a directory\n");
        return;
    }

    char destination[MAX];
    strcpy(destination, file2);

    size_t firstSlash = 0;
    for (int i = strlen(file1) - 2; i >= 0; i--)
    {
        if (file1[i] == '/')
        {
            firstSlash = i + 1;
            break;
        }
    }
    // checking if file2 is a directory
    if (isdir(file2))
    {
        strcat(destination, "/");
        strcat(destination, file1 + firstSlash);
    }

    if (access(destination, F_OK))
    {
        copy(file1, destination);
        return;
    }

    char backUp[MAX];
    strcpy(backUp, destination);
    strcat(backUp, "~");

    copy(destination, backUp);
    copy(file1, destination);
}

// copies multiple files
void copyMultiple(char *tokens[], size_t index, char *command)
{
    // if last entry is not a directory
    if (!isdir(tokens[index - 1]))
    {
        puts("mycp : Last Entry must be a directory!");
        return;
    }

    if (tokens[1][0] != '-')
    {
        char dirName[MAX];
        strcpy(dirName, tokens[index - 1]);
        for (int i = 1; i < index - 1; i++)
            copy(tokens[i], dirName);
        return;
    }

    if (!strcmp(tokens[1], "-n"))
    {
        char dirName[MAX];
        strcpy(dirName, tokens[index - 1]);
        for (int i = 2; i < index - 1; i++)
            dontOverWriteExistingcp(tokens[i], dirName);
        return;
    }

    else if (!strcmp(tokens[1], "-v"))
    {
        char dirName[MAX];
        strcpy(dirName, tokens[index - 1]);
        for (int i = 2; i < index - 1; i++)
            verbosecp(tokens[i], dirName);
        return;
    }

    else if (!strcmp(tokens[1], "-b"))
    {
        char dirName[MAX];
        strcpy(dirName, tokens[index - 1]);
        for (int i = 2; i < index - 1; i++)
            backupcp(tokens[i], dirName);
        return;
    }

    else
    {
        printf("mycp : '%s' doesn't exist", command);
        return;
    }
}
