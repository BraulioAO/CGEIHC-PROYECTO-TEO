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
GLfloat contador = 0;

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

void display(Shader shader, Shader shaderLamp, Shader shaderSkybox, Model prueba, Model carpa, Model carpaInt,
			 Model grada)
{
	//Lighting
	//float posLuzX = movLuzX;
	float posLuzX = 0.0f;
	glm::vec3 lightPosition0(0.0f, 5.0f, 0.0f);
	glm::vec3 lightPosition1(posLuzX, 8.0f,  0.0f);
	glm::vec3 lightPosition2(posLuzX, 8.0f,  7.0f);
	glm::vec3 lightPosition3(-posLuzX, 8.0f, -7.0f);
	glm::vec3 lightPosition4(-posLuzX, 8.0f,  0.0f);
	glm::vec3 lightPosition5(-posLuzX, 8.0f,  7.0f);
	glm::vec3 lightDirection1(1.0f, -1.0f, -1.0f);  //Dirección de la luz ambiental 1
	glm::vec3 lightDirection2(-1.0f, -1.0f, 1.0f);  //Dirección de la luz ambiental 2


	shader.use();
	shader.setVec3("viewPos", camera.Position);

	//Luz direccional, fuente infinita
	shader.setVec3("dirLight[0].direction", lightDirection1);      // Se pasa la direccion de la fuente de luz direccional
	shader.setVec3("dirLight[0].ambient", glm::vec3(0.1f));    //AMBIENTAL, indica hacia que color tienden las caras menos iluminadas por la fuente de luz
	shader.setVec3("dirLight[0].diffuse", glm::vec3(0.5f));    //DIFUSA, indica el color que van a tomar las caras más iluminadas del objeto
	shader.setVec3("dirLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));   //ESPECULAR, se trata de simular un brillo que va a tener la superficie
	shader.setVec3("dirLight[1].direction", lightDirection2);      // Se pasa la direccion de la fuente de luz direccional
	shader.setVec3("dirLight[1].ambient", glm::vec3(0.1f));    //AMBIENTAL, indica hacia que color tienden las caras menos iluminadas por la fuente de luz
	shader.setVec3("dirLight[1].diffuse", glm::vec3(0.5f));    //DIFUSA, indica el color que van a tomar las caras más iluminadas del objeto
	shader.setVec3("dirLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));   //ESPECULAR, se trata de simular un brillo que va a tener la superficie

	//Luz posicional
	float lin = 0.001f;
	float quad = 0.003f;
	shader.setVec3("pointLight[0].position", lightPosition0);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[0].diffuse", estadoLuces);
	shader.setVec3("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[0].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[0].linear", lin);     //Distancia máxima
	shader.setFloat("pointLight[0].quadratic", quad);  //Distancia máxima
	/*
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
	*/

	shader.setFloat("material_shininess", 150.0f);

	// create transformations and Projection
	glm::mat4 temp = glm::mat4(1.0f);
	glm::mat4 origenCarpa = glm::mat4(1.0f);
	glm::mat4 centro = glm::mat4(1.0f);
	glm::mat4 origenMesa = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1600.0f);
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
	/*//FUENTE DE LUZ POSICIONAL 1
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
	glDrawArrays(GL_QUADS, 0, 24);*/
	


	/*----------------------------------------------------------*/
	/* -------- Shader con efectos de luz y texturizado ------- */
	/*----------------------------------------------------------*/
	shader.use();  //Shader con los efectos de luz y texturizado
	//PISO
	centro = glm::mat4(1.0f);
	//origenHab = glm::translate(origenHab, glm::vec3(posX, 0.0f, 0.0f));
	model = glm::translate(centro, glm::vec3(0.0f, -0.4f, 0.0f));
	model = glm::scale(model, glm::vec3(410.0f, 1.0f, 410.0f));
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_pasto);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
	shader.use();  //Shader con los efectos de luz y texturizado
	//******************************************************************************************
	//MODELOS CARGADOS
	//CARPA
	origenCarpa = glm::mat4(1.0);
	model = glm::translate(origenCarpa, glm::vec3(0.0f, -0.12f, 0.0f));
	model = glm::scale(model, glm::vec3(25.0, 28.0f, 25.0f));
	shader.setMat4("model", model);
	carpa.Draw(shader);
	//CARPA INTERIOR

	model = glm::translate(origenCarpa, glm::vec3(0.0f, -0.15f, 0.0f));
	model = glm::scale(model, glm::vec3(24.97, 27.97f, 24.97f));
	shader.setMat4("model", model);
	carpaInt.Draw(shader);

	model = glm::rotate(origenCarpa, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-3.0f, 0.0f, -20.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.5, 1.0));
	shader.setMat4("model", model);
	grada.Draw(shader);

	model = glm::rotate(origenCarpa, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3.2f, 0.0f, -23.5f));
	model = glm::scale(model, glm::vec3(1.0, 1.5, 1.0));
	shader.setMat4("model", model);
	grada.Draw(shader);




	glBindVertexArray(VAO);
	shaderSkybox.use();
	glm::vec3 centroCaja(0.0f, 90.0f, 0.0f);
	shaderSkybox.setVec3("lightColor", 1.0f, 1.0f, 1.0f); //Indica el color que genera la fuente de luz
	shaderSkybox.setVec3("lightPos", centroCaja);	//Indica posición de la luz
	shaderSkybox.setVec3("viewPos", camera.Position);
	shaderSkybox.setMat4("projection", projection);
	shaderSkybox.setMat4("view", view);
	shaderSkybox.setMat4("model", model);

	model = glm::mat4(1.0f);
	//model = glm::translate(model, camera.Position/2.0f);
	model = glm::translate(model, centroCaja);
	model = glm::scale(model, glm::vec3(400.0f));
	shaderSkybox.setMat4("model", model);	//SE PASAN VALORES DE ILUMINACIÓN
	shaderSkybox.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);  //DIFUSA, indica el color que van a tomar las caras más iluminadas del objeto
	glBindTexture(GL_TEXTURE_2D, t_dia);
	glDrawArrays(GL_QUADS, 48, 24);
	glBindVertexArray(0);
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
	Shader skyboxShader("shaders/shader_skybox.vs", "shaders/shader_skybox.fs");
	// Load models
	Model carpa = ((char*)"Models/carpa/carpa.obj");
	Model carpaInt = ((char*)"Models/carpaInterior/carpa.obj");
	Model grada = ((char*)"Models/grada/grada.obj");
	Model prueba = ((char*)"Models/prueba/grada.obj");
	

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

		display(modelShader, lampShader, skyboxShader, prueba, carpa, carpaInt, grada);

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

