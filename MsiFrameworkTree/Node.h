#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"
#include "LogicCondition.h"

class Node {
protected:
//  Node(const wstring& databasePath);
//  Node(const DatabaseInfo& aDatabaseInfo);
//
//  // Needs support for adding conditions at different steps
//  unique_ptr<Node> addConditionDbInfo(LogicCondition aCondition);
//  
//  // add a table
//  unique_ptr<Node> addTableDbInfo(const wstring& aTableName);
//
//  // add columns for the table already added
//  template<typename... Types>
//  unique_ptr<Node> addColumnsDbInfo( const Types& ... aColumns)
//  {
//    mDatabaseInfo.addTableWithColumns(aTableName, aColumns...);
//  }
//
//  unique_ptr<Node> selectDbInfo();
//
//  // NOT IMPLEMENTED
//  vector<wstring> getColumnDbInfo(const wstring& aColumnName);
//  vector<vector<wstring>> getAllDbInfo();

  // data
  DatabaseInfo mDatabaseInfo;

};
