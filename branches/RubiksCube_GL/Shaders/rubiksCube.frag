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

  // Each cubie has a colored sticker on it that's square.
  if (oVertPos.x > -.46 && oVertPos.x < .46 && oVertPos.y > -.46 && oVertPos.y < .46 ||
      oVertPos.x > -.46 && oVertPos.x < .46 && oVertPos.z > -.46 && oVertPos.z < .46 ||
      oVertPos.y > -.46 && oVertPos.y < .46 && oVertPos.z > -.46 && oVertPos.z < .46)
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

