#include "precomp.h"
#include "cregistry.h"

#include <stdio.h>
#include <string.h>

CRegistry::CRegistry(const char *pszCompany, const char *pszProduct)
{
   strncpy(m_szCompany, pszCompany, sizeof(m_szCompany) - 1);
   strncpy(m_szProduct, pszProduct, sizeof(m_szProduct) - 1);
}

int CRegistry::ReadInt(char *pszPath, int nDefault)
{
   DWORD dwType;
   DWORD cbData = sizeof(int);
   int nValue;

   if (!ReadValue(pszPath, &dwType, (BYTE *)&nValue, &cbData) || dwType != REG_DWORD)
   {
      nValue = nDefault;
   }
   return nValue;
}

bool CRegistry::ReadString(char *pszPath, char *pszDefault, char *pszBuffer, DWORD cbBuffer)
{
   DWORD dwType;
   DWORD cbData = cbBuffer;

   if (ReadValue(pszPath, &dwType, (BYTE *)pszBuffer, &cbData))
   {
      return dwType == REG_SZ;
   }

   if (strlen(pszDefault) < cbBuffer)
   {
      strcpy(pszBuffer, pszDefault);
   }
   return false;
}

bool CRegistry::ReadValue(char *pszPath, DWORD *pdwType, BYTE *pData, DWORD *pcbData)
{
   char szSubKey[MAX_PATH];
   char szValue[MAX_PATH];
   char szKey[MAX_PATH];
   HKEY hKey;

   if (!SplitPath(pszPath, szSubKey, MAX_PATH, szValue, MAX_PATH))
   {
      return false;
   }

   sprintf(szKey, "Software\\%s\\%s\\%s", m_szCompany, m_szProduct, szSubKey);

   if (RegOpenKeyA(HKEY_CURRENT_USER, szKey, &hKey) == ERROR_SUCCESS &&
       RegQueryValueExA(hKey, szValue, NULL, pdwType, pData, pcbData) == ERROR_SUCCESS)
   {
      return true;
   }

   if (RegOpenKeyA(HKEY_LOCAL_MACHINE, szKey, &hKey) == ERROR_SUCCESS)
   {
      return RegQueryValueExA(hKey, szValue, NULL, pdwType, pData, pcbData) == ERROR_SUCCESS;
   }
   return false;
}

bool CRegistry::WriteInt(char *pszPath, int nValue)
{
   return WriteValue(pszPath, REG_DWORD, (BYTE *)&nValue, sizeof(int));
}

bool CRegistry::WriteValue(char *pszPath, DWORD dwType, BYTE *pData, DWORD cbData)
{
   char szSubKey[MAX_PATH];
   char szValue[MAX_PATH];
   char szKey[MAX_PATH];
   HKEY hKey;

   if (!SplitPath(pszPath, szSubKey, MAX_PATH, szValue, MAX_PATH))
   {
      return false;
   }

   sprintf(szKey, "Software\\%s\\%s\\%s", m_szCompany, m_szProduct, szSubKey);

   if (RegCreateKeyA(HKEY_CURRENT_USER, szKey, &hKey) != ERROR_SUCCESS)
   {
      return false;
   }
   return RegSetValueExA(hKey, szValue, 0, dwType, pData, cbData) == ERROR_SUCCESS;
}

bool __stdcall CRegistry::SplitPath(char *pszPath, char *pszKey, UINT cbKey, char *pszValue, UINT cbValue)
{
   UINT nSep = strlen(pszPath);
   while (nSep != 0 && pszPath[nSep] != '\\')
   {
      nSep--;
   }

   if (nSep == 0 || nSep >= cbKey || strlen(pszPath) - nSep - 1 >= cbValue)
   {
      return false;
   }

   strncpy(pszKey, pszPath, nSep);
   pszKey[nSep] = '\0';
   strcpy(pszValue, pszPath + nSep + 1);
   return true;
}
