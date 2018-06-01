#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {

public:
    MainWindow();

private:
    Gtk::Box m_box;
    Gtk::Button m_saveFileButton;

    void onButtonClicked();
    std::string generateData();
};
