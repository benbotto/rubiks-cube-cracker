// Vertex normal in eye space.
in vec3 oNormalEC;

// The vector from the vertex to the light.
in vec3 oVertToDistLight;

// The vertex position in eye space.
in vec3 oVertPosEC;

// The vertex color and position.
in vec4 oColor;
in vec3 oVertPos;
in vec3 oTranslatedVertPos;

uniform vec4           ambient;
uniform DistanceLight  distLight;
uniform Material       material;

out vec4 fragColor;

/**
 * Get the blend amount of a coordinate.
 * @param coord The coordinate to blend.
 */
float getBlendAmount(float coord)
{
  return -1 * pow((abs(coord) + .54), 32) + 1;
}

void main()
{
  vec3  L;
  vec3  N;
  vec3  V;
  const vec4 brown = vec4(0.58, 0.25, 0.25, 1.0);
  float fRand    = snoise(oTranslatedVertPos); // Simplex noise.
  bool  sticker  = false;
  float blendX   = 1.0;
  float blendY   = 1.0;
  float blendZ   = 1.0;
  float blendAmt = 1.0;

  // The global ambient effect on the frag color.
  fragColor = ambient * material.ambient;

  // Make the cube look a bit dirty.
  fragColor = mix(fragColor, brown, fRand * .010);

  // If this is not a hiden side of the cubie then it may need to be colored.
  if (1.52 - abs(oTranslatedVertPos.x) < .01 ||
      1.52 - abs(oTranslatedVertPos.y) < .01 ||
      1.52 - abs(oTranslatedVertPos.z) < .01)
  {
    // Each cubie has a colored sticker on it that's square.  The blending
    // is a negative polynomial that blends the material color and the
    // sticker color to reduce anti aliasing.
    if (oVertPos.x > -.46 && oVertPos.x < .46 && oVertPos.y > -.46 && oVertPos.y < .46)
    {
      sticker = true;
      blendX  = getBlendAmount(oVertPos.x);
      blendY  = getBlendAmount(oVertPos.y);
    }
    else if (oVertPos.x > -.46 && oVertPos.x < .46 && oVertPos.z > -.46 && oVertPos.z < .46)
    {
      sticker = true;
      blendX  = getBlendAmount(oVertPos.x);
      blendZ  = getBlendAmount(oVertPos.z);
    }
    else if (oVertPos.y > -.46 && oVertPos.y < .46 && oVertPos.z > -.46 && oVertPos.z < .46)
    {
      sticker = true;
      blendY  = getBlendAmount(oVertPos.y);
      blendZ  = getBlendAmount(oVertPos.z);
    }

    // Use the sticker color if needed, blended at the edges.
    if (sticker)
    {
      vec4 holdFrag  = fragColor;
      vec4 newFrag   = fragColor * oColor * 40;
      
      blendAmt  = min(min(blendX, blendY), blendZ);
      fragColor = mix(holdFrag, newFrag, blendAmt);
    }
  }

  // The vertex normal.
  N  = normalize(oNormalEC);

  // Mess with the normal a bit to enhance the reflection.
  N += fRand * .065;

  // The vector from the vertex to the eye.
  V = normalize(-oVertPosEC);

  // Vertex to the light.
  L = normalize(oVertToDistLight);

  // Distance light intensity.
  fragColor += getIntensity(distLight, material, L, N, V) * 1.2;
}

