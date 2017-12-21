#include "stdafx.h"
#include "LogicCondition.h"

LogicCondition::LogicCondition(const LogicCondition& aSubCondition)
{
  mSqlCondition = L"( " + aSubCondition.getCondition() + L" )";
}

LogicCondition::LogicCondition(const wstring& aSqlCondition)
  :mSqlCondition(aSqlCondition)
{
}

LogicCondition LogicCondition::And(const LogicCondition& aCondition)
{
  mSqlCondition += L" AND ";
  mSqlCondition += aCondition.getCondition();

  return LogicCondition(mSqlCondition);
}

LogicCondition LogicCondition::Or(const LogicCondition& aCondition)
{
  mSqlCondition += L" OR ";
  mSqlCondition += aCondition.getCondition();

  return LogicCondition(mSqlCondition);
}

LogicCondition LogicCondition::Not(const LogicCondition& aCondition)
{
  mSqlCondition += L" NOT ";
  mSqlCondition += aCondition.getCondition();

  return LogicCondition(mSqlCondition);
}

std::wstring LogicCondition::getCondition() const
{
  return mSqlCondition;
}

std::wstring LogicCondition::composeSqlCondition(wstring target, wstring operation, wstring comparison, vector<wstring>& expectedValues)
{
  wstring resultSqltCondition = L"( ";

  for (auto it = expectedValues.begin(); it != expectedValues.end(); it++)
  {
    if (it != expectedValues.begin())
      resultSqltCondition += mListOperation;

    resultSqltCondition += target + mComparison + *it;
  }

  resultSqltCondition += L" )";

  return resultSqltCondition;
}
