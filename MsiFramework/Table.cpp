#include "stdafx.h"
#include "Table.h"

Table::Table(wstring aTableName, MSIHANDLE aTableView):
  tableView(aTableView), tableName(aTableName)
{
}

Table::~Table()
{
  for (auto record : records)
  {
    delete(record);
  }
}

void Table::saveTable()
{
  for (auto record : records)
  {
    record->saveRecord();
  }
}

Record Table::getRecord(Condition aCondition)
{
  return Record();
}

void Table::setRecord(Record aRecord)
{

}
