#pragma once

#include "snail/application.hpp"
#include <string>

namespace elona
{

struct position_t;

position_t gmes(const std::string&, int, int, int, const snail::color&, bool);
void initialize_ui_constants();
void display_customkey(const std::string&, int, int);
void display_key(int = 0, int = 0, int = 0);
void display_msg(int = 0, int = 0);
void display_note(const std::string&, int = 0);
void display_topic(const std::string&, int = 0, int = 0, int = 0);
void display_window(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
void display_window2(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
void fillbg(int = 0, int = 0, int = 0, int = 0, int = 0);
void drawmenu(int = 0);
void screen_txtadv();
void label_1416();
void update_entire_screen();
void update_screen_hud();
void update_screen();
void update_minimap();
void label_1420();
void render_hud();
void label_1422();
void label_1423();
void draw_caption();
void label_1428();
void label_1429();
void label_1433();
void label_1434();
void label_1435();
void label_1436();
void label_1437();
void label_1438();
void label_1439();
void label_1440();
void fade_out();
void label_1442();
void label_1443();
void label_1444();
void label_1445();
void label_1446();
void clear_background_in_character_making();

}
