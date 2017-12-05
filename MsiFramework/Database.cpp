#include "stdafx.h"
#include "Database.h"


Database::Database(wstring aDatabasePath):
  databasePath(aDatabasePath.c_str())
{
  MsiOpenDatabase(databasePath, MSIDBOPEN_DIRECT, &databaseHandle);
}

Database::~Database()
{
  MsiCloseHandle(databaseHandle);

  for (auto table : tables)
  {
    delete(table);
  }
}

void Database::saveDatabase()
{
  for (auto table : tables)
  {
    table->saveTable();
  }

  MsiDatabaseCommit(databaseHandle);
}

Table* Database::getTable(wstring tableName)
{
  wstring sqlQuerryString = L"SELECT * FROM `" + tableName + L"`";

  LPCTSTR sqlQuerry = sqlQuerryString.c_str();

  MSIHANDLE tableView;
  UINT errorMessage = ::MsiDatabaseOpenView(databaseHandle, sqlQuerry, &tableView);
  if (errorMessage == ERROR_SUCCESS)
  {
    Table* tb = new Table(tableName, tableView);
    tables.push_back(tb);

    return tb;
  }
  else
  {
    return nullptr;
  }

}
