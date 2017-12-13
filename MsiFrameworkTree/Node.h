#pragma once
#include "stdafx.h"
#include "NodeProtocol.h"
#include "DatabaseInfo.h"

class Node: public NodeProtocol {
public:

  Node(const DatabaseInfo& aDatabaseInfo);
  Node(const wstring& databasePath);

  unique_ptr<NodeProtocol> children(wstring condition) override;

  // select
  virtual unique_ptr<NodeProtocol> select();
  virtual unique_ptr<NodeProtocol> selectInt();
  virtual unique_ptr<NodeProtocol> selectWstring();

  // update
  bool update(wstring newValue) override;

  // delete
  bool deleteThis() override;

  int getInt() override;
  wstring getWstring() override;

  // unicorns
  virtual void joinStuff(unique_ptr<NodeProtocol> aNodeProtocol) override;

private:
  DatabaseInfo databaseInfo;

};
