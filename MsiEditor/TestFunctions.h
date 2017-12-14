#pragma once
#include "stdafx.h"
#include "../MsiFrameworkTree/Node.h"
#include "../MsiFrameworkTree/LogicCondition.h"


void selectUpdate(MSIHANDLE handleTest) {
  
  UINT errorMessage = ERROR_SUCCESS;

  // Open View
  MSIHANDLE phView;
  LPCTSTR sqlQuerry = L"SELECT `Text` FROM `Control` WHERE `Dialog_`='WelcomeDlg' AND `X`= 135 ";
  errorMessage = ::MsiDatabaseOpenView(handleTest, sqlQuerry, &phView);
  if (errorMessage == ERROR_SUCCESS)
    cout << " \n YEE";

  // create record
  MSIHANDLE emptyRecord = ::MsiCreateRecord(2);
  if (emptyRecord != NULL)
    cout << " \n Record Created";

  // execute view
  errorMessage = ::MsiViewExecute(phView, NULL);
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n Msi view executed";


  MSIHANDLE recordToColumn;
  errorMessage = ::MsiViewGetColumnInfo(phView, MSICOLINFO_TYPES, &recordToColumn);
  if (errorMessage == ERROR_SUCCESS)
    cout << " \n YEE";

  cout << "\n" << ::MsiRecordGetFieldCount(recordToColumn);

  // view fetch
  DWORD stringLenght = 0;
  MSIHANDLE phRecord;
  errorMessage = ::MsiViewFetch(phView, &phRecord);
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n Fetch succeeded";



  // print the string
  errorMessage = ::MsiRecordGetString(phRecord, 1, L"", &stringLenght);
  if (errorMessage == ERROR_MORE_DATA)
    cout << "\n not enough memory";

  stringLenght++;
  wchar_t stringResult[256];
  ::MsiRecordGetString(phRecord, 1, stringResult, &stringLenght);
  wcout << L"\n " << stringResult;
  stringLenght = 0;

  // modify the record
  wchar_t newString[256] = L"{\\VerdanaBold13} SELECT then UPDATE";
  errorMessage = MsiRecordSetString(phRecord, 1, newString);
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n string set";



  // print the string again
  errorMessage = ::MsiRecordGetString(phRecord, 1, L"", &stringLenght);
  if (errorMessage == ERROR_MORE_DATA)
    cout << "\n not enough memory";

  stringLenght++;
  ::MsiRecordGetString(phRecord, 1, stringResult, &stringLenght);
  wcout << L"\n " << stringResult;
  stringLenght = 0;



  // save the modify
  errorMessage = ::MsiViewModify(phView, MSIMODIFY_REPLACE, phRecord);
  if (errorMessage == ERROR_SUCCESS)
    wcout << L"\n view modified";

  errorMessage = ::MsiDatabaseCommit(handleTest);
  if (errorMessage == ERROR_SUCCESS)
    wcout << L"\n committed";

  ::MsiCloseHandle(handleTest);

}


void justUpdate(MSIHANDLE handleTest)
{
  UINT errorMessage = ERROR_SUCCESS;

  // Open View
  MSIHANDLE phView;
  LPCTSTR sqlQuerry = L"UPDATE `Control` SET `Text`=\'{\\VerdanaBold13} Just UPDATE\' WHERE `Dialog_`='WelcomeDlg' AND `X`= 135";
  errorMessage = ::MsiDatabaseOpenView(handleTest, sqlQuerry, &phView);
  if (errorMessage != ERROR_SUCCESS)
    return;

  cout << " \n Open view";

  if (ERROR_SUCCESS != ::MsiViewExecute(phView, 0))
    return;

  cout << "\n executed";


  errorMessage = ::MsiDatabaseCommit(handleTest);
  if (errorMessage == ERROR_SUCCESS)
    wcout << L"\n committed";

}

//void msiFramework(LPCTSTR msiPath)
//{
  //Database db = Database(msiPath);
  //
  //Table tb = db.getTable(L"Control");
  //Condition cd = Condition(L"Text");
  //cd.addRequirements(L"Dialog_", { L"WelcomeDlg", L"BLAH" });
  //cd.addRequirements(L"X", { L"135" });
  //
  //RecordCollection rd = tb.getRecordCollection(cd);
  //vector<SingleRecord> records = rd.getAllRecords();
  //records[0].setValue(L"new value");
//}


// very sweet in theory
void msiFrameworkTree(LPCTSTR msiPath)
{
  //Node database(msiPath);
  //auto value = database.children(L"Control")->children(L"Text")->size(); 
  //value++;

  LogicCondition(LogicCondition(L"Text", vector<wstring>{L"someString", L"anotherString"}).And(L"Dialog", vector<wstring>{L"someValue"}));

}

