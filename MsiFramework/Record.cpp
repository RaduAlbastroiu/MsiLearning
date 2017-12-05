#include "stdafx.h"
#include "Record.h"


Record::Record(wstring tableName, wstring columnName, vector<wstring> values):
  tableName(tableName), columnName(columnName), values(values)
{
}

Record::~Record()
{
}
