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
//#define RECTANGLE_X(counter) (ESPACIO_LAT_RECT + (counter * ESPACIO_INT_RECT) + (counter *LARGO_RECT_X))


void init_coord (void * element_pointer ,bool led_on ,bool led_enabled,void * bitmap_pointer)
{
    button * elemento = element_pointer;
    ALLEGRO_BITMAP * bitmap = bitmap_pointer;
    static int counter1 = 0;
    static int counter2 = 0;
    
    elemento->led_enabled = led_enabled;

    if (elemento->led_enabled)                          // Si es un led
    {
        elemento->position_x = SQUARE_X(counter1); 
        elemento->position_y = 100;
        elemento->lenght_x= LARGO_X;
        elemento->lenght_y= LARGO_Y;
        ++counter1;
    }
    else if (!(elemento->led_enabled))                  // Si es un boton
    {
        elemento->position_x = SQUARE_X(counter2); 
        elemento->position_y = 400;
        elemento->lenght_x= LARGO_X;
        elemento->lenght_y= LARGO_Y;
        ++counter2;
    }
    elemento->led_on = led_on;
    elemento->bitmap = bitmap;
  
}