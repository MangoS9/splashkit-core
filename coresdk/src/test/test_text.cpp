//
//  test_text.cpp
//  splashkit
//
//  Created by Kai Renshaw on 27/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "test_text.hpp"

#include "text.h"
#include "graphics.h"
#include "input.h"
#include "color.h"
#include "utils.h"
#include "random.h"

#include <iostream>
#include <string>
using namespace std;

string stringify_font_style(int style) {
    switch (style) {
        case NORMAL_FONT: return "NORMAL_FONT";
        case BOLD_FONT: return "BOLD_FONT";
        case ITALIC_FONT: return "ITALIC_FONT";
        case UNDERLINE_FONT: return "UNDERLINE_FONT";
        default: return "NO_STYLE_FONT";
    }
}

void test_load_font()
{
    cout << "Has hara.ttf (expect 0): " << has_font("hara") << endl;
    cout << "Has LeagueGothic.otf (expect 0): " << has_font("leaguegothic") << endl;

    load_font("hara", "hara.ttf");
    font fnt = load_font("leaguegothic", "LeagueGothic.otf");

    cout << "Has hara.ttf (expect 1): " << has_font("hara") << endl;
    cout << "Has LeagueGothic.otf (expect 1): " << has_font("leaguegothic") << endl;

    draw_text("Text draws weee!", COLOR_BLACK, fnt, 25, 0, 0);
}

void test_font_styles()
{
    cout << "Setting font styles on hara.ttf" << endl;
    
    font fnt = font_named("leaguegothic");
    
    font_style style = get_font_style(fnt);
    cout << "Initial font style: " << stringify_font_style(style) << endl;
    
    set_font_style(fnt, ITALIC_FONT);
    style = get_font_style(fnt);
    cout << "After setting the font style to ITALIC: " << stringify_font_style(style) << endl;
    
    draw_text("Text draws in ITALIC weee!", COLOR_BLACK, fnt, 25, 0, 25);
    set_font_style(fnt, BOLD_FONT);
    draw_text("Text draws in BOLD weee!", COLOR_BLACK, fnt, 25, 0, 50);
    set_font_style(fnt, UNDERLINE_FONT);
    draw_text("Text draws with UNDERLINES weee!", COLOR_BLACK, fnt, 25, 0, 75);
}

void test_font_auto_load()
{
    font fnt = font_named("leaguegothic");

    draw_text(
            "Drawing text with a font size that was not explictly loaded first. (UNDERLINE)",
            COLOR_BLACK,
            fnt,
            15,
            0, 100);


    cout << "The next line should fail as the font has not been loaded." << endl;
    cout << flush;
    font_load_size("fail", 20);

    cout << "Checking is size 50 exists. Should be false: " << font_has_size("leaguegothic", 50) << endl;
    font_load_size("leaguegothic", 50);
    cout << "Checking if size 50 exists. Should be true: " << font_has_size("leaguegothic", 50) << endl;
    draw_text(
            "Preloaded... (UNDERLINE)",
            COLOR_BLACK,
            fnt,
            50,
            0, 115
    );

    set_font_style(fnt, BOLD_FONT);
    draw_text("Test... (BOLD)", COLOR_BLACK, fnt, 35, 0, 165);

    set_font_style(fnt, ITALIC_FONT);
    draw_text("Test... (ITALIC)", COLOR_BLACK, fnt, 40, 0, 200);
    for (int n : {0, 1, 2})
    {
        draw_text("Already loaded... (ITALIC)", COLOR_BLACK, fnt, 15, 0, 240 + n * 15);
    }

}

void run_text_test()
{
    open_window("Test Text", 800, 600);
    
    cout << "Testing text API" << endl;
    
    test_load_font();
    test_font_styles();
    test_font_auto_load();
    
    load_font("taroko", "Taroko.ttf");
    draw_text("タロ子フォント 教育漢字カ", COLOR_BLACK, "taroko", 30, 0, 280);

    refresh_screen();
    delay(5000);

    close_window(window_named("Test Text"));
}
