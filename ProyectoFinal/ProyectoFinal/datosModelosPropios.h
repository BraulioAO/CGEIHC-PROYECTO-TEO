#pragma once
GLuint VBO, VAO, EBO;
#define BUFFER_OFFSET(i) ((void*)(i*sizeof(float)))

void myData(){
	float vertices[] = {  
		// positions			// normals				//texture coords
		//	Cubo misma Textura por lado
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,	//V0 - Frontal
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.0f,	//V1
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,	//V5
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  1.0f,	//V4
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  0.0f,	//V3
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  1.0f,	//V7
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  1.0f,	//V6
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  0.0f,	//V3 - Izquierda
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  0.0f,	//V0
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  1.0f,	//V4
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  1.0f,	//V7
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  0.0f,	//V1 - Derecha
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  0.0f,	//V2
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  1.0f,	//V6
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  1.0f,	//V5		 
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  0.0f,	//V4 - Superior
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  1.0f,	//V5
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  1.0f,	//V6
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  0.0f,	//V7
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  0.0f,	//V0 - Inferior
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  0.0f,	//V1
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  1.0f,	//V2
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  1.0f,	//V3

		//	Cubo para columnas pared
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,	//V0 - Frontal
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.0f,	//V1
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,	//V5
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  1.0f,	//V4
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  0.0f,	//V3
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  1.0f,	//V7
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  1.0f,	//V6
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.6f,  0.0f,	//V3 - Izquierda
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  0.0f,	//V0
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  1.0f,	//V4
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.6f,  1.0f,	//V7
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  0.0f,	//V1 - Derecha
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.6f,  0.0f,	//V2
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.6f,  1.0f,	//V6
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  1.0f,	//V5		 
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  0.0f,	//V4 - Superior
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  0.0f,	//V5
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  1.0f,	//V6
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  1.0f,	//V7
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  0.0f,	//V0 - Inferior
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  0.0f,	//V1
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  1.0f,	//V2
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  1.0f,	//V3

		//	Cubo skybox
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  -1.0f,	1.00f,  0.33f,	//V0 - Frontal
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  -1.0f,	0.75f,  0.33f,	//V1
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  -1.0f,	0.75f,  0.66f,	//V5
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  -1.0f,	1.00f,  0.66f,	//V4
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f,  1.0f,	0.50f,  0.33f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f,  1.0f,	0.25f,  0.33f,	//V3
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f,  1.0f,	0.25f,  0.66f,	//V7
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f,  1.0f,	0.50f,  0.66f,	//V6
		-0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.25f,  0.33f,	//V3 - Izquierda
		-0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.00f,  0.33f,	//V0
		-0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.00f,  0.66f,	//V4
		-0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.25f,  0.66f,	//V7
		 0.5f, -0.5f,  0.5f,	 -1.0f,  0.0f,  0.0f,	0.75f,  0.33f,	//V1 - Derecha
		 0.5f, -0.5f, -0.5f,	 -1.0f,  0.0f,  0.0f,	0.50f,  0.33f,	//V2
		 0.5f,  0.5f, -0.5f,	 -1.0f,  0.0f,  0.0f,	0.50f,  0.66f,	//V6
		 0.5f,  0.5f,  0.5f,	 -1.0f,  0.0f,  0.0f,	0.75f,  0.66f,	//V5		 

		-0.5f,  0.5f,  0.5f,	 0.0f,  -1.0f,  0.0f,	0.25f,  1.00f,	//V4 - Superior
		 0.5f,  0.5f,  0.5f,	 0.0f,  -1.0f,  0.0f,	0.50f,  1.00f,	//V5
		 0.5f,  0.5f, -0.5f,	 0.0f,  -1.0f,  0.0f,	0.50f,  0.66f,	//V6
		-0.5f,  0.5f, -0.5f,	 0.0f,  -1.0f,  0.0f,	0.25f,  0.66f,	//V7

		-0.5f, -0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.25f,  0.00f,	//V0 - Inferior
		 0.5f, -0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.50f,  0.00f,	//V1
		 0.5f, -0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.50f,  0.33f,	//V2
		-0.5f, -0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.25f,  0.33f,	//V3

		// PISO
		-0.5f,  0.0f,  0.5f,	 0.0f,  1.0f,  0.0f,	00.0f,  0.0f,	//V4 --Superior
		 0.5f,  0.0f,  0.5f,	 0.0f,  1.0f,  0.0f,	2.0f,  0.0f,	//V5
		 0.5f,  0.0f, -0.5f,	 0.0f,  1.0f,  0.0f,	2.0f,  2.0f,	//V6
		-0.5f,  0.0f, -0.5f,	 0.0f,  1.0f,  0.0f,	00.0f,  2.0f,	//V7
		
		//LETREROENTRADA
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,	//V0 - Frontal
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.0f,	//V1
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,	//V5
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  1.0f,	//V4
	};

	unsigned int indices[] = {
		//PISO
		72, 73, 75, // first triangle
		73, 74, 75,  // second triangle
		//LETRERO_ENTRADA
		76, 77, 79, // first triangle
		77, 78, 79,  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}