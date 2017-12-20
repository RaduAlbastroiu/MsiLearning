#pragma once
#include "stdafx.h"
#include "LogicCondition.h"


// operators && || == !=


class AnyOf : public LogicCondition
{
public:
  template<typename... Types>
  AnyOf(const wstring& target, const wstring& expectedValue, const Types& ... expectedValues)
    :LogicCondition(target, expectedValue, expectedValue...)
  {
    mListOperation = L" OR ";
    mComparison = L" = ";
  }
};

class NoneOf : public LogicCondition
{
public:
  template<typename... Types>
  NoneOf(const wstring& target, const wstring& expectedValue, const Types& ... expectedValues)
    :LogicCondition(target, expectedValue, expectedValue...)
  {
    mListOperation = L" AND ";
    mComparison = L" <> ";
  }
};

class Equal : public LogicCondition
{
public:
  Equal(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" = ";
  }
};

class NotEqual : public LogicCondition
{
public:
  NotEqual(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" <> ";
  }
};

class LessThan : public LogicCondition
{
public:
  LessThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" < ";
  }
};

class LessEqualThan : public LogicCondition
{
public:
  LessEqualThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" <= ";
  }
};

class GreaterThan : public LogicCondition
{
public:
  GreaterThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" > ";
  }
};

class GreaterEqualThan : public LogicCondition
{
public:
  GreaterEqualThan(const wstring& target, const wstring& expectedValue)
    :LogicCondition(target, expectedValue)
  {
    mComparison = L" >= ";
  }
};
