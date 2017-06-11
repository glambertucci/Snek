/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Allegro_operations.h
 * Author: lucas
 *
 * Created on June 8, 2017, 7:38 PM
 */

#ifndef ALLEGRO_OPERATIONS_H
#define ALLEGRO_OPERATIONS_H

#include "Common_definitions.h"

#define ESPACIO_LAT (100)
#define ESPACIO_INT (100)
#define LARGO_X (200)
#define LARGO_Y (90)

// Esta funcion se encarga de cargar todos los datos necesarios en la estructura definida como 'element'
//
// void * element_pointer : Es un puntero a la estructura 'element', donde debera cargar los demas datos enviados
// bool led_on : Indica si el led va a estar encendido. debe ser  'true' o 'false'
// bool led_enabled : Indica si se trata de un led, de estar en 'true' se lo va a cargar como si fuese un led. Si esta en 'false' podra tener su bitmap propio y se comportara como un boton
// void * bitmap_pointer : Es un puntero al bitmap que se le cargara en caso de que led_enabled este desactivado. Si led_enabled esta activado debe ser NULL.
void init_coord (void * element_pointer ,bool button_enabled ,void * bitmap_pointer);

void apply_movement(button * snek, valid_keys * active_keys,body * snek_body, int lenght);

void correct_movement(button * snek);

bool interception (int head_x, int head_y, void * forb_coord, int elements);
body * manage_body (body * snek_body, int lenght, button * snek);
int convert_char (char * string);
const char * convert_int (int numero);
int power ( int base, int exp);
bool valid_placement(body * food, button * snek, body * snek_body,int lenght);
void generate_food (body * food);




#endif /* ALLEGRO_OPERATIONS_H */
