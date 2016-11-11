#include "main.h"
#define ORIG_FILE   "file6"
#define CHANGE_FILE "file6_c"
#define GZ_FILE     "file6_c.gz"




int main (int argc,char **argv)
{
    /*
    FILE *record=fopen("record","wb");
    int i,j;
    double percent,ffront,frear;
    string instr;
    File::ReadFileToStringOrDie(ORIG_FILE,&instr);
    string outstr;
    int w_fd=open(CHANGE_FILE,O_WRONLY|O_CREAT);
    close(w_fd);
    char *repstr,*tempstr;
    tempstr=(char*)calloc(sizeof(char),instr.length()+1);
    repstr=(char*)calloc(sizeof(char),(int)((instr.length())*0.01+1));
    for(i=0;i<(int)((instr.length())*0.01);i++)
        repstr[i]=' ';
    repstr[i]='\0';
    for(i=0;i<10;i++)
    {
        percent=(i+1)*0.001;
        for(j=0;j<10;j++)
        {
            ffront=j*0.1;
            frear=ffront+0.1;
            instr.copy(tempstr,instr.length(),0);
            memcpy(tempstr+(int)(instr.length()*ffront),repstr,instr.length()*percent);
            outstr=tempstr;
            File::WriteStringToFileOrDie(outstr,CHANGE_FILE);
            gzip(argc,argv);
            printf("%d\t",file_size2(GZ_FILE));
            fprintf(record,"%d\t",file_size2(GZ_FILE));
            remove(GZ_FILE);
        }
        printf("\n");
        fprintf(record,"\n");
    }

    fclose(record);
    */
    FILE *record=fopen("record","a+");
    __int64 c1;
    double dff;


    QueryPerformanceFrequency(&large_interger);
    dff = large_interger.QuadPart;
    QueryPerformanceCounter(&large_interger);
    c1 = large_interger.QuadPart;
    gzip(argc,argv);
    for(int i=0;i<10;i++)
        fprintf(record,"%lf\t",(c[i]-c1)/dff);

    fprintf(record,"\n");
    fclose(record);
    return 0;
}
