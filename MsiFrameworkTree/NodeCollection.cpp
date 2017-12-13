#pragma once
#include "stdafx.h"
#include "NodeCollection.h"

NodeCollection::NodeCollection(const DatabaseInfo& aDatabaseInfo, vector<unique_ptr<NodeProtocol>> aNodeCollection)
  :databaseInfo(aDatabaseInfo), nodeCollection(move(aNodeCollection))
{
}

std::unique_ptr<NodeProtocol> NodeCollection::children(wstring condition)
{
  vector<unique_ptr<NodeProtocol>> result;
  DatabaseInfo databaseInfoResult;
  for (const auto& node : nodeCollection)
  {
    unique_ptr<NodeProtocol> resultNode = node->children(condition);
    if (resultNode)
    {
      result.push_back(move(resultNode));

      // combine database info
      databaseInfoResult;
    }
  }

  if (result.size())
  {
    if (result.size() > 1)
    {
      return make_unique<NodeCollection>(databaseInfoResult, move(result));
    }
    else
    {
      return make_unique<Node>(databaseInfoResult);
    }
  }
  else
  {
    return nullptr;
  }
}

bool NodeCollection::update(wstring newValue)
{

}

bool NodeCollection::deleteThis()
{

}

void NodeCollection::size()
{

}

void NodeCollection::joinStuff(unique_ptr<NodeProtocol> aNodeProtocol)
{

}

std::unique_ptr<NodeProtocol> NodeCollection::select()
{
  throw std::logic_error("The method or operation is not implemented.");
}

int NodeCollection::getInt()
{
  throw std::logic_error("The method or operation is not implemented.");
}

std::wstring NodeCollection::getWstring()
{
  throw std::logic_error("The method or operation is not implemented.");
}
