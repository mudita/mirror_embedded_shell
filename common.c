/*
 * common.c
 *
 *  Created on: 24 Nov 2017
 *      Author: mati
 */
#include <string.h>
#include <stdint.h>

void encryptDecrypt(const char* toEncrypt,char* encrypted) {
    char key = 'K'; //Any char will work

    for (uint16_t i = 0; i < strlen(toEncrypt); i++)
        encrypted[i] = toEncrypt[i] ^ key;

}
