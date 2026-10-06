#ifndef CREGISTRY_H
#define CREGISTRY_H

#include <windows.h>

// Size: 0x78
class CRegistry
{
public:
   CRegistry(const char *pszCompany, const char *pszProduct);

   int ReadInt(char *pszPath, int nDefault);
   bool ReadString(char *pszPath, char *pszDefault, char *pszBuffer, DWORD cbBuffer);
   bool ReadValue(char *pszPath, DWORD *pdwType, BYTE *pData, DWORD *pcbData);

   bool WriteInt(char *pszPath, int nValue);
   bool WriteValue(char *pszPath, DWORD dwType, BYTE *pData, DWORD cbData);

   static bool __stdcall SplitPath(char *pszPath, char *pszKey, UINT cbKey, char *pszValue, UINT cbValue);

private:
   char m_szCompany[0x28];
   char m_szProduct[0x50];
};

#endif
