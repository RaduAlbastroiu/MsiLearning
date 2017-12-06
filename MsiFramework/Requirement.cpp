#include "stdafx.h"
#include "Requirement.h"

Requirement::Requirement(const wstring aTargetColumn, const vector<wstring>& aValue) :
  mTargetColumn(aTargetColumn), mValues(aValue)
{
}

Requirement::Requirement(const wstring aTargetColumn) :
  mTargetColumn(aTargetColumn)
{
}

void Requirement::addRequirement(wstring & aValue)
{
  mValues.push_back(aValue);
}

int Requirement::getNrRequirements()
{
  return mValues.size();
}

vector<wstring> Requirement::getAllValues() const
{
  return mValues;
}

wstring Requirement::getTargetColumn() const
{
  return mTargetColumn;
}
