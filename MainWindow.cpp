#include "MainWindow.h"
#include "savefiledialog.hpp"
#include <giomm.h>
#include <glibmm.h>
#include <iostream>
#include <vector>

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

        std::cout << "Target filepath: " << file->get_path() << std::endl;

        try {
            std::cout << "Saving using g_file_replace_contents" << std::endl;

            file->replace_contents(generateData(),
                etag,
                etag,
                false,
                Gio::FILE_CREATE_REPLACE_DESTINATION);

            std::cout << "Success" << std::endl;
        } catch (Glib::Error& e) {
            std::cerr << e.what() << std::endl;
        }

        std::string tempFilePath;
        int tempFileDescriptor = Glib::file_open_tmp(tempFilePath);
        auto tempFile = Gio::File::create_for_path(tempFilePath);

        try {
            tempFile->replace_contents(generateData(),
                etag,
                etag,
                false,
                Gio::FILE_CREATE_REPLACE_DESTINATION);
        } catch (Glib::Error& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            std::cout << "Saving using g_file_copy" << std::endl;
            tempFile->copy(file, Gio::FILE_COPY_OVERWRITE);
            std::cout << "Success" << std::endl;
        } catch (Glib::Error& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            std::cout << "Saving using g_file_move" << std::endl;
            tempFile->move(file, Gio::FILE_COPY_OVERWRITE);
            std::cout << "Success" << std::endl;
        } catch (Glib::Error& e) {
            std::cerr << e.what() << std::endl;
        }

        std::cout << "" << std::endl;
        ::close(tempFileDescriptor);
    }
}

Glib::ustring MainWindow::generateData()
{
    Glib::ustring result;
    for (int i = 0; i < 40000; ++i)
        result += "This is a test, you can safely delete me.\n";

    return result;
}
