#include "precomp.h"
#include <mbstring.h>
#include "language.h"

const char *g_langCodes[18] = {
		"US", "FR", "DE", "SP", "SE", "IT",   
		"JP", "NL", "PT", "UK", "DK", "FI",   
		"NO", "SK", "RS", "LT", "ES", "GK",  
}; 
const char *g_langNames[18] = {
	"English", "French", "German", "Spanish", "Swedish", "Italian", 
	"Japanese", "Dutch", "Portuguese", "British", "Danish", "Finnish",
	"Norwegian", "Norse", "Russian", "Latin", "Esperanto", "Greek",
};

int g_activeLangIndex;

// FUNCTION: GAME 0x00447670
int IsCurrentLanguageName(const char *name)
{
    const char *activeName =
        (g_activeLangIndex >= 0 && g_activeLangIndex < 18) ? g_langNames[g_activeLangIndex] : "UNKNOWN";

    return _mbscmp((const unsigned char *)activeName, (const unsigned char *)name) == 0;
}