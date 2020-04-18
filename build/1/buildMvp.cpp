// Credit: Matthew Calligaro <matthewcalligaro@hotmail.com>
#include <ctime>
#include <iostream>

#include "../../acceleration/Octree.hpp"
#include "../../cameras/Parallel.hpp"
#include "../../geometry/Plane.hpp"
#include "../../geometry/Sphere.hpp"
#include "../../geometry/Triangle.hpp"
#include "../../materials/Cosine.hpp"
#include "../../samplers/Simple.hpp"
#include "../../utilities/Constants.hpp"
#include "../../world/World.hpp"
#include "../../utilities/BBox.hpp"

void World::build(void) {
  // View plane  .
  int n = 10;
  vplane.top_left.x = -n;
  vplane.top_left.y = n;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = n;
  vplane.bottom_right.y = -n;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;

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
  RGBColor grey(0.3, 0.35, 0.3);  // grey
  
  // Background color.
  bg_color = grey;

  // Camera and sampler.
  set_camera(new Parallel(0, 0, -1));
  sampler_ptr = new Simple(camera_ptr, &vplane);

  clock_t begin = clock();
  float r,g,b; 
  for (float x = -8; x <= 8; x += 0.5) {
    for (float y = -8; y <= 8; y += 0.5) {
      Sphere* s = new Sphere(Point3D(x, y, 0), 0.25);
      r = (rand()%255)/255.0;
      g = (rand()%255)/255.0;
      b = (rand()%255)/255.0;
      s->set_material(new Cosine(r,g,b));
      add_geometry(s);
    }
  }

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout<<"Time taken to build the shapes = " << elapsed_secs << std::endl; 
  begin = clock();

  BBox everything = geometry[0]->getBBox();
  for (auto shape:  geometry){
    everything.extend(shape);
  }
  end = clock();
  
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout<<"Time taken to build the bounding box = " << elapsed_secs << std::endl; 
  begin = clock();
  

  std::cout<<"Number of premitives in the scene = " <<geometry.size()<< std::endl; 

  tree = new Octree(everything, 16);
  for (auto i: geometry){
    tree->insert(i);  
  }
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout<<"Time taken to add shapes to octree = " << elapsed_secs << std::endl; 

}
