#pragma once

// entry point in framework
namespace Framework
{
  namespace PrintFunc
  {
    listAllTables();
    printSchemaTbl(int aTable);
    printRowTbl(int aTable, int aRow);
  }

  namespace LoadFunc
  {
    loadTable(int aTable);
  }

  namespace AddFunc
  {
    addRowTbl(int aTable, int aRow, wstring aValue);
  }

  namespace UpdateFunc
  {
    updateColRowTbl(int aTable, int aRow, int aCol, wstring aValue);
  }

  namespace RemoveFunc
  {

  }
}
