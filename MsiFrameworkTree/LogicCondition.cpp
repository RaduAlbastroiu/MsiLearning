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

LogicCondition::LogicCondition(const wstring aSqlCondition)
  :sqlCondition(aSqlCondition)
{
}

LogicCondition LogicCondition::And(wstring target, vector<wstring>& expectedValues)
{
  sqlCondition += L" AND ";
  sqlCondition += composeSqlCondition(target, expectedValues);

  return LogicCondition(sqlCondition);
}

LogicCondition LogicCondition::And(LogicCondition aCondition)
{
  sqlCondition += L" AND ";
  sqlCondition += aCondition.getCondition();

  return LogicCondition(sqlCondition);
}

LogicCondition LogicCondition::Or(wstring target, vector<wstring>& expectedValues)
{
  sqlCondition += L" OR ";
  sqlCondition += composeSqlCondition(target, expectedValues);

  return LogicCondition(sqlCondition);
}

std::wstring LogicCondition::getCondition() const
{
  return sqlCondition;
}

std::wstring LogicCondition::composeSqlCondition(wstring target, vector<wstring>& expectedValues)
{
  wstring resultSqltCondition = L"( ";

  for (auto it = expectedValues.begin(); it != expectedValues.end(); it++)
  {
    if (it != expectedValues.begin())
      resultSqltCondition += L" OR ";

    resultSqltCondition += target + L" = " + *it;
  }

  resultSqltCondition = L" )";

  return resultSqltCondition;
}
