#include "stdafx.h"
#include "Table.h"



Table::Table(wstring aTableName, MSIHANDLE aTableView, MSIHANDLE aDatabaseHandle) :
  mTableView(aTableView), mTableName(aTableName), mDatabaseHandle(aDatabaseHandle)
{
}

Table::~Table()
{
  ::MsiCloseHandle(mTableView);
}

wstring Table::composeSqlQuerry(Condition aCondition)
{
  wstring sqlQuerry = L"SELECT `";

  // add target column
  sqlQuerry += aCondition.getTargetColumn() + L"`";

  // add table name
  sqlQuerry += L" FROM `" + mTableName + L"`";

  // add requirements
  auto requirements = aCondition.getAllRequirements();

  bool neeedAND = false;
  if (requirements.size())
  {
    // WHERE
    sqlQuerry += L" WHERE ";
    for (const auto& localRequirement : requirements)
    {
      if (neeedAND)
      {
        sqlQuerry += L" AND ";
        neeedAND = true;
      }

      sqlQuerry += L"( ";

      bool needOR = false;
      auto values = localRequirement.getAllValues();
      for (const auto& value : values)
      {
        if (needOR)
        {
          sqlQuerry += L" OR ";
          needOR = true;
        }

        sqlQuerry += L"`" + localRequirement.getTargetColumn() + L"`=`" + value + L"`";

      }

      sqlQuerry += L" )";
    }
  }

  return sqlQuerry;
}

Record Table::getRecord(Condition aCondition, bool& succeded)
{
  LPCTSTR sqlQuerry = composeSqlQuerry(aCondition).c_str();

  MSIHANDLE recordHandle;
  UINT errorMessage = ::MsiDatabaseOpenView(mDatabaseHandle, sqlQuerry, &recordHandle);

  if (errorMessage == ERROR_SUCCESS)
  {
    succeded = true;
  }
  else
  {
    succeded = false;
  }

  return Record(recordHandle, mTableName, aCondition.getTargetColumn());
}
