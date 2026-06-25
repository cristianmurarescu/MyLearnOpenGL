#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Shader.h"

#include "stb_image.h"

#include "Camera.h"


glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f); // Define the position of the camera in world space
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // Define the direction the camera is facing in world space
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Define the up vector for the camera in world space

float yaw = -90.0f; // Initialize the yaw angle for the camera
float pitch = 0.0f; // Initialize the pitch angle for the camera

bool firstMouse = true; // Flag to check if this is the first mouse movement

float lastMouseX = 400.0f; // Initialize the last mouse X position to the center of the window
float lastMouseY = 300.0f; // Initialize the last mouse Y position to the center of the window

float fov = 45.0f; // Initialize the field of view for the camera

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // Create a Camera object with the initial position))

// Function to process input
void processInput(GLFWwindow* window)
{
	float deltaTime = 0.0f; // Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	float currentFrame = glfwGetTime(); // Get the current time
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastMouseX = xpos;
		lastMouseY = ypos;
		firstMouse = false;
	}

	float xOffset = xpos - lastMouseX;
	float yOffset = lastMouseY - ypos;
	lastMouseX = xpos;
	lastMouseY = ypos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide the cursor and capture it for camera movement
	glfwSetCursorPosCallback(window, mouse_callback); // Set the mouse callback function to handle mouse movement
	glfwSetScrollCallback(window, scroll_callback); // Set the scroll callback function to handle mouse scroll events)

	// Load all OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

	// Enable depth testing for correct rendering of 3D objects
	glEnable(GL_DEPTH_TEST);

	// Define the vertex data for a cube (XYZ)
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	// Define the positions of multiple cubes in the scene
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// Texture coordinate attribute
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// Create a shader program from the vertex and fragment shader source files
	Shader shaderProgram("vertex_shader.glsl", "fragment_shader.glsl");

	// Activate the shader program before setting any uniforms
	shaderProgram.use();
	shaderProgram.setInt("texture1", 0); // Set the texture uniform to the corresponding texture unit
	shaderProgram.setInt("texture2", 1); // Set the texture uniform to the corresponding texture unit

	// Create the viewport and set its dimensions (x, y, width, height)
	glViewport(0, 0, 800, 600);

	// Render loop
    while (!glfwWindowShouldClose(window))
    {
		// Input
        processInput(window);

		// Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculate the green color value based on the current time
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");

		// Bind the texture for rendering
		//glBindTexture(GL_TEXTURE_2D, texture);

		// Use the shader program for rendering
		shaderProgram.use();

		// Create the model matrix and apply transformations to it
		glm::mat4 model = glm::mat4(1.0f); // Initialize the model matrix to the identity matrix
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate the model matrix by -55 degrees around the X-axis
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); // Rotate the model matrix by an angle that changes over time around the axis (0.5, 1.0, 0.0)

		// Create the view matrix and apply transformations to it
		glm::mat4 view; // Initialize the view matrix to the identity matrix
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // Translate the view matrix by (0, 0, -3) to move the camera back along the Z-axis
		//view = glm::lookAt(cameraPosition, cameraTarget, cameraUp); // Create a view matrix using the lookAt function with the camera position, target point, and up vector

		// Create the view matrix and apply transformations to it
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f); // Create a perspective projection matrix with a field of view of 45 degrees, an aspect ratio of 800/600, and near and far clipping planes at 0.1 and 100.0 units, respectively))

		shaderProgram.setMat4("model", model); // Set the value of the model matrix uniform in the shader program)

		view = camera.GetViewMatrix(); // Get the view matrix from the camera object

		shaderProgram.setMat4("view", view); // Set the value of the view matrix uniform in the shader program
		
		shaderProgram.setMat4("projection", projection); // Set the value of the projection matrix uniform in the shader program")

		glm::mat4 transformMatrix = glm::mat4(1.0f); // Initialize the transformation matrix to the identity matrix
		transformMatrix = glm::translate(transformMatrix, glm::vec3(0.5f, -0.5f, 0.0f)); // Rotate the transformation matrix by 90 degrees around the Z-axis
		transformMatrix = glm::rotate(transformMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // Scale the transformation matrix by a factor of 0.5 in all dimensions)

		shaderProgram.setMat4("transform", transformMatrix); // Set the value of the transformation matrix uniform in the shader program

		// Bind the vertex array object for rendering
		glBindVertexArray(vertexArrayObject);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f); // Initialize the model matrix to the identity matrix)
			model = glm::translate(model, cubePositions[i]); // Translate the model matrix by the position of the current cube
			float angle = 20.0f * i; // Calculate the rotation angle for the current cube based on its index
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f)); // Rotate the model matrix by an angle that changes over time around the axis (1.0, 0.3, 0.5)
			shaderProgram.setMat4("model", model); // Set the value of the model matrix uniform in the shader program for the current cube)
			// Draw the triangle using the currently bound vertex array object and shader program
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
