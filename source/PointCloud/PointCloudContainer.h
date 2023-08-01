#pragma once

#include <UnigineComponentSystem.h>
#include "pcl/point_types.h"
#include "pcl/io/pcd_io.h"

using namespace Unigine;

class PointCloudContainer : public ComponentBase
{
public:
  COMPONENT_DEFINE(PointCloudContainer, ComponentBase)
  COMPONENT_INIT(init)

  PROP_PARAM(Node, cameraNode)

  void OpenPointCloud(const char* path, float size);
  void SetPointsSize(float size);
  void SetPointColor(int index, int r, int g, int b);

  void SetLoadFailCallback(CallbackBase *callback);
protected:
  void init();
private:
  ObjectBillboards *objectsBillboards = nullptr;
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
  CallbackBase* loadFailCbk = nullptr;
};
