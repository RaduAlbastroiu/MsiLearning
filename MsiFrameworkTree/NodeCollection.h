#pragma once
#include "stdafx.h"
#include "NodeProtocol.h"
#include "Node.h"
#include "DatabaseInfo.h"

/*
class NodeCollection: public NodeProtocol {
public:

  NodeCollection(const DatabaseInfo& aDatabaseInfo, vector<unique_ptr<NodeProtocol>> aNodeCollection);
  
  virtual unique_ptr<NodeProtocol> children(wstring condition);

  virtual bool update(wstring newValue) override;
  virtual bool deleteThis() override;

  virtual void size();

  virtual unique_ptr<NodeProtocol> select() override;

  virtual int getInt() override;
  virtual wstring getWstring() override;

  // unicorns
  virtual void joinStuff(unique_ptr<NodeProtocol> aNodeProtocol) override;

private:
  // data
  DatabaseInfo databaseInfo;
  vector<unique_ptr<NodeProtocol>> nodeCollection;

};
*/
