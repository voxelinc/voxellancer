#version 330

// Input
layout(location = 0) in vec3 v_vertex;
layout(location = 1) in vec3 v_normal;


layout(location = 2) in vec3 v_gridCell;
layout(location = 3) in vec4 v_color;
/*layout(location = 4) in float v_emissiveness;
*/
/*layout(location = 5) in vec3 v_originPosition;
layout(location = 6) in vec3 v_originEulers;
layout(location = 7) in vec3 v_directionalSpeed;
layout(location = 8) in vec3 v_angularSpeed;
layout(location = 9) in float v_originTime;
layout(location = 10) in float v_deathTime;
layout(location = 11) in float v_active;
*/

// Output
out vec3 f_color;
flat out vec3 f_normal;
out float f_deathTime;
out float f_emissiveness;
out vec3 f_modelposition;
out float f_active;


// Uniforms
uniform mat4 viewProjection;
uniform float time;
uniform float scale;


vec3 qtransform(vec4 q, vec3 v);
vec4 quat(vec3 euler);

void main() {
    /*
    float timeDelta = time - v_originTime;
    f_deathTime = v_deathTime;

    vec3 bulletPosition = v_directionalSpeed * timeDelta + v_originPosition;
    vec3 bulletEulers = v_angularSpeed * timeDelta + v_originEulers;
    vec4 bulletOrientation = quat(bulletEulers);
    f_color = v_color.xyz;
    f_emissiveness = v_emissiveness;
    f_modelposition = v_vertex;
    f_normal = qtransform(bulletOrientation, v_normal);
    
    f_active = v_active;

    gl_Position = viewProjection * vec4(qtransform(bulletOrientation, v_gridCell + v_vertex) * scale + bulletPosition, 1.0);
    */
    f_color = vec4(v_gridCell.x,1,v_color.x*0,1);
    f_normal = v_normal;
    f_deathTime = 1000;
    f_emissiveness = 0;
    f_modelposition = v_vertex;
    f_active = 1.0f;
    gl_Position = viewProjection * vec4(v_vertex + v_gridCell*0, 1.0f);
}

