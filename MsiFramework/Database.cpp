#include "stdafx.h"
#include "Database.h"


Database::Database(wstring aDatabasePath):
  mDatabasePath(aDatabasePath.c_str())
{
  MsiOpenDatabase(mDatabasePath, MSIDBOPEN_DIRECT, &mDatabaseHandle);
}

Database::~Database()
{
  // commit
  ::MsiDatabaseCommit(mDatabaseHandle);

  // free handle
  ::MsiCloseHandle(mDatabaseHandle);
}

void Database::saveDatabase()
{
  MsiDatabaseCommit(mDatabaseHandle);
}

Table Database::getTable(wstring tableName)
{
  wstring sqlQuerryString = L"SELECT * FROM `" + tableName + L"`";

  LPCTSTR sqlQuerry = sqlQuerryString.c_str();

  MSIHANDLE tableView;
  UINT errorMessage = ::MsiDatabaseOpenView(mDatabaseHandle, sqlQuerry, &tableView);
  if (errorMessage == ERROR_SUCCESS)
  {
    // everything is good
    ;
  }

  Table tb = Table(tableName, tableView, mDatabaseHandle);
  tables.push_back(tb);

  return tb;

}
