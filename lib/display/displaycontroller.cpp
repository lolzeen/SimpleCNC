#include "displaycontroller.hpp"

DisplayController::DisplayController()
{
    DisplayController::display_pins = {13,12,12,10,9,8};
}
DisplayController::DisplayController(const DisplayPins& pins)
{
    DisplayController::display_pins = pins;
}
DisplayController::~DisplayController()
{
    // intentionally empty
}

void DisplayController::show_main_menu()
{
    lc
}

void DisplayController::show_speed_menu()
{

}

void DisplayController::show_distance_menu()
{

}

void DisplayController::show_time_menu()
{

}
