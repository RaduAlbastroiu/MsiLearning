// CustomAction.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CustActUtil.h"
#include "../MsiFramework/Database.h"

// My CustAct #Test
UINT WINAPI TestCustAct(MSIHANDLE hSession)
{
  ::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);
  
  // too much work for an insert
  auto database = Database(hSession);
  auto t = database.inTable(L"Control")->insertInColumnWithValue(L"Dialog_", L"FolderDlg");
  t = t->insertInColumnWithValue(L"Control", L"Something");
  t = t->insertInColumnWithValue(L"Attributes", L"3");
  t = t->insertInColumnWithValue(L"Type", L"PushButton");
  t = t->insertInColumnWithValue(L"X", L"100");
  t = t->insertInColumnWithValue(L"Y", L"100");
  t = t->insertInColumnWithValue(L"Width", L"100");
  t = t->insertInColumnWithValue(L"Height", L"100");
  t = t->insertInColumnWithValue(L"Text", L"SOME RANDOM TEXT");
  t->insert();

  auto t2 = database.inTable(L"Control")->insertInColumnWithValue(L"Dialog_", L"FolderDlg");
  t2 = t2->insertInColumnWithValue(L"Control", L"Something2");
  t2 = t2->insertInColumnWithValue(L"Attributes", L"3");
  t2 = t2->insertInColumnWithValue(L"Type", L"PushButton");
  t2 = t2->insertInColumnWithValue(L"X", L"120");
  t2 = t2->insertInColumnWithValue(L"Y", L"120");
  t2 = t2->insertInColumnWithValue(L"Width", L"100");
  t2 = t2->insertInColumnWithValue(L"Height", L"100");
  t2 = t2->insertInColumnWithValue(L"Text", L"SOME OTHER RANDOM TEXT");
  t2->insert();


  // delete
  auto d = database.inTable(L"Control")->whereConditionIs(Equal(L"Dialog_", L"FolderDlg"))->whereConditionIs(Equal(L"Control", L"Something"))->deleteRows();
  d;
  return ERROR_SUCCESS;
}

// My CustAct #1
UINT WINAPI MeasureUIText(MSIHANDLE hSession)
{
  Database database(hSession);

  // optimize property search

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

UINT WINAPI PopulateComboboxDialogNames(MSIHANDLE hSession)
{
  Database database(hSession);

  // get all dialog names
  vector<wstring> dialogNames;
  auto table = database.inTable(L"Dialog")->withColumns(L"Dialog")->select();
  if (table)
  {
    int nrRows = table->getNumberOfRows();
    for (int i = 0; i < nrRows; i++)
    {
      dialogNames.push_back(table->getRowWithNumber(i)->getElementFromColumn(L"Dialog")->getAsString());
    }
  }

  // populate combobox
  int i = 0;
  for (const auto& dialogName : dialogNames)
  {
    auto inserter = database.inTable(L"ComboBox")->insertInColumnWithValue(L"Property", L"COMBOBOX_1_PROP");
    inserter = inserter->insertInColumnWithValue(L"Order", to_wstring(++i));
    inserter = inserter->insertInColumnWithValue(L"Value", dialogName);
    inserter = inserter->insertInColumnWithValue(L"Text", dialogName);
    inserter->insert();
  }

  return ERROR_SUCCESS;
}

// My CustAct #2
UINT WINAPI PopulateListBoxAtoZ(MSIHANDLE hSession)
{
  //::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);
  
  Database database(hSession);

  // delete elements from listbox
  database.inTable(L"ListBox")->whereConditionIs(Equal(L"Property", L"LISTBOX_1_PROP"))->deleteRows();

  // populate listbox
  wstring chosenDialog = database.getValueFromProperty(L"COMBOBOX_1_PROP");
  if (chosenDialog.size())
  {
    auto controlTable = database.inTable(L"Control")->withColumns(L"Control", L"Type")->whereConditionIs(Equal(L"Dialog_", chosenDialog))->orderByAsc(L"Control")->select();
    int nrRows = controlTable->getNumberOfRows();
    for (int i = 0; i < nrRows; i++)
    {
      auto row = controlTable->getRowWithNumber(i);
      wstring value = L"Control: " + row->getElementFromColumn(L"Control")->getAsString();// +L", Type: " + row->getElementFromColumn(L"Type")->getAsString();
      
      // insert 
      auto inserter = database.inTable(L"ListBox")->insertInColumnWithValue(L"Property", L"LISTBOX_1_PROP");
      inserter = inserter->insertInColumnWithValue(L"Order", to_wstring(i + 1));
      inserter = inserter->insertInColumnWithValue(L"Value", value);
      inserter = inserter->insertInColumnWithValue(L"Text", value);
      inserter->insert();
    }
  }
  else
  {
    return 1;
  }

  return ERROR_SUCCESS;
}

UINT WINAPI PopulateListBoxTabOrder(MSIHANDLE hSession)
{
  hSession;
  return ERROR_SUCCESS;
}
