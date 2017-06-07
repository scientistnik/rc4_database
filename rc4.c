#include <stdio.h>
#include <string.h>

typedef unsigned long ULONG;

unsigned char s[256] = {0}; //S-box
char key[256] = {"12345678"};

void rc4_reset()
{
	for(int i=0;i< 256;i++)
		s[i] = 0;
}

void rc4_init()
{
    int i =0, j = 0;
    char k[256] = {0};
    unsigned char tmp = 0;
		unsigned long Len = strlen(key);

    for (i=0;i<256;i++) {
        s[i] = i;
        k[i] = key[i%Len];
    }
    for (i=0; i<256; i++) {
        j=(j+s[i]+k[i])%256;
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
 }

void rc4_crypt(unsigned char *Data, unsigned long Len)
{
    int i = 0, j = 0, t = 0;
    unsigned long k = 0;
    unsigned char tmp;

    for(k=0;k<Len;k++) {
        i=(i+1)%256;
        j=(j+s[i])%256;
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        t=(s[i]+s[j])%256;
        Data[k] ^= s[t];
     }
} 
/*
int main()
{ 
    unsigned char s[256] = {0}; //S-box
    char key[256] = {"12345678"};
    char pData[512] = "dfsdf@91waijiao";
    ULONG len = strlen(pData);
    printf("key : %s\n", key);
    printf("raw : %s\n", pData);
    
    rc4_init(s,(unsigned char *)key,strlen(key));
		//
    rc4_crypt(s,(unsigned char *)pData,len);
    printf("encrypt  : %s\n", pData);
    //printf("encrypt64: %s\n", base64_encode(pData, len));
    rc4_init(s,(unsigned char *)key, strlen(key));
    rc4_crypt(s,(unsigned char *)pData,len);
    printf("decrypt  : %s\n",pData);
    return 0;
}
*/
