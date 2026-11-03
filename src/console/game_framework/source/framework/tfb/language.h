#ifndef _TFB_LANGUAGE_H_
#define _TFB_LANGUAGE_H_

extern const char *g_langCodes[18];
extern const char *g_langNames[18];
extern int g_activeLangIndex;

int IsCurrentLanguageName(const char *name);

#endif