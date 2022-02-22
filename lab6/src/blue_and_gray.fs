// Set the pixel color to blue or gray depending on is_moon.
//
// Uniforms:
uniform bool is_moon;
// Outputs:
out vec3 color;
void main()
{
  color = is_moon ? vec3(0.83, 0.83, 0.83) : vec3(0.20, 0.29, 0.8);
}
