#include "application.h"

Application::Application(){
    system = new SolarSystem(8);

    system->addPlanet(new Planet("Меркурий", 3.302  * pow(10,23),   57909227000,     0.20563593,  0.3f,  0), 0);
    system->addPlanet(new Planet("Венера",   4.8685 * pow(10,24),  108208930000,         0.0068,  0.4f,  0), 1);
    system->addPlanet(new Planet("Земля",    5.973  * pow(10,24),  149598261000,     0.01671123,  0.5f,  0), 2);
    system->addPlanet(new Planet("Марс",     6.4185 * pow(10,23),  227943820000,      0.0933941,  0.45f, 0), 3);
    system->addPlanet(new Planet("Юпитер",   1.8986 * pow(10,27),  778547200000,       0.048775,  0.8f,  0), 4);
    system->addPlanet(new Planet("Сатурн",   5.6846 * pow(10,26), 1433449370000,    0.055723219,  0.7f,  0), 5);
    system->addPlanet(new Planet("Уран",     8.6832 * pow(10,25), 2876679082000,    0.044405586, 0.6f,  0), 6);
    system->addPlanet(new Planet("Нептун",   1.0243 * pow(10,26), 4503443661000,    0.011214269, 0.6f,  0), 7);
    planetsTable = new bool[8];
    for(int i = 0; i < 8; i++)
        planetsTable[i] = false;
    /*
    cout << system << "\n";
    system.step(4);
    cout << system << "\n";
    */
}

void Application::run()
{
    printMainMenu();
    int choice;
    while((choice = getChoice()) != 0)
        processMainMenu(choice);
    printMainMenu();

}

void Application::printMainMenu()
{
    cout << "\n"
            "Симулятор звездной системы" << endl
         << "1. Вывести информацию о планете" << endl
         << "2. Открыть таблицу для сравнения" << endl
         << "3. Открыть таблицу со всеми данными" << endl
         << "0. Exit" << endl
         << ">>> ";
}

void Application::printPlanets()
{
    cout << "\n"
            "Выберите планету" << endl
         << "1. Меркурий" << endl
         << "2. Венера" << endl
         << "3. Земля" << endl
         << "4. Марс" << endl
         << "5. Юпитер" << endl
         << "6. Сатурн" << endl
         << "7. Уран" << endl
         << "8. Нептун" << endl
         << ">>> ";
}

void Application::printPlanetMenu(){
    cout << "\n"
            "Выберите действие" << endl
         << "1. Вывести статические параметры" << endl
         << "2. Вывести динамические параметры" << endl
         << "3. Вывести все параметры" << endl
         << "4. Сдвинуть планету на дельту" << endl
         << "0. Выход" << endl;
}

void Application::printTableMenu(){
    cout << "\n"
            "Выберите операцию с таблицей" << endl
         << "1. Добавить планету для сравнения" << endl
         << "2. Убрать планету из таблицы" << endl
         << "3. Ввести дельту по времени" << endl
         << "4. Вывести таблицу" << endl
         << "0. Exit" << endl;
}

void Application::printInfoTable(){
    cout << "Планета         Масса           Расстояние      Период          Текущий угол\n";
    cout << "----------------------------------------------------------------------------\n";
    for(int i = 0; i < 8; i++)
        if (planetsTable[i]){
            (*system->getPlanet(i + 1)).printShortInfo(cout);
        }
    cout << "----------------------------------------------------------------------------\n";
}

void Application::processTableMenu(){
    int tmp;
    for(int i = 0 ; i< 8; i++)
        planetsTable[i] = false;
    printTableMenu();
    while((tmp = getChoice())!=0){
        switch(tmp){
        case 1:
            printPlanets();
            tmp = getChoice();
            if(system->idValid(tmp))
                planetsTable[tmp-1] = true;
            break;
        case 2:
            printPlanets();
            tmp = getChoice();
            if(system->idValid(tmp))
                planetsTable[tmp-1] = false;
            break;
        case 3:
            tmp = getDeltaTime();
            for(int i = 0 ; i< 8; i++)
                if (planetsTable[i])
                    (*system->getPlanet(i + 1)).step(tmp);
            cout << "\n\tДЕЛЬТА " << tmp << " секунд" << endl;
            printInfoTable();
            break;
        case 4:
            printInfoTable();
            break;
        default:
            break;
        }
        printTableMenu();
    }
    printMainMenu();
}

void Application::processPlanetInfoMenu(int planetId){
    int tmp;
    printPlanetMenu();
    while((tmp = getChoice())!=0){
        switch(tmp){
        case 1:
            (*system->getPlanet(planetId)).printStaticParameters(cout);
            printPlanetMenu();
            break;
        case 2:
            (*system->getPlanet(planetId)).printDynamicParameters(cout);
            printPlanetMenu();
            break;
        case 3:
            cout << *system->getPlanet(planetId);
            printPlanetMenu();
            break;
        case 4:
            tmp = getDeltaTime();
            (*system->getPlanet(planetId)).printDelta(cout, tmp);
            printPlanetMenu();
            break;
        default:
            printPlanetMenu();
            break;
        }
    }
    printMainMenu();

}

int Application::getChoice()
{
    int userInput;
    cin >> userInput;
    return userInput;
}

int Application::getDeltaTime(){
    int tmp, ttmp = 0;
    cout << "Введите дельту времени\n";
    cout << "дни ";
    tmp = getChoice();
    ttmp = tmp;
    cout << "часы ";
    tmp = getChoice();
    ttmp = 24*ttmp+tmp;
    cout << "минуты ";
    tmp = getChoice();
    ttmp = 60*ttmp+tmp;
    cout << "секунды ";
    tmp = getChoice();
    ttmp = 60*ttmp+tmp;
    return ttmp;
}

void Application::processMainMenu(int choice)
{
    int tmp;
    switch (choice)
    {
    case 0:

        break;
    case 1:
        printPlanets();
        tmp = getChoice();
        if (system->idValid(tmp)){
            processPlanetInfoMenu(tmp);
        }
        else
            cout << "Некорректный номер планеты";
        break;
    case 2:
        processTableMenu();
        break;
    case 3:
        cout << *system << "\n";
        printMainMenu();
        break;
    default:
        cout << "Error! Invalid number." << endl;
        printMainMenu();
        break;
    }
}
