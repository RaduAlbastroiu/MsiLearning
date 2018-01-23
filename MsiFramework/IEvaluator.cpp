#include "stdafx.h"
#include "IEvaluator.h"
#include "Database.h"

bool InstallComponentEvaluator::operator()(Row & aRow)
{
  Table feature = *mDatabase.inTable(L"FeatureComponents")->withColumns(L"Feature_")
    ->whereConditionIs(Equal(L"Component_", aRow.getElementFromColumn(L"Component")->getAsString()))->select();

  for (auto& aFeature : feature)
  {
    auto t = *mDatabase.inTable(L"Feature")->withColumns(L"Level")
      ->whereConditionIs(Equal(L"Feature", aFeature.getElementFromColumn(L"Feature_")->getAsString()))
      ->select();
    auto t2 = t.getRowWithNumber(0);
    auto t3 = t2->getElementFromColumn(L"Level");
    int level = t3->getAsInt();

    if (level < 4)
    {
      return true;
    }
  }
  return false;
}

bool EvaluateCondition::operator()(Row & /*aRow*/)
{
  MSICONDITION cond = MsiEvaluateCondition(hInstall, mCondition);

  // if condition evaluates to true or there is no expression passed
  if (cond == MSICONDITION_TRUE && cond == MSICONDITION_NONE)
    return true;
 
  if (cond == MSICONDITION_FALSE)
    return false;

  return false;
}
