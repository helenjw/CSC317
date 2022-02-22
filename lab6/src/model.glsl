// Construct the model transformation matrix. The moon should orbit around the
// origin. The other object should stay still.
//
// Inputs:
//   is_moon  whether we're considering the moon
//   time  seconds on animation clock
// Returns affine model transformation as 4x4 matrix
//
// expects: identity, rotate_about_y, translate, PI
mat4 model(bool is_moon, float time)
{
  // Transform if it is a moon
  if (is_moon) {
    float theta = 0.5 * M_PI * time;
    mat4 res = translate( vec3(2 * cos(theta), 1  , 2 * sin(theta)) ) * uniform_scale(0.5); // translate and shrink planet by 70%
    res *= rotate_about_y(theta); // rotate around earth
    return res;
  }

  // Otherwise we don't do anything
  return identity();
}

