#include "filechoosernative.hpp"

FileChooserNative::FileChooserNative(Gtk::Window& parent,
    const Glib::ustring& title,
    GtkFileChooserAction action,
    const Glib::ustring& accept_label,
    const Glib::ustring& cancel_label)
{
    m_fileChooser = gtk_file_chooser_native_new(title.c_str(),
        parent.gobj(),
        action,
        accept_label.c_str(),
        cancel_label.c_str());
}

FileChooserNative::~FileChooserNative()
{
    g_object_unref(m_fileChooser);
}

void FileChooserNative::set_current_name(const Glib::ustring& name)
{
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(m_fileChooser),
        name.c_str());
}

Glib::RefPtr<Gio::File> FileChooserNative::get_file() const
{
    return Glib::wrap(gtk_file_chooser_get_file(GTK_FILE_CHOOSER(m_fileChooser)));
}

gint FileChooserNative::run()
{
    return gtk_native_dialog_run(GTK_NATIVE_DIALOG(m_fileChooser));
}
