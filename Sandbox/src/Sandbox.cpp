#include <Fullbeard/fullbeard.hpp>

#include <iostream>

class ExampleLayer : public Fullbeard::Layer
{
    public:
        ExampleLayer():
        Layer("Example")
        {
            std::cout << "LOOOOOOOOOL" << std::endl;
        }

        void on_update() override
        {
            Fullbeard::Log::info("Update");
        }

        void on_event(Fullbeard::Event &t_event) override
        {
            Fullbeard::Log::trace("{0}", t_event);
        }
};

class Sandbox : public Fullbeard::Application
{
    public:
        Sandbox();
        ~Sandbox();
};

Sandbox::Sandbox()
{
    push_layer(new ExampleLayer());
}

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