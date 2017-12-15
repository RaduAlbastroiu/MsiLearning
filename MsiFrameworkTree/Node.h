#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"
#include "LogicCondition.h"

class Node {
public:

  Node(const wstring& databasePath);
  Node(const DatabaseInfo& aDatabaseInfo, vector<unique_ptr<Node>> aNodeCollection);
  
  // deleted copy constructor
  Node(const Node& something) = delete;

  virtual unique_ptr<Node> children(wstring aCondition);
  virtual unique_ptr<Node> children(LogicCondition aCondition);

  virtual bool update(wstring newValue);
  virtual bool deleteThis();

  virtual int size();

  virtual unique_ptr<Node> select();

  virtual int getInt();
  virtual wstring getWstring();
  vector<wstring> getAllRecords();

  // unicorns
  virtual void joinStuff(unique_ptr<Node> aNodeProtocol);

private:
  // data
  DatabaseInfo mDatabaseInfo;
  vector<unique_ptr<Node>> mNodeCollection;

};
