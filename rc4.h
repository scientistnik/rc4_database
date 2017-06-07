#ifndef __RC4_H__
#define __RC4_H__

void rc4_init();
void rc4_reset();
void rc4_crypt(char *Data, unsigned long Len);

#endif
