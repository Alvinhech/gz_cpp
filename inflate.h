#include<time.h>
#include<omp.h>
#include"acsmx.h"

#define CPU_NUM 8                    //CPU 并行数目
#define dkeylength 4                     //每个CPU任务
#define wordlength 50
#define FILEBUFFER 64
extern int nline;

typedef struct Buffer{
	char ch;
	unsigned int bits;
}Buffer;
typedef struct ac{

	unsigned char* File_binary;
	unsigned char pattern[CPU_NUM][dkeylength][MAXKEYWORDLENGTH][wordlength];
	ACSM_STRUCT * acsm[CPU_NUM];
	clock_t begin, end;
	double cost;
	ACSMX acsmx;
	Buffer buf;
	FILE *infp;
}AC,*P_AC;

void Read(P_AC p_ac, unsigned int *bit);
int FILE_READ_BINARY(P_AC p_ac, char* infName);
void Compile(P_AC p_ac);
void End(P_AC p_ac);
void Comput(P_AC p_ac);
void Read(P_AC p_ac,unsigned int *bit)				//从infp中读出一个比特
{
	if (p_ac->buf.bits == 0){
		p_ac->buf.ch = fgetc(p_ac->infp);
		p_ac->buf.bits = 8;
	}
	*bit = (p_ac->buf.ch & 128) >> 7;
	p_ac->buf.ch = p_ac->buf.ch << 1;
	p_ac->buf.bits--;
}

int FILE_READ_BINARY(P_AC p_ac,char* infName)
{
	p_ac->File_binary = (char *)malloc(sizeof(char)*8*2048);// new unsigned char[SIZE];
	if ((p_ac->infp = fopen(infName, "rb")) == NULL){
		return -1;
	}
	unsigned int bit;
	int point = 0;
	char in_char;
	while (!feof(p_ac->infp))
	{
		Read(p_ac,&bit);
		if (bit == 0)
		{
			in_char = '0';
		}
		else
		{
			in_char = '1';
		}
		memcpy(p_ac->File_binary + point, &in_char, 8);
		point += 1;
	}
	p_ac->File_binary[point] = '\0';
	fclose(p_ac->infp);
	return 1;
}

void Compile(P_AC p_ac)
{
	int  nocase = 1;
	p_ac->begin = clock();
//	omp_set_num_threads(8);
    for(int i=0;i<CPU_NUM;i++){
        p_ac->acsm[i] = acsmNew();
}
//#pragma omp parallel for
	for (int i = 0; i<CPU_NUM; i++)
	{


		for (int index = 4 * i, dex = 0; index<(i + 1) * 4; index++, dex++)
		{
			for (int j = 0; j<keylist_len[index]; j++)                   //每个字符对应的huffman放一块
			{
				int patlen = 0;
				patlen = strlen((const char*)(char*)p_ac->pattern[i][dex][j]);
				acsmAddPattern(p_ac->acsm[i], p_ac->pattern[i][dex][j], patlen, nocase);

			}
		}
		/* Generate GtoTo Table and Fail Table */
		acsmCompile(p_ac->acsm[i]);
	}
	p_ac->end = clock();
}
void Comput(P_AC p_ac)
{
	int text_length = strlen((const char*)(char*)p_ac->File_binary);
	p_ac->begin = clock();
//	omp_set_num_threads(8);
//#pragma omp parallel for
	for (int i = 0; i<CPU_NUM; i++)
	{
		acsmSearch(p_ac->acsm[i], p_ac->File_binary, text_length);
		nline++;
		PrintSummary(p_ac->acsm[i]->acsmPatterns);
	}
	p_ac->end = clock();
	printf("\n### AC Match Finished ###\n");
	p_ac->cost = (double)(p_ac->end - p_ac->begin) / CLOCKS_PER_SEC;
	printf("%lf seconds\n", p_ac->cost);

}


void End(P_AC p_ac)
{
	for (int i = 0; i<CPU_NUM; i++)
	{
		acsmFree(p_ac->acsm[i]);
	}

}
