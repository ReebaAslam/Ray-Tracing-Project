#include <iostream>
#include "KDNode.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/BBox.hpp"


KDNode::KDNode(){}

KDNode::~KDNode(){}

KDNode::KDNode(BBox box): box{box} {}

bool KDNode::insert(Geometry* shape) {
  shapes.push_back(shape);
  return true;
}

KDNode* KDNode::build(std::vector<Geometry*>& shapes, int depth){
  KDNode* node = new KDNode();
  node->shapes = shapes;
  node->left = NULL;
  node->right = NULL;
  node->box = BBox();

  if (shapes.size() == 0){
    return node;
  }

  if (shapes.size() == 1){
    node->box = shapes[0]->getBBox();
    node->left = new KDNode();
    node->right = new KDNode();
    node->left->shapes = std::vector<Geometry*>();
    node->right->shapes = std::vector<Geometry*>();
    return node;
  }

  node->box = shapes[0]->getBBox();
  for (auto shape:  shapes){
    node->box.extend(shape);
  }

  Point3D mid = Point3D(0,0,0);
  for (auto shape: shapes){
    mid = mid + shape->mid_point() * (1.0/shapes.size());
  }

  std::vector<Geometry*> left_shapes;
  std::vector<Geometry*> right_shapes;
  int axis = node->box.longest_axis();
  for (auto shape: shapes){
    switch(axis){
      case 0:
        mid.x >= shape->mid_point().x ? right_shapes.push_back(shape):left_shapes.push_back(shape);
      case 1:
        mid.y >= shape->mid_point().y ? right_shapes.push_back(shape):left_shapes.push_back(shape);
      case 2:
        mid.z >= shape->mid_point().z ? right_shapes.push_back(shape):left_shapes.push_back(shape);
    }
  }
  if (left_shapes.size() == 0 && right_shapes.size() > 0) left_shapes = right_shapes;
  if (right_shapes.size() == 0 && left_shapes.size() > 0) right_shapes = left_shapes;

  int matches = 0;
  for (auto lshape: left_shapes){
    for (auto rshape: right_shapes){
      if (lshape == rshape){
        matches++;
      }
    }
  }

  if ((float)matches / left_shapes.size() < 0.5 && (float)matches / right_shapes.size() < 0.5){
    node->left = build(left_shapes, depth+1);
    node->right = build(right_shapes, depth+1);
  } 
  else{
    node->left = new KDNode();
    node->right = new KDNode();
    node->left->shapes = std::vector<Geometry*>();
    node->right->shapes = std::vector<Geometry*>();
  }
  return node;
}


ShadeInfo KDNode::hit_objects(const Ray &ray, ShadeInfo &shade){
  float t;
  float tmin = kHugeValue;
  hit_objects(this, ray, t, tmin, shade);
  return shade;
}

bool KDNode::hit_objects(KDNode* node, const Ray &ray, float& t, float&tmin, ShadeInfo &shade){
  
  if (node->box.hit(ray, t, tmin)) {
    
    bool hit_shape = false;
    Point3D hit_pt, local_hit_pt;

    if (node->left->shapes.size() > 0 || node->right->shapes.size() > 0){
      std::cout<<"B\n";
      bool hitLeft = hit_objects(node->left, ray, t, tmin, shade);
      bool hitRight = hit_objects(node->right, ray, t, tmin, shade);
      return hitLeft || hitRight;
    }
    else{
      for (auto shape: node->shapes){
        if (shape->hit(ray, t, shade)){

          shade.hit = true;
          shade.t = tmin;
          shade.material_ptr = shape->get_material();

        }
      }
      if (hit_shape){
          shade.hit = true;
          shade.t = tmin;
        return true;
      }
      return false;
    }
  } 
  return false; 
}