
#include <iostream>
#include <ctime>
#include <omp.h>

#include "materials/Cosine.hpp"

#include "samplers/Sampler.hpp"

#include "utilities/Image.hpp"
#include "utilities/RGBColor.hpp"
#include "utilities/Ray.hpp"
#include "utilities/ShadeInfo.hpp"

#include "world/World.hpp"
#include "world/ViewPlane.hpp"

#include "tracers/Tracer.hpp"

const size_t MIN_ROWS_PER_CHUNK = 4;
const size_t LOAD_BALANCE_FACTOR = 4;


int main(int argc, char **argv)
{

  
  World world;
  world.build();

  Sampler *sampler = world.sampler_ptr;
  ViewPlane &viewplane = world.vplane;
  Image image(viewplane);

  std::vector<Ray> rays;
  clock_t begin = clock();

    
  #pragma omp parallel for private(rays)
  for (int x = 0; x < viewplane.hres; x++)
  { // across.
    for (int y = 0; y < viewplane.vres; y++)
    { // down.
      // Get rays for the pixel from the sampler. The pixel color is the
      // weighted sum of the shades for each ray.

      RGBColor pixel_color(0);
      rays = sampler->get_rays(x, y);
      for (const auto &ray : rays)
      {
        // float weight = ray.w; // ray weight for the pixel.
        // ShadeInfo sinfo = world.hit_objects(ray);
        // if (sinfo.hit)
        // {
        //   pixel_color += weight * sinfo.material_ptr->shade(sinfo);
        // }
        // else
        // {
        //   pixel_color += weight * world.bg_color;
        // }
        pixel_color += world.tracer->trace_ray(ray, 0);
      }
      // Save color to image.
      image.set_pixel(x, y, pixel_color);
      // std::cout << pixel_color << "\n";
    }
  }

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  std::cout<<"Time taken to trace rays = " << elapsed_secs << std::endl; 
  // Write image to file.
  begin = clock();
  image.write_ppm("scene.ppm");

  std::cout << "Wrote image.\n";
  end = clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout<<"Time taken to write image = " << elapsed_secs << std::endl; 
  return 0;
}
