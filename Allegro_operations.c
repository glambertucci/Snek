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

void apply_movement(button * snek, valid_keys * active_keys,body * snek_body, int lenght)
{
    int counter = 20;
  
       
    for (counter = lenght -1 ; counter >=1 ; --counter)
    {
        snek_body[counter].x = snek_body[counter-1].x;
        snek_body[counter].y = snek_body[counter-1].y;
    }
    if ((counter == 0) || (lenght ==0))
    {
        snek_body[0].x = snek->position_x;
        snek_body[0].y =snek->position_y;
    }
        
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
#include "Allegro_IO.h"
int interception (int head_x, int head_y, void * forb_coord, int elements)
{
    body * snek_body = forb_coord;
    int counter;
    bool valid = false;
    
    for (counter = 0 ; !valid && (counter < (elements+1)) ; ++counter) // Se fija si se toco a algun boton
    {
        valid = click_button(head_x,head_y,(snek_body + counter)->x,(snek_body + counter)->y, 20, 20);
    }
    

    printf((valid ? "OK\n" : "OUT\n"));
    return valid;
}

body * manage_body (body * snek_body, int lenght, button * snek)
{
    if (snek_body = realloc(snek_body,(lenght +1) * sizeof(body)))
    {
        snek_body[lenght].x = snek->position_x;
        snek_body[lenght].y = snek->position_y;
    }
    return snek_body;
}