//guidance taken from https://github.com/Bly7/OBJ-Loader/
#include <iostream>
#include <bits/stdc++.h> 

#include "../utilities/Point3D.hpp"



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
#include "../lights/PointLight.hpp"

using namespace std; 

std::vector<Point3D> vertices = {};
std::vector<Point3D> verticesT = {};
std::vector<Point3D> verticesNormal = {};
std::vector<Triangle*> faces = {};

std::vector<std::string> parseLine(std::string sentence, char delimeter);

bool World::buildLoadOBJ(void) {
	// If the file is not an .obj file return false //scenecolor1

  //string Path = "../scene/graphics/box-blende-normalr.obj";
  string Path = "../scene/graphics/bear.obj";
  if (Path.substr(Path.size() - 4, 4) != ".obj")
    return false;

  std::ifstream file(Path);

  if (!file.is_open())
    return false;

  std::string curline;

  while (std::getline(file, curline))
  {
    std::vector<string> result = parseLine(curline, ' ');
    
    if(result[0] == "v"){
      vertices.push_back(Point3D(std::stof(result[1]), std::stof(result[2]), std::stof(result[3])));
    }

    
    else if(result[0] == "vt"){
      continue;
    }

    else if(result[0] == "vn"){
      verticesNormal.push_back(Point3D(std::stof(result[1]), std::stof(result[2]), std::stof(result[3])));
    }
    
    else if(result[0] == "f"){

      std::vector<string> result_slash_1 = parseLine(result[1], '/');
      std::vector<string> result_slash_2 = parseLine(result[2], '/');
      std::vector<string> result_slash_3 = parseLine(result[3], '/');

      // std::cout << result_slash_1[0] << " "
      // << result_slash_2[0] << " " <<
      // result_slash_3[0] << "\n";

      Triangle* temp = new Triangle(vertices[std::stoi(result_slash_1[0])-1],
                                    vertices[std::stoi(result_slash_2[0])-1],
                                    vertices[std::stoi(result_slash_3[0])-1]);

      faces.push_back(temp);
    }
    
  }
}

std::vector<std::string> parseLine(std::string sentence, char delimeter)
{
    std::stringstream ss(sentence);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}


void World::build(void) {
  // View plane  .
  vplane.top_left.x = -30;
  vplane.top_left.y = 40;
  vplane.top_left.z = 14;
  vplane.bottom_right.x = 50;
  vplane.bottom_right.y = -40;
  vplane.bottom_right.z = 14;
  vplane.hres = 2000;
  vplane.vres = 2000;

  std::cout<<"Resolution = " << vplane.hres << "x" << vplane.vres << std::endl; 

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
  set_camera(new Perspective(0,0,200));
  sampler_ptr = new Simple(camera_ptr, &vplane);
  tracer = new Basic(this);

  PointLight *pntL = new PointLight();
  pntL->scaleRadiance(0.3);
  pntL->setColor(RGBColor(1.0));
  pntL->setLocation(Point3D(1000,0,0));
  add_light(pntL);

  float factor = 2.0;
  float r,g,b;
  float kd_ambient = 0.5;
  float kd_diffuse = 0.1;
  /**
  for (float i = -n - 10 ; i<n+10; i+=factor){
    for (float j = -n - 10 ; j<n+10; j+=factor){
      // Sphere* triangle_ptr = new Sphere(                                                        
      //                                   Point3D(0, 0, i),
      //                                   j+11
      //                                   );
      // r = (rand()%255)/255.0;
      // g = (rand()%255)/255.0;
      // b = (rand()%255)/255.0;
      // RGBColor col(r,g,b);
      // Lambertian *l_amb = new Lambertian(kd_ambient, col);
      // Lambertian *l_diff = new Lambertian(kd_diffuse, col);

      // triangle_ptr->set_material(new Matte(l_amb, l_diff));
      // add_geometry(triangle_ptr);

      Triangle* triangle_ptr2 = new Triangle(                                                        
                                        Point3D(i+factor, j, 1),
                                        Point3D(i+factor, j+factor, 1),
                                        Point3D(i, j+factor, 1)
                                        );
      r = (rand()%255)/255.0;
      g = (rand()%255)/255.0;
      b = (rand()%255)/255.0;
      triangle_ptr2->set_material(new Cosine(r,g,b));
      add_geometry(triangle_ptr2);

    }    
  }
  **/
  clock_t begin = clock();

  buildLoadOBJ();

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout<<"Time taken to read file = " << elapsed_secs << std::endl; 

  begin = clock();
  std::cout<<"Number of vertices in the scene = " <<vertices.size()<< std::endl; 
  for (auto i: faces){
    r = (rand()%255)/255.0;
    g = (rand()%255)/255.0;
    b = (rand()%255)/255.0;
    
    i->set_material(new Cosine(r,g,b));
    geometry.push_back(i);
  }
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout<<"Time taken to add objects to scene = " << elapsed_secs << std::endl; 

  std::cout<<"Number of premitives in the scene = " <<geometry.size()<< std::endl; 

  begin = clock();
  BBox everything = geometry[0]->getBBox();
  for (auto shape:  geometry){
    everything.extend(shape);
  }
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout<<"Time taken to build bounding box = " << elapsed_secs << std::endl; 

  begin = clock();
  tree = new Octree(everything, 32);
  for (auto i: geometry){
    tree->insert(i);
  }
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout<<"Time taken to add objects to structure " << elapsed_secs << std::endl; 

  faces.clear();
  vertices.clear();

  std::cout<<"____________\n";

}
