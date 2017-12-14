#include "stdafx.h"
#include "LogicCondition.h"

LogicCondition::LogicCondition(wstring target, vector<wstring>& expectedValues)
{
  composeSqlCondition(target, expectedValues);
}

LogicCondition::LogicCondition(const LogicCondition& aSubCondition)
{
  sqlCondition = L"( " + aSubCondition.getCondition() + L" )";
}

LogicCondition LogicCondition::And(wstring target, vector<wstring>& expectedValues)
{
  sqlCondition += L" AND ";
  sqlCondition += composeSqlCondition(target, expectedValues);
}

LogicCondition LogicCondition::Or(wstring target, vector<wstring>& expectedValues)
{
  sqlCondition += L" OR ";
  sqlCondition += composeSqlCondition(target, expectedValues);
}

std::wstring LogicCondition::getCondition() const
{
  return sqlCondition;
}

std::wstring LogicCondition::composeSqlCondition(wstring target, vector<wstring>& expectedValues)
{
  sqlCondition = L"( ";

  for (auto it = expectedValues.begin(); it != expectedValues.end(); it++)
  {
    if (it != expectedValues.begin())
      sqlCondition += L" OR ";

    sqlCondition += target + L" = " + *it;
  }

  sqlCondition = L" )";
}
