#pragma once
//Keyframes
float	posY = 0.0f,	//Animación terrestre
		posZ = 0.0f,
		rotX = 0.0f;
float	incY = 0.0f,
		incZ = 0.0f,
		incRotX = 0.0f;

float	posY2 = 0.0f,	//Animación Aerea
		posZ2 = 0.0f,
		rotX2 = 0.0f,
		rotCol = 0.0f,
		rotPay = 0.0f;
float	incY2 = 0.0f,
		incZ2 = 0.0f,
		incRotX2 = 0.0f,
		incRotCol = 0.0f,
		incRotPay = 0.0f;



#define MAX_FRAMES 15
#define MAX_FRAMES2 40
int i_curr_steps = 0;
int i_curr_steps2 = 0;
typedef struct _frame{
	//Variables para GUARDAR Key Frames
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotX;
	int FrameIndex;
}FRAME;

typedef struct _frame2 {
	//Variables para GUARDAR Key Frames
	float posY2;		//Variable para PosicionY
	float posZ2;		//Variable para PosicionZ
	float rotX2;
	float rotCol;
	float rotPay;
	int FrameIndex2;
}FRAME2;

FRAME KeyFrame[MAX_FRAMES];
int i_max_steps = 20;
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

FRAME2 KeyFrame2[MAX_FRAMES2];
int i_max_steps2 = 10;
int FrameIndex2 = 0;			//introducir datos
bool play2 = false;
int playIndex2 = 0;

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

void saveFrame2(void) {
	printf("frameindex2 %d\n", FrameIndex2);
	KeyFrame2[FrameIndex2].posY2 = posY2;
	KeyFrame2[FrameIndex2].posZ2 = posZ2;
	KeyFrame2[FrameIndex2].rotX2 = rotX2;
	KeyFrame2[FrameIndex2].rotCol = rotCol;
	KeyFrame2[FrameIndex2].rotPay = rotPay;
	KeyFrame2[FrameIndex2].FrameIndex2 = FrameIndex2 + 1;
	FrameIndex2++;
}
void resetElements2(void) {
	posY2 = KeyFrame2[0].posY2;
	posZ2 = KeyFrame2[0].posZ2;
	rotX2 = KeyFrame2[0].rotX2;
	rotPay = KeyFrame2[0].rotPay;
	rotCol = KeyFrame2[0].rotCol;
}
void interpolation2(void){
	incY2 = (KeyFrame2[playIndex2 + 1].posY2 - KeyFrame2[playIndex2].posY2) / i_max_steps2;
	incZ2 = (KeyFrame2[playIndex2 + 1].posZ2 - KeyFrame2[playIndex2].posZ2) / i_max_steps2;
	incRotX2 = (KeyFrame2[playIndex2 + 1].rotX2 - KeyFrame2[playIndex2].rotX2) / i_max_steps2;
	incRotCol = (KeyFrame2[playIndex2 + 1].rotCol - KeyFrame2[playIndex2].rotCol) / i_max_steps2;
	incRotPay = (KeyFrame2[playIndex2 + 1].rotPay - KeyFrame2[playIndex2].rotPay) / i_max_steps2;
}

void saveFile(void) {
	//KeyFrame[0].FrameIndex = KeyFrame[FrameIndex-1].FrameIndex;
	KeyFrame2[0].FrameIndex2 = KeyFrame2[FrameIndex2-1].FrameIndex2;
	FILE *archivo;
	//archivo = fopen("keyframeTerrestre.txt", "wb+");
	archivo = fopen("keyframeAereo.txt", "wb+");
	if (archivo != NULL) {
		//fwrite(KeyFrame, sizeof(KeyFrame), 1, archivo);
		fwrite(KeyFrame2, sizeof(KeyFrame2), 1, archivo);
		fclose(archivo);
		printf("Archivo guardado\n");
	}
	else
		printf("El archivo no existe o no se tiene permisos de lectura/escritura.\n");
}


void openFile(void) {
	FILE *archivo;
	archivo = fopen("keyframeTerrestre.txt", "rb");
	if (archivo != NULL) {
		fread(KeyFrame, sizeof(KeyFrame), 1, archivo);
		fclose(archivo);
		printf("Archivo 1 cargado \n");
		FrameIndex = KeyFrame[0].FrameIndex;
	}
	else
		printf("El archivo 1 no existe o no se tiene permisos de lectura /escritura.\n");
}

void openFile2(void) {
	FILE *archivo2;
	archivo2 = fopen("keyframeAereo.txt", "rb");
	if (archivo2 != NULL) {
		fread(KeyFrame2, sizeof(KeyFrame2), 1, archivo2);
		fclose(archivo2);
		printf("Archivo 2 cargado \n");
		FrameIndex2 = KeyFrame2[0].FrameIndex2;
	}
	else
		printf("El archivo 2 no existe o no se tiene permisos de lectura /escritura.\n");
}

void mostrarDatos(void) {
	for (int i = 0; i < MAX_FRAMES; i++)
		printf("%d\n", KeyFrame[i].FrameIndex);
	printf("no frame %d\n", FrameIndex);
}
