/*---------------------------------------------------------------*/
/* -----------------   Proyecto Final ---------------------------*/
/*------------------       2020-1     ---------------------------*/
/*---------- Alumno:  Arrieta Ocampo Braulio Enrique   ----------*/
//#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "camera.h"
#include "Model.h"

// Other Libs
#include "SOIL2/SOIL2.h"

// settings
#include "texturas.h"
#include "datosModelosPropios.h"
#include "keyFrame.h"
#include "init.h"


glm::vec3 estadoLuces;
float 	despPuerta = 0.0f;


void animate(void)
{

	if (estadoLuz == 1)
		estadoLuces = glm::vec3(1.0f, 1.0f, 1.0f);
	else
		estadoLuces = glm::vec3(0.0f, 0.0f, 0.0f);

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;
			rotAvion += rotInc;

			i_curr_steps++;
		}

	}
	
}

void display(Shader shader, Shader shaderLamp)
{
	//Lighting
	//float posLuzX = movLuzX;
	float posLuzX = 7.0f;
	glm::vec3 lightPosition0(posLuzX, 8.0f, -7.0f);
	glm::vec3 lightPosition1(posLuzX, 8.0f,  0.0f);
	glm::vec3 lightPosition2(posLuzX, 8.0f,  7.0f);
	glm::vec3 lightPosition3(-posLuzX, 8.0f, -7.0f);
	glm::vec3 lightPosition4(-posLuzX, 8.0f,  0.0f);
	glm::vec3 lightPosition5(-posLuzX, 8.0f,  7.0f);
	glm::vec3 lightPosition6(posLuzX-7.0f, 4.0f, 0.0f);
	glm::vec3 lightDirection(1.0f, -1.0f, -1.0f);  //Dirección de la luz ambiental


	shader.use();
	shader.setVec3("viewPos", camera.Position);

	//Luz direccional, fuente infinita
	shader.setVec3("dirLight.direction", lightDirection);  	// Se pasa la direccion de la fuente de luz direccional
	shader.setVec3("dirLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));	//AMBIENTAL, indica hacia que color tienden las caras menos iluminadas por la fuente de luz
	shader.setVec3("dirLight.diffuse", glm::vec3(0.2f, 0.2f, 0.2f));	//DIFUSA, indica el color que van a tomar las caras más iluminadas del objeto
	shader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));	//ESPECULAR, se trata de simular un brillo que va a tener la superficie

	//Luz posicional
	float lin = 0.001f;
	float quad = 0.03f;
	shader.setVec3("pointLight[0].position", lightPosition0);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[0].diffuse", estadoLuces);
	shader.setVec3("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[0].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[0].linear", lin);     //Distancia máxima
	shader.setFloat("pointLight[0].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[1].position", lightPosition1);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].diffuse", estadoLuces);
	shader.setVec3("pointLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[1].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[1].linear", lin);     //Distancia máxima
	shader.setFloat("pointLight[1].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[2].position", lightPosition2);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[2].diffuse", estadoLuces);
	shader.setVec3("pointLight[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[2].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[2].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[2].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[3].position", lightPosition3);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[3].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[3].diffuse", estadoLuces);
	shader.setVec3("pointLight[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[3].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[3].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[3].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[4].position", lightPosition4);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[4].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[4].diffuse", estadoLuces);
	shader.setVec3("pointLight[4].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[4].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[4].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[4].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[5].position", lightPosition5);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[5].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[5].diffuse", estadoLuces);
	shader.setVec3("pointLight[5].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[5].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[5].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[5].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[6].position", lightPosition6);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[6].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[6].diffuse", estadoLuces);
	shader.setVec3("pointLight[6].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[6].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[6].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[6].quadratic", quad);  //Distancia máxima

	shader.setFloat("material_shininess", 250.0f);

	// create transformations and Projection
	glm::mat4 temp = glm::mat4(1.0f);
	glm::mat4 origenHab = glm::mat4(1.0f);
	glm::mat4 origenMesa = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 150.0f);
	view = camera.GetViewMatrix();

	view = glm::scale(view, glm::vec3(2.0f, 2.0f, 2.0f));
//	view = glm::scale(view, glm::vec3(1.0f, 1.0f, 1.0f));

	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);


	//******************************************************************************************
	// MODELOS PROPIOS, A PARTIR DE CUBOS Y PLANOS

	/*----------------------------------------------------------*/
	/* ---- Shader sin efectos de luz, crea fuentes de luz ---- */
	/*----------------------------------------------------------*/
	glBindVertexArray(VAO);
	shaderLamp.use();	//
	/*
	//Se dibujan cubos amarillos para ubicar la posicion de las luces
	//Se reemplaza con las lámparas.
	//FUENTE DE LUZ POSICIONAL 0
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition0);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 1
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition1);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 2
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition2);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 3
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition3);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 4
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition4);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 5
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition5);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	*/

	/*----------------------------------------------------------*/
	/* -------- Shader con efectos de luz y texturizado ------- */
	/*----------------------------------------------------------*/
	shader.use();  //Shader con los efectos de luz y texturizado
	//CUBO EN EL CENTRO
	
	/*model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(rotAvion), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	shader.setVec3("aColor", 1.0f, 0.0f, 0.0f);
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_white);
	glDrawArrays(GL_QUADS, 0, 24);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	}*/
	//PISO
	origenHab = glm::mat4(1.0f);
	//origenHab = glm::translate(origenHab, glm::vec3(posX, 0.0f, 0.0f));
	model = glm::scale(origenHab, glm::vec3(28.0f, 1.0f, 28.0f));
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_piso);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	

	glBindVertexArray(0);

	//******************************************************************************************
	//MODELOS CARGADOS



	
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window = initWindow("Proyecto Final");

	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData();
	glEnable(GL_DEPTH_TEST);

	
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");
	// Load models
	//Model mesaModel = ((char*)"Models/Mesa/mesa.obj");
	

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0.0f;
		KeyFrame[i].posY = 0.0f;
		KeyFrame[i].posZ = 0.0f;
		KeyFrame[i].rotAvion = 0.0f;
		KeyFrame[i].abrirPuerta = 0;
	}
	openFile();

	double currentFrame;
	// render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		animate();

        // render
        // Backgound color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(modelShader, lampShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

