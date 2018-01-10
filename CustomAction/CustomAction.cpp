// CustomAction.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CustActUtil.h"
#include "../MsiFramework/Database.h"

// My CustAct #Test
UINT WINAPI TestCustAct(MSIHANDLE hSession)
{
  ::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);
  
  // works
  //MSIHANDLE hActiveDatabase = ::MsiGetActiveDatabase(hSession);
  //wstring selectQuery = L"SELECT * FROM Control";
  //MSIHANDLE hView;
  //UINT err = ::MsiDatabaseOpenView(hActiveDatabase, selectQuery.c_str(), &hView);
  //err = ::MsiViewExecute(hView, 0);
  //MSIHANDLE hExtract;
  //err = ::MsiViewFetch(hView, &hExtract);
  //
  //wstring folderDlg = L"FolderDLg";
  //wstring control = L"blahhhh";
  //
  //err = ::MsiRecordSetString(hExtract, 1, folderDlg.c_str());
  //err = ::MsiRecordSetString(hExtract, 2, control.c_str());
  //
  //err = ::MsiViewModify(hView, MSIMODIFY_INSERT_TEMPORARY, hExtract);

  auto t = Database(hSession).inTable(L"Control")->insertInColumnWithValue(L"Dialog_", L"FolderDlg");
  t = t->insertInColumnWithValue(L"Control", L"Something");
  t = t->insertInColumnWithValue(L"Attributes", L"3");
  t = t->insertInColumnWithValue(L"Type", L"PushButton");
  t = t->insertInColumnWithValue(L"X", L"100");
  t = t->insertInColumnWithValue(L"Y", L"100");
  t = t->insertInColumnWithValue(L"Width", L"100");
  t = t->insertInColumnWithValue(L"Height", L"100");
  t = t->insertInColumnWithValue(L"Text", L"SOME RANDOM TEXT");
  t->insert();

  return ERROR_SUCCESS;
}

// My CustAct #1
UINT WINAPI MeasureUIText(MSIHANDLE hSession)
{
  Database database(hSession);

  // select table
  auto folderDlgText = database.inTable(L"Control")->withColumns(L"Text")->whereConditionIs(Equal(L"Dialog_", L"FolderDlg"))->orderByAsc(L"Control")->select();
  
  auto numberRows = folderDlgText->getNumberOfRows();
  for (auto it = 0; it < numberRows; it++)
  {
    // get element
    auto e = folderDlgText->getRowWithNumber(it)->getElementFromColumn(L"Text");
    
    auto initialString = e->getAsString();

    // put value insted of property
    initialString = CustActUtil::getStringWithProperties(database, initialString);

    // nr chars after ignoring some types of sequences
    UINT nrChars = CustActUtil::getNrCharDisplayed(initialString);

    // update value
    e->update(to_wstring(nrChars) + L" " + initialString);
  }

  return ERROR_SUCCESS;
}

// My CustAct #2
UINT WINAPI PopulateCombo(MSIHANDLE hSession)
{
  hSession;
  return ERROR_SUCCESS;
}

