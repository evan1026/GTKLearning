#include <Logger/Logger.hpp>
#include <MiscUtils/MiscUtils.hpp>
#include <gtkmm.h>
#include "main.hpp"

//Used to suppress "Unused variable" warnings
#define MON_Internal_UnusedStringify(macro_arg_string_literal) #macro_arg_string_literal
#define MarkUnused(macro_arg_parameter) _Pragma(MON_Internal_UnusedStringify(unused(macro_arg_parameter)))

Logger logger;

Glib::RefPtr<Gtk::Adjustment> ad1;
Glib::RefPtr<Gtk::Adjustment> ad2;

Gtk::ProgressBar* pb1;
Gtk::ProgressBar* pb2;

Glib::RefPtr<Gtk::StatusIcon> icon;

void on_adjustment1_value_changed(){
    pb1->set_fraction(ad1->get_value() / 100);
}

void on_adjustment2_value_changed(){
    pb2->set_fraction(1 - ad2->get_value() / 100);
}

void icon_thread(){
    while (true){
        delay(500);
        icon->set_from_file("../icon/export/icon2.png"); //I wanted to do caching, but couldn't get it figured out.
        delay(500);
        icon->set_from_file("../icon/export/icon1.png"); //But this doesn't actually cause a performance drop.
    }
}

int main(int argc, char* argv[]){
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("Unsaved 1.glade");

    Gtk::Window* window;
    builder->get_widget("window1", window);

    ad1 = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(builder->get_object("adjustment1"));
    ad2 = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(builder->get_object("adjustment2"));

    ad1->signal_value_changed().connect(sigc::ptr_fun(on_adjustment1_value_changed));
    ad2->signal_value_changed().connect(sigc::ptr_fun(on_adjustment2_value_changed));

    builder->get_widget("progressbar1", pb1);
    builder->get_widget("progressbar2", pb2);

    icon = Glib::RefPtr<Gtk::StatusIcon>::cast_dynamic(builder->get_object("statusicon1"));

    Glib::Threads::Thread* iconThread = Glib::Threads::Thread::create(sigc::ptr_fun(icon_thread));
    MarkUnused(iconThread); //Suppresses "Unused variable" warnings

    return app->run(*window);
}
