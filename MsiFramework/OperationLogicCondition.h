#pragma once
#include "stdafx.h"
#include "LogicCondition.h"


// operators && || == !=


class AnyOf : public LogicCondition
{
public:
  template<typename... Types>
  AnyOf(const wstring& target, const wstring& expectedValue, const Types& ... expectedValues)
    :mListOperation(L" OR "), mComparison(L" = "), LogicCondition(target, expectedValue, expectedValue...)
  {
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class NoneOf : public LogicCondition
{
public:
  template<typename... Types>
  NoneOf(const wstring& target, const wstring& expectedValue, const Types& ... expectedValues)
    :mListOperation(L" AND "), mComparison(L" <> "), LogicCondition(target, expectedValue, expectedValue...)
  {
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class Equal : public LogicCondition
{
public:
  Equal(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" = ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class NotEqual : public LogicCondition
{
public:
  NotEqual(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" <> ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class LessThan : public LogicCondition
{
public:
  LessThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" < ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class LessEqualThan : public LogicCondition
{
public:
  LessEqualThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" <= ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class GreaterThan : public LogicCondition
{
public:
  GreaterThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" > ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class GreaterEqualThan : public LogicCondition
{
public:
  GreaterEqualThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" >= ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};
