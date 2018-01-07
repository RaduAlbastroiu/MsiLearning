#pragma once
#include "stdafx.h"
#include "../MsiFramework/Database.h"
#include "../MsiFramework/OperationLogicCondition.h"

void selectUpdate(MSIHANDLE /*handleTest*/) {
  
  //UINT errorMessage = ERROR_SUCCESS;
  //
  //// Open View
  //MSIHANDLE phView;
  //LPCTSTR sqlQuerry = L"SELECT `Text` FROM `Control` WHERE `Dialog_`='WelcomeDlg' AND `X`= 135 ";
  //errorMessage = ::MsiDatabaseOpenView(handleTest, sqlQuerry, &phView);
  //if (errorMessage == ERROR_SUCCESS)
  //  cout << " \n YEE";
  //
  //// create record
  //MSIHANDLE emptyRecord = ::MsiCreateRecord(2);
  //if (emptyRecord != NULL)
  //  cout << " \n Record Created";
  //
  //// execute view
  //errorMessage = ::MsiViewExecute(phView, NULL);
  //if (errorMessage == ERROR_SUCCESS)
  //  cout << "\n Msi view executed";
  //
  //
  //MSIHANDLE recordToColumn;
  //errorMessage = ::MsiViewGetColumnInfo(phView, MSICOLINFO_TYPES, &recordToColumn);
  //if (errorMessage == ERROR_SUCCESS)
  //  cout << " \n YEE";
  //
  //cout << "\n" << ::MsiRecordGetFieldCount(recordToColumn);
  //
  //// view fetch
  //DWORD stringLenght = 0;
  //MSIHANDLE phRecord;
  //errorMessage = ::MsiViewFetch(phView, &phRecord);
  //if (errorMessage == ERROR_SUCCESS)
  //  cout << "\n Fetch succeeded";
  //
  //
  //
  //// print the string
  //errorMessage = ::MsiRecordGetString(phRecord, 1, L"", &stringLenght);
  //if (errorMessage == ERROR_MORE_DATA)
  //  cout << "\n not enough memory";
  //
  //stringLenght++;
  //wchar_t stringResult[256];
  //::MsiRecordGetString(phRecord, 1, stringResult, &stringLenght);
  //wcout << L"\n " << stringResult;
  //stringLenght = 0;
  //
  //// modify the record
  //wchar_t newString[256] = L"{\\VerdanaBold13} SELECT then UPDATE";
  //errorMessage = MsiRecordSetString(phRecord, 1, newString);
  //if (errorMessage == ERROR_SUCCESS)
  //  cout << "\n string set";
  //
  //
  //
  //// print the string again
  //errorMessage = ::MsiRecordGetString(phRecord, 1, L"", &stringLenght);
  //if (errorMessage == ERROR_MORE_DATA)
  //  cout << "\n not enough memory";
  //
  //stringLenght++;
  //::MsiRecordGetString(phRecord, 1, stringResult, &stringLenght);
  //wcout << L"\n " << stringResult;
  //stringLenght = 0;
  //
  //
  //
  //// save the modify
  //errorMessage = ::MsiViewModify(phView, MSIMODIFY_REPLACE, phRecord);
  //if (errorMessage == ERROR_SUCCESS)
  //  wcout << L"\n view modified";
  //
  //errorMessage = ::MsiDatabaseCommit(handleTest);
  //if (errorMessage == ERROR_SUCCESS)
  //  wcout << L"\n committed";
  //
  //::MsiCloseHandle(handleTest);

}


