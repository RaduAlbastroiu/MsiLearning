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

