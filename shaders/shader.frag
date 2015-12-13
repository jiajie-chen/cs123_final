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


mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv) {
    vec3 dp1 = dFdx(p);
    vec3 dp2 = dFdy(p);
    vec2 duv1 = dFdx(uv);
    vec2 duv2 = dFdy(uv);

    vec3 dp2perp = cross(dp2, N);
    vec3 dp1perp = cross(N, dp1);
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

    float invmax = inversesqrt(max(dot(T, T), dot(B, B)));
    return mat3(T * invmax, B * invmax, N);
}

vec3 perturb_normal(vec3 N, vec3 V) {
    vec3 map = texture(bump, texc).xyz;
    map = map * 255.f/127.f - 128.f/127.f;
    mat3 TBN = cotangent_frame(N, -V, texc);
    return normalize(TBN * map);
}

void main() {
    vec2 uv = texc;

    vec3 N = normalize(vec3(alsoNormal));
    vec3 eyeDirection = normalize(vec3(-alsoNormal));
    vec3 V = normalize(eyeDirection);
    vec3 PN = perturb_normal(N, V);

    vec4 texColor = texture(tex, texc).rgba;
    fragColor = vec4(.2, .15, .15, 1) * texColor;

    for (int i = 0; i < MAX_LIGHTS; i++) {
        vec4 vertexToLight = normalize(v * vec4(lightPositions[i], 1) - vec4(alsoPosition, 1));
        vec3 L = normalize(vec3(vertexToLight));
        float lambertTerm = dot(PN, L);
        if (lambertTerm > 0.0) {
            vec3 lightDiffuse = lightColors[i];
            vec3 materialDiffuse = diffuse_color;
            fragColor += vec4(lightDiffuse * materialDiffuse * lambertTerm * vec3(texColor), 0);

            vec3 E = V;
            vec3 R = reflect(-L, PN);
            float specular = pow(max(dot(R, E), 0.0), shininess);
            fragColor += vec4(lightColors[i] * specular_color * specular, 0);
        }
    }
    fragColor = clamp(fragColor, 0.0, 1.0);
    fragColor.a = 1;
}

// not used
 void main2(){
    vec3 color;
    vec3 position = alsoPosition;
    vec3 normal = alsoNormal;
    vec3 t;
    vec3 b;
    vec3 c1 = cross(normal, vec3(0, 0, 1));
    vec3 c2 = cross(normal, vec3(0, 1, 0));
    if (length(c1) > length(c2))
        t = c1;
    else
        t = c2;
    t = normalize(t);
    b = normalize(cross(normal, t));

    vec4 bumpVec   = normalize(vec4(texture(bump, texc).rgb * 2 - 1, 0));
    vec4 bumpedNormal_cameraSpace = normal_cameraSpace + bumpVec * useBump;

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
    color = clamp(color, 0.0, 1.0) * vec3(1);

    vec3 texColor = texture(tex, texc).rgb;

    texColor = clamp(texColor + vec3(1-useTexture), vec3(0), vec3(1));
    fragColor = vec4((color * texColor), 1);
    //vec3 bumpColor = texture(bump, texc).rgb;
    //fragColor = vec4(bumpColor, 1);
}

