#pragma once

#include "Record.h"

class Condition
{
  wstring targetColumn;
  vector<pair<> requirements;

public:
  Condition(wstring aTargetColumn);
  ~Condition();

  void saveCondition();

  void addRequirements(Record aRequirement);
};

