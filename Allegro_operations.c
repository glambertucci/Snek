/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Allegro_operations.c
 * Author: lucas
 * 
 * Created on June 8, 2017, 7:38 PM
 */

#include "Allegro_operations.h"
#include <stdbool.h>


#define SQUARE_X(counter) (ESPACIO_LAT+(counter * ESPACIO_INT) + (counter * LARGO_X ))


void init_coord (void * element_pointer ,bool button_enabled,void * bitmap_pointer)
{
    button * elemento = element_pointer;
    ALLEGRO_BITMAP * bitmap = bitmap_pointer;
    static int counter1 = 0;
    static int counter2 = 0;
    
    elemento->button_enabled = button_enabled;

    if (!(elemento->button_enabled))                          // Si es la snek
    {
        elemento->position_x = UNIT * 13; 
        elemento->position_y = UNIT * 7 + TEXT_SPACE;
        elemento->lenght_x= UNIT;
        elemento->lenght_y= UNIT;
        ++counter1;
    }
    else if (elemento->button_enabled)                  // Si es un boton
    {
        elemento->position_x = SQUARE_X(counter2); 
        elemento->position_y = DISPLAY_H / 2.0;
        elemento->lenght_x= LARGO_X;
        elemento->lenght_y= LARGO_Y;
        ++counter2;
    }
    elemento->bitmap = bitmap;
  
}

void apply_movement(button * snek, valid_keys * active_keys)
{
    if (active_keys->up)
        snek->position_y -= UNIT;
    else if (active_keys->down)
        snek->position_y += UNIT;
    if (active_keys->left)
        snek->position_x -= UNIT;
    else if (active_keys->right)
        snek->position_x += UNIT;
}

void correct_movement(button * snek)
{
    if (snek->position_x >= DISPLAY_W)
        snek->position_x = 0;
    if (snek->position_y >= DISPLAY_H)
        snek->position_y = 0 + TEXT_SPACE;
    if (snek->position_x < 0)
        snek->position_x = DISPLAY_W;
    if (snek->position_y < 0 + TEXT_SPACE)
        snek->position_y = DISPLAY_H;
}
