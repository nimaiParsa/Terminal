#include "MyShellFunctions.h"

// mygrep function
void mygrep(char *tokens[], size_t index, char *commandCopy)
{
    char key[MAX];
    char fileName[MAX];

    if (index == 3)
    {
        if (tokens[1][0] == '-')
        {
            errorGrep(commandCopy);
            return;
        }

        strcpy(key, tokens[1]);
        strcpy(fileName, tokens[2]);

        justGrep(key, fileName);
    }

    else if (index == 4 && tokens[1][0] == '-')
    {
        strcpy(key, tokens[2]);
        strcpy(fileName, tokens[3]);

        if (!strcmp(tokens[1], "-n"))
            printLines(key, fileName);

        else if (!strcmp(tokens[1], "-i"))
            notCaseSensi(key, fileName);

        else if (!strcmp(tokens[1], "-v"))
            invert(key, fileName);

        else if (!strcmp(tokens[1], "-c"))
            countOccur(key, fileName);
        else
        {
            errorGrep(commandCopy);
            return;
        }
    }

    else if (index > 3)
    {
        grepMany(tokens, index, commandCopy);
        return;
    }

    else
    {
        errorGrep(commandCopy);
        return;
    }
}

// displays error message
void errorGrep(char *commandCopy)
{
    printf("mygrep : '%s' is not valid\n", commandCopy);
    return;
}

// executes grep
void justGrep(char *key, char *fileName)
{
    if (isdir(fileName))
    {
        printf("mygrep : '%s' is a directory\n", fileName);
        return;
    }

    FILE *filePtr = fopen(fileName, "r");

    if (filePtr == NULL)
    {
        printf("mygrep : '%s' is not valid\n", fileName);
        return;
    }

    char line[MAX];

    while (fgets(line, MAX, filePtr))
    {
        char *wordPtr = strstr(line, key);

        if (wordPtr == NULL)
            continue;

        printf(CBLUEL);
        printf("%s:", fileName);
        printf(CDEFAULT);

        for (int i = 0; line[i] != '\n'; i++)
        {
            if (!strncmp(line + i, key, strlen(key)))
            {
                printf("%s", CREDL);
                printf("%s", key);
                printf("%s", CDEFAULT);

                i += strlen(key) - 1;
            }

            else
                printf("%c", line[i]);
        }

        puts("");
    }

    fclose(filePtr);
}

// prints the line numbers also
void printLines(char *key, char *fileName)
{
    if (isdir(fileName))
    {
        printf("mygrep : '%s' is a directory\n", fileName);
        return;
    }

    FILE *filePtr = fopen(fileName, "r");

    if (filePtr == NULL)
    {
        printf("mygrep : '%s' is not valid\n", fileName);
        return;
    }

    char line[MAX];
    size_t lineCount = 0;

    while (fgets(line, MAX, filePtr))
    {
        lineCount++;
        char *wordPtr = strstr(line, key);

        if (wordPtr == NULL)
            continue;

        printf(CBLUEL);
        printf("%s:", fileName);
        printf(CDEFAULT);

        printf("%s", CGREENL);
        printf("%lu:", lineCount);
        printf("%s", CDEFAULT);

        for (int i = 0; line[i] != '\n'; i++)
        {
            if (!strncmp(line + i, key, strlen(key)))
            {
                printf("%s", CREDL);
                printf("%s", key);
                printf("%s", CDEFAULT);

                i += strlen(key) - 1;
            }

            else
                printf("%c", line[i]);
        }

        puts("");
    }

    fclose(filePtr);
}

// counts occurences -c
void countOccur(char *key, char *fileName)
{
    if (isdir(fileName))
    {
        printf("mygrep : '%s' is a directory\n", fileName);
        return;
    }

    FILE *filePtr = fopen(fileName, "r");

    if (filePtr == NULL)
    {
        printf("mygrep : '%s' is not valid\n", fileName);
        return;
    }

    char line[MAX];
    size_t count = 0;

    while (fgets(line, MAX, filePtr))
    {
        char *wordPtr = strstr(line, key);

        if (wordPtr == NULL)
            continue;

        count++;
    }

    printf(CBLUEL);
    printf("%s:", fileName);
    printf(CDEFAULT);

    printf(CGREENL);
    printf("%lu\n", count);
    printf(CDEFAULT);

    fclose(filePtr);
}

// prints lines not containing key (-v)
void invert(char *key, char *fileName)
{
    if (isdir(fileName))
    {
        printf("mygrep : '%s' is a directory\n", fileName);
        return;
    }
    FILE *filePtr = fopen(fileName, "r");

    if (filePtr == NULL)
    {
        printf("mygrep : '%s' is not valid\n", fileName);
        return;
    }

    char line[MAX];

    while (fgets(line, MAX, filePtr))
    {
        char *wordPtr = strstr(line, key);

        if (wordPtr != NULL)
            continue;

        printf(CBLUEL);
        printf("%s:", fileName);
        printf(CDEFAULT);

        int itr = -1;
        do
        {
            itr++;
            printf("%c", line[itr]);
        } while (line[itr] != '\n');
    }

    fclose(filePtr);
}

// not case sensitive -i
void notCaseSensi(char *key, char *fileName)
{
    if (isdir(fileName))
    {
        printf("mygrep : '%s' is a directory\n", fileName);
        return;
    }

    convertLower(key);

    FILE *filePtr = fopen(fileName, "r");

    if (filePtr == NULL)
    {
        printf("mygrep : '%s' is not valid\n", fileName);
        return;
    }

    char line[MAX];

    while (fgets(line, MAX, filePtr))
    {
        char temp[MAX];
        strncpy(temp, line, MAX);
        convertLower(temp);
        char *wordPtr = strstr(temp, key);

        if (wordPtr == NULL)
            continue;

        printf(CBLUEL);
        printf("%s:", fileName);
        printf(CDEFAULT);

        for (int i = 0; line[i] != '\n'; i++)
        {
            if (!strncmp(temp + i, key, strlen(key)))
            {
                printf("%s", CREDL);
                for (int j = i; j < i + strlen(key); j++)
                    printf("%c", line[j]);
                printf("%s", CDEFAULT);

                i += strlen(key) - 1;
            }

            else
                printf("%c", line[i]);
        }

        puts("");
    }

    fclose(filePtr);
}

// search in multiple files
void grepMany(char *tokens[], size_t index, char *command)
{
    if (tokens[1][0] != '-')
    {
        for (int i = 2; i < index; i++)
            justGrep(tokens[1], tokens[i]);
        return;
    }

    else
    {
        if (!strcmp(tokens[1], "-n"))
        {
            for (int i = 3; i < index; i++)
                printLines(tokens[2], tokens[i]);
            return;
        }
        else if (!strcmp(tokens[1], "-i"))
        {
            for (int i = 3; i < index; i++)
                notCaseSensi(tokens[2], tokens[i]);
            return;
        }
        else if (!strcmp(tokens[1], "-v"))
        {
            for (int i = 3; i < index; i++)
                invert(tokens[2], tokens[i]);
            return;
        }
        else if (!strcmp(tokens[1], "-c"))
        {
            for (int i = 3; i < index; i++)
                countOccur(tokens[2], tokens[i]);
            return;
        }
        else
        {
            errorGrep(command);
            return;
        }
    }
}
