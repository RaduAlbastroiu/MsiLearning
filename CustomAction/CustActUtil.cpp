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
    }
    return finalText;
  }

  vector<wstring> tokenizeProperties(const wstring & aTokenizable)
  {
    vector<wstring> tokenized;
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
    wstring propValue = L"";
    if (isProperty(aProperty))
    {
      wstring prop = aProperty.substr(1);
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
}
