#ifndef _TFB_LANGUAGE_H_
#define _TFB_LANGUAGE_H_

extern const char *g_langCodes[18] = {
		"US", "FR", "DE", "SP", "SE", "IT",   
		"JP", "NL", "PT", "UK", "DK", "FI",   
		"NO", "SK", "RS", "LT", "ES", "GK",  
}; 
extern const char *g_langNames[18] = {
	"English", "French", "German", "Spanish", "Swedish", "Italian", 
	"Japanese", "Dutch", "Portuguese", "British", "Danish", "Finnish",
	"Norwegian", "Norse", "Russian", "Latin", "Esperanto", "Greek",
};

extern int g_activeLangIndex;

int IsCurrentLanguageName(const char *name);

#endif