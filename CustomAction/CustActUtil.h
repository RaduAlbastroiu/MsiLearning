#pragma once
#include "../MsiFramework/Database.h"

namespace CustActUtil
{
  wstring getStringWithProperties(Database& aDatabase, const wstring& aText);
  vector<wstring> tokenizeProperties(const wstring& aTokenizable);
  bool isProperty(const wstring& aProperty);
  wstring getPropertyValue(Table& aPropertyTable, const wstring& aProperty);
}
