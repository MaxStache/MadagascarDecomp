#ifndef _TFB_READER_H_
#define _TFB_READER_H_

#include <stddef.h>

// GLOBAL: GAME 0x0061f888
int g_tfbReadPos;
// GLOBAL: GAME 0x0061f88c
unsigned char *g_tfbReadBuf;

// FUNCTION: GAME 0x004328d0
void TFBRead_u8(unsigned char *out)
{
	*out = g_tfbReadBuf[g_tfbReadPos];
	g_tfbReadPos++;
}

// FUNCTION: GAME 0x004328f0
void TFBRead_u16(unsigned short *out)
{
	unsigned char lo = g_tfbReadBuf[g_tfbReadPos++];
	unsigned char hi = g_tfbReadBuf[g_tfbReadPos++];
	*out = (unsigned short)(hi << 8 | lo);
}

// FUNCTION: GAME 0x00432920
void TFBRead_u32(unsigned int *out)
{
	unsigned char b[4];
	TFBRead_u8(&b[0]);
	TFBRead_u8(&b[1]);
	TFBRead_u8(&b[2]);
	TFBRead_u8(&b[3]);
	*out = ((b[3] << 8 | b[2]) << 8 | b[1]) << 8 | b[0];
}

// FUNCTION: GAME 0x004329a0
void TFBRead_pstr(char *out)
{
	char scratch[256];
	unsigned char n = g_tfbReadBuf[g_tfbReadPos++];

	if (out == NULL)
		out = scratch;

	for (; n != 0; n--) {
		TFBRead_u8((unsigned char *)out);
		out++;
	}
	if (*out != '\0')
		*out = '\0';
}

#endif
