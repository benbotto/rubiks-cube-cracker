// Vertex normal in eye space.
in vec3 oNormalEC;

// The vector from the vertex to the light.
in vec3 oVertToDistLight;

// The vertex position, which will be moved to eye coords.
in vec3 oVertPosEC;

// The vertex color.
in vec4 oColor;

uniform vec4           ambient;
uniform DistanceLight  distLight;
uniform Material       material;
uniform bool           materialEnabled;

out vec4 fragColor;

void main()
{
  vec3 L, N, V;

  // If material and texturing is disabled use the standard color.
  if (!materialEnabled)
  {
    fragColor = oColor;
    return;
  }

  // The global ambient effect on the frag color.
  fragColor = ambient * material.ambient;

  // The object's color.
  fragColor *= oColor * 50;

  // The vertex normal.
  N = normalize(oNormalEC);

  // The vector from the vertex to the eye.
  V = normalize(-oVertPosEC);

  // Vertex to the light.
  L = normalize(oVertToDistLight);

  // Distance light intensity.
  fragColor += getIntensity(distLight, material, L, N, V);
}

