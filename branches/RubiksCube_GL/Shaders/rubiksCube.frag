// Vertex normal in eye space.
in vec3 oNormalEC;

// The vector from the vertex to the light.
in vec3 oVertToDistLight;

// The vertex position in eye space.
in vec3 oVertPosEC;

// The vertex color and position.
in vec4 oColor;
in vec3 oVertPos;

uniform vec4           ambient;
uniform DistanceLight  distLight;
uniform Material       material;
uniform bool           materialEnabled;

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
  float fRand  = snoise(oVertPos); // Simplex noise.
  bool  sticker = false;
  float blendX   = 1.0;
  float blendY   = 1.0;
  float blendZ   = 1.0;
  float blendAmt = 1.0;

  // If material and texturing is disabled use the standard color.
  if (!materialEnabled)
  {
    fragColor = oColor;
    return;
  }

  // The global ambient effect on the frag color.
  fragColor = ambient * material.ambient;

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

  // The vertex normal.
  N  = normalize(oNormalEC);

  // Mess with the normal a bit to enhance the reflection.
  N += fRand * .045;

  // The vector from the vertex to the eye.
  V = normalize(-oVertPosEC);

  // Vertex to the light.
  L = normalize(oVertToDistLight);

  // Distance light intensity.
  fragColor += getIntensity(distLight, material, L, N, V);
}

