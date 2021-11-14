#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
	{
	//initialise GLWF
	glfwInit();

	// glad -> version of OpenGL (3.3)

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// GLFW-CORE Profile
	// only modern functionality
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//vertices coordinates 
	GLfloat vertices[] =
		{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner

		};

	// creates window with given param
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	// in case of NULL value, window terminates 
	if (window == NULL)
		{

		std::cout << "Failed to load GLFW window" << std::endl;
		glfwTerminate();
		return -1;

		}

	// introduces the window into the current context
	glfwMakeContextCurrent(window);


	//load glad so it configures opengl for me
	gladLoadGL();
	// creates window from x = 0 and y = 0 to x = 800 and y = 800
	glViewport(0, 0, 800, 800);


	//CREATES VERTEX SHADER
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach vertex shader source to the vertex shader object 
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile the vertex shader
	glCompileShader(vertexShader);


	//CREATES FRAGMENT SHADER
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//compile the fragment shader
	glCompileShader(fragmentShader);


	//create shader prgram object
	GLuint shaderProgram = glCreateProgram();
	//attach vertex and fragment shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//link all shaders together into shader program
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// create reference containers for the vertex array object and the vertex buffer 
	GLuint VAO, VBO;
	//generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//make VAO the current vertex array object
	glBindVertexArray(VAO);
	
	//bind the VBO specifying its a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // vertices will be modified

	//configure the vertex attribute so that OpenGl knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//enable the VAO so openl knows to use it
	glEnableVertexAttribArray(0);
	
	
	//bind both VBO and VAO to 0 so we cant modify it
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);






	//specify colour in frame
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//clean back buffer and assign new colour to it

	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// main while loop 
	while (!glfwWindowShouldClose(window))
		{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//which shader program opengl must use
		glUseProgram(shaderProgram);
		//bind the VBO so opengl knows to use it
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		//draws the object
		glfwSwapBuffers(window);
		//ALL GLFW events

		glfwPollEvents();
		}


	// delete the objects we've made 
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

	}