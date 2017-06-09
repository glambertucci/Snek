/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Common_definitions.h
 * Author: lucas
 *
 * Created on June 8, 2017, 8:03 PM
 */

#ifndef COMMON_DEFINITIONS_H
#define COMMON_DEFINITIONS_H

#include <allegro5/allegro5.h>

typedef struct
{
    float position_x;
    float position_y;
    int lenght_x;
    int lenght_y;
    bool button_enabled;
    ALLEGRO_BITMAP * bitmap;
    
} button;

typedef struct
{
    bool up;
    bool down;
    bool left;
    bool right;
    bool pause;
} valid_keys;


// Screen related
#define FPS (60.0)
#define UNIT (40)
#define VERTICAL_UNITS (15)
#define HORIZONTAL_UNITS (25)
#define TEXT_SPACE (60)
#define DISPLAY_W (UNIT * HORIZONTAL_UNITS)
#define DISPLAY_H (UNIT * VERTICAL_UNITS + TEXT_SPACE)

// Keyboard related
#define UP (ALLEGRO_KEY_UP)
#define DOWN (ALLEGRO_KEY_DOWN)
#define LEFT (ALLEGRO_KEY_LEFT)
#define RIGHT (ALLEGRO_KEY_RIGHT)
#define PAUSE (ALLEGRO_KEY_SPACE)

#endif /* COMMON_DEFINITIONS_H */

