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
#include "../lights/Directional.hpp"
#include "../materials/Phong.hpp" 
#include "../materials/Material.hpp" 
#include "../brdf/GlossySpecular.hpp"

using namespace std; 

std::vector<Point3D> vertices = {};
std::vector<Point3D> verticesT = {};
std::vector<Point3D> verticesNormal = {};
std::vector<Triangle*> faces = {};
float fackA = 0.25;
float fackD = 1.0;
float fackS = 1.0;
float e = 5;
Material *material = NULL;
Lambertian *ka = NULL;
Lambertian *kd = NULL;
GlossySpecular *ks = new GlossySpecular(fackS, RGBColor(0.5), e); 



std::vector<std::string> parseLine(std::string sentence, char delimeter);

bool World::buildLoadOBJ(void) {
  // If the file is not an .obj file return false //scenecolor1

  string Path = "new3.obj";   
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


      Triangle* temp = new Triangle(vertices[std::stoi(result_slash_1[0])-1],
                                    vertices[std::stoi(result_slash_2[0])-1],
                                    vertices[std::stoi(result_slash_3[0])-1]);

      temp->set_material(material);
      faces.push_back(temp);
    }
    else if(result[0] == "usemtl"){
        if (result[1] == "Mat.004"){
          RGBColor col(0.8);
          ka = new Lambertian(fackA, col);
          kd = new Lambertian(fackD, col);
          material = new Phong(ka,kd,ks);
        }
        else if (result[1] == "Mat.1"){
          RGBColor col(0.149772, 0.361638, 1.0);
          ka = new Lambertian(fackA, col);
          kd = new Lambertian(fackD, col);
          material = new Matte(ka, kd);
        }

        else if(result[1] == "Mat.2"){
          RGBColor col(0.153061, 0.142941, 0.142941);
          ka = new Lambertian(fackA, col);
          kd = new Lambertian(fackD, col);
          material = new Phong(ka,kd,ks); 
        }
        else if(result[1]=="Mat.3"){
          RGBColor col(0.318435, 0.326531, 0.325451);
          ka = new Lambertian(fackA, col);
          kd = new Lambertian(fackD, col);
          material = new Phong(ka,kd,ks);
        }
        else{
          RGBColor col(0.0);
          ka = new Lambertian(fackA, col);
          kd = new Lambertian(fackD, col);
          material = new Matte(ka,kd);
        }        
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
  vplane.top_left.x = -20;
  vplane.top_left.y = 20;
  vplane.top_left.z = -10;
  vplane.bottom_right.x = 30;
  vplane.bottom_right.y = -20;
  vplane.bottom_right.z = -10;
  vplane.hres = 480;
  vplane.vres = 480;

  std::cout<<"Resolution = " << vplane.hres << "x" << vplane.vres << std::endl; 

  RGBColor grey(0.3, 0.35, 0.3);  // grey
  
  // Background color.
  bg_color = grey;

  // Camera and sampler.
  set_camera(new Perspective(0,10,-20));
  sampler_ptr = new Simple(camera_ptr, &vplane);
  tracer = new Basic(this);

 PointLight *pntL = new PointLight();
  pntL->setLocation(Point3D(0,20,0));
  add_light(pntL);

  Directional *dirL = new Directional();
  dirL->setDirection(Vector3D(1, 1, 1));
  add_light(dirL);

  float factor = 2.0;
  float r,g,b;


  clock_t begin = clock();

  buildLoadOBJ();

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout<<"Time taken to read file = " << elapsed_secs << std::endl; 


  begin = clock();
  std::cout<<"Number of vertices in the scene = " <<vertices.size()<< std::endl; 
  for (auto i: faces){
    add_geometry(i);
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
  tree = new Octree(everything, 46);
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