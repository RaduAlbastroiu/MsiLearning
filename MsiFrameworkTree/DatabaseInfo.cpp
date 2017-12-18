#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

void DatabaseInfo::addTable(const wstring & aTableName)
{
  for (auto table : tableCollection)
  {
    if (table.tableName == aTableName)
      return;
  }

  tableCollection.push_back(DbInfoTable(aTableName, vector<wstring>{}));
}

void DatabaseInfo::openDatabase(const wstring aDatabasePath)
{
  databasePath = aDatabasePath;
}

std::wstring DatabaseInfo::selectSqlCondition()
{
  wstring sqlQuerry = L" SELECT ";
  sqlQuerry += composeSqlQuerryColumns();
  sqlQuerry += L" FROM ";
  sqlQuerry += composeSqlQuerryTables();
  sqlQuerry += L" WHERE ";
  sqlQuerry += condition.getCondition();

  return sqlQuerry;
}

std::wstring DatabaseInfo::updateSqlCondition(wstring aNewValue)
{
  return wstring();
}

std::wstring DatabaseInfo::deleteSqlCondition()
{
  return wstring();
}
