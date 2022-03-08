// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  // Calculate where light is
  float theta = 0.25 * M_PI * animation_seconds;
  vec4 light = view * vec4(4 * cos(theta), 4, 4 * sin(theta), 0.75);
  
  // Blinn Phong parameters
  vec3 ka = vec3(0.01, 0.01, 0.01);
  vec3 kd = is_moon ? vec3(0.83, 0.83, 0.83) : vec3(0.20, 0.29, 0.8);
  vec3 ks = vec3(0.8, 0.8, 0.8);
  float p = is_moon ? 1000 : 500;

  // Put bumps on surface - account for new location that light hits and reflects
  // Reference: https://github.com/alecjacobson/computer-graphics-shader-pipeline
  vec3 T, B;
  tangent(sphere_fs_in, T, B);
  vec3 bump = bump_position(is_moon, sphere_fs_in);

  float e = 1e-4;
  vec3 dp_dt = (bump_position (is_moon, sphere_fs_in + e * T) - bump) / e;
  vec3 dp_db = (bump_position (is_moon, sphere_fs_in + e * B) - bump) / e;

  vec3 perceived_normal = normalize( cross(dp_dt, dp_db) );
  if ( dot(perceived_normal, sphere_fs_in) < 0 ) {
    perceived_normal *= -1;
  }

  // Undo the view and model transformations on percieved normal
  mat4 model = model(is_moon, animation_seconds);
  vec3 n = normalize( ( transpose(inverse(view)) * transpose(inverse(model)) * vec4(perceived_normal,1) ).xyz );
  
  // Since we are looking at the picture straight on, our eye is at (0,0,0)
  vec3 v = -normalize(view_pos_fs_in.xyz); // from point on surface -> eye
  vec3 l = normalize(light.xyz - view_pos_fs_in.xyz); // from point on surface -> light

  color = blinn_phong(ka, kd, ks, p, n, v, l);
}
