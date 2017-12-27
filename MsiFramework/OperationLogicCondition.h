#pragma once
#include "stdafx.h"
#include "LogicCondition.h"


// operators && || == !=


class AnyOf : public LogicCondition
{
public:
  // string
  template<typename... Types>
  AnyOf(const wstring& target, const wstring& expectedValue, const Types& ... expectedValues)
    :LogicCondition(target, expectedValue, expectedValues...)
  {
    mListOperation = L" OR ";
    mComparison = L" = ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }

  // integer
  template<typename... Types>
  AnyOf(const wstring& target, const int expectedValue, const Types& ... expectedValues)
    :LogicCondition(target, expectedValue, expectedValues...)
  {
    mListOperation = L" OR ";
    mComparison = L" = ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class NoneOf : public LogicCondition
{
public:
  // string
  template<typename... Types>
  NoneOf(const wstring& target, const wstring& expectedValue, const Types& ... expectedValues)
    :LogicCondition(target, expectedValue, expectedValues...)
  {
    mListOperation = L" AND ";
    mComparison = L" <> ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }

  // int
  template<typename... Types>
  NoneOf(const wstring& target, const int expectedValue, const Types& ... expectedValues)
    :LogicCondition(target, expectedValue, expectedValues...)
  {
    mListOperation = L" AND ";
    mComparison = L" <> ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class Equal : public LogicCondition
{
public:
  // string 
  Equal(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" = ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }

  // integer
  Equal(const wstring& target, const int expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" = ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class NotEqual : public LogicCondition
{
public:
  // string
  NotEqual(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" <> ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }

  // integer
  NotEqual(const wstring& target, const int expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" <> ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class LessThan : public LogicCondition
{
public:
  // string
  LessThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" < ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }

  // int
  LessThan(const wstring& target, const int expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" < ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class LessEqualThan : public LogicCondition
{
public:
  // string
  LessEqualThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" <= ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }

  // int
  LessEqualThan(const wstring& target, const int expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" <= ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class GreaterThan : public LogicCondition
{
public:
  // string
  GreaterThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" > ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }

  // int
  GreaterThan(const wstring& target, const int expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" > ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};

class GreaterEqualThan : public LogicCondition
{
public:
  // string
  GreaterEqualThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" >= ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }

  // int
  GreaterEqualThan(const wstring& target, const int expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" >= ";
    mSqlCondition = composeSqlCondition(target, mListOperation, mComparison, mExpectedValues);
  }
};
