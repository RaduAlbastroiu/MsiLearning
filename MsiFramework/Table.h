#pragma once

#include "Condition.h"
#include "Record.h"

class Table
{
  MSIHANDLE tableView;
  wstring tableName;
  vector<Record*> records;

public:
  Table(wstring aTableName, MSIHANDLE aTableView);
  ~Table();

  void saveTable();

  Record getRecord(Condition aCondition);
  void setRecord(Record aRecord);
};

