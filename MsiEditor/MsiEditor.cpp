// MsiEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "EngineMsi.h"


int main()
{
  // test driver for our MSI Framework (EXE)

  // path to msi
  LPCTSTR msiPath = L"E:\\MSI\\MsiTest\\Your Application-SetupFiles\\Your Application.msi";
  LPCTSTR pathExport = L"E:\\MSI\\MsiTest\\Your Application-SetupFiles";
  LPCTSTR afileName = L"somefile.txt";

  MSIHANDLE handleTest;

  UINT errorMessage = MsiOpenDatabase(msiPath, MSIDBOPEN_DIRECT, &handleTest);
  cout << handleTest;

  // start works
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n YEEE";

  LPCWSTR tableName = L"Dialog";
  MSIHANDLE primaryKeys;
  errorMessage = MsiDatabaseGetPrimaryKeys(handleTest, tableName, &primaryKeys);
  
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n Yeee \n";

  cout << MsiRecordGetFieldCount(primaryKeys);

  errorMessage = MsiDatabaseExport(handleTest, tableName, pathExport, afileName);

  if (errorMessage == ERROR_SUCCESS)
    cout << " \n perfect";

  cin >> handleTest;

  /*
  Framework::LoadFunc::loadTable(2);
  listAllTables();
  printSchemaTbl(2);
  printRowTbl(2, 1);
  Framework::AddFunc::addRowTbl(2, 1, L" some value ");
  Framework::UpdateFunc::updateColRowTbl(2, 1, 3, L" some value ");
  */


  return 0;


}

