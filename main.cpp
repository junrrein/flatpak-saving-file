#include "MainWindow.h"

int main(int argc, char* argv[])
{
    auto application = Gtk::Application::create("com.sharedpointer.simple-gtkmm-app");

    MainWindow window;

    return application->run(window, argc, argv);
}
