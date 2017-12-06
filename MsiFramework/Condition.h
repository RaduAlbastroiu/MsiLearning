#pragma once

#include "RecordCollection.h"
#include "Requirement.h"

class Condition
{
  wstring mTargetColumn;
  vector<Requirement> mRequirements;

public:
  Condition(wstring aTargetColumn);

  void addRequirements(wstring aRequiredColumn, vector<wstring> aRequirementValues);
  
  wstring getTargetColumn();
  vector<Requirement> getAllRequirements();
};
