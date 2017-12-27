#pragma once
#include "stdafx.h"

class LogicCondition
{
public:
  // override operators
  // variadic arg list

  // for strings
  template<typename... Types>
  LogicCondition(const wstring& target, const wstring& expectedValue, const Types& ... expectedValues)
    :mTarget(target)
  {
    vector<wstring> temp = { expectedValue, expectedValues... };
    std::transform(temp.begin(), temp.end(), back_inserter(mExpectedValues), 
                   [](auto element) { return L"'" + element + L"'"; });
  }

  // for integers
  template<typename... Types>
  LogicCondition(const wstring& target, const int expectedValue, const Types& ... expectedValues)
    :mTarget(target)
  {
    vector<int> temp = {expectedValue, expectedValues...};
    std::transform(temp.begin(), temp.end(), back_inserter(mExpectedValues), 
                   [](auto element) { return to_wstring(element); });
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
