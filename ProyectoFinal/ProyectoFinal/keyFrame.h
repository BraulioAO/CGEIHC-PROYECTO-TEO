#pragma once
//Keyframes
float	posY = 0.0f,
		posZ = 0.0f,
		rotX = 0.0f;

float	rotCol = 0.0f;

float	incY = 0.0f,
		incZ = 0.0f,
		incRotX = 0.0f;

float	incRotCol = 0.0f;



#define MAX_FRAMES 30
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotX;
	int FrameIndex;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void){
	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;
	KeyFrame[FrameIndex].rotX = rotX;
	KeyFrame[FrameIndex].FrameIndex = FrameIndex+1;
	FrameIndex++;
}

void resetElements(void){
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	rotX = KeyFrame[0].rotX;
}

void interpolation(void)
{
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	incRotX = (KeyFrame[playIndex + 1].rotX - KeyFrame[playIndex].rotX) / i_max_steps;
}

void saveFile(void) {
	KeyFrame[0].FrameIndex = KeyFrame[FrameIndex-1].FrameIndex;
	FILE *archivo;
	archivo = fopen("keyframeTerrestre.txt", "wb+");
	if (archivo != NULL) {
		fwrite(KeyFrame, sizeof(KeyFrame), 1, archivo);
		fclose(archivo);
		printf("Archivo guardado\n");
	}
	else {
		printf("El archivo no existe o no se tiene permisos de lectura/escritura.\n");
	}
}


void openFile(void) {
	FILE *archivo;
	archivo = fopen("keyframeTerrestre.txt", "rb");
	if (archivo != NULL) {
		fread(KeyFrame, sizeof(KeyFrame), 1, archivo);
		fclose(archivo);
		printf("Archivo cargado \n");
		FrameIndex = KeyFrame[0].FrameIndex;
	}
	else {
		printf("El archivo no existe o no se tiene permisos de lectura /escritura.\n");
	}
}
/*
void mostrarDatos(void) {
	for (int i = 0; i < MAX_FRAMES; i++)
		printf("%d\n", KeyFrame[i].frameIndex);
	printf("no frame %d\n", FrameIndex);
}
*/