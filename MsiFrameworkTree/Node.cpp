#pragma once
#include "stdafx.h"
#include "Node.h"

Node::Node(const DatabaseInfo& aDatabaseInfo)
  :databaseInfo(aDatabaseInfo)
{
}

Node::Node(const wstring& databasePath)
{
  // modify databaseInfo
}

bool Node::update(wstring newValue)
{


  return true;
}
