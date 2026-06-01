#include "GameManager.h"

GameManager::GameManager()
{
    nivelActual = nullptr;

    numeroNivel = 1;

    juegoTerminado = false;
}

GameManager::~GameManager()
{
    delete nivelActual;
}

void GameManager::iniciarJuego()
{
    delete nivelActual;

    nivelActual = nullptr;

    nivelActual = new NivelSelva();

    numeroNivel = 1;

    juegoTerminado = false;
}

void GameManager::actualizar()
{
    if(nivelActual != nullptr)
    {
        nivelActual->actualizar();

        // Revisar cambio de nivel
        if(nivelActual->estaTerminado())
        {
            cambiarNivel();
        }
    }
}

void GameManager::cambiarNivel()
{
    delete nivelActual;

    // PASAR A NIVEL 2


    if(numeroNivel == 1)
    {
        nivelActual = new NivelBoss();

        numeroNivel = 2;
    }


    // FIN DEL JUEGO
   

    else
    {
        juegoTerminado = true;

        nivelActual = nullptr;
    }
}

Nivel* GameManager::getNivelActual() const
{
    return nivelActual;
}

ConfiguracionJuego&
GameManager::getConfiguracion()
{
    return configuracion;
}

bool GameManager::estaTerminado() const
{
    return juegoTerminado;
}


// CONFIGURAR DIFICULTAD


void GameManager::setDificultad(
        Dificultad dificultad)
{
    configuracion.setDificultad(
        dificultad
    );
}


// CONFIGURAR NOMBRE


void GameManager::setNombreJugador(
        QString nombre)
{
    configuracion.setNombreJugador(
        nombre
    );
}


// OBTENER NIVEL


int GameManager::getNumeroNivel() const
{
    return numeroNivel;
}
