#version 330 core

in vec2 texc;
out vec4 fragColor;

uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

in vec3 alsoPosition; // Position of the vertex
in vec4 position_cameraSpace;
in vec4 normal_cameraSpace;
in vec4 position_worldSpace;
in vec4 normal_worldSpace;
in vec3 alsoNormal;   // Normal of the vertex


uniform sampler2D tex;
uniform int useTexture = 0;
uniform sampler2D bump;
uniform int useBump = 0;

// Light data
const int MAX_LIGHTS = 10;
uniform int lightTypes[MAX_LIGHTS];         // 0 for point, 1 for directional
uniform vec3 lightPositions[MAX_LIGHTS];    // For point lights
uniform vec3 lightDirections[MAX_LIGHTS];   // For directional lights
uniform vec3 lightAttenuations[MAX_LIGHTS]; // Constant, linear, and quadratic term
uniform vec3 lightColors[MAX_LIGHTS];

// Material data
uniform vec3 ambient_color;
uniform vec3 diffuse_color;
uniform vec3 specular_color;
uniform float shininess;
//in float arrowOffset; // Sideways offset for billboarded normal arrows
//uniform bool useArrowOffsets; // True if rendering the arrowhead of a normal for Shapes

uniform bool useLighting;     // Whether to calculate lighting using lighting equation
uniform vec3 allBlack = vec3(1);


void main(){
    vec3 color;
    vec3 position = alsoPosition;
    vec3 normal = alsoNormal;
    vec4 bumpVec   = normalize(vec4(texture(bump, texc).rgb * 2 - 1, 0));
    bumpVec / 2;

    vec4 bumpedNormal_cameraSpace = normal_cameraSpace + bumpVec;

    // lol arrow mode
    /*
    if (useArrowOffsets) {
        // Figure out the axis to use in order for the triangle to be billboarded correctly
        vec3 offsetAxis = normalize(cross(vec3(position_cameraSpace), vec3(normal_cameraSpace)));
        position_cameraSpace += arrowOffset * vec4(offsetAxis, 0);
    }
    */
    if (useLighting) {
        color = ambient_color.xyz; // Add ambient component

        for (int i = 0; i < MAX_LIGHTS; i++) {
            vec4 vertexToLight = vec4(0);
            // Point Light
            if (lightTypes[i] == 0) {
                vertexToLight = normalize(v * vec4(lightPositions[i], 1) - position_cameraSpace);
            } else if (lightTypes[i] == 1) {
                // Dir Light
                vertexToLight = normalize(v * vec4(-lightDirections[i], 0));
            }

            // Add diffuse component
            float diffuseIntensity = max(0.0, dot(vertexToLight, bumpedNormal_cameraSpace));
            color += max(vec3(0), lightColors[i] * diffuse_color * diffuseIntensity);

            // Add specular component
            vec4 lightReflection = normalize(-reflect(vertexToLight, bumpedNormal_cameraSpace));
            vec4 eyeDirection = normalize(vec4(0,0,0,1) - position_cameraSpace);
            float specIntensity = pow(max(0.0, dot(eyeDirection, lightReflection)), shininess);
            color += max (vec3(0), lightColors[i] * specular_color * specIntensity);
        }
    } else {
        color = ambient_color + diffuse_color;
    }
    color = clamp(color, 0.0, 1.0) * allBlack;

    vec3 texColor = texture(tex, texc).rgb;

    texColor = clamp(texColor + vec3(1-useTexture), vec3(0), vec3(1));
    fragColor = vec4((color * texColor), 1);
    //vec3 bumpColor = texture(bump, texc).rgb;
    //fragColor = vec4(bumpColor, 1);
}

