// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  vec2 rand = random2(seed);

  // Random distrubution over a sphere.
  // Sphere Reference: https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2
  float theta = M_PI * rand.y; // Inclination level - [0, pi]
  float phi = 2 * M_PI * rand.x; // Azimuthal angle - [0, 2pi]

  return normalize(
    vec3(
      cos(phi) * sin(theta), 
      sin(phi) * sin(theta), 
      cos(theta)
    ) 
  );
}
