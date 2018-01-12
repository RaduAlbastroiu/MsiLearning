#include "stdafx.h"
#include "CustActUtil.h"

namespace CustActUtil
{
  wstring getStringWithProperties(Database & aDatabase, const wstring & aText)
  {
    wstring finalText;
    vector<wstring> tokenized = CustActUtil::tokenizeProperties(aText);
    Table propertyTable = *aDatabase.inTable(L"Property")->withColumns(L"Property", L"Value")->select();
    
    for (auto& token : tokenized)
    {
      token = getPropertyValue(propertyTable, token);
      finalText += token;
    }
    return finalText;
  }

  vector<wstring> tokenizeProperties(const wstring & aTokenizable)
  {
    vector<wstring> tokenized;
    tokenized.push_back({});

    bool isProp = false;
    for (auto& c : aTokenizable)
    {
      if (c == L'[')
      {
        isProp = true;
        tokenized.push_back({c});
      }
      if (c == L']')
      {
        isProp = false;
        tokenized[tokenized.size() - 1].push_back(c);
        tokenized.push_back({});
      }
      if (c != L'[' && c != ']')
      {
        tokenized[tokenized.size() - 1].push_back(c);
      }
    }
    return tokenized;
  }

  bool isProperty(const wstring & aProperty)
  {
    if (aProperty[0] == L'[' && aProperty[aProperty.size() - 1] == L']')
      return true;
    return false;
  }

  wstring getPropertyValue(Table& aPropertyTable, const wstring & aProperty)
  {
    wstring propValue = aProperty;
    if (isProperty(aProperty))
    {
      wstring prop = aProperty.substr(1);
      
      if(prop.size())
        prop.pop_back();

      for (int i = 0; i < aPropertyTable.getNumberOfRows(); ++i)
      {
        if (aPropertyTable.getRowWithNumber(i)->getElementFromColumn(L"Property")->getAsString() == prop)
        {
          propValue = aPropertyTable.getRowWithNumber(i)->getElementFromColumn(L"Value")->getAsString();
          break;
        }
      }
    }
    return propValue;
  }

  UINT getNrCharDisplayed(const wstring & aText)
  {
    UINT result = aText.size();

    if (result > 2)
    {
      for (auto it = aText.begin(); it != aText.end() - 2; ++it)
      {
        // {verdanaBold 13} skip
        if (*it == L'{')
        {
          it++;
          UINT counter = 2;
          while (it != aText.end() && *it != L'}')
          {
            it++;
            counter++;
          }
          result -= counter;
        }

        // /" skip
        if (*it == L'\'' && *(it + 1) == L'"')
        {
          result--;
        }

        // &Folder
        if (*it == L'&' && ((*(it + 1) >= L'a' && *(it + 1) <= L'z') || (*(it + 1) >= L'A' && *(it + 1) <= L'Z')))
        {
          result--;
        }
      }
    }
    return result;
  }

  // dfs on directory graph
  wstring findFullPathForDirectory(Database& aDatabase, const wstring& aDirectoryId)
  {
    Table table = *aDatabase.inTable(L"Directory")->withColumns(L"Directory", L"Directory_Parent", L"DefaultDir")->
      whereConditionIs(Equal(L"Directory", aDirectoryId))->select();
    wstring parentDir = table.getRowWithNumber(0)->getElementFromColumn(L"Directory_Parent")->getAsString();
    wstring dirName = table.getRowWithNumber(0)->getElementFromColumn(L"DefaultDir")->getAsString();
    
    if (parentDir.size())
    {
      return findFullPathForDirectory(aDatabase, parentDir) + L"/" + dirName;
    }
    return L"";
  }

  // find dirId Kid for dirIdParrent
  vector<wstring> findAllKidsForDirectory(Database& aDatabase, const wstring& aDirectoryId)
  {
    vector<wstring> result;
    Table table = *aDatabase.inTable(L"Directory")->withColumns(L"Directory")->
      whereConditionIs(Equal(L"Directory_Parent", aDirectoryId))->select();
    int nr = table.getNumberOfRows();
    for (int i = 0; i < nr; i++)
    {
      wstring dirId = table.getRowWithNumber(i)->getElementFromColumn(L"Directory")->getAsString();
      result.push_back(dirId);
    }
    return result;
  }

  // get all files from one directory
  vector<wstring> getAllFilesFromDirectory(Database& aDatabase, const wstring& aDirectoryId)
  {
    vector<wstring> result;
    Table table = *aDatabase.inTable(L"Component")->withColumns(L"Component")
      ->whereConditionIs(Equal(L"Directory_", aDirectoryId))->select();

    int nr = table.getNumberOfRows();
    wstring componentId = table.getRowWithNumber(nr-1)->getElementFromColumn(L"Component")->getAsString();

    Table fileTable = *aDatabase.inTable(L"File")->withColumns(L"FileName")
      ->whereConditionIs(Equal(L"Component_", componentId))->select();

    int nrRows = fileTable.getNumberOfRows();
    for (int i = 0; i < nrRows; i++)
    {
      wstring fileName = fileTable.getRowWithNumber(i)->getElementFromColumn(L"FileName")->getAsString();
      result.push_back(fileName);
    }
    return result;
  }

  // get all files from sub tree
  vector<wstring> getAllFilesFromSubTreeOfDirectory(Database& aDatabase, const wstring& aDirectoryId)
  {
    // find dirName
    wstring dirName = aDatabase.inTable(L"Directory")->withColumns(L"DefaultDir")
      ->whereConditionIs(Equal(L"Directory", aDirectoryId))->select()->getRowWithNumber(0)
      ->getElementFromColumn(L"DefaultDir")->getAsString();

    // files in local directory
    vector<wstring> allFileNames = getAllFilesFromDirectory(aDatabase, aDirectoryId);
    for (auto& fileName : allFileNames)
    {
      fileName = dirName + L"/" + fileName;
    }

    // all folder names
    vector<wstring> folderIds = findAllKidsForDirectory(aDatabase, aDirectoryId);

    for (auto& folderId : folderIds)
    {
      vector<wstring> kidFolderFiles = getAllFilesFromSubTreeOfDirectory(aDatabase, folderId);
      for (auto& kidFile : kidFolderFiles)
      {
        allFileNames.push_back(dirName + L"/" + kidFile);
      }
    }

    return allFileNames;
  }

  UINT DirectorFilesPopulateListBox(MSIHANDLE hSession)
  {
    Database database(hSession);

    wstring fullPath = database.getValueFromProperty(L"COMBOBOX_2_PROP");
    wstring dirName = fullPath; 
    auto found = dirName.find_last_of(L'/');
    dirName = dirName.substr(found + 1);

    // get dirID from dir name
    wstring dirID = database.inTable(L"Directory")->withColumns(L"Directory")->
      whereConditionIs(Equal(L"DefaultDir", dirName))->select()->getRowWithNumber(0)->
      getElementFromColumn(L"Directory")->getAsString();

    vector<wstring> allFiles = getAllFilesFromSubTreeOfDirectory(database, dirID);

    // delete elements from listbox
    database.inTable(L"ListBox")->whereConditionIs(Equal(L"Property", L"LISTBOX_2_PROP"))->deleteRows();

    // insert files in listBox
    database.insertElementsInListBox(L"LISTBOX_2_PROP", allFiles);

    return ERROR_SUCCESS;
  }
}
