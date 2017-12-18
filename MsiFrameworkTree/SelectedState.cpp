#pragma once
#include "stdafx.h"
#include "SelectedState.h"


SelectedState::SelectedState(const DatabaseInfo & aDatabaseInfo)
  :Node(aDatabaseInfo)
{
}

vector<wstring> SelectedState::getColumn(const wstring & aColumnName)
{
  // call databaseINFO
}

vector<vector<wstring>> SelectedState::getAll()
{
  // call databaseINFO
}

