#include "application.h"

Application::Application(){
    system = new SolarSystem(8);
    system->addPlanet(new Planet("Меркурий", 3.302 * pow(10,23),  57910000000, 0.3f,  0), 0);
    system->addPlanet(new Planet("Венера",   4.8685 * pow(10,24), 108200000000, 0.4f,  0), 1);
    system->addPlanet(new Planet("Земля",    5.973  * pow(10,24), 149600000000, 0.5f,  0), 2);
    system->addPlanet(new Planet("Марс",     6.4185 * pow(10,23), 227900000000, 0.45f, 0), 3);
    system->addPlanet(new Planet("Юпитер",   1.8986 * pow(10,27), 778500000000, 0.8f,  0), 4);
    system->addPlanet(new Planet("Сатурн",   5.6846 * pow(10,26), 1433000000000, 0.7f, 0), 5);
    system->addPlanet(new Planet("Уран",     8.6832 * pow(10,25), 2877000000000, 0.6f, 0), 6);
    system->addPlanet(new Planet("Нептун",   1.0243 * pow(10,26), 4503000000000, 0.6f, 0), 7);
    /*
    cout << system << "\n";
    system.step(4);
    cout << system << "\n";
    */
}

void Application::printMainMenu()
{
    cout << "Симулятор звездной системы" << endl
         << "1. Показать список планет" << endl
         << "2. Сдвинуть планеты на дельту по времени" << endl
         << "3. " << endl
         << "0. Exit" << endl
         << ">>> ";
}

void Application::planetMenu()
{

}

int Application::getChoice()
{
    int tmp;
    cin >> tmp;
    return tmp;
}
void Application::processChoice(int choice)
{
    switch (choice)
    {
    case 0:

        break;
    case 1:
        cout << *system << "\n";
        break;
    case 2:
        int tmp;
        cout << "Введите дельту времени ";
        cin >> tmp;
        system->step(tmp);
        break;
    default:
        cout << "Error! Invalid number." << endl;
        printMainMenu();
        break;
    }
}

void Application::run()
{
    printMainMenu();
    int choice;
    while((choice = getChoice()) != 0)
        processChoice(choice);

}