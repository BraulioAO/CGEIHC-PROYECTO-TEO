#pragma once
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//Texture
unsigned int	t_pasto;
unsigned int	t_dia;
unsigned int	t_noche;


unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;	//Genera textura desde un archivo
	glGenTextures(1, &textureID);	//Genera un identificador
	glBindTexture(GL_TEXTURE_2D, textureID); //Tipo de textura que va a generar, 1D o 2D
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Prepara la textura, activa opcion de repetir
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Filtros para el redimencionamiento, tanto cuando se haga pequeña
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //o se haga mas grande
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);  //Lee el archivo
	if (data){
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //convierte la invormación en mapa de bits
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID; //Regresa el identificador de la textura que se esta manejando
	}
	else{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void LoadTextures()
{
	t_pasto = generateTextures("Texturas/pasto.jpg", 0); //El 1 indica que hay canal alfa, importante agregar
	t_dia = generateTextures("Texturas/dia.jpg", 0);
	t_noche = generateTextures("Texturas/noche.jpg", 0);
}