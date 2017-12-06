#include "stdafx.h"
#include "Condition.h"

Condition::Condition(wstring aTargetColumn):
  mTargetColumn(aTargetColumn)
{
}

void Condition::addRequirements(wstring aTargetColumn, vector<wstring> aRequirements)
{
  mRequirements.push_back(Requirement(aTargetColumn, aRequirements));
}

wstring Condition::getTargetColumn()
{
  return mTargetColumn;
}

vector<Requirement> Condition::getAllRequirements()
{
  return mRequirements;
}
