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
#include <Windows.h>

#include "camera.h"
#include "Model.h"

// Other Libs
#include "SOIL2/SOIL2.h"


// settings
#include "texturas.h"
#include "datosModelosPropios.h"
#include "keyFrame.h"
#include "musica.h"
#include "init.h"

#include <time.h>
void wait(unsigned timeout)
{
	timeout += clock();
	while (clock() < timeout) continue;
}

glm::vec3 estadoLuces, estadoLucesEscenario;
float 	rotOso = 0.0f,
		rotPelota = 0.0f,
		movGloboZ = 0.0f,
		movGloboY = 0.0f,
		rotSombrilla = 0.0f;

bool fin1 = false, fin2 = false;


float contZ = 0.0f;
float contY = 0.0f;
float contX = 0.0f;
float contX1 = 0.0f;
float contZ1 = 0.0f;
float contZ2 = 0.0f;
double der = 0, der1 = 0, der2 = 0;
double izq = 0, izq1 = 0;


void animate(void)
{
	if (rotOso < 360.0f)
		rotOso+=1.0f;
	else
		rotOso = 0.0f;

	if (rotPelota < 360.0f)
		rotPelota+=4.0f;
	else
		rotPelota = 0.0f;

	if (rotSombrilla < 360.0f)
		rotSombrilla += 4.0f;
	else
		rotSombrilla = 0.0f;


	if (fin1 == false) {
		movGloboZ += 0.1f;
		if(movGloboZ > 9.0f)
			fin1 = true;
	}
	else{
		movGloboZ -= 0.1f;
		if (movGloboZ < 0.0f)
			fin1 = false;
	}

	if (fin2 == false) {
		movGloboY += 0.04f;
		if (movGloboY > 4.0f)
			fin2 = true;
	}
	else {
		movGloboY -= 0.04f;
		if (movGloboY < 0.0f)
			fin2 = false;
	}

	if(!modoLibre)
		if (cameraActual == 1)
			camera = &camera1;
		else if (cameraActual == 2)
			camera = &camera2;


	if (estadoLuz == 1 && estadoLuzEscenario ==1)
		estadoLuces = glm::vec3(0.8f);
	else if (estadoLuz == 1 && estadoLuzEscenario == 0)
		estadoLuces = glm::vec3(1.0f, 1.0f, 1.0f);
	else
		estadoLuces = glm::vec3(0.0f, 0.0f, 0.0f);

	if (estadoLuzEscenario == 1)
		estadoLucesEscenario = glm::vec3(0.40f);
	else
		estadoLucesEscenario = glm::vec3(0.0f);


	if (play){
		if (i_curr_steps >= i_max_steps){ //end of animation between frames?
			playIndex++;
			if (playIndex > FrameIndex - 2){	//end of total animation?
				printf("termina anim 1\n");
				playIndex = 0;
				play = false;
				sonidoActo1 = false;
			}
			else{ //Next frame interpolations
				i_curr_steps = 0; //Reset counter	  
				interpolation();//Interpolation
				if (playIndex > 1)
					sonidoActo1 = false;
			}
		}
		else{
			//Draw animation
			posY += incY;
			posZ += incZ;
			rotX += incRotX;
			i_curr_steps++;
		}
	}

	if (play2) {
		if (i_curr_steps2 >= i_max_steps2) { //end of animation between frames?
			playIndex2++;
			if (playIndex2 > FrameIndex2 - 2) {	//end of total animation?
				printf("termina anim 2\n");
				playIndex2 = 0;
				play2 = false;
				sonidoActo2 = false;
			}
			else { //Next frame interpolations
				if (playIndex2 > 4)
					sonidoActo2 = false;
				i_curr_steps2 = 0; //Reset counter	  
				interpolation2();//Interpolation
			}
		}
		else {
			//Draw animation
			posY2 += incY2;
			posZ2 += incZ2;
			rotX2 += incRotX2;
			rotPay += incRotPay;
			rotCol += incRotCol;
			i_curr_steps2++;
		}
	}

	
	if (modoLibre) {
		lastX = SCR_WIDTH / 2.0f;
		lastY = SCR_HEIGHT / 2.0f;
		camera = &camera4; 
		if (contZ < 36.0f) { //36
			camera->ProcessKeyboard(FORWARD, (float)deltaTime);
			mouseModoLibre(mouseX, mouseY);
			contZ+= 0.5;
		}
		else if (contZ < 50.0f) {
			contZ += 0.5;
		}
		else if (contZ < 51.0f) {
			contZ ++;
			resetElements2();			
			interpolation2();
			play2 = true;
			playIndex2 = 0;
			i_curr_steps2 = 0;
			resetElements();			
			interpolation();
			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else if (contZ < 54.0f) {
			contZ += 0.5;
		}
		else {
			if (contX < 2.0f) {
				camera->ProcessKeyboard(LEFT, (float)deltaTime);
				mouseModoLibre(mouseX, mouseY);
				contX += 0.5;
			}
			else if (contX < 9.0f) {
				contX += 0.5;
			}
			else {
				if (der < 14) {
					mouseModoLibre(mouseX + der, mouseY);
					der += 0.5;
				}
				else if (der < 60) {
					der += 0.5;
				}
				else if (izq < 14) {
					mouseModoLibre(mouseX - izq, mouseY);
					izq += 0.5;
				}
				else if (izq < 28) {
					izq += 0.5;
				}
				else {

					if (contX1 < 2.5f) {
						camera->ProcessKeyboard(RIGHT, (float)deltaTime);
						mouseModoLibre(mouseX, mouseY);
						contX1 += 0.5;
					}
					else {
						if (contZ1 < 12.0f) {
							camera->ProcessKeyboard(BACKWARD, (float)deltaTime);
							mouseModoLibre(mouseX, mouseY);
							contZ1 += 0.5;
						}
						else {
							if (der1 < 13) {
								mouseModoLibre(mouseX + der1, mouseY);
								der1 += 0.5;
							}
							else if (der1 < 30) {
								der1 += 0.5;
							}
							else if (izq1 < 13) {
								mouseModoLibre(mouseX - izq1, mouseY);
								izq1 += 0.5;
							}
							else if (izq1 < 30) {
								izq1 += 0.5;
							}
							else {
								if (contZ1 < 40.0f) {
									camera->ProcessKeyboard(BACKWARD, (float)deltaTime);
									mouseModoLibre(mouseX, mouseY);
									contZ1 += 0.5;
								}
								else if (contZ1 < 60.0f) {
									contZ1 += 0.5;
								}
								else {
									modoLibre = false;
									contZ = 0.0f;
									contX = 0.0f;
									contZ1 = 0.0f;
									contX1 = 0.0f;
									der = 0;
									der1 = 0;
									der2 = 0;
									izq = 0;
									izq1 = 0;
									play = false;
									play2 = false;
								}
								
							}
						}
					}
				}
			}
		}
		//printf("contZ: %f\n", contZ);
		
		
	}
	//printf("lastX: %f, lastY: %f\n", lastX, lastY);
}

void display(Shader shader, Shader shaderLamp, Shader shaderSkybox, Model carpa, Model carpaInt,
			 Model grada, Model cerca, Model taquilla, Model oso, Model pelota, Model canon, Model trampolin,
			 Model elefante, Model zancos, Model plataforma, Model payaso, Model payaso2, Model columpio,
			 Model lampara, Model globos, Model iceCreamCar, Model sombrilla)
{
	//Lighting
	//float posLuzX = movLuzX;
	float posLuzX = 0.0f;
	glm::vec3 lightPosition0(-25.0f, 30.0f, 0.0f);
	glm::vec3 lightPosition1(25.0f, 30.0f,  0.0f);

	glm::vec3 lightDirection1(1.0f, -1.0f, -1.0f);  //Dirección de la luz ambiental 1
	glm::vec3 lightDirection2(-1.0f, -1.0f, 1.0f);  //Dirección de la luz ambiental 2


	shader.use();
	shader.setVec3("viewPos", camera->Position);

	//Luz direccional, fuente infinita
	shader.setVec3("dirLight[0].direction", lightDirection1);      // Se pasa la direccion de la fuente de luz direccional
	shader.setVec3("dirLight[0].ambient", glm::vec3(0.06f));    //AMBIENTAL, indica hacia que color tienden las caras menos iluminadas por la fuente de luz
	shader.setVec3("dirLight[0].diffuse", estadoLucesEscenario);    //DIFUSA, indica el color que van a tomar las caras más iluminadas del objeto
	shader.setVec3("dirLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));   //ESPECULAR, se trata de simular un brillo que va a tener la superficie
	shader.setVec3("dirLight[1].direction", lightDirection2);      // Se pasa la direccion de la fuente de luz direccional
	shader.setVec3("dirLight[1].ambient", glm::vec3(0.06f));    //AMBIENTAL, indica hacia que color tienden las caras menos iluminadas por la fuente de luz
	shader.setVec3("dirLight[1].diffuse", estadoLucesEscenario);    //DIFUSA, indica el color que van a tomar las caras más iluminadas del objeto
	shader.setVec3("dirLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));   //ESPECULAR, se trata de simular un brillo que va a tener la superficie

	//Luz posicional
	float lin = 0.001f;
	float quad = 0.0003f;
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
	projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1600.0f);
	view = camera->GetViewMatrix();

	view = glm::scale(view, glm::vec3(2.0f, 2.0f, 2.0f));
//	view = glm::scale(view, glm::vec3(1.0f, 1.0f, 1.0f));

	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);




	/*----------------------------------------------------------*/
	/* -------- Shader con efectos de luz y texturizado ------- */
	/*----------------------------------------------------------*/
	//MODELADO GEOMETRICO CON PRIMITIVAS
	glBindVertexArray(VAO);
	shader.use();  //Shader con los efectos de luz y texturizado
	//PISO
	centro = glm::mat4(1.0f);
	model = glm::translate(centro, glm::vec3(0.0f, -0.4f, 0.0f));
	model = glm::scale(model, glm::vec3(610.0f, 1.0f, 610.0f));
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_pasto);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	//LETRERO 1 DERECHA
	model = glm::translate(centro, glm::vec3(19.0f, 6.0f, 29.0f));
	model = glm::scale(model, glm::vec3(12.0f, 7.0f, 1.0f));
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_walpurgis1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(6));
	//LETRERO 2 IZQUIERDA
	model = glm::translate(centro, glm::vec3(-15.0f, 6.0f, 29.0f));
	model = glm::scale(model, glm::vec3(12.0f, 7.0f, 1.0f));
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_walpurgis2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(6));

	glBindVertexArray(0);



	//******************************************************************************************
	//MODELOS CARGADOS
	origenCarpa = glm::mat4(1.0);

	//FUENTES DE LUZ
	model = glm::translate(origenCarpa, glm::vec3(-24.0f, 33.0f, 0.0f));
	shader.setMat4("model", model);
	lampara.Draw(shader);
	model = glm::translate(origenCarpa, glm::vec3(24.0f, 33.0f, 0.0f));
	shader.setMat4("model", model);
	lampara.Draw(shader);


	//CARPA

	model = glm::translate(origenCarpa, glm::vec3(0.0f, -0.12f, 0.0f));
	model = glm::scale(model, glm::vec3(25.0, 28.0f, 25.0f));
	shader.setMat4("model", model);
	carpa.Draw(shader);
	//CARPA INTERIOR
	model = glm::translate(origenCarpa, glm::vec3(0.0f, -0.15f, 0.0f));
	model = glm::scale(model, glm::vec3(24.97, 27.97f, 24.97f));
	shader.setMat4("model", model);
	carpaInt.Draw(shader);

	musicaFondoCarpa(camera->Position, musicaCarpa);

	//GRADA IZQUIERDA
	model = glm::rotate(origenCarpa, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-3.0f, 0.0f, -20.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.5, 1.0));
	shader.setMat4("model", model);
	grada.Draw(shader);
	//GRADA DERECHA
	model = glm::rotate(origenCarpa, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(3.2f, 0.0f, -23.5f));
	model = glm::scale(model, glm::vec3(1.0, 1.5, 1.0));
	shader.setMat4("model", model);
	grada.Draw(shader);
	//CERCA
	model = glm::scale(origenCarpa, glm::vec3(1.0, 0.6, 1.0));
	shader.setMat4("model", model);
	cerca.Draw(shader);
	//TAQUILLA
	model = glm::translate(origenCarpa, glm::vec3(40.0f, 0.0f, 85.0f));
	shader.setMat4("model", model);
	taquilla.Draw(shader);
	//ELEFANTE
	model = glm::translate(origenCarpa, glm::vec3(-40.0f, 0.0f, 55.0f));
	model = glm::scale(model, glm::vec3(0.7f));
	shader.setMat4("model", model);
	elefante.Draw(shader);
	//ZANCOS RECARGADOS
	model = glm::translate(origenCarpa, glm::vec3(-4.0f, 0.0f, -22.0f));
	shader.setMat4("model", model);
	zancos.Draw(shader);
	model = glm::translate(model, glm::vec3(8.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	zancos.Draw(shader);
	model = glm::translate(model, glm::vec3(8.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	zancos.Draw(shader);

	//ANIMACION ADICIONAL 1
	//CARRO HELADOS
	temp = model = glm::translate(origenCarpa, glm::vec3(40.0f, 0.0f, 65.0f));
	model = glm::scale(model, glm::vec3(0.75f));
	shader.setMat4("model", model);
	iceCreamCar.Draw(shader);
	model = glm::rotate(temp, glm::radians(rotSombrilla), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -7.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.1f));
	shader.setMat4("model", model);
	sombrilla.Draw(shader);

	//ANIMACION ADICIONAL 2
	//GLOBOS
	model = glm::translate(origenCarpa, glm::vec3(16.0f, movGloboY, -19.0f+movGloboZ));
	shader.setMat4("model", model);
	globos.Draw(shader);
	model = glm::translate(origenCarpa, glm::vec3(-16.0f, movGloboY, 25.0f-movGloboZ));
	shader.setMat4("model", model);
	globos.Draw(shader);

	//ANIMACION ADICIONAL 3
	//OSO SOBRE PELOTA
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));
	model = glm::rotate(origenCarpa, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-rotOso), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(15.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	oso.Draw(shader);
	model = glm::translate(model, glm::vec3(0.0f, 1.08f, 0.0f));
	model = glm::rotate(model, glm::radians(rotPelota), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	pelota.Draw(shader);

	//ANIMACION 1 (TERRESTRE)
	//CAÑON
	model = glm::translate(origenCarpa, glm::vec3(-14.0f, 0.0f, -16.0f));
	shader.setMat4("model", model);
	canon.Draw(shader);
	//TRAMPOLIN
	model = glm::translate(origenCarpa, glm::vec3(19.0f, 0.0f, 20.0f));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.2f));
	shader.setMat4("model", model);
	trampolin.Draw(shader);
	//PAYASO
	model = glm::translate(origenCarpa, glm::vec3(-14.5f, 2.0f, -16.5f));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, posY, posZ));
	model = glm::rotate(model, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	payaso.Draw(shader);

	efectoActo1(sonidoActo1, camera->Position, musicaActo1);

	//ANIMACION 2 (AEREA)
	//PLATAFORMA
	model = glm::translate(origenCarpa, glm::vec3(19.5f, -0.1f, 2.5f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.8f, 0.9f, 0.08));
	shader.setMat4("model", model);
	plataforma.Draw(shader);
	model = glm::translate(origenCarpa, glm::vec3(-18.1f, -0.1f, 3.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.8f, 0.85f, 0.08f));
	shader.setMat4("model", model);
	plataforma.Draw(shader);
	//COLUMPIO
	model = glm::translate(origenCarpa, glm::vec3(0.0f, 40.0f, 3.0f));
	model = glm::rotate(model, glm::radians(120.0f+rotCol), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 2.5f, 1.0f));
	shader.setMat4("model", model);
	columpio.Draw(shader);
	//PAYASO2
	model = glm::translate(origenCarpa, glm::vec3(19.2f, 21.0f, 3.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -posZ2, -posY2));
	model = glm::rotate(model, glm::radians(rotX2), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotPay), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	payaso2.Draw(shader);

	efectoActo2(sonidoActo2, camera->Position, musicaActo2);

	glBindVertexArray(VAO);
	shaderSkybox.use();
	glm::vec3 centroCaja(0.0f, 90.0f, 0.0f);
	shaderSkybox.setVec3("lightColor", 1.0f, 1.0f, 1.0f); //Indica el color que genera la fuente de luz
	shaderSkybox.setVec3("lightPos", centroCaja);	//Indica posición de la luz
	shaderSkybox.setVec3("viewPos", camera->Position);
	shaderSkybox.setMat4("projection", projection);
	shaderSkybox.setMat4("view", view);
	shaderSkybox.setMat4("model", model);

	model = glm::mat4(1.0f);
	model = glm::translate(model, centroCaja);
	model = glm::scale(model, glm::vec3(600.0f));
	shaderSkybox.setMat4("model", model);	//SE PASAN VALORES DE ILUMINACIÓN
	shaderSkybox.setVec3("diffuseColor", estadoLucesEscenario+estadoLucesEscenario+0.2f);  //DIFUSA, indica el color que van a tomar las caras más iluminadas del objeto
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

	GLFWwindow* window = initWindow("Proyecto Final - Circo");

	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData();
	glEnable(GL_DEPTH_TEST);

	//%%%%%%%%%%% sonido %%%%%%%%%%%%%%%%%%%%%
	vec3df position_musicaCarpa(0, 0, 0);
	vec3df position_musicaActo1(0, 0, 0);
	vec3df position_musicaActo2(0, 0, 0);

	musicaCarpa = musica_Carpa->play3D("music/musicaCarpa.ogg", position_musicaCarpa, true, true);
	musicaCarpa->setMinDistance(60);
	musicaCarpa->setVolume(1);

	musicaActo1 = musica_Acto1->play3D("music/musicaActo1.mp3", position_musicaActo1, true, true);
	musicaActo1->setMinDistance(60);
	musicaActo1->setVolume(1);

	musicaActo2 = musica_Acto2->play3D("music/musicaActo2.mp3", position_musicaActo2, true, true);
	musicaActo2->setMinDistance(60);
	musicaActo2->setVolume(1);
	
	musica_General->play2D("music/musicaGeneral.ogg", true);
	musica_General->setSoundVolume(0.3f);

	//%%%%%%%%%%%%%%%%%%%%%%%% Shaders %%%%%%%%%%%%%%%%%%%%%
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");
	Shader skyboxShader("shaders/shader_skybox.vs", "shaders/shader_skybox.fs");
	
	//%%%%%%%%%%%%%%%%%%%%%%%% Load Models %%%%%%%%%%%%%%%%%%%%%
	Model carpa = ((char*)"Models/carpa/carpa.obj");
	Model carpaInt = ((char*)"Models/carpaInterior/carpa.obj");
	Model grada = ((char*)"Models/grada/grada.obj");
	Model cerca = ((char*)"Models/cerca/cerca.obj");
	Model taquilla = ((char*)"Models/taquilla/taquilla.obj");
	Model oso = ((char*)"Models/oso/oso.obj");
	Model pelota = ((char*)"Models/oso/pelota.obj");
	Model canon = ((char*)"Models/canon/canon.obj");
	Model trampolin = ((char*)"Models/trampolin/trampolin.obj");
	Model elefante = ((char*)"Models/elefante/elefante.obj");
	Model zancos = ((char*)"Models/zancos/zancos.obj");
	Model plataforma = ((char*)"Models/plataforma/plataforma.obj");
	Model payaso = ((char*)"Models/payaso/payaso.obj");
	Model payaso2 = ((char*)"Models/payaso/payaso2.obj");
	Model columpio = ((char*)"Models/columpio/columpio.obj");
	Model lampara = ((char*)"Models/lampara/lampara.obj");
	Model globos = ((char*)"Models/globos/globos.obj");
	Model iceCreamCar = ((char*)"Models/iceCreamCar/iceCreamCar.obj");
	Model sombrilla = ((char*)"Models/iceCreamCar/sombrilla.obj");
	

	//Inicialización de KeyFrames
	openFile();
	openFile2();

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

		display(modelShader, lampShader, skyboxShader, carpa, carpaInt, grada, cerca, taquilla, oso, 
				pelota, canon, trampolin, elefante, zancos, plataforma, payaso, payaso2, columpio, lampara,
				globos, iceCreamCar, sombrilla);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
		
			glfwSwapBuffers(window);
		if (!modoLibre) {
			glfwPollEvents();
		}
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();

	musica_General->drop();
	musica_Carpa->drop();
	musica_Acto1->drop();
	musica_Acto2->drop();

	musicaCarpa->drop();
	musicaActo1->drop();
	musicaActo2->drop();
    return 0;
}

