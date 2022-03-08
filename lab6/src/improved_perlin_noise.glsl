// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  // Reference: https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1/creating-simple-2D-noise
  // Reference: https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2
  // Reference: https://en.wikipedia.org/wiki/Perlin_noise

  // Determine grid cell coordinates closest to the 3D seed
  int x0 = int( floor(st.x) );
  int x1 = x0 + 1;
  int y0 = int( floor(st.y) );
  int y1 = y0 + 1;
  int z0 = int( floor(st.z) );
  int z1 = z0 + 1;

  // Establish all the corners of the current cube we are working with
  vec3 c000 = vec3(x0, y0, z0);
  vec3 c100 = vec3(x1, y0, z0);
  vec3 c010 = vec3(x0, y1, z0);
  vec3 c110 = vec3(x1, y1, z0);
  vec3 c001 = vec3(x0, y0, z1);
  vec3 c101 = vec3(x1, y0, z1);
  vec3 c011 = vec3(x0, y1, z1);
  vec3 c111 = vec3(x1, y1, z1);
  

  // Compute the dot grid gradient between gradient at corner, and distance to st
  float g0 = dot( random_direction(c000), st - c000 );
  float g1 = dot( random_direction(c100), st - c100 );
  float g2 = dot( random_direction(c010), st - c010 );
  float g3 = dot( random_direction(c110), st - c110 );
  float g4 = dot( random_direction(c001), st - c001 );
  float g5 = dot( random_direction(c101), st - c101 );
  float g6 = dot( random_direction(c011), st - c011 );
  float g7 = dot( random_direction(c111), st - c111 );

  // Smooth step interpolation
  vec3 interp = improved_smooth_step( st - vec3(x0, y0, z0) );
  
  float ix0 = g0 + interp.x * (g1 - g0);
  float ix1 = g2 + interp.x * (g3 - g2);
  float ix2 = g4 + interp.x * (g5 - g4);
  float ix3 = g6 + interp.x * (g7 - g6);

  float iy0 = ix0 + interp.y * (ix1 - ix0);
  float iy1 = ix2 + interp.y * (ix3 - ix2);

  float iz0 = iy0 + interp.z * (iy1 - iy0);

  return iz0;
}

