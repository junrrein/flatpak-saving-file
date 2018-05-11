# A test program for saving files using GtkFileChooserNative and Gtkmm

## How to use

```bash
git clone https://github.com/junrrein/flatpak-saving-file.git
flatpak remote-add --from gnome https://sdk.gnome.org/gnome.flatpakrepo
flatpak install gnome org.gnome.Platform//3.28
flatpak install gnome org.gnome.Sdk//3.28
flatpak-builder --repo=flatpak-bug-repo flatpak-bug flatpak-saving-file/com.sharedpointer.simple-gtkmm-app.json --force-clean
flatpak --user remote-add --no-gpg-verify --if-not-exists flatpak-bug-repo flatpak-bug-repo
flatpak --user install flatpak-bug-repo com.sharedpointer.simple-gtkmm-app
flatpak run --command=bash com.sharedpointer.simple-gtkmm-app
export LANG=C
simple-gtkmm-app
```

The error shown in the console (if any occur) will have the form of:

```
(simple-gtkmm-app:7): glibmm-CRITICAL **: 20:23:45.725: 
unhandled exception (type Glib::Error) in signal handler:
domain: g-io-error-quark
code  : 1
what  : Error opening file ?/run/user/1000/doc/8e667a75/text file.txt?: No such file or directory
```

## Cleaning up

```bash
flatpak --user uninstall com.sharedpointer.simple-gtkmm-app
flatpak --user remote-delete flatpak-bug-repo
rm -rf flatpak-bug-repo/ flatpak-saving-file/
```

## Acknowledgments

Sample project using Gtkmm and Flatpak taken from https://github.com/futuretim/simple-gtkmm-flatpak-app/.
