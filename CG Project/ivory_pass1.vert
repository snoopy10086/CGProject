#version 330 core
                   
layout (location = 0) in vec3 v; //λ�ñ���������λ��ֵΪ0
layout (location = 1) in vec3 vn; 
uniform mat4 model_view;
uniform mat4 projection;
out vec4 vertexColor; 	//ָ��һ����ɫ�����ΪƬ����ɫ������

void main()
{

    //gl_Position = projection * (model_view * (vec4(v, 1.0) + normalize(vec4(vn, 0.0)))) ;
    gl_Position = projection * (model_view * vec4(v, 1.0)) ;
    vertexColor = vec4(0.0,0.0,1.0, 1.0); //�������������Ϊ��ɫ
}