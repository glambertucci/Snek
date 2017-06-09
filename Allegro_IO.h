/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Allegro_IO.h
 * Author: lucas
 *
 * Created on June 8, 2017, 8:28 PM
 */

#ifndef ALLEGRO_IO_H
#define ALLEGRO_IO_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Common_definitions.h"

// Se fija si al hacer click, tocaste algun boton. Si lo tocaste devuelve 'true', sino devuelve 'false'
//
// int mouse_x  :   Debe ser la coordenada en X de donde el mouse hizo click ( debe ser >=0 y menor al alto total de la pantalla)
// int mouse_y  :   Debe ser la coordenada en Y de donde el mouse hizo click ( debe ser >=0 y menor al alto total de la pantalla)
// int button_x :   Es la coordenada en X donde comienza el boton
// int button_y :   Es la coordenada en Y donde comienza el boton
// int lenght_x :   Es el largo en el eje X del boton
// int lenght_y :   Es la altura del boton en el eje Y
bool click_button(int mouse_x, int mouse_y, int button_x, int button_y , int lenght_x, int lenght_y );

// Dada una cantidad de botones que se le envia a la funcion, devuelve el valor (0 a (cantidad de elementos-1)) que identifica al boton
//
// int mouse_x  :   Debe ser la coordenada en X de donde el mouse hizo click ( debe ser >=0 y menor al alto total de la pantalla)
// int mouse_y  :   Debe ser la coordenada en Y de donde el mouse hizo click ( debe ser >=0 y menor al alto total de la pantalla)
// void * pointer2 : Debe ser un puntero al primer elemento de un arreglo de estructuras definidas con el typedef 'element' en el archivo 'define.h'
// int elements :   Es la cantidad de botones que hay en pantalla y que se quiere fijar si se han tocado
int button_pressed (int mouse_x, int mouse_y, void * pointer2, int elements);

// Esta funcion se encarga de imprimir en el display al fondo de pantalla y a todos los botones en su lugar
// La funcion tambien puede imprimir los bitmaps que  estan en la estructura de cada boton, pero para eso deben
// tener la opcion led_enabled en 'false'
//
// void * element_pointer : Debe ser un puntero al primer elemento de un arreglo de estructuras definidas con el typedef 'element' en el archivo 'define.h'
// void * background : Es un puntero que apunta a un bitmap de allegro, que contiene el fondo que se le va a aplicar
// void * led_on_void : Es un puntero que apunta a un bitmap de allegro, que se utiliza para mostrar que un led esta encendido
// void * led_off_void : Es un puntero que apunta a un bitmap de allegro, que se utiliza para mostrar que un led esta apagado
// int elements :   Es la cantidad de botones que hay en pantalla y que se quiere fijar si se han tocado
void print_display (button * head,body * snek_body, void * background, int elementos);

// Esta funcion permite controlar el movimiento
//
// valid_keys * active_keys : Es un puntero a una estructura definida en Common_definitios.h, que contiene a las teclas que puede ser presionadas
// int key_typed : Es la tecla que fue presionada, de no haber presionada ninguna tecla, no modificara nada.
// bool is_key_down : Establece si se esta presionando la tecla, o si se esta levantado el dedo. 
void manage_movement ( valid_keys * active_keys, int key_typed, bool is_key_down);
#endif /* ALLEGRO_IO_H */
