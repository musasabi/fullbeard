#include <CylinderBank/CylinderBank.hpp>

#include <iostream>

class ExampleLayer : public CylinderBank::Layer
{
    public:
        ExampleLayer():
        Layer("ExampleLayer")
        { }

        ~ExampleLayer() { }

        // virtual void on_update() override
        // {
        //     if(CylinderBank::Input::is_key_pressed(CB_KEY_TAB))
        //     {
        //         CylinderBank::Log::info("Tab is down");
        //     }
        // }

        // virtual void on_event(CylinderBank::Event &t_event) override
        // {
        //     CylinderBank::Log::info(t_event.to_string());
        // }
};

class Sandbox : public CylinderBank::Application
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
    CylinderBank::Log::init();

    Sandbox *application = new Sandbox();
    application->run();
    delete application;

    return 0;
}