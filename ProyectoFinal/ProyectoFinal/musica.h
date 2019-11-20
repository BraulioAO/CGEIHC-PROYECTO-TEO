#include "irrKlang.h"

bool sonidoActo1 = false, sonidoActo2 = false;

//%%%%%%%%%%%%%% Sonido %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") 
ISoundEngine *musica_General = createIrrKlangDevice();
ISoundEngine *musica_Carpa = createIrrKlangDevice();
ISoundEngine *musica_Acto1 = createIrrKlangDevice();
ISoundEngine *musica_Acto2 = createIrrKlangDevice();

ISound *musicaCarpa, *musicaActo1, *musicaActo2;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int musicaFondoCarpa(glm::vec3 position, ISound *musica_3d){
    irrklang::vec3df position_3d((int)position.x, (int)position.y, (int)position.z);           // position of the listener
    irrklang::vec3df lookDirection(10, 0, 10); // the direction the listener looks into
    irrklang::vec3df velPerSecond(0, 0, 0); // only relevant for doppler effects
    irrklang::vec3df upVector(0, 1, 0);        // where 'up' is in your 3D scene

    musica_Carpa->setListenerPosition(position_3d, lookDirection, velPerSecond, upVector);

    if (!musica_Carpa)
        return 0;

	if ((position.x < 106.0f && position.x > -90.0f) && 
		(position.y < 130.0f && position.y >   0.0f) &&
		(position.z < 60.0f && position.z > -50.0f)){
		musica_3d->setIsPaused(true); // unpause the sound
		//musica_3d->setIsPaused(false); // unpause the sound
		//musica_General->setAllSoundsPaused(true);
	}
	else {
		musica_3d->setIsPaused(true); // pause the sound
		//musica_General->setAllSoundsPaused(false);
	}
}


int efectoActo1(bool empezar, glm::vec3 position, ISound *musica_3d) {
	irrklang::vec3df position_3d((int)position.x, (int)position.y, (int)position.z);           // position of the listener
	irrklang::vec3df lookDirection(10, 0, 10); // the direction the listener looks into
	irrklang::vec3df velPerSecond(0, 0, 0); // only relevant for doppler effects
	irrklang::vec3df upVector(0, 1, 0);        // where 'up' is in your 3D scene

	musica_Acto1->setListenerPosition(position_3d, lookDirection, velPerSecond, upVector);
	if (!musica_Acto1)
		return 0;

	if(empezar)
		if ((position.x < 106.0f && position.x > -90.0f) &&
			(position.y < 130.0f && position.y >   0.0f) &&
			(position.z < 60.0f && position.z > -50.0f)) {
			musica_3d->setIsPaused(false); // unpause the sound
		}
		else {
			musica_3d->setIsPaused(true); // pause the sound
		}
	else
		musica_3d->setIsPaused(true); // pause the sound
}

int efectoActo2(bool empezar, glm::vec3 position, ISound *musica_3d) {
	irrklang::vec3df position_3d((int)position.x, (int)position.y, (int)position.z);           // position of the listener
	irrklang::vec3df lookDirection(10, 0, 10); // the direction the listener looks into
	irrklang::vec3df velPerSecond(0, 0, 0); // only relevant for doppler effects
	irrklang::vec3df upVector(0, 1, 0);        // where 'up' is in your 3D scene

	musica_Acto2->setListenerPosition(position_3d, lookDirection, velPerSecond, upVector);
	if (!musica_Acto2)
		return 0;

	//printf("X:%f, Y:%f, Z:%f\n", position.x, position.y, position.z);

	if (empezar)
		if ((position.x < 106.0f && position.x > -90.0f) &&
			(position.y < 130.0f && position.y >   0.0f) &&
			(position.z < 60.0f && position.z > -50.0f)) {
			musica_3d->setIsPaused(false); // unpause the sound
		}
		else {
			musica_3d->setIsPaused(true); // pause the sound
		}
	else
		musica_3d->setIsPaused(true); // pause the sound
}