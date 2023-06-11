#include "MyShellFunctions.h"

// function to get the prompt
void getPrompt(char *prompt)
{
    // getting hostName
    char hostName[MAX];
    gethostname(hostName, MAX);

    // getting loginName
    char *loginName = getlogin();

    // changing textcolor and making the prompt
    strcpy(prompt, CGREENL);
    strcat(prompt, loginName);
    strcat(prompt, "@");
    strcat(prompt, hostName);
    strcat(prompt, CWHITEL);
    strcat(prompt, ":");
    strcat(prompt, CBLUEL);

    // getting the working directory
    char *workingDirectory = (char *)malloc(MAX * sizeof(char));

    if (workingDirectory != NULL)
        getcwd(workingDirectory, MAX);

    strcat(prompt, workingDirectory);

    // changing textcolor and making the propmt
    strcat(prompt, CDEFAULT);
    strcat(prompt, "$ ");
}

// function to show the help page
void showHelp(char *path)
{
    char helpPage[MAX];
    sprintf(helpPage, "cat %s/help", path);
    system(helpPage);
}

// function to get the man page
void getManPage(char *tokens[], size_t index, char *command, char *path)
{
    if (index == 1)
    {
        puts("What manual page do you want?\nFor example, try 'man man'.");
        return;
    }

    if (!strcmp(tokens[1], "myls"))
    {
        char manFile[MAX];
        sprintf(manFile, "cat %s/man_ls", path);
        system(manFile);
        return;
    }
    else if (!strcmp(tokens[1], "mymv"))
    {
        char manFile[MAX];
        sprintf(manFile, "cat %s/man_mv", path);
        system(manFile);
        return;
    }
    else if (!strcmp(tokens[1], "mygrep"))
    {
        char manFile[MAX];
        sprintf(manFile, "cat %s/man_grep", path);
        system(manFile);
        return;
    }
    else if (!strcmp(tokens[1], "mycp"))
    {
        char manFile[MAX];
        sprintf(manFile, "cat %s/man_cp", path);
        system(manFile);
        return;
    }
    else if (!strcmp(tokens[1], "myps"))
    {
        char manFile[MAX];
        sprintf(manFile, "cat %s/man_ps", path);
        system(manFile);
        return;
    }
    else
    {
        system(command);
        return;
    }
}

// function to change directory
void changeDir(char *tokens[], size_t index, char *command)
{
    if (index == 1)
    {
        char path[MAX];
        sprintf(path, "/home/%s", getlogin());
        if (chdir(path))
        {
            printf("cd : couldn't change directory\n");
            return;
        }

        return;
    }

    else if (index == 2)
    {
        if (chdir(tokens[1]))
        {
            printf("cd : couldn't change directory\n");
            return;
        }
        return;
    }
}

// function to check if fileName is a directory
int isdir(char *fileName)
{
    stats dirCheck;
    if (!stat(fileName, &dirCheck))
    {
        if (S_ISDIR(dirCheck.st_mode))
            return 1;
    }
    return 0;
}

// converts string to lower case
void convertLower(char *word)
{
    int i = 0;
    while (word[i] != '\0')
    {
        word[i] = tolower(word[i]);
        i++;
    }
}