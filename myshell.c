#include "myshelll.h"


//Most important component of program. Takes commands and executes them. Also handles I/O
static int command(int in, int begin, int end, char *commExec)
{

    int pipe_fileD[2];
    int pipeReturn_val;
    int in_fileD;
    int out_fileD;
    pipeReturn_val = pipe(pipe_fileD);
    if(pipeReturn_val == -1)
    {
        return 1;
    }
    pid = fork();

    if (pid == 0)
    {
        if (begin==1 && end==0 && in==0)
        {

            dup2( pipe_fileD[1], 1 );
        }
        else if (begin==0 && end==0 && in!=0)
        {

            dup2(in, 0);
            dup2(pipe_fileD[1], 1);
        }
        else
        {

            dup2(in, 0);
        }
        if (strchr(commExec, '<') && strchr(commExec, '>'))
        {

            input_redi=1;
            output_redi=1;
            tok_rediIO(commExec);
        }
        else if (strchr(commExec, '<'))
        {

            input_redi=1;
            tok_rediI(commExec);
        }
        else if (strchr(commExec, '>'))
        {

            output_redi=1;
            tok_rediO(commExec);
        }
        if(output_redi == 1)
        {

            out_fileD= creat(output_rediFile, 0644);
            if (out_fileD < 0)
            {
                fprintf(stderr, "File open error %s \n", output_rediFile);
                return(EXIT_FAILURE);
            }
            dup2(out_fileD, 1);
            close(out_fileD);
            output_redi=0;
        }
        if(input_redi  == 1)
        {

            in_fileD=open(input_rediFile,O_RDONLY, 0);
            if (in_fileD < 0)
            {
                fprintf(stderr, "File open error %s \n", input_rediFile);
                return(EXIT_FAILURE);
            }
            dup2(in_fileD, 0);
            close(in_fileD);
            input_redi=0;
        }

        if (strcmp(args[0], "echo") == 0)
        {

            //echo_call(commExec);
        }
        if (strcmp(args[0], "cd") == 0)
        {

        }
        //if (strcmp(args[0]))


        else if(execvp(args[0], args)<0) {

            printf("%s: error: command or file not recognized\n", args[0]);
        }

        if (!(execvp(args[0], args)<0)) {
            printf("%s", shell);
        }
        exit(0);
    }
    else
    {
        waitpid(pid, 0, 0);
    }


    if (end == 1)
        close(pipe_fileD[0]);
    if (in != 0)
        close(in);
    close(pipe_fileD[1]);
    return pipe_fileD[0];

}


