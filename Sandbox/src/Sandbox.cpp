#include <CylinderBank/CylinderBank.hpp>

#include <iostream>

class Sandbox : public CylinderBank::Application
{
    public:
        Sandbox();
        ~Sandbox();
};

Sandbox::Sandbox()
{
    push_overlay(new CylinderBank::LayerImGUI());
}

Sandbox::~Sandbox()
{ }

int main()
{
    CylinderBank::Log::init();

    Sandbox *application = new Sandbox();
    application->run();
    delete application;

    return 0;
}