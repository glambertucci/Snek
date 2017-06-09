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
    bool led_on;
    bool led_enabled;
    ALLEGRO_BITMAP * bitmap;
    
} button;

#define DISPLAY_W (1000)
#define DISPLAY_H (1000)

#endif /* COMMON_DEFINITIONS_H */

