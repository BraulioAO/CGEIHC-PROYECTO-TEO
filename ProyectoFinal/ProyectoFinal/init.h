#pragma once
void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

//Camera
Camera camera1(glm::vec3(-30.0f, 105.0f, 350.0f));  //Posición inicial de la cámara
Camera camera2(glm::vec3(0.0f, 30.0f, 35.0f));  //Posición inicial de la cámara
Camera *camera;

bool firstMouse = false;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//For Keyboard
int	estadoLuz = 1,
cameraActual = 1;

float	rotArr = 0.0f;


//Movimiento luz
float movLuzX = 0.0f;

// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

double	lastX = 0.0f,
		lastY = 0.0f;

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;
}

GLFWwindow* initWindow(const char *nombreVentana = "Ventana") {
	// glfw window creation
	// --------------------
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, nombreVentana, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, my_input);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();
	return window;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, (float)deltaTime);

	//To Configure Model
	//Endendido y apagado de luces
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		estadoLuz = 1;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		estadoLuz = 0;


	//Cambio de camara
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		cameraActual = 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		cameraActual = 2;

	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ2 -= 0.5f;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ2 += 0.5f;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posY2 -= 0.5f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posY2 += 0.5f;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		rotX2+=2.0f;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		rotX2-=2.0f;

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		rotPay+= 3.0f;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		rotPay-=3.0f;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotCol+= 3.0f;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rotCol-= 3.0f;

	//To save data keyFrame
	/*if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		saveFile();
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		openFile();
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		mostrarDatos();
		*/
	//To play KeyFrame animation terrestre
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		if (play == false && (FrameIndex > 1)){
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
			play = false;
	}

	//To play KeyFrame animation aereo
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		if (play2 == false && (FrameIndex2 > 1)) {
			resetElements2();
			//First Interpolation				
			interpolation2();

			play2 = true;
			playIndex2 = 0;
			i_curr_steps2 = 0;
		}
		else
			play2 = false;
	}

	//To Save a KeyFrame
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		if (FrameIndex2 < MAX_FRAMES2)
		{
			saveFrame2();
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}