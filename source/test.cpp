#include "../include/Common.h"
#define __WINDOW_WIDTH__ 800
#define __WINDOW_HEIGHT__ 800

static const char* vs_source[] = {
	"#version 410 core                                	\n"
	"                                                 	\n"
	"layout (location = 0) in vec4 offset;            	\n"
	"                                                 	\n"
	"void main()                                      	\n"
	"{                                                	\n"
	"    const vec4 vertices[3] = vec4[3](            	\n"
	"            vec4( 0.25, -0.25, 0.5, 1.0),        	\n"
	"            vec4(-0.25, -0.25, 0.5, 1.0),        	\n"
	"            vec4( 0.25, 0.25, 0.5, 1.0));        	\n"
	"                                                 	\n"
	"    gl_Position = vertices[gl_VertexID] + offset;	\n"
	"}                                                	\n"
};

static const char* fs_source[] = {
	"#version 410 core                                               	\n"
	"// color is the output color of this fragment shader            	\n"
	"out vec4 color;                                                 	\n"
	"                                                                	\n"
	"void main()                                                     	\n"
	"{                                                               	\n"
	"    // compute color based on the fragment’s screen coordinate	\n"
	"    color = vec4(                                               	\n"
	"        sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,                 	\n"
	"        cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,                 	\n"
	"        sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.15),	\n"
	"        1.0);                                                   	\n"
	"}                                                               	\n"
};

GLuint rendering_program;
GLuint vertex_array_object;
float time_count;

GLuint setup_shaders();
void my_init();
void my_display();
void my_reshape(int, int);
void my_timer(int);

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DOUBLE);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(__WINDOW_WIDTH__, __WINDOW_HEIGHT__);
    glutCreateWindow(__FILENAME__);

    glewInit();
    printGLContextInfo();

    my_init();

    glutDisplayFunc( my_display );
    glutReshapeFunc( my_reshape );
    glutTimerFunc(16, my_timer, 0);

    glutMainLoop();

    return 0;
}

GLuint setup_shaders(){
    GLuint vs_handle, fs_handle, program;

    vs_handle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs_handle, 1, vs_source, NULL);
    glCompileShader( vs_handle );

    std::cout << "\nVertex Shader Log:" << std::endl;
    printGLShaderLog(vs_handle);

    fs_handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs_handle, 1, fs_source, NULL);
    glCompileShader( fs_handle );

    std::cout << "\nFragment Shader Log:" << std::endl;
    printGLShaderLog(fs_handle);

    program = glCreateProgram();
    glAttachShader(program, vs_handle);
    glAttachShader(program, fs_handle);
    glLinkProgram(program);

    glDeleteShader(vs_handle);
    glDeleteShader(fs_handle);

    return program;
}

void my_init(){
    time_count = 0.0;
    rendering_program = setup_shaders();

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray( vertex_array_object );
}

void my_display(){
    static const GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glClearBufferfv( GL_COLOR, 0, white );

    glUseProgram( rendering_program );

    GLfloat attr[] = {sin(time_count)*0.5f, cos(time_count)*0.6f, 0.0f, 0.0f};
    glVertexAttrib4fv(0, attr);

    glPointSize( 40.0f );
    glDrawArrays(GL_TRIANGLES, 0, 3 );
    
    glutSwapBuffers();
}

void my_reshape(int width, int height){
    glViewport(0, 0, width, height);
    return;
}

void my_timer(int val){
    // do something
    time_count += 0.01f;
    glutPostRedisplay();
    glutTimerFunc(16, my_timer, val);
}