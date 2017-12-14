#pragma once
#include "stdafx.h"
#include "Node.h"

Node::Node(const DatabaseInfo& aDatabaseInfo, vector<unique_ptr<Node>> aNodeCollection)
  :databaseInfo(aDatabaseInfo), nodeCollection(move(aNodeCollection))
{
}

Node::Node(const wstring& databasePath)
{
  // init database Info
  // databaseInfo.openDatabase(databasepath);
}

std::unique_ptr<Node> Node::children(wstring condition)
{
  vector<unique_ptr<Node>> result;
  DatabaseInfo databaseInfoResult;
  for (const auto& node : nodeCollection)
  {
    unique_ptr<Node> resultNode = node->children(condition);
    if (resultNode)
    {
      result.push_back(move(resultNode));

      // combine database info
      databaseInfoResult;
    }
  }

  if (result.size())
  {
    return make_unique<Node>(databaseInfoResult, move(result));
  }
  else
  {
    return nullptr;
  }
}

bool Node::update(wstring newValue)
{
  return true;
}

bool Node::deleteThis()
{
  return true;
}

int Node::size()
{
  return 0;
}

void Node::joinStuff(unique_ptr<Node> aNodeProtocol)
{

}

std::unique_ptr<Node> Node::select()
{
  throw std::logic_error("The method or operation is not implemented.");
}

int Node::getInt()
{
  throw std::logic_error("The method or operation is not implemented.");
}

std::wstring Node::getWstring()
{
  throw std::logic_error("The method or operation is not implemented.");
}
