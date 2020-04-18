
/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/

#include <iostream>

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
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;

  // Background color.  
  bg_color = black;
  float kd_ambient = 0.25;
  float kd_diffuse = 1.0;

  PointLight *pntL = new PointLight();
  //pntL->scaleRadiance(1.0);
  pntL->setLocation(Point3D(-3,2,10));
  pntL->set_shadows(true);
  add_light(pntL);

  Directional *dirL = new Directional();
  dirL->setDirection(Vector3D(-1, 0, 0));
  dirL->set_shadows(true);
  add_light(dirL);
  
  // Camera, sampler and tracer
  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = new Simple(camera_ptr, &vplane);
  tracer = new Basic(this);

  Lambertian *l_amb = new Lambertian(kd_ambient, red);
  Lambertian *l_diff = new Lambertian(kd_diffuse, red);
	
  // sphere
  Sphere* sphere_ptr = new Sphere(Point3D(-5, 2, 0), 5); 
  sphere_ptr->set_material(new Matte(l_amb, l_diff));
  add_geometry(sphere_ptr);

  sphere_ptr = new Sphere(Point3D(-1, 2, 4), 5);
  sphere_ptr->set_material(new Matte(l_amb, l_diff));
  add_geometry(sphere_ptr);

  
  // triangle
  Point3D a(2.5, -5, 1); 
  Point3D b(14, -1, 0); 
  Point3D c(8.5, 5, 0.5); 

  Triangle* triangle_ptr = new Triangle(a, b, c);
  
  l_amb = new Lambertian(kd_ambient, blue);
  l_diff = new Lambertian(kd_diffuse, blue);
  triangle_ptr->set_material(new Matte(l_amb, l_diff));
  add_geometry(triangle_ptr);

  // plane
  // Plane* plane_ptr = new Plane(Point3D(0,1,0), Vector3D(0, 10, 2)); 
  // plane_ptr->set_material(new Cosine(green));  // green
  // add_geometry(plane_ptr);


  BBox everything = geometry[0]->getBBox();
  for (auto shape:  geometry){
    everything.extend(shape);
  }


  std::cout<<"Number of premitives in the scene = " <<geometry.size()<< std::endl; 

  tree = new Octree(everything, 4);
  for (auto i: geometry){
    tree->insert(i);  
  }

}