void tok_commands(char *com_exec)
{
    int x = 1;
    args[0]=strtok(com_exec," ");


    while((args[x]=strtok(NULL," "))!=NULL)
        x++;
}
void tok_rediIO(char *commExec)
{
    char *io_tok[100];
    char *commExec2;
    commExec2=strdup(commExec);
    int x = 1;
    io_tok[0]=strtok(commExec2,"<");
    while((io_tok[x]=strtok(NULL,">"))!=NULL)
        x++;



    io_tok[1]=ignoreWhiteSpace(io_tok[1]);
    io_tok[2]=ignoreWhiteSpace(io_tok[2]);
    input_rediFile=strdup(io_tok[1]);
    output_rediFile=strdup(io_tok[2]);
    tok_commands(io_tok[0]);

}
void tok_rediI(char *commExec)
{
    char *i_tok[100];
    char *commExec2;
    commExec2=strdup(commExec);
    int x=1;
    i_tok[0]=strtok(commExec2,"<");


    while((i_tok[x]=strtok(NULL,"<"))!=NULL)
        x++;
    i_tok[1]=ignoreWhiteSpace(i_tok[1]);
    input_rediFile=strdup(i_tok[1]);
    tok_commands(i_tok[0]);
}
void tok_rediO(char *commExec)
{
    char *o_tok[100];
    char *commExec2;
    commExec2=strdup(commExec);
    int m=1;
    o_tok[0]=strtok(commExec2,">");

    while((o_tok[m]=strtok(NULL,">"))!=NULL)
        m++;
    o_tok[1]=ignoreWhiteSpace(o_tok[1]);
    output_rediFile=strdup(o_tok[1]);
    tok_commands(o_tok[0]);

}
//splits arguments and does some internal command handling
static int split(char *commExec, int in, int begin, int end)
{
    char *commExec2;
    commExec2=strdup(commExec);


    int m=1;
    args[0]=strtok(commExec," ");
    while((args[m]=strtok(NULL," "))!=NULL)
        m++;
    args[m]=NULL;
    if (args[0] != NULL)
    {

        if (strcmp(args[0], "echo") != 0)
        {
            commExec = ignoreComma(commExec2);
            int m=1;
            args[0]=strtok(commExec," ");
            while((args[m]=strtok(NULL," "))!=NULL)
                m++;
            args[m]=NULL;

        }

        if (strcmp(args[0], "exit") == 0)
            exit(0);

        if(strcmp("cd",args[0])==0 && args[1] == NULL)
        {

            getcwd(cwd, sizeof(cwd));
            printf("current directory is: %s \n", cwd);

            return 1;


        }
        if(strcmp("cd",args[0])==0 && args[1] != NULL)
        {

            change_dir();

            return 1;


        }
        if(strcmp("help",args[0])==0){
            printf(" \n \n INTERNAL COMMANDS: \n cd \n echo \n dir \n pause \n clr \n env  \n \n");
        }
        if(strcmp("clr",args[0])==0){
            printf("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n ");
            return 1;
        }
        if(strcmp("pause",args[0])==0){
            printf("\n \n Paused. Press Enter to continue \n");
            while(getchar() != '\n') {
                getchar();
            }
            return 1;
        }

        else if(strcmp("pwd",args[0])==0)
        {
            parent_dir();
            return 1;
        }

    }

    return command(in, begin, end, commExec2);
}
static char* ignoreWhiteSpace(char* l)
{
    while (isspace(*l)) ++l;
    return l;
}
//clears variables
void clr_var()
{
    environFl=0;
    pipeFl=0;
    len=0;
    numLines=0;
    pipeNum=0;
    inputBuff[0]='\0';
    flNoFlag=0;
    output_redi=0;
    input_redi=0;
    flag=0;
    cwd[0] = '\0';
    pid=0;
    bFlag=0;
}

void environ_()
{
    int i = 1;
    int i2=0;
    char environVals[1000], *value;
    while(args[1][i]!='\0')
    {
        environVals[i2]=args[1][i];
        i2++;
        i++;
    }
    environVals[i2]='\0';
    value=getenv(environVals);

    if(!value)
        printf("\n");
    else printf("%s\n", value);
}

