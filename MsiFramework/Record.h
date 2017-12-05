#pragma once
class Record
{
  const wstring tableName;
  const wstring columnName;

public:
  Record(wstring tableName, wstring columnName, vector<wstring> values);
  ~Record();

  vector<wstring> values;
};

