#pragma once
class Database
{
private:
  LPCTSTR databasePath;
  MSIHANDLE databaseHandle;
  

  void saveDatabase();

public:
  Database(LPCTSTR aDatabasePath);

  ~Database();
};

