#include "solarsystem.h"

SolarSystem::SolarSystem(){
    planetsCount = 0;
    planets = 0;
}

SolarSystem::SolarSystem(int count){
    planetsCount = count;
    planets = new Planet*[count];
}

void SolarSystem::step(float delta){
}

void SolarSystem::addPlanet(Planet* planet, int id){
    if (id>=planetsCount)
        return;
    planets[id] = planet;
}

/*int SolarSystem::planetsCount(){
    return planetsCount;
}*/

ostream& operator << (ostream& out, const SolarSystem& solarSystem){
    if (&solarSystem==NULL){
        out << "NULL";
        return out;
    }
    out << "{\n";
    for(int i = 0; i<solarSystem.planetsCount; i++)
        out << "\t" << *solarSystem.planets[i] << "\n";
    out << "}";
    return out;
}
