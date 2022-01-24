#version 330 core
                   
layout (location = 0) in vec3 v; //位置变量的属性位置值为0
layout (location = 1) in vec3 vn; 
uniform mat4 model_view;
uniform mat4 projection;
out vec4 vertexColor; 	//指定一个颜色输出作为片段着色器输入

void main()
{

    vec3 normal = mat3(inverse(transpose(model_view))) * vn ;
    gl_Position = projection * (model_view * (vec4(v, 1.0) + normalize(vec4(vn, 0.0))*0.5 )) ;
    // gl_Position = projection * (model_view * vec4(v, 1.0)) ;
    vertexColor = vec4(0.0,0.0,0.0, 1.0); //把输出变量设置为黑色
}