#ifndef SAVEFILEDIALOG_HPP
#define SAVEFILEDIALOG_HPP

#include "filechoosernative.hpp"

class SaveFileDialog : public FileChooserNative {
public:
	SaveFileDialog(Gtk::Window& parent);
};

#endif // SAVEFILEDIALOG_HPP
