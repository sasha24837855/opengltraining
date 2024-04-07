#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/ShaderProgram.h"
#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>
#include <external/glm/gtc/type_ptr.hpp>
#include "stb/stb_image.h"
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
float vertices[] = {
	-0.5f, 0.5f,0,  //0
	-0.5f, -0.5f,0,  //1
	0.5f, 0.5f,0,   //2
	0.5f, -0.5f,0,  //3

	-0.5f, 0.5f,-1.0,  //4
	-0.5f, -0.5f,-1.0,  //5 
	0.5f, 0.5f,-1.0,  //6 
	0.5f, -0.5f,-1.0  //7
};
unsigned int indices[] = {
	1, 0, 3, // первый треугольник
	3, 2, 0,  // второй треугольник
	5, 4, 7,
	7, 6, 4,
	5, 4, 1,
	1, 0, 4,
	3, 2, 7,
	7, 6, 2,
	0, 4, 2,
	2, 6, 4,
	7, 3, 5,
	5, 1, 3


};
GLfloat points2[] =
{
	 0.5f,  0.5f, 0.0f,  // верхн€€ права€
	 0.5f, -0.5f, 0.0f,  // нижн€€ права€
	-0.5f, -0.5f, 0.0f,  // нижн€€ лева€
	-0.5f,  0.5f, 0.0f   // верхн€€ лева€ 

};

GLfloat textcoord[] =
{
	 1.0f, 1.0f,  // верхн€€ права€
	 1.0f, 0.0f,   // нижн€€ права€
	 0.0f, 0.0f,  // нижн€€ лева€
	 0.0f, 1.0f,    // верхн€€ лева€ 

};


int windowSizeX = 800;
int windowSizeY = 600;
int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(windowSizeX, windowSizeY, "heh", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to load GLAD" << endl;
		return -1;
	}
	glClearColor(0, 0, 0, 0);
	
	
	renderer::ShaderProgram shaderProgram("C:/proekti/opengltraining/src/renderer/Vshader.txt",
											"C:/proekti/opengltraining/src/renderer/Fshader.txt");
	if (!shaderProgram.isCompiled()) {
		std::cerr << "cant create shader program" << std::endl;
	}

	unsigned int vao = 0;
	unsigned int ebo = 0;
	unsigned int points_vbo = 0;
	unsigned int texcoord_vbo = 0;




	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &points_vbo);
	glGenBuffers(1, &ebo);

	glGenBuffers(1, &texcoord_vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textcoord), textcoord, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);

	
	
			 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	int width, height, nrChannels;
	unsigned char* data = stbi_load("../textures/tex4.jpg", &width, &height, &nrChannels, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
	}
	else {
		std::cout << "failed to generate texture" << std::endl;
	}
	stbi_image_free(data);
	
	
	glEnable(GL_DEPTH_TEST);

	glm::vec3 cubePositions[] = {
		 glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	while (!glfwWindowShouldClose(window))

	{
		
		
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		

		
		
		int modelLoc = glGetUniformLocation(shaderProgram.getm_ID(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));		 //get model matrix adress

		int viewLoc = glGetUniformLocation(shaderProgram.getm_ID(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));		 //get view matrix adress

		int projectionLoc = glGetUniformLocation(shaderProgram.getm_ID(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));   //get projection matrix adress

		
		shaderProgram.use();

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);

	/*	for (int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
		*/
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		
		
		
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &points_vbo);
	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}