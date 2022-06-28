#include "UserInterface.hpp"


UserInterface::UserInterface()
{
    UserInterface::io_device = false;
}
UserInterface::UserInterface(const InputPins& pins)
{
    UserInterface::io_device = false;
    UserInterface::input_pins = pins;
}
UserInterface::~UserInterface()
{
}
void UserInterface::get_serial_input()
{
    while (Serial.available() == 0)
    {

    }
    UserInterface::menu_option = Serial.parseInt();
}
void UserInterface::display_main_menu()
{
    if (!io_device)
    {
        // TODO: tornar as opções mais enxutas e adequadas para o display 16x2;
        Serial.println("Digite o número da opção desejada.");
        Serial.println("1) Definir velocidade.");
        Serial.println("2) Definir distância.");
        // IMPROVEMENT > Serial.println("3) Definir intervalo de tempo.");
        Serial.println("4) Definir tempo contagem regressiva.");
    }
    else
    {
        
    }
    // TODO: else {lcd display}
}
void UserInterface::display_speed_menu()
{
    Serial.println("Insira a velocidade de mergulho:");


}


