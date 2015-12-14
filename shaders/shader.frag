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
uniform vec4 allBlack = vec4(1);


// used for object that are not normal-mapped
 void main2(){
    vec3 color;
    vec4 bumpedNormal_cameraSpace = normal_cameraSpace;

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
    color = clamp(color, 0.0, 1.0) * vec3(1);

    vec3 texColor = texture(tex, texc).rgb;

    texColor = clamp(texColor + vec3(1-useTexture), vec3(0), vec3(1));
    fragColor = vec4((color * texColor), 1);
}

 void main() {
     if (useBump == 0) {
         main2();
         return;
     }
     vec2 uv = texc;

     vec3 map = texture(bump, texc).xyz;
     map = map * 2 - 1;
     vec3 eye_cameraSpace = normalize(-vec3(position_worldSpace)); // TODO: incorrect
     // get edge vectors of the pixel triangle
     vec3 dp1 = dFdx( eye_cameraSpace );
     vec3 dp2 = dFdy( eye_cameraSpace );
     vec2 duv1 = dFdx( texc );
     vec2 duv2 = dFdy( texc );

     // solve the linear system
     vec3 dp2perp = cross( dp2, vec3(normal_worldSpace) );
     vec3 dp1perp = cross( vec3(normal_worldSpace), dp1 );
     vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
     vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

     // construct a scale-invariant frame
     float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
     mat3 TBN =  mat3( T * invmax, B * invmax, normal_worldSpace );

     vec4 bumpedNormal_cameraSpace = v * vec4(normalize(TBN * map), 0);
     vec3 color;




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
     color = clamp(color, 0.0, 1.0) * vec3(1);

     vec3 texColor = texture(tex, texc).rgb;

     texColor = clamp(texColor + vec3(1-useTexture), vec3(0), vec3(1));
     fragColor = vec4((color * texColor), 1);
 }
