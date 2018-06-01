#include "MainWindow.h"
#include "savefiledialog.hpp"
#include <giomm/file.h>
#include <iostream>

MainWindow::MainWindow()
    : m_box{ Gtk::ORIENTATION_VERTICAL }
    , m_saveFileButton{ "Save file" }
{
    set_size_request(300, 300);

    m_box.pack_start(m_saveFileButton, true, false);
    add(m_box);

    m_saveFileButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onButtonClicked));

    show_all();
}

void MainWindow::onButtonClicked()
{
    SaveFileDialog dialog{ *this };
    gint result = dialog.run();

    if (result == GTK_RESPONSE_ACCEPT) {
        std::string etag = "";
        Glib::RefPtr<Gio::File> file = dialog.get_file();

        static const int numAttempts = 100;
        int failCount = 0;

        for (int i = 0; i < numAttempts; ++i)
            try {
                file->replace_contents(generateData(),
                    etag,
                    etag,
                    false,
                    Gio::FILE_CREATE_REPLACE_DESTINATION);
            } catch (Glib::Error& e) {
                std::cout << e.what() << std::endl;
                ++failCount;
            }

        std::cout << "Number of saving failures/attempts: " << failCount << "/" << numAttempts << std::endl;
    }
}

std::string MainWindow::generateData()
{
    std::string result;
    for (int i = 0; i < 40000; ++i)
        result += "This is a test, you can safely delete me.\n";

    return result;
}
