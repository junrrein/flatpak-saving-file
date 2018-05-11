#include "MainWindow.h"
#include "savefiledialog.hpp"
#include <giomm/file.h>

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

        file->replace_contents(generateData(),
            etag,
            etag,
            false,
            Gio::FILE_CREATE_REPLACE_DESTINATION);
    }
}

std::string MainWindow::generateData()
{
    std::string result;
    for (int i = 0; i < 40000; ++i)
        result += "This is a test, you can safely delete me.\n";

    return result;
}
