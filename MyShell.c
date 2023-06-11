/*
 *   CS1023 Assignment 1     *main file*
 *   author : Nimai Parsa
 */

#include "MyShellFunctions.h"

// a string that stores our command
char *command;

// our prompt
char prompt[MAX];

// stores the intial path
char initialPath[MAX];

int main()
{
    printf("\t\t\tMY SHELL\n");
    puts("********************************************************************");

    // getting the intial path
    getcwd(initialPath, MAX);

    while (true)
    {
        // getting the prompt
        getPrompt(prompt);

        // input of the command
        command = readline(prompt);
        if (strlen(command) > 0)
            add_history(command);

        // making a copy of old command
        char commandCopy[MAX];
        if (MAX >= strlen(command))
            strcpy(commandCopy, command);

        else
        {
            puts("Command too big!");
            continue;
        }

        // parsing the input
        // delimiters for parsing
        char *tokens[MAX];
        char delim[] = " \"\n";

        size_t index = 0;
        if (strtok(commandCopy, delim) == NULL)
            continue;
        strcpy(commandCopy, command);

        tokens[index++] = strtok(commandCopy, delim);

        // tokenizing the input
        while ((tokens[index] = strtok(NULL, delim)) != NULL && index < MAX)
            index++;

        // myls
        if (!strcmp(tokens[0], "myls"))
        {
            myls(tokens, index, command);
            continue;
        }

        // mymv
        else if (!strcmp(tokens[0], "mymv"))
        {
            mymv(tokens, index, command);
            continue;
        }

        // mycp
        else if (!strcmp(tokens[0], "mycp"))
        {
            mycp(tokens, index, command);
            continue;
        }

        // mygrep
        else if (!strcmp(tokens[0], "mygrep"))
        {
            mygrep(tokens, index, command);
            continue;
        }

        // myps
        else if (!strcmp(tokens[0], "myps"))
        {
            myps(tokens, index, command);
            continue;
        }

        // man page
        else if (!strcmp(tokens[0], "man"))
        {
            getManPage(tokens, index, command, initialPath);
            continue;
        }

        // change directory
        else if (!strcmp(tokens[0], "cd"))
        {
            changeDir(tokens, index, command);
            continue;
        }

        // exit / quit
        else if (index == 1 && (!strcmp(tokens[0], "exit") || !strcmp(tokens[0], "quit") || !strcmp(tokens[0], "q")))
            break;

        // help page
        else if (index == 1 && !strcmp(tokens[0], "help"))
        {
            showHelp(initialPath);
            continue;
        }

        // execute command
        system(command);
    }

    printf("\t\t\tEXITING...\n");

    return EXIT_SUCCESS;
}
