#include <iostream>
#include <string>

int main()
{
    std::string planet[10] = {
        "Меркурий", "Венера", "Земля",
        "Марс", "Юпитер", "Сатурн",
        "Уран", "Нептун", "Плутон"
    };
    std::cout << planet[0] <<  std::endl;
    return 0;
}
