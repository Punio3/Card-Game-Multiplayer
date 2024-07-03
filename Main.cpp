#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
using namespace std;


int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
		0.5f,-0.5f * float(sqrt(3))/3,0.0f,
		0.0f,0.5f * float(sqrt(3))*2/3,0.0f,
		-0.5f/2,0.5f*float(sqrt(3))/6,0.0f,
		0.5f/2,0.5f*float(sqrt(3))/6,0.0f,
		0.0f,-0.5f*float(sqrt(3))/3,0.0f
	};

	GLuint indices[] =
	{
		0,3,5,
		3,2,4,
		5,4,1
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "Gra", NULL, NULL);
	if (window == NULL) {
		cout << "Nie udalo sie stworzyc okna" << endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();


	glViewport(0, 0, 800, 800);

	Shader shaderProgram("deafult.vert", "default.frag");
	
	VAO vao;
	vao.Bind();

	VBO vbo(vertices,sizeof(vertices));
	EBO ebo(indices,sizeof(indices));


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}