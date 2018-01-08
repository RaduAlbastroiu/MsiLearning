#pragma once
#include "stdafx.h"
#include "../MsiFramework/Database.h"
#include "../MsiFramework/OperationLogicCondition.h"

void testFunction(LPCTSTR msiPath)
{
  UINT errorMessage = ERROR_SUCCESS;
//  MSIHANDLE hDatabase;
  //MsiUtil::openDatabase(msiPath, hDatabase);

  //errorMessage = MsiUtil::runSqlQuerryCommit(hDatabase, L"SELECT * FROM `Control` ORDER BY `Control` ");

  Database database(msiPath);

  errorMessage = database.inTable(L"Control")->withColumns()->orderByAsc(L"Dialog_")->orderByAsc(L"Control")->order();
  auto t = database.inTable(L"Control")->withColumns(L"Control")->select();

  auto s = t->getRowWithNumber(0)->getElementFromColumn(L"Control")->getAsString();
 

  wstring err;
  MsiUtil::getLastError(err);

}

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

//void orderAtoZ(LPCTSTR msiPath)
//{
//  Database database(msiPath);
//
//  errorMessage = database.inTable(L"Control")->withColumns()->orderByAsc(L"Dialog_")->orderByAsc(L"Control")->order();
//  auto t = database.inTable(L"Control")->withColumns(L"Control")->select();
//
//}
