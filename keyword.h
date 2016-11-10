#include<stdlib.h>
#include<stdio.h>
#include"charlist.h"
#include<string.h>

#define MAXKEYWORD 1000                               //�б��йؼ����������
#define MAXKEYWORDLENGTH 50                   //ÿ���ؼ�����ֽ�����
#define MAXKEYWORDLENGTH_UTF8 5         //UFT8��ֽ�

extern int LIST_COUNT;                                                                                                                                                          //�ؼ����б�����
extern int keylist_len[MAXKEYWORD];                                                                                                                               //ÿ���ؼ��ʵ��ֽ�
extern int keylist_len_utf8[MAXKEYWORD][MAXKEYWORDLENGTH];                                                                    //UTF8�ֽڳ���
extern char keyword_utf8[MAXKEYWORD][MAXKEYWORDLENGTH][MAXKEYWORDLENGTH_UTF8];     //UTF8�ֽ�
extern char* keyword_binary[MAXKEYWORD][MAXKEYWORDLENGTH][MAXKEYWORDLENGTH_UTF8];  //huffman code

typedef struct KEYMANENT{
	CharList LIST_KEYWORDS;
}KEYMANENT, *P_KEYMANENT;


void init_list_keyword(P_KEYMANENT p_km,char ** listkeyword,int count){
	LIST_COUNT = count;
	for (int i = 0; i < LIST_COUNT; i++){
		pushback_ch(&(p_km->LIST_KEYWORDS), listkeyword[i]);
	}
	for (int i = 0; i < LIST_COUNT; i++){
       char* key = front_ch(p_km->LIST_KEYWORDS);// LIST_KEYWORDS.front();
		pop_front_ch(&(p_km->LIST_KEYWORDS));//LIST_KEYWORDS.pop_front();
		int length=strlen(key);
		int word_length=0;
		for(int j=0;j<length;j++){
            if(key[j]>=0x00&&key[j]<=0x7F){

               keyword_utf8[i][word_length][0]=key[j];
               keylist_len_utf8[i][word_length]=1;
                word_length++;
                }
            else if((unsigned)key[j]>=(unsigned)0xE0){
                for(int k=0;k<3;k++){
               keyword_utf8[i][word_length][k]=key[j+k];
               }
               keylist_len_utf8[i][word_length]=3;
                word_length++;
                j=j+2;
                }
		}
		keylist_len[i]=word_length;
	}
}
