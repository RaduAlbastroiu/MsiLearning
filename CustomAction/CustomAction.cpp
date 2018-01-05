// CustomAction.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../MsiFramework/Database.h"


// My CustAct #1
UINT WINAPI MeasureUIText(MSIHANDLE hSession)
{
  ::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);
  Database database(hSession);
  
  auto folderDlgText = database.inTable(L"Control")->withColumns(L"Text")->whereConditionIs(Equal(L"Dialog_", L"FolderDlg"))->select();

  auto numberRows = folderDlgText->getNumberOfRows();
  for (auto it = 1; it <= numberRows; it++)
  {
    auto initialString = folderDlgText->getRowWithNumber(it)->getElementFromColumn(L"Text")->getAsString();
    folderDlgText->getRowWithNumber(it)->getElementFromColumn(L"Text")->update(to_wstring(initialString.size()) + L" " + initialString);
  }

  return ERROR_SUCCESS;
}


// My CustAct #2
UINT WINAPI PopulateCombo(MSIHANDLE hSession)
{
  hSession;
  return ERROR_SUCCESS;
}

