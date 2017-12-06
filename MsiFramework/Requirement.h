#pragma once
class Requirement
{
  const wstring mTargetColumn;
  vector<wstring> mValues;

public:
  Requirement(const wstring aTargetColumn, const vector<wstring>& aValue);
  Requirement(const wstring aTargetColumn);

  void addRequirement(wstring& aValue);
  int getNrRequirements();

  vector<wstring> getAllValues() const;
  wstring getTargetColumn() const;

};

