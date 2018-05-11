#ifndef FILECHOOSERNATIVE_HPP
#define FILECHOOSERNATIVE_HPP

#include <gtkmm.h>

// Wrapper class around GtkFileChooserNative

class FileChooserNative {
public:
    FileChooserNative(Gtk::Window& parent,
                      const Glib::ustring& title,
                      GtkFileChooserAction action,
                      const Glib::ustring& accept_label,
                      const Glib::ustring& cancel_label);
    ~FileChooserNative();

    void set_current_name(const Glib::ustring& name);
    Glib::RefPtr<Gio::File> get_file() const;
    gint run();

private:
    GtkFileChooserNative* m_fileChooser;
};

#endif // FILECHOOSERNATIVE_HPP
