in vec3 vertPos;
in vec4 vertColor;
in vec3 vertNormal;

uniform DistanceLight distLight;
uniform mat4          model;
uniform mat4          cubieTranslation;
uniform mat4          view;
uniform mat4          projection;

// Vertex normal converted to eye space.
out vec3 oNormalEC;

// The vector from light to the vertex, converted to eye space.
out vec3 oVertToDistLight;

// The vertex position in eye coords.
out vec3 oVertPosEC;

// The vertex color and position.
out vec4 oColor;
out vec3 oVertPos;
out vec3 oTranslatedVertPos;

void main()
{
  mat4 modelView     = view * model;
  mat4 normalTrans   = transpose(inverse(view * model));

  // Pass down the vertex position.  The translated position
  // is the position on the rubik's cube.
  oVertPos           = vertPos;
  oTranslatedVertPos = (cubieTranslation * vec4(vertPos, 1)).xyz;

  // Convert the vertex position to eye space.
  vec4 vertPosEC = modelView * vec4(vertPos, 1);

  // Pass the transformed vertex position down the pipeline.
  oVertPosEC = vertPosEC.xyz;

  // With a distance light the vector from the vertex to the light
  // is always the same - the opposite of the distance light's direction -
  // and the distance light is very far away.
  vec4 distLightPosEC = view * vec4(-distLight.direction * 1000.0, 1);
  oVertToDistLight    = (distLightPosEC - vertPosEC).xyz;

  // Pass down the color.
  oColor = vertColor;

  // Move the normal to eye space and pass it down.
  oNormalEC = (normalTrans * vec4(vertNormal, 0)).xyz;
  gl_Position = projection * vertPosEC;
}

