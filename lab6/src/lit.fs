// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  // Calculate where light is
  float theta = 0.25 * M_PI * animation_seconds;
  vec4 light = view * vec4(4 * cos(theta), 4, 4 * sin(theta), 1);
  
  // Blinn Phong parameters
  vec3 ka = vec3(0.01, 0.01, 0.01);
  vec3 kd = is_moon ? vec3(0.83, 0.83, 0.83) : vec3(0.20, 0.29, 0.8);
  vec3 ks = vec3(0.8, 0.8, 0.8);
  float p = is_moon ? 1000 : 500;

  // Since we are looking at the picture straight on, our eye is at (0,0,0)
  vec3 n = normalize(normal_fs_in);
  vec3 v = -normalize(view_pos_fs_in.xyz); // from point on surface -> eye
  vec3 l = normalize(light.xyz - view_pos_fs_in.xyz); // from point on surface -> light

  color = blinn_phong(ka, kd, ks, p, n, v, l);
}
