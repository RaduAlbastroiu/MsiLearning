#include "stdafx.h"
#include "Database.h"


Database::Database(LPCTSTR aDatabasePath)
  :databasePath(aDatabasePath)
{
  MsiOpenDatabase(databasePath, MSIDBOPEN_DIRECT, &databaseHandle);
}

Database::~Database()
{
  MsiCloseHandle(databaseHandle);
}

void Database::saveDatabase()
{
  MsiDatabaseCommit(databaseHandle);
}
