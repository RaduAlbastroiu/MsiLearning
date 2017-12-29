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
  LPCTSTR sqlQuerry = L" SELECT `Control`, `Text` FROM `Control` WHERE ( ( ( `Dialog_` = 'WelcomeDlg' ) ) )";
  MsiUtil::openView(handleTest, sqlQuerry, phView);

  vector<map<wstring, wstring>> resultMap;
  MsiUtil::getSelectedTable(phView, vector<wstring>{L"Control", L"Text"}, resultMap);

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
  auto row = database.inTable(L"Control")->withColumns(L"Control", L"X")->whereConditionIs(Equal(L"Dialog_", L"WelcomeDlg"))->select();
  row;

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
