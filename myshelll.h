#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>


char shell[1000];
char curr_dir[1000];
char cwd[1024];
int pipeNum=0;
static char* args[512];

char inputBuff[1024];
char *commExec[100];
char *input_rediFile;
int flag, len;
int pipeFl=1;
pid_t pid;
int numLines;
int environFl;
int pipeFl;
int flNoFlag;
int output_redi;
int input_redi;
int bFlag;
int pid;
int status;
char hisVar[2000];
char *output_rediFile;
extern char** environ;



void environ_();
static int command(int, int, int, char *commExec);
void clr_var();
void file_proc ();
void file_write();
void tok_rediIO(char *commExec);
void bang_exec();
void set_environVar();
void pipe_exec();
void change_dir();
void tok_rediO(char *commExec);
void parent_dir();
void echo_call(char *echo_val);
void hist_exec();
static char* ignoreWhiteSpace(char* s);
void tok_commands(char *com_exec);
char* ignoreComma(char* str);
static int split(char *commExec, int, int, int);
void tok_rediI(char *commExec);
void print_prompt();
void signInteger(int sig_num);
void pipe_exec2(char* line);


