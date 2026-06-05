#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

#include "stb_image.h"

// Function to process input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
	// Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

	// Set the required OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "MyLearnOpenGL", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

	// Make the OpenGL context of the window current on the calling thread
    glfwMakeContextCurrent(window);

	// Load all OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.75f, 0.75f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.75f, 0.25f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.25f, 0.25f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.25f, 0.75f    // top left 
	};

	// Texture 1
	// Generate a texture object and bind it to the GL_TEXTURE_2D target
	unsigned int texture;
	glActiveTexture(GL_TEXTURE0); // Activate the texture unit before binding the texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set the texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load the texture image using stb_image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		// Set the texture wrapping parameters
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// Free the image data after generating the texture
	stbi_image_free(data);

	stbi_set_flip_vertically_on_load(true); // Flip the texture image vertically on load to match OpenGL's coordinate system

	// Texture 2
	// Generate a texture object and bind it to the GL_TEXTURE_2D target
	unsigned int texture2;
	glActiveTexture(GL_TEXTURE1); // Activate the texture unit before binding the texture
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set the texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load the texture image using stb_image
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		// Set the texture wrapping parameters
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// Free the image data after generating the texture
	stbi_image_free(data);

	unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// Generate a vertex buffer object (VBO)
    unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);

	// Generate a element buffer object (EBO)
	unsigned int elementBufferObject;
	glGenBuffers(1, &elementBufferObject);

	// Generate a vertex array object (VAO)
	unsigned int vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);

	// Bind the vertex array object for rendering
	glBindVertexArray(vertexArrayObject);
	
	// Bind the vertex buffer object and copy the vertex data into it
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the element buffer object and copy the index data into it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Specify the layout of the vertex data
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Create a shader program from the vertex and fragment shader source files
	Shader shaderProgram("vertex_shader.glsl", "fragment_shader.glsl");

	// Activate the shader program before setting any uniforms
	shaderProgram.use();
	shaderProgram.setInt("texture1", 0); // Set the texture uniform to the corresponding texture unit
	shaderProgram.setInt("texture2", 1); // Set the texture uniform to the corresponding texture unit


	// Create the viewport and set its dimensions (x, y, width, height)
	glViewport(0, 0, 800, 600);

	float mixAmount = 0.0f;

	// Render loop
    while (!glfwWindowShouldClose(window))
    {
		// Input
        processInput(window);

		// Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");

		int mixAmountLocation = glGetUniformLocation(shaderProgram.ID, "mixAmount");

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			if (mixAmount >= 1.0f)
			{
				mixAmount = 1.0f;
			}
			else
			{
				mixAmount += 0.01f;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			if (mixAmount <= 0.0f)
			{
				mixAmount = 0.0f;
			}
			else
			{
				mixAmount -= 0.01f;
			}
		}
		glUniform1f(mixAmountLocation, mixAmount);

		// Use the shader program for rendering
		shaderProgram.use();


		// Bind the vertex array object for rendering
		glBindVertexArray(vertexArrayObject);

		// Draw the triangle using the currently bound vertex array object and shader program
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

	// Optional: de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObject);

	// Clean up and exit
    glfwTerminate();
    return 0;
}
