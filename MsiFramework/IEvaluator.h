#pragma once
#include "Row.h"
#include "Database.h"

// interface
class IEvaluator 
{
public:
  
  bool virtual operator()(Row& aRow) = 0;
 
};

class AlwaysTrueEvaluator : public IEvaluator
{
public:

  bool virtual operator()(Row& /*aRow*/) override { return true; }

};

class InstallComponentEvaluator : public IEvaluator
{
public:

  InstallComponentEvaluator(Database& aDatabase) :mDatabase(aDatabase) {}

  bool virtual operator()(Row& aRow) override;
  
private:
  Database mDatabase;

};

class EvaluateCondition : public IEvaluator
{
public:
  EvaluateCondition(MSIHANDLE& hInstall, wstring& aCondition) : hInstall(hInstall), mCondition(aCondition.c_str()) {}

  bool virtual operator()(Row& aRow) override;

private:
  MSIHANDLE hInstall;
  LPCTSTR mCondition;
};
