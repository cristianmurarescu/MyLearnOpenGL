#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Vertex shader source code
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

// Fragment shader source code
const char* fragmentShaderSourceOne =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

// Fragment shader source code
const char* fragmentShaderSourceTwo =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n";

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

	float verticesOne[] = {
		-0.5f,  0.5f, 0.0f,  // top-left
		 0.5f,  0.5f, 0.0f,  // top-right
		 0.0f,  0.0f, 0.0f,  // tip (center)
	};

	float verticesTwo[] = {
		-0.5f, -0.5f, 0.0f,  // bottom-left
		 0.5f, -0.5f, 0.0f,  // bottom-right
		 0.0f,  0.0f, 0.0f,  // tip (center)
	};

	//float vertices[] = {
	//	// first triangle
	//	0.5f, 0.5f, 0.0f,   // top right
	//	0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f, // bottom left
	//	-0.5f, 0.5f, 0.0f   // top left
	//};

	//unsigned int indices[] = { // note that we start from 0!
	//	0, 1, 3, // first triangle
	//	1, 2, 3  // second triangle
	//};

	// Generate a vertex buffer object (VBO)
    unsigned int vertexBufferObjects[2];
	glGenBuffers(2, vertexBufferObjects);

	// Generate a element buffer object (EBO)
	//unsigned int elementBufferObject;
	//glGenBuffers(1, &elementBufferObject);

	// Generate a vertex array object (VAO)
	unsigned int vertexArrayObjects[2];
	glGenVertexArrays(2, vertexArrayObjects);

	// Bind the vertex array object for rendering
	glBindVertexArray(vertexArrayObjects[0]);
	
	// Bind the vertex buffer object and copy the vertex data into it
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOne), verticesOne, GL_STATIC_DRAW);
	
	// Specify the layout of the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vertexArrayObjects[1]);

	// Bind the vertex buffer object and copy the vertex data into it
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTwo), verticesTwo, GL_STATIC_DRAW);

	// Specify the layout of the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Bind the element buffer object and copy the index data into it
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Call after suspicious GL calls during setup
	while (GLenum err = glGetError()) {
		std::cerr << "GL error: 0x" << std::hex << err << std::endl;
	}


    // Create a vertex shader object
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attach the shader source code to the vertex shader object and compile the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Values to store the success status and error message of shader compilation
	int success;
	char infoLog[512];

	// Check for vertex shader compile errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}  

	// Create a fragment shader object
	unsigned int fragmentShaderOne;
	fragmentShaderOne = glCreateShader(GL_FRAGMENT_SHADER);

	// Attach the shader source code to the fragment shader object and compile the shader
	glShaderSource(fragmentShaderOne, 1, &fragmentShaderSourceOne, nullptr);
	glCompileShader(fragmentShaderOne);

	// Check for fragment shader compile errors
	glGetShaderiv(fragmentShaderOne, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderOne, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Create a fragment shader object
	unsigned int fragmentShaderTwo;
	fragmentShaderTwo = glCreateShader(GL_FRAGMENT_SHADER);

	// Attach the shader source code to the fragment shader object and compile the shader
	glShaderSource(fragmentShaderTwo, 1, &fragmentShaderSourceTwo, nullptr);
	glCompileShader(fragmentShaderTwo);

	// Check for fragment shader compile errors
	glGetShaderiv(fragmentShaderTwo, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderTwo, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create a shader program object and link the vertex and fragment shaders to it
	unsigned int shaderProgramOne;
	shaderProgramOne = glCreateProgram();
	glAttachShader(shaderProgramOne, vertexShader);
	glAttachShader(shaderProgramOne, fragmentShaderOne);
	glLinkProgram(shaderProgramOne);

	// Check for shader program linking errors
	glGetProgramiv(shaderProgramOne, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramOne, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}	

	// Create a shader program object and link the vertex and fragment shaders to it
	unsigned int shaderProgramTwo;
	shaderProgramTwo = glCreateProgram();
	glAttachShader(shaderProgramTwo, vertexShader);
	glAttachShader(shaderProgramTwo, fragmentShaderTwo);
	glLinkProgram(shaderProgramTwo);


	// Delete the shader objects once we've linked them into the shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOne);
	glDeleteShader(fragmentShaderTwo);

	// Create the viewport and set its dimensions (x, y, width, height)
	glViewport(0, 0, 800, 600);

	// Render loop
    while (!glfwWindowShouldClose(window))
    {
		// Input
        processInput(window);

		// Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		// Use the shader program for rendering
		glUseProgram(shaderProgramOne);

		// Bind the vertex array object for rendering
		glBindVertexArray(vertexArrayObjects[0]);
		

		// Draw the triangle using the currently bound vertex array object and shader program
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramTwo);

		glBindVertexArray(vertexArrayObjects[1]);

		// Draw the triangle using the currently bound vertex array object and shader program
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

	// Clean up and exit
    glfwTerminate();
    return 0;
}
