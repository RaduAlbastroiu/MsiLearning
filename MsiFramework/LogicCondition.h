#pragma once
#include "stdafx.h"

class LogicCondition
{
public:
  // override operators
  // variadic arg list

  template<typename... Types>
  LogicCondition(const wstring& target, const wstring& expectedValue, const Types& ... expectedValues)
    :mTarget(target), mExpectedValues{ expectedValue, expectedValues... }
  {
  }

  LogicCondition(const LogicCondition& aSubCondition);
  LogicCondition(const wstring& aSqlCondition);
  
  LogicCondition And(const LogicCondition& aCondition);
  LogicCondition Or(const LogicCondition& aCondition);
  LogicCondition Not(const LogicCondition& aCondition);

  wstring getCondition() const;
  
protected:
  
  wstring mSqlCondition;

  // default values
  wstring mListOperation = L" OR ";
  wstring mComparison = L" = ";
  wstring mTarget = L"";
  
  vector<wstring> mExpectedValues;

  // target and expected values must become another class
  wstring composeSqlCondition(wstring target, wstring operation, wstring comparison, vector<wstring>& expectedValues);
};
