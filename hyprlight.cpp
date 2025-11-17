#include <gtk/gtk.h>
#include <iostream>
#include <sstream>
#include <array>
#include <cstdio>
#include <string>

std::string 
execCmd(const std::string &cmd) {
    std::array<char, 128> buffer{};
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    while (fgets(buffer.data(), 128, pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    return result;
}

int 
getCurrentBrightness() {
    std::string out = execCmd("brightnessctl g");
    int current = std::stoi(out);
    out = execCmd("brightnessctl m");
    int max = std::stoi(out);
    return (100 * current) / max; // percent
}

static void 
on_brightness_changed(GtkRange *range, gpointer) {
    int value = (int)gtk_range_get_value(range);
    std::ostringstream cmd;
    cmd << "brightnessctl set " << value << "%";
    execCmd(cmd.str());
}

static void 
on_temp_changed(GtkRange *range, gpointer) {
    int value = (int)gtk_range_get_value(range);
    std::ostringstream cmd;
    cmd << "hyprctl hyprsunset temperature " << value;
    execCmd(cmd.str());
}

static void 
on_gamma_changed(GtkRange *range, gpointer) {
    int value = (int)gtk_range_get_value(range);  // gamma percent
    std::ostringstream cmd;
    cmd << "hyprctl hyprsunset gamma " << value;
    execCmd(cmd.str());
}

int 
main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "HyprLight");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Black background
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "* { background-color: #000000; color: white; }", -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Brightness
    GtkWidget *brightness = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
    gtk_scale_set_value_pos(GTK_SCALE(brightness), GTK_POS_RIGHT);
    gtk_box_pack_start(GTK_BOX(vbox), brightness, TRUE, TRUE, 5);

    // Temperature
    GtkWidget *temp = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1000, 10000, 50);
    gtk_scale_set_value_pos(GTK_SCALE(temp), GTK_POS_RIGHT);
    gtk_box_pack_start(GTK_BOX(vbox), temp, TRUE, TRUE, 5);

    // Gamma
    GtkWidget *gamma = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 50, 200, 1);
    gtk_scale_set_value_pos(GTK_SCALE(gamma), GTK_POS_RIGHT);
    gtk_box_pack_start(GTK_BOX(vbox), gamma, TRUE, TRUE, 5);

    // Load real brightness
    int curBright = getCurrentBrightness();
    gtk_range_set_value(GTK_RANGE(brightness), curBright);

    // Default values for hyprsonset (we can't read them easily)
    gtk_range_set_value(GTK_RANGE(temp), 6500);
    gtk_range_set_value(GTK_RANGE(gamma), 100);

    // Signals
    g_signal_connect(brightness, "value-changed", G_CALLBACK(on_brightness_changed), NULL);
    g_signal_connect(temp, "value-changed", G_CALLBACK(on_temp_changed), NULL);
    g_signal_connect(gamma, "value-changed", G_CALLBACK(on_gamma_changed), NULL);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
 
