#include <Fullbeard/fullbeard.hpp>

#include <iostream>

class Sandbox : public Fullbeard::Application
{
    public:
        Sandbox();
        ~Sandbox();
};

Sandbox::Sandbox()
{ }

Sandbox::~Sandbox()
{ }

int main()
{
    Fullbeard::Log::init();

    Sandbox *application = new Sandbox();
    application->run();
    delete application;

    return 0;
}