void justUpdate(LPCTSTR msiPath)
{
  UINT errorMessage = ERROR_SUCCESS;
  
  MSIHANDLE handleTest;
  MsiUtil::openDatabase(msiPath, handleTest);

  // Open View
  MSIHANDLE phView;
  LPCTSTR sqlQuerry = L" SELECT `Control`, `Text`, `Type` FROM `Control` WHERE ( ( ( `Dialog_` = 'WelcomeDlg' ) ) )";
  errorMessage = MsiUtil::openView(handleTest, sqlQuerry, phView);

  MSIHANDLE recordNr1;
  MSIHANDLE recordNr2;
  MSIHANDLE recordNr3;
  MSIHANDLE recordNr4;
  MSIHANDLE recordNr5;
  wstring valueBefore;
  wstring valueAfter;

  // fetch selected table
  errorMessage = ::MsiViewExecute(phView, 0);
  errorMessage = ::MsiViewFetch(phView, &recordNr1);
  errorMessage = ::MsiViewFetch(phView, &recordNr2);
  errorMessage = ::MsiViewFetch(phView, &recordNr3);
  errorMessage = ::MsiViewFetch(phView, &recordNr4);
  errorMessage = ::MsiViewFetch(phView, &recordNr5);

  // doesn't work -> ERROR_FUNCTION_FAILED
  errorMessage = ::MsiRecordSetString(recordNr3, 2, L"0987654321");
  errorMessage = ::MsiViewModify(phView, MSIMODIFY_UPDATE, recordNr3);

  // update value process for recordNr3:
  // 1. fetch again to recordNr3z
  errorMessage = ::MsiViewExecute(phView, 0);
  errorMessage = ::MsiViewFetch(phView, &recordNr1);
  errorMessage = ::MsiViewFetch(phView, &recordNr2);
  errorMessage = ::MsiViewFetch(phView, &recordNr3);

  // 2. set record
  errorMessage = ::MsiRecordSetString(recordNr3, 2, L"1234567890");
  // 3. view modify
  errorMessage = ::MsiViewModify(phView, MSIMODIFY_UPDATE, recordNr3);
  // 4. database commit
  errorMessage = ::MsiDatabaseCommit(handleTest);

  

  //MSIHANDLE anotherRecordHandle;
  //errorMessage = ::MsiViewFetch(phView, &anotherRecordHandle);
  //errorMessage = ::MsiViewFetch(phView, &anotherRecordHandle);
  //errorMessage = ::MsiViewFetch(phView, &anotherRecordHandle);
  //
  //
  //errorMessage = MsiUtil::openView(handleTest, sqlQuerry, phView);
  //errorMessage = ::MsiViewExecute(phView, 0);
  //errorMessage = ::MsiViewFetch(phView, &recordHandle);
  //
  
  
  //errorMessage = ::MsiDatabaseCommit(handleTest);
  //
  //errorMessage = MsiUtil::openView(handleTest, sqlQuerry, phView);
  //
  //errorMessage = ::MsiViewExecute(phView, 0);
  //errorMessage = ::MsiViewFetch(phView, &recordHandle);
  //MsiUtil::getStringFromRecord(recordHandle, 2, value);


  wstring err;
  MsiUtil::getLastError(err);

  //vector<map<wstring, wstring>> resultMap;
  //MsiUtil::getSelectedTable(phView, vector<wstring>{L"Control", L"Text", L"Type"}, resultMap);

  //map<wstring, wstring> columns;
  //MsiUtil::getColumnsInfo(phView, columns);
  
  errorMessage = MsiUtil::commit(handleTest);
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
  auto database = Database(msiPath);
  //auto collection = Database(msiPath).addTable(L"Control")->addColumns("Text", "Dialog_")->addCondition(Equal(L"Type", L"Text").And(Equal(L"Control", L"Title")))->select();

  //auto x = Equal(L"Type", L"Text").And(NotEqual(L"Text", L"Dialog_")).Or(LessEqualThan(L"Text", L"Dialog_")).getCondition();
 
  // select
  //auto ele = database.inTable(L"Control")->withColumns(L"Text")->whereConditionIs(Equal(L"Dialog_", L"ProgressDlg"))->select();
  //ele->getRowWithNumber(0)->getElementFromColumn(L"Text")->update(L"new string 0");
  //ele->getRowWithNumber(1)->getElementFromColumn(L"Text")->update(L"new string 1");
  //ele->getRowWithNumber(2)->getElementFromColumn(L"Text")->update(L"new string 2");
  //ele->getRowWithNumber(3)->getElementFromColumn(L"Text")->update(L"new string 3");
  //ele->getRowWithNumber(4)->getElementFromColumn(L"Text")->update(L"new string 4");
  //ele->getRowWithNumber(5)->getElementFromColumn(L"Text")->update(L"new string 5");
  //t->update(L"Original string");

  auto folderDlgText = database.inTable(L"Control")->withColumns(L"Text")->whereConditionIs(Equal(L"Dialog_", L"FolderDlg"))->select();
  
  auto numberRows = folderDlgText->getNumberOfRows();
  for (auto it = 0; it < numberRows; it++)
  {
    auto initialString = folderDlgText->getRowWithNumber(it)->getElementFromColumn(L"Text")->getAsString();
    folderDlgText->getRowWithNumber(it)->getElementFromColumn(L"Text")->update(to_wstring(initialString.size()) + L" " + initialString);
  }

  //ele = database.inTable(L"Control")->withColumns(L"Control", L"X", L"Y", L"Text")->whereConditionIs(Equal(L"Dialog_", L"WelcomeDlg"))->select();
  //t = ele->getRowWithNumber(3)->getElementFromColumn(L"Text");

  wstring lastError = database.getLastError();


  //// update
  //auto updated3 = database.inTable(L"Condition")->whereConditionIs(Equal(L"Level", 11))->updateColumnWithValue(L"Condition", L"16")->update();
  //updated3;
  //
  //// insert 
  //auto ins = database.inTable(L"Condition")->insertInColumnWithValue(L"Feature_", L"1")->insertInColumnWithValue(L"Level", L"11")->insertInColumnWithValue(L"Condition", L"someValue")->insert();
  //ins;
  //
  //// insert 
  //auto ins2 = database.inTable(L"Condition")->insertInColumnWithValue(L"Feature_", L"1")->insertInColumnWithValue(L"Level", L"12")->insertInColumnWithValue(L"Condition", L"someValue")->insert();
  //ins2;
  //
  //// insert 
  //auto ins3 = database.inTable(L"Condition")->insertInColumnWithValue(L"Feature_", L"1")->insertInColumnWithValue(L"Level", L"13")->insertInColumnWithValue(L"Condition", L"someValue")->insert();
  //ins3;
  //
  //// delete
  //auto del = database.inTable(L"Condition")->whereConditionIs(Equal(L"Level", 13))->deleteRows();
  //del;
  
}
