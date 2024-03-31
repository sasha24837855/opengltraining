#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/ShaderProgram.h"
#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>
#include <external/glm/gtc/type_ptr.hpp>
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLfloat point[] =
{
-1.0f,-0.5f,0.0f,
0.0f,-0.5f,0.0f,
-0.5f,0.5f,0.0f,

0.0f,-0.5f,0.0f,
0.5f,0.5f,0.0f,
1.0f,-0.5f,0.0f,
};
GLfloat colors[] = {
//1.0f,0.0f,0.0f,
//0.0f,1.0f,0.0f,
//0.0f,0.0f,1.0f,
1.0f,0.0f,0.0f,
1.0f,0.0f,0.0f,
1.0f,0.0f,0.0f,

0.0f,1.0f,0.0f,
0.0f,1.0f,0.0f,
0.0f,1.0f,0.0f,


};
GLfloat colors2[] = {
0.0f,0.0f,1.0f,
0.0f,0.0f,1.0f,
0.0f,0.0f,1.0f,
};


int windowSizeX = 640;
int windowSizeY = 480;
int main() {


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(windowSizeX, windowSizeY, "heh", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed ti create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to load GLAD" << endl;
		return -1;
	}
	glClearColor(1, 1, 0.4, 1);
	
	
	renderer::ShaderProgram shaderProgram("C:/proekti/opengltraining/src/renderer/Vshader.txt",
											"C:/proekti/opengltraining/src/renderer/Fshader.txt");
	if (!shaderProgram.isCompiled()) {
		std::cerr << "cant create shader program" << std::endl;
	}

	GLuint points_vbo = 0;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLint), point, GL_STATIC_DRAW);


	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint vao = 0;
	

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		float timeValue = glfwGetTime();
		float greenValue = sin(tan(timeValue));
		int vertexColorLocation = glGetUniformLocation(shaderProgram.getm_ID(), "color");

		int vertex1LocationLocation = glGetUniformLocation(shaderProgram.getm_ID(), "vertex1");
		int vertex2LocationLocation = glGetUniformLocation(shaderProgram.getm_ID(), "vertex2");
		int vertex3LocationLocation = glGetUniformLocation(shaderProgram.getm_ID(), "vertex3");


		shaderProgram.use();
		glUniform4f(vertexColorLocation, sin(timeValue), cos(timeValue), sin(timeValue), 1.0f);
		glUniform3f(vertex1LocationLocation, sin(timeValue), sin(timeValue), point[2]);
		glUniform3f(vertex2LocationLocation, cos(timeValue), sin(timeValue), point[5]);
		glUniform3f(vertex3LocationLocation, sin(timeValue), cos(timeValue), point[8]);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &colors_vbo);
	glDeleteBuffers(1, &points_vbo);
	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}