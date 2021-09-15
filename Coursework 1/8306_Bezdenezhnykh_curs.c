#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 1000

void screen_cl(int a);
void info();
void work(char **text, char *w1, char *w2, int *size, int len1, int m);
int oper_sys();
int user_inter(int os);
int new_gets(char *s, int lim);

int main()
{
    int i, j;
    int t1, t2;
    int str_count,counter2,length2;
    int tsize;
    int answ, os;
    int length_st1[MAXLEN];
    char *text = NULL;
    char **text1 = NULL;
    char word1[MAXLEN], word2[MAXLEN];
    char c0;
    FILE *df;

    str_count=0;
    counter2=0;
    t1=0;t2=0;
    os = oper_sys();
    screen_cl(os);
    answ=2;
    if((answ<=3)&&(answ>=1))
    {
        answ = user_inter(os);
        switch(answ)
        {
            case 1: // Main part of the program
                df = fopen("text.txt","r");
                if(df != NULL)
                {
                    fseek(df,0,SEEK_SET);
                    fseek(df,0,SEEK_END);
                    tsize = ftell(df);
                    rewind(df);
                    text = (char*)calloc((tsize),sizeof(char));
                    if((text != NULL)||(tsize=0))
                    {
                        fread(text,tsize,1,df);

                        puts("----------------------------------------------------");
                        printf("Original text:\n%s",text); // Display text in file
                        fclose(df);

                        for(i = 0;i < tsize; i++)
                        {
                            c0 = text[i];
                            if(c0 == '\n') str_count++;  //Counting the number of lines
                        }
                        str_count++;
                        if((text1=(char**)calloc(str_count,sizeof(char*)))!=NULL)    //Line memory allocation
                        {
                            for(i=0;i<str_count;i++)
                                if((text1[i] = (char*)calloc(MAXLEN,sizeof(char)))!=NULL) counter2++;
                            if((counter2)==str_count)
                            {
                                for(i = 0;i <= tsize; i++)       //Splitting text into lines
                                {
                                    c0 = text[i];
                                    if((c0 != '\n')||(t2!=tsize))
                                    {
                                        text1[t1][t2]=c0;
                                        length_st1[t1]=t2;
                                        t2++;
                                    }
                                    else
                                    {
                                        text1[t1][t2]='\0';
                                        t1++;
                                        t2=0;
                                    }
                                }
                                getchar();
                                printf("\n");
                                printf("\n");
                                printf("Enter the word you want to replace: ");
                                length2=new_gets(word1, MAXLEN);
                                printf("\n");
                                printf("Input a word to replace: ");
                                new_gets(word2, MAXLEN);
                                printf("\n");
                                printf("Modified text\n");
                                for(j=0;j<str_count;j++)
                                    length_st1[j]=strlen(text1[j]);

                                work(text1, word1, word2, length_st1, length2, str_count); //Main function

                        }else printf("Error at memory allocation!");
                    }else printf("Error at memory allocation!");
                    for(i=0;i<str_count;i++) //Memory clear
                    {
                        free(text1[i]);
                        text1[i]=NULL;
                    }
                    if(text1!=NULL)
                    {
                        free(text1);
                        text1=NULL;
                    }
                }
                else puts("Text is empty");
                break;

            case 2: // Information
                info();
                break;

            case 3: // Exit
                printf("The program is over.\n");
                break;
            default: printf("Wrong key!\n");
        }
    }
    }else printf("Incorrect value!");

return 0;
}

void screen_cl(int a) //Screen cleaning depending on OS
{
    switch(a)
    {
        case 1:
            system("CLS"); //For Windows
            break;
        case 2:
            system("clear"); //For Linux
            break;

        default:
            puts("Wrong key.");
    }
}
void info() //Information
{
    puts("    Creator of the programm: Bezdenezhnykh Sergey   ");
    puts("                                                    ");
    puts("    If you have any problems with the program,      ");
    puts("    please, contact with us.                        ");
}

int oper_sys() //Selection OS
{
    int q, os;

    puts("           Choose your OS:                         ");
    puts("               1 - Windows                         ");
    puts("               2 - Linux                           ");

    while(q != 1)
    {
        printf("Your answer is: ");
        scanf("%d", &os);
        switch(os)
        {
            case 1:
                q = 1;
                break;
            case 2:
                q = 1;
                break;
            default: puts("Wrong input! Try again.");
        }
    }

    return os;
}

int user_inter(int os) //Interface
{
    int b;


    puts("          Press '1' to start                        ");
    puts("          Press '2' to get the information          ");
    puts("          Press '3' to close the program            ");

    printf("Your answer is: ");
    scanf("%d", &b);
    screen_cl(os);

    return b;
}

int new_gets(char *s, int lim) //Read row
{
    char c;
    int i;
    for(i=0;((c=getchar())!='\n')&&(i<lim-1);i++,s++) *s=c;
    *s='\0';
    return i;
}

void work(char **text, char *w1, char *w2, int *size, int len1, int m) //Working with strings
{
    int i,j,counter1,flag1,begin,last,x;
    counter1=0;
    flag1=0;
    last=0;
    begin=0;
    for(i=0;i<m;i++)
    {
        for(j=0;j<(size[i]);j++)
        {
            if ((isspace(text[i][j]) != 0) || (ispunct(text[i][j]) != 0)) //Punctuation test
            {
                printf("%c",text[i][j]);
                flag1=0;
            }
            else
            {
                if((isspace(text[i][j]) == 0) && (ispunct(text[i][j]) == 0)&&(flag1!=1)&&(text[i][j]!='\0')) //Letter Verification
                {
                    begin=j;
                    flag1=1;
                }
                if((isspace(text[i][j]) == 0) && (ispunct(text[i][j]) == 0)&&((isspace(text[i][j+1]) != 0) || (ispunct(text[i][j+1]) != 0)||((j+1)>=strlen(text[i])))) //End of word check
                {
                    counter1=0;
                    last=j;
                    for(x=begin;x<(last+1);x++)
                    {
                        if(text[i][x]==w1[x-begin]) counter1++; //Compare a word from a string with a word entered by the user
                    }
                    if((counter1==len1)&&((last-begin+1)==len1))
                        printf("%s", w2);                         //Replacing one word to another
                    else
                    {
                        for(x=begin;x<(last+1);x++)
                            printf("%c",text[i][x]);
                    }
                 }
             }
        } printf("\n");
    }
}




