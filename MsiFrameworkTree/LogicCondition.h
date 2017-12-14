#pragma once
#include "stdafx.h"

class LogicCondition
{
public:
  LogicCondition(wstring target, vector<wstring>& expectedValues);
  LogicCondition(const LogicCondition& aSubCondition);
  LogicCondition(const wstring aSqlCondition);
  
  LogicCondition And(wstring target, vector<wstring>& expectedValues);
  LogicCondition And(LogicCondition aCondition);
  LogicCondition Or(wstring target, vector<wstring>& expectedValues);

  wstring getCondition() const;

private:
  wstring sqlCondition;

  // target and expected values must become another class
  wstring composeSqlCondition(wstring target, vector<wstring>& expectedValues);
};
