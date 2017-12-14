#pragma once
#include "stdafx.h"

class LogicCondition
{
public:
  LogicCondition(wstring target, vector<wstring>& expectedValues);
  LogicCondition(const LogicCondition& aSubCondition);
  
  LogicCondition And(wstring target, vector<wstring>& expectedValues);
  LogicCondition Or(wstring target, vector<wstring>& expectedValues);

  wstring getCondition() const;

private:
  wstring sqlCondition;

  wstring composeSqlCondition(wstring target, vector<wstring>& expectedValues);
};
