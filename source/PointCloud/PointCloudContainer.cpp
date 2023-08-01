#include "PointCloudContainer.h"

REGISTER_COMPONENT(PointCloudContainer);

void PointCloudContainer::init()
{
  objectsBillboards = node->getInternalObject()->getInterface<ObjectBillboards>();
  objectsBillboards->clearBillboards();
  cloud = std::make_shared<pcl::PointCloud<pcl::PointXYZRGB>>();
}

void PointCloudContainer::OpenPointCloud(const char* path, float size)
{
  if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(path, *cloud) != -1)
  {
    objectsBillboards->clearBillboards();
    for (pcl::PointCloud<pcl::PointXYZRGB>::iterator iter = cloud->begin(); iter != cloud->end(); iter++)
    {
      int idx = objectsBillboards->addBillboard(size, size);
      const Math::vec3 xyz(iter->x, iter->y, iter->z);
      objectsBillboards->setBillboardPosition(idx, xyz);
      SetPointColor(idx, iter->r, iter->g, iter->b);
    }
  }
  else
  {
    loadFailCbk->run();
  }
}

void PointCloudContainer::SetPointsSize(float size)
{
  for (int i = 0; i < objectsBillboards->getNumBillboards(); i++)
  {
    objectsBillboards->setHeight(i, size);
    objectsBillboards->setWidth(i, size);
  }
}

void PointCloudContainer::SetPointColor(int index, int r, int g, int b)
{
  const int pixelsPerColor = 2;
  const int bitsPerChannel = 256;
  const int bpcSqrt = 16;
  const int size = (bitsPerChannel * bpcSqrt * pixelsPerColor);
  const float scale = (float)pixelsPerColor / size;
  Math::vec4 color(scale, scale,
    float(14) / size, float(14) / size
  );
  //Math::vec4 color(scale, scale,
  //  (float)(pixelsPerColor * bpcSqrt * r + pixelsPerColor * (b % bpcSqrt) + pixelsPerColor / 2) / size,
  //  1.0 - (float)(pixelsPerColor * bpcSqrt * g + pixelsPerColor * (b / bpcSqrt) + pixelsPerColor / 2) / size);
  //Math::vec4 color(scale, scale,
  //  (float)(pixelsPerColor * bpcSqrt * r + pixelsPerColor * (b % bpcSqrt)) / size,
  //  1.0 - (float)(pixelsPerColor * bpcSqrt * g + pixelsPerColor * (b / bpcSqrt)) / size);
  objectsBillboards->setTexCoord(index, color);
}

void PointCloudContainer::SetLoadFailCallback(CallbackBase* callback)
{
  loadFailCbk = callback;
}