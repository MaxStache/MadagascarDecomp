#include "precomp.h"
#include "language.h"

// FUNCTION: Game 0x00447670
int IsCurrentLanguageName(const char *name) {
    const char* activeName = (g_activeLangIndex >= 0 && g_activeLangIndex < 18)
        ? g_langNames[g_activeLangIndex]
        : "UNKNOWN";
  
    return _mbscmp(activeName, name) == 0;
}