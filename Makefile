#MyShell makeFile
#author : Nimai Parsa

all : Myls.o Myps.o Mymv.o Mycp.o Mygrep.o MyShell.o MyShellUtils.o
	gcc Myls.o Myps.o Mymv.o Mycp.o Mygrep.o MyShell.o MyShellUtils.o -lreadline -o myshell && rm *.o

Myls.o : Myls.c
	gcc -c Myls.c -o Myls.o

Mycp.o : Mycp.c
	gcc -c Mycp.c -o Mycp.o

Mymv.o : Mymv.c
	gcc -c Mymv.c -o Mymv.o

Myps.o : Myps.c
	gcc -c Myps.c -o Myps.o

Mygrep.o : Mygrep.c
	gcc -c Mygrep.c -o Mygrep.o

MyShell.o : MyShell.c
	gcc -c MyShell.c -o MyShell.o

MyShellUtils.o : MyShellUtils.c
	gcc -c MyShellUtils.c -o MyShellUtils.o