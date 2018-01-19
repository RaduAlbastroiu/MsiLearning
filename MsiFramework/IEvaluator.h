#pragma once
#include "Row.h"

// interface
class IEvaluator 
{
public:

  virtual bool evaluate(Row& aRow) = 0;

};

class AlwaysTrueEvaluator : public IEvaluator
{
public:

  bool evaluate(Row& /*aRow*/) override { return true; }

};
