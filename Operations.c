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

#include "operations.h"
#include <stdbool.h>


#define SPACE_X(counter,display_w,largo) ( ( (UNIT * display_w * ( 1 +counter )) / 4.0 ) - (largo / 2) )
#define SPACE_Y(display_h) ( (display_h * UNIT / 2 )+ TEXT_SPACE )
#define LARGO_X(display_w) ( display_w * UNIT / 5)
#define LARGO_Y(display_h) ( display_h * UNIT / 10)

void init_coord (void * element_pointer ,bool button_enabled,void * bitmap_pointer, int display_h, int display_w)
{
    button * elemento = element_pointer;
    ALLEGRO_BITMAP * bitmap = bitmap_pointer;
    static int counter1 = 0;
    static int counter2 = 0;
    
    elemento->button_enabled = button_enabled;

    if (!(elemento->button_enabled))                          // Si es la snek
    {
        elemento->position_x = UNIT * display_w / 2; 
        elemento->position_y = (UNIT * display_h / 2) + TEXT_SPACE;
        elemento->lenght_x= UNIT;
        elemento->lenght_y= UNIT;
        ++counter1;
    }
    else if (elemento->button_enabled)                  // Si es un boton
    {
        elemento->position_x = SPACE_X(counter2,display_w,LARGO_X(display_w)); 
        elemento->position_y = SPACE_Y(display_h);
        elemento->lenght_x= LARGO_X(display_w);
        elemento->lenght_y= LARGO_Y(display_h);
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
    if ((lenght >0))
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

void correct_movement(button * snek,int display_h,int display_w)
{
    if (snek->position_x >= display_w * UNIT)
        snek->position_x = 0;
    if (snek->position_y >= display_h * UNIT + TEXT_SPACE)
        snek->position_y = 0 + TEXT_SPACE;
    if (snek->position_x < 0)
        snek->position_x = display_w * UNIT;
    if (snek->position_y < TEXT_SPACE)
        snek->position_y = (display_h * UNIT)+ TEXT_SPACE;
}
#include "Allegro_IO.h"
bool interception (int head_x, int head_y, void * forb_coord, int elements)
{
    body * snek_body = forb_coord;
    int counter;
    bool valid = false;
    
    for (counter = 0 ; !valid && (counter < (elements)) ; ++counter) // Se fija si se toco a algun boton
    {
        valid = click_button(head_x,head_y,(snek_body + counter)->x,(snek_body + counter)->y, 20, 20);
    }
    

    //printf((valid ? "OK\n" : "OUT\n"));
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

int convert_char (char * string)
{
	int counter;
	int num = 0;

	for ( counter = 0; (string[counter] != 0 ) ; ++counter)
	{
		num = num * 10 + (string[counter] - '0');
	}
	return num;
}

 void convert_int (int numero, char * num)
{
	int counter;
	int how_long, try_num = numero;


	for ( how_long = 0; (try_num != 0 ) ; ++how_long)
	{
		try_num = try_num / 10;
	}

	try_num = numero;

	for (counter = how_long ; counter != 0 ; --counter)
	{
		num[how_long - counter] = ( (try_num / power(10, counter -1)) + '0');
		try_num = try_num - ( (try_num / power(10, counter -1)) * power(10, counter -1));
	}

}

int power ( int base, int exp)
{
	int counter, num = 1;
	for (counter = 1 ; counter <= exp ; ++counter)
	{
		num = num * base;
	}
	return num;
}
#include <time.h> 
void generate_food (body * food,int display_h, int display_w)
{
    srand(time(NULL));
    food->x =UNIT * ( rand() % display_w);
    food->y =UNIT * ( rand() % display_h) + TEXT_SPACE;
}
#include "Allegro_IO.h"
bool valid_placement(body * food, button * snek, body * snek_body,int lenght)
{
    bool valid = true;
    if ( interception(food->x,food->y,(void *) snek_body, lenght) )
        valid = false;
    if (button_pressed(food->x,food->y,(void *) snek,1) != (-1))
        valid = false;
    return valid;
        
}       

bool valid_movement(int keycode,valid_keys * active_keys)
{
    bool valid = true;
    int key;
    
    switch(keycode)
    {
        case UP : 
            if (active_keys->down)
                valid = false;
            break;
        case DOWN : 
            if (active_keys->up)
                valid = false;
            break;
        case LEFT :
            if (active_keys->right)
                valid = false;
            break;
        case RIGHT :
            if (active_keys->left)
                valid = false;
            break;
    }
    
    return valid;
    
}

bool validate_input(char * input)
{
    int counter;
    bool valid = true;
    
    if ( input[0] == 0)
    {
        valid = false;
    }
    else
    {
        for (counter = 0 ; input[counter] != 0 ; ++input)
        {
            if( (input[counter] > '9') || (input[counter] < '0') )
            {
                valid = false;
            }
        }
    }
    
    return valid;
}
