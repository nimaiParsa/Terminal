
#include "MyShellFunctions.h"

// mymv function
void mymv(char *tokens[], size_t index, char *commandCopy)
{
    if (index == 3)
    {
        renameFile(tokens[1], tokens[2]);
        return;
    }

    else if (index == 4 && tokens[1][0] == '-')
    {
        if (!strcmp(tokens[1], "-n"))
        {
            doNotOverWrite(tokens[2], tokens[3]);
            return;
        }
        else if (!strcmp(tokens[1], "-i"))
        {
            promptOverWrite(tokens[2], tokens[3]);
            return;
        }
        else if (!strcmp(tokens[1], "-v"))
        {
            verbose(tokens[2], tokens[3]);
            return;
        }
        else if (!strcmp(tokens[1], "-b"))
        {
            backup(tokens[2], tokens[3]);
            return;
        }
        else
        {
            printf("mymv : Command '%s' is not valid\n", commandCopy);
            return;
        }
    }

    else if (index > 3)
    {
        renameMany(tokens, index, commandCopy);
        return;
    }

    else
    {
        printf("mymv : Command '%s' is not valid\n", commandCopy);
        return;
    }
}

// function to rename files
void renameFile(char *file1, char *file2)
{
    // finding the destination
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

    if (rename(file1, destination))
        printf("mymv : couldn't move %s\n", file1);
}

// to implement -n
void doNotOverWrite(char *file1, char *file2)
{
    // finding the destination
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

    if (isdir(file2))
    {
        strcat(destination, "/");
        strcat(destination, file1 + firstSlash);
    }

    if (!access(destination, F_OK))
        return;

    renameFile(file1, destination);
}

// to implement cp -i
void promptOverWrite(char *file1, char *file2)
{
    // finding the destination
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

    if (isdir(file2))
    {
        strcat(destination, "/");
        strcat(destination, file1 + firstSlash);
    }

    char response;
    if (!access(file2, F_OK))
    {
        printf("mymv: overwrite '%s'? ", file2);
        scanf("%c", &response);

        if (response != 'Y' && response != 'y')
            return;

        renameFile(file1, file2);
    }

    else
        renameFile(file1, file2);
}

// to implement -v
void verbose(char *file1, char *file2)
{
    // finding the destination
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

    //checking if file2 is a directory
    if (isdir(file2))
    {
        strcat(destination, "/");
        strcat(destination, file1 + firstSlash);
    }

    if (rename(file1, destination))
    {
        printf("mymv : couldnt move '%s'\n", file1);
        return;
    }
    printf("'%s' -> '%s'\n", file1, destination);
}

// to implement cp -b
void backup(char *file1, char *file2)
{
    // finding the destination
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

    // checking if file1 and file2 are directories
    if (isdir(file2))
    {
        strcat(destination, "/");
        strcat(destination, file1 + firstSlash);
    }

    if (isdir(file1))
    {
        printf("mymv : SOURCE cannot be a directory\n");
        return;
    }

    if (access(destination, F_OK))
    {
        renameFile(file1, destination);
        return;
    }

    char backUp[MAX];
    strcpy(backUp, destination);
    strcat(backUp, "~");

    FILE *backUpPtr = fopen(backUp, "wb");
    FILE *f2Ptr = fopen(destination, "r");

    char read;
    while ((read = fgetc(f2Ptr)) != EOF)
        fputc(read, backUpPtr);

    fclose(backUpPtr);
    fclose(f2Ptr);

    renameFile(file1, destination);
}

// to implement moving many files into a directory
void renameMany(char *tokens[], size_t index, char *command)
{
    // if last entry is directory
    if (!isdir(tokens[index - 1]))
    {
        puts("mymv : Last Entry must be a directory!");
        return;
    }

    if (tokens[1][0] != '-')
    {
        char dirName[MAX];
        strcpy(dirName, tokens[index - 1]);
        for (int i = 1; i < index - 1; i++)
            renameFile(tokens[i], dirName);
        return;
    }

    else if (!strcmp(tokens[1], "-n"))
    {
        char dirName[MAX];
        strcpy(dirName, tokens[index - 1]);
        for (int i = 2; i < index - 1; i++)
            doNotOverWrite(tokens[i], dirName);
        return;
    }

    else if (!strcmp(tokens[1], "-v"))
    {
        char dirName[MAX];
        strcpy(dirName, tokens[index - 1]);
        for (int i = 2; i < index - 1; i++)
            verbose(tokens[i], dirName);
        return;
    }

    else if (!strcmp(tokens[1], "-b"))
    {
        char dirName[MAX];
        strcpy(dirName, tokens[index - 1]);
        for (int i = 2; i < index - 1; i++)
            backup(tokens[i], dirName);
        return;
    }

    else
    {
        printf("mymv : Command '%s' is not valid\n", command);
        return;
    }
}
