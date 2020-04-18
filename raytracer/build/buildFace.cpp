
/**
   This builds a scene that consists of 35 shaded spheres and a plane.
   Perspective viewing is used with a single sample per pixel.
   The spheres are the same as those in the Chapter 14 page one image. 

   Courtesy Kevin Suffern.
*/

#include "../acceleration/Octree.hpp"
#include "../cameras/Parallel.hpp"
#include "../cameras/Perspective.hpp"
#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"
#include "../materials/Cosine.hpp"
#include "../samplers/Simple.hpp"
#include "../tracers/Basic.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../utilities/BBox.hpp"
#include "../materials/Matte.hpp"
#include "../brdf/Lambertian.hpp"
#include "../lights/Light.hpp"
#include "../lights/Directional.hpp"
#include "../lights/PointLight.hpp"


void
World::build(void) {
  // view plane  
  int n = 10;
  vplane.top_left.x = -n;
  vplane.top_left.y = n;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = n;
  vplane.bottom_right.y = -n;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;
  
  bg_color = black;  // background color.
  
  // camera, sampler and tracer
  set_camera(new Parallel(0, 0, -10));
  sampler_ptr = new Simple(camera_ptr, &vplane);
  tracer = new Basic(this);
	
  // colors
  RGBColor yellow(1, 1, 0);  // yellow
  RGBColor brown(0.71, 0.40, 0.16);  // brown
  RGBColor darkGreen(0.0, 0.41, 0.41);  // darkGreen
  RGBColor orange(1, 0.75, 0);  // orange
  RGBColor green(0, 0.6, 0.3);  // green
  RGBColor lightGreen(0.65, 1, 0.30);  // light green
  RGBColor darkYellow(0.61, 0.61, 0);  // dark yellow
  RGBColor lightPurple(0.65, 0.3, 1);  // light purple
  RGBColor darkPurple(0.5, 0, 1);  // dark purple
  RGBColor grey(0.25);  // grey
	
  // spheres
  Sphere* sphere_ptr1 = new Sphere(Point3D(0, 0, 0),8); 
  sphere_ptr1->set_material(new Cosine(yellow));  
  add_geometry(sphere_ptr1);

  Sphere* sphere_ptr2 = new Sphere(Point3D(-2.5, 3, 10),1.5); 
  sphere_ptr2->set_material(new Cosine(RGBColor(1)));  
  add_geometry(sphere_ptr2);

  Sphere* sphere_ptr3 = new Sphere(Point3D(2.5, 3, 10),1.5); 
  sphere_ptr3->set_material(new Cosine(RGBColor(1)));  
  add_geometry(sphere_ptr3);

  Sphere* sphere_ptr4 = new Sphere(Point3D(-2.5, 3, 10),0.5); 
  sphere_ptr4->set_material(new Cosine(black));  
  add_geometry(sphere_ptr4);

  Sphere* sphere_ptr5 = new Sphere(Point3D(2.5, 3, 10),0.5); 
  sphere_ptr5->set_material(new Cosine(black));  
  add_geometry(sphere_ptr5);

  Sphere* sphere_ptr6 = new Sphere(Point3D(0, -3, 10),2.5); 
  sphere_ptr6->set_material(new Cosine(black));  
  add_geometry(sphere_ptr6);

  BBox everything = geometry[0]->getBBox();
  for (auto shape:  geometry){
    everything.extend(shape);
  }

  tree = new Octree(everything, 4);
  for (auto i: geometry){
    tree->insert(i);  
  }
}

