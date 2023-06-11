/*
 *   CS1023 Assignment 1    *Header file*
 *   author : Nimai Parsa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <pwd.h>
#include <grp.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ncurses.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>

#define MAX 1024
#define CWHITEL "\001\033[37;1m\002"
#define CGREENL "\001\033[32;1m\002"
#define CBLUEL "\001\033[34;1m\002"
#define CREDL "\001\033[31;1m\002"
#define CYELLOWL "\001\033[33;1m\002"
#define CDEFAULT "\001\033[0m\002"

#define stats struct stat
#define dirent struct dirent

// data required for myps
typedef struct processInfo
{
    char cmd[MAX];
    char comm[MAX];

    int tty;
    pid_t pid;
    pid_t sid;
    pid_t ppid;
    pid_t pgid;
    time_t utime;
    time_t stime;
    long rss;
    long psr;

} pInfo;

// MyShell Utilities
void getPrompt(char *); // function to get the prompt

void getManPage(char **, size_t, char *, char *); // to get the man page

void showHelp(char *); // to get the help page

void changeDir(char **, size_t, char *); // function to change the directory

int isdir(char *); // checks if the file is a directory

void convertLower(char *); // to convert string to lowercase

// mycp

void mycp(char **, size_t, char *); // to check which case

void copyMultiple(char **, size_t, char *); // to copy multiple files

void copy(char *, char *); // to implement cp

void dontOverWriteExistingcp(char *, char *); // to implement cp -n

void promptOverWritecp(char *, char *); // to implement cp -i

void verbosecp(char *, char *); // to implement cp -v

void backupcp(char *, char *); // to implement cp -b

// myps

void myps(char **, size_t, char *); // figures out the command

void printTimeps(time_t); // formats the time

void giveTTY(char *, char *); // get the tty of the given pid

void psExecute(); // implements ps

void allprocess(); // to implement ps -e

void skipSessionHead(); // to implement ps -d

void skipSessAndNull(); // to implement ps -a

void showMore(); // to implement ps -j

void allProcessMoreInfo(); // to implement -ej

int extractPInfo(char *, pInfo *); // to get the data

bool checkString(char *); // checks if a string is a valid number

// mygrep

void mygrep(char **, size_t, char *); // grep function

void errorGrep(char *); // prints error message

void justGrep(char *, char *); // to implement grep with no options

void countOccur(char *, char *); // counts occurences -c

void invert(char *, char *); // prints lines not containing key -v

void notCaseSensi(char *, char *); // not case sensitive -i

void printLines(char *, char *); // prints lines numbers -n

void grepMany(char **, size_t, char *); // to search in many files

// mymv

void mymv(char **, size_t, char *); // mymv function

void renameFile(char *, char *); // to implement mymv without options

void doNotOverWrite(char *, char *); // doesn't overwrite existing files (-n)

void promptOverWrite(char *, char *); // prompts before overwriting existing files (-i)

void verbose(char *, char *); // says what it does (-v)

void backup(char *, char *); // creates backup for destination files if it already exists (not for directories) (-b)

void renameMany(char **, size_t, char *); // to implement mv with multiple files going into a directory

// myls 

void myls(char **, size_t, char *); // figures out the command

int extractEntries(char *); // get all the entries

void convertLowerls(char *); // converts string to lowercase

void getBlocks(); // function to print the total blocks

void printData(); // function to implement ls -U

void alphaSort(); // function to sort the data in alphabetical order of name

void sizeSort(); // function to implement ls -S

void printAllData(); // function to implement ls -a

void ls(); // function to implement ls

void printPermission(mode_t); // function to convert permission from binary to rwx format

void printUser(uid_t); // function that prints the user name

void printGroup(gid_t); // function that prints the group name

void printLastTime(time_t); // print last access time

void printList(); // function to implement ls -l

void printListNoOwner(); // function to implement ls -g

void printInNewLine(); // function to implement ls -1
