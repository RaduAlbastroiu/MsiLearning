#pragma once
#include "../MsiFramework/Database.h"

namespace CustActUtil
{
  wstring getStringWithProperties(Database& aDatabase, const wstring& aText);
  vector<wstring> tokenizeProperties(const wstring& aTokenizable);
  bool isProperty(const wstring& aProperty);
  wstring getPropertyValue(Table& aPropertyTable, const wstring& aProperty);
  UINT getNrCharDisplayed(const wstring& aText);
  
  wstring findFullPathForDirectory(Database& aDatabase, const wstring& aDirectoryName);
  vector<wstring> findAllKidsForDirectory(Database& aDatabase, const wstring& aDirectoryId);
  vector<wstring> findAllKidsForDirectory(Database& aDatabase, const wstring& aDirectoryId);
  vector<wstring> getAllFilesFromDirectory(Database& aDatabase, const wstring& aDirectoryId, bool installed);
  vector<wstring> getAllFilesFromSubTreeOfDirectory(Database& aDatabase, const wstring& aDirectoryId, bool installed);

  UINT DirectorFilesPopulateListBox(MSIHANDLE hSession, bool installed);
}
