#version 330 core
in vec3 position; // Position of the vertex
in vec3 normal;   // Normal of the vertex
out vec3 alsoPosition; // Position of the vertex
out vec3 alsoNormal;   // Normal of the vertex

out vec4 position_cameraSpace;
out vec4 normal_cameraSpace;
out vec4 position_worldSpace;
out vec4 normal_worldSpace;

in vec2 texCoord; // UV texture coordinates
//in float arrowOffset; // Sideways offset for billboarded normal arrows

out vec2 texc;
out mat4 view;
out mat4 model;

// Transformation matrices
uniform mat4 p;
uniform mat4 v;
uniform mat4 m;


void main(){
    texc = texCoord;
    //vec3 normal = (texture(tex, texc).rgb*2)-1;
    position_cameraSpace = v * m * vec4(position, 1.0);
    normal_cameraSpace = vec4(normalize(mat3(transpose(inverse(v * m))) * normal), 0);

    position_worldSpace = m * vec4(position, 1.0);
    normal_worldSpace = vec4(normalize(mat3(transpose(inverse(m))) * normal), 0);
    alsoPosition = position;
    alsoNormal = normal;
    gl_Position = p * position_cameraSpace;

    view = v;
    model = m;


    // color = abs(normal);
    // color = vec3(texCoord, 1.0);
}
