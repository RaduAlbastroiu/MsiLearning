#pragma once
#include "../MsiFramework/Database.h"

namespace CustActUtil
{
  wstring getStringWithProperties(Database& aDatabase, const wstring& aText);
  vector<wstring> tokenizeProperties(const wstring& aTokenizable);
  bool isProperty(const wstring& aProperty);
  wstring getPropertyValue(Table& aPropertyTable, const wstring& aProperty);
  UINT getNrCharDisplayed(const wstring& aText);
  UINT insertElementsInComboBox(Database & aDatabase, const wstring& comboBoxProp, vector<wstring>& values);
  UINT insertElementsInListBox(Database & aDatabase, const wstring& listBoxProp, vector<wstring>& values);
  wstring findFullPathForDirectory(Database& aDatabase, const wstring& aDirectoryName);
  vector<wstring> findAllKidsForDirectory(Database& aDatabase, const wstring& aDirectoryId);
  vector<wstring> findAllKidsForDirectory(Database& aDatabase, const wstring& aDirectoryId);
  vector<wstring> getAllFilesFromDirectory(Database& aDatabase, const wstring& aDirectoryId);

  UINT DirectorFilesPopulateListBox(MSIHANDLE hSession);
}
