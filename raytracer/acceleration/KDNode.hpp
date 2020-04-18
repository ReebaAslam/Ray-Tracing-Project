#pragma once 

#include <vector>
#include "Acceleration.hpp" 
#include "../geometry/Geometry.hpp"
#include "../utilities/BBox.hpp"

class KDNode : public Acceleration {
 protected:
  KDNode* left;
  KDNode* right;
  std::vector<Geometry*> shapes;
  BBox box;

 public:

  KDNode();

  KDNode(BBox box);

  ~KDNode();

  bool insert(Geometry* shape) override;

  std::vector<Geometry*> get_primitives() const;

  //https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/
  KDNode* build(std::vector<Geometry*>& shapes, int depth) override;

  ShadeInfo hit_objects(const Ray &ray, ShadeInfo &shade) override;
  
  //https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/
  bool hit_objects(KDNode* node, const Ray &ray, float& t, float&tmin, ShadeInfo &shade);

};
