#include "savefiledialog.hpp"

SaveFileDialog::SaveFileDialog(Gtk::Window& parent)
    : FileChooserNative{ parent,
        "Save document as",
        GTK_FILE_CHOOSER_ACTION_SAVE,
        "Save",
        "Cancel" }
{
    set_current_name("text file.txt");
}
