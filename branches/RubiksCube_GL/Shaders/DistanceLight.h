/**
 * Representation of a distance light.
 */
struct DistanceLight
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec3 direction;
};

/**
 * Calculate the intensity of the DistanceLight using the Material m.
 * @param m The Material.
 *
 * @param L The vector from the vertex to the light.
 * @param N The vertex normal.
 * @param V The vector from the vertex to the eye.
 *
 * @param ambient The ambient light of the light.
 * @param diffuse The diffuse light of the light.
 * @param specular The specular light of the light.
 */
vec4 getIntensity(Material m, vec3 L, vec3 N, vec3 V,
  vec4 ambient, vec4 diffuse, vec4 specular)
{
  /*   
   *   L  N  R
   *    \ | /
   *     \|/___V  (eye)
   */
  float cosLN, cosVR;
  vec4  intensity;
  vec3  R;

  // Reflect the light off the normal.
  R = normalize(reflect(-L, N));

  // The angle between the light and the surface normal.
  cosLN = dot(L, N);

  // The angle between the vector to the eye and the reflected light.
  cosVR = dot(V, R);

  intensity = 
    ambient  * m.ambient  +
    diffuse  * m.diffuse  * max(cosLN,     0.0)  +
    specular * m.specular * pow(max(cosVR, 0.0), m.shininess);

  return intensity * 1.5;
}

/**
 * Same as above but accepts a DistanceLight.
 * @param l The DistanceLight.
 * @param m The Material.
 * @param L The vector from the vertex to the light.
 * @param N The vertex normal.
 * @param V The vector from the vertex to the eye.
 */
vec4 getIntensity(DistanceLight l, Material m, vec3 L, vec3 N, vec3 V)
{
  return getIntensity(m, L, N, V, l.ambient, l.diffuse, l.specular);
}

