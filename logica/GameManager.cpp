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
    nivelActual = new NivelSelva();
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

    // Pasa al nivel 2
    if(numeroNivel == 1)
    {
        nivelActual = new NivelBoss();

        numeroNivel = 2;
    }
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

ConfiguracionJuego& GameManager::getConfiguracion()
{
    return configuracion;
}

bool GameManager::estaTerminado() const
{
    return juegoTerminado;
}