//helper function for cd
void change_dir()
{
    char *h="/home";
    if(args[1]==NULL)
        printf("%s", cwd);
    else if ((strcmp(args[1], "~")==0) || (strcmp(args[1], "~/")==0))
        chdir(h);
    else if(chdir(args[1])<0)
        printf("%s Unable to find file/directory \n", args[1]);

}
void set_environVar()
{
    int n=1;
    char *left_right[100];
    if(args[1]==NULL)
    {
        char** env;
        for (env = environ; *env != 0; env++)
        {
            char* value = *env;
            printf("declare -x %s\n", value);
        }
        return;
    }
    left_right[0]=strtok(args[1],"=");
    while ((left_right[n]=strtok(NULL,"="))!=NULL)
        n++;
    left_right[n]=NULL;
    setenv(left_right[0], left_right[1], 0);
}
void parent_dir()
{
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd );
    }
    else
        perror("getcwd() error");


}
void echo_call(char *echo_val)
{
    int i=0, index=0;
    environFl=0;
    char new_args[1024],env_val[1000], *str[10];
    str[0]=strtok(echo_val," ");
    str[1]=strtok(NULL, "");
    strcpy(env_val, args[1]);
    if(str[1]==NULL)
    {
        printf("\n");
        return;
    }
    if (strchr(str[1], '$'))
    {
        environFl=1;
    }

    memset(new_args, '\0', sizeof(new_args));
    i=0;
    while(str[1][i]!='\0')
    {
        if(str[1][i]=='"')
        {
            index=0;
            while(str[1][i]!='\0')
            {
                if(str[1][i]!='"')
                {
                    new_args[index]=str[1][i];
                    flag=1;
                    index++;
                }
                i++;
            }
        }
        else if(str[1][i]==39)
        {
            index=0;
            while(str[1][i]!='\0')
            {
                if(str[1][i]!=39)
                {
                    new_args[index]=str[1][i];
                    flag=1;
                    index++;
                }
                i++;
            }
        }
        else if(str[1][i]!='"')
        {
            new_args[index]=str[1][i];
            index++;
            i++;
        }
        else i++;
    }


    new_args[index]='\0';
    if((strcmp(args[1], new_args)==0)&&(environFl==0))
        printf("%s\n", new_args);
    else {
        strcpy(args[1], new_args);
        if(environFl==1)
        {
            environ_();
        }
        else if(environFl==0)
        {
            printf("%s\n", new_args );
        }
    }
}



char* ignoreComma(char* str)
{
    int i=0;
    int j=0;
    char temp[1000];
    while(str[i++]!='\0')
    {
        if(str[i-1]!='"')
            temp[j++]=str[i-1];
    }
    temp[j]='\0';
    str = strdup(temp);

    return str;
}



void pipe_exec()
{

    int i, n=1, in, begin;

    in=0;
    begin= 1;

    commExec[0]=strtok(inputBuff,"|");

    while ((commExec[n]=strtok(NULL,"|"))!=NULL)
        n++;
    commExec[n]=NULL;
    pipeNum=n-1;
    for(i=0; i<n-1; i++)
    {
        in = split(commExec[i], in, begin, 0);
        begin=0;
    }
    in=split(commExec[i], in, begin, 1);
    in=0;
    return;

}

void pipe_exec2(char* line)
{

    int i, n=1, in, begin;

    in=0;
    begin= 1;

    commExec[0]=strtok(line,"|");

    while ((commExec[n]=strtok(NULL,"|"))!=NULL)
        n++;
    commExec[n]=NULL;
    pipeNum=n-1;
    for(i=0; i<n-1; i++)
    {
        in = split(commExec[i], in, begin, 0);
        begin=0;
    }
    in=split(commExec[i], in, begin, 1);
    in=0;
    return;

}
void print_prompt()
{
    //printf("%s ", shell);
}
//driver function
int main(int argc, char *argv[])
{
    getcwd(cwd, sizeof(cwd));
    if(argc == 2) {
        FILE *fptr;
        char line[200];
        char **args;
        fptr = fopen(argv[1], "r");
        if (fptr == NULL) {
            printf("Unable to find batch file");
        } else {
            while (fgets(line, sizeof(line), fptr) != NULL) {
                pipe_exec2(line);
            }
        }
    }

    else {

        printf(" \n \n \n Hello, welcome to myShell. Type 'help' for more information \n \n \n \n");




        int status;
        //char chara[2]={"\n"};
        getcwd(curr_dir, sizeof(curr_dir));
        while (1) {

            clr_var();
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                strcpy(shell, "myShell[");
                strcat(shell, cwd);
                strcat(shell, "]>");



            } else
                perror("getcwd() error");

            printf("%s ", shell);

            fgets(inputBuff, 1024, stdin);


            len = strlen(inputBuff);
            inputBuff[len - 1] = '\0';
            strcpy(hisVar, inputBuff);
            if (strcmp(inputBuff, "exit") == 0) {
                flag = 1;
                break;
            }

            pipe_exec();
            waitpid(pid, &status, 0);

        }


        if (flag == 1) {
            printf("\n Exiting Shell!\n");
            exit(0);
            return 0;
        }
        return 0;
    }
}