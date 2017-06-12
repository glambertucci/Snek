/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: lucas
 *
 * Created on June 8, 2017, 7:22 PM
 */



#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include "Allegro_operations.h"
#include "Common_definitions.h"
#include "Allegro_IO.h"

#define EASY_MODE (0)
#define MEDIUM_MODE (1)
#define HARD_MODE (2)
#define LOW_SPEED (2)
#define MID_SPEED (4)
 #define HIGH_SPEED (16)
#define SLOW_GROWTH (1)
#define MID_GROWTH  (5)
#define FAST_GROWTH (3)


#define DIFFICULTY_BUTTONS (3)

int main(void) 
{
    ALLEGRO_DISPLAY * display = NULL;           // El display
    ALLEGRO_EVENT_QUEUE * event_line = NULL;    // La event queue
    ALLEGRO_TIMER * timer = NULL;               // El timer
    
    body * snek_body = NULL;                    // El arreglo que va a guardar las coordenadas del cuerpo de la serpiente
    body food;
    
    button difficulty[3];                       // El arreglo que guarda los botones de dificultad
    button snek;                                // La cabeza de la serpiente
    valid_keys active_keys = {false,false,false,false,false}; // El arreglo que maneja la inputo del teclado
    
    bool mode_locked = false;                   // bloquea el modo de la dificultad
    bool wait_key = true;
    char mode = 0;                              // aqui se guarda la dificultad elegida
    int speed = 0, growth = 0,lenght =(-1), score = 0, growth_copy = 0;     
    
    bool close_screen = false;                  // Determina si termina el programa
    bool redraw = false;     
    bool food_exist = false;
    
    
    init_coord((void *) &(difficulty[EASY_MODE]) , true, NULL);     // Inicia los botones y la cabeza de la serpiente
    init_coord((void *) &(difficulty[MEDIUM_MODE]) , true, NULL);
    init_coord((void *) &(difficulty[HARD_MODE]) ,  true, NULL);
    init_coord((void *) &snek, false, NULL);
    
    if (al_init())
    {
        if ( ( display = al_create_display(DISPLAY_W, DISPLAY_H)))
        {
            if (event_line = al_create_event_queue())
            {
                if (difficulty[EASY_MODE].bitmap = al_create_bitmap(difficulty[EASY_MODE].lenght_x,difficulty[EASY_MODE].lenght_y) )
                {
                    if (difficulty[MEDIUM_MODE].bitmap = al_create_bitmap(difficulty[MEDIUM_MODE].lenght_x, difficulty[MEDIUM_MODE].lenght_y))
                    {
                        if (difficulty[HARD_MODE].bitmap = al_create_bitmap(difficulty[HARD_MODE].lenght_x, difficulty[HARD_MODE].lenght_y))
                        {  
                            if (timer = al_create_timer(1 / FPS))
                            {
                                if (snek.bitmap = al_create_bitmap(snek.lenght_x,snek.lenght_y))
                                {
                                    al_install_mouse();
                                    al_install_keyboard();
                                }
                                else
                                {
                                    fprintf(stderr,"Timer not initialized");
                                    al_destroy_bitmap(difficulty[HARD_MODE].bitmap);
                                    al_destroy_bitmap(difficulty[EASY_MODE].bitmap);
                                    al_destroy_bitmap(difficulty[MEDIUM_MODE].bitmap);
                                    al_destroy_timer(timer);
                                    al_destroy_event_queue(event_line);
                                    al_destroy_display(display);
                                    return 1;
                                }
                            }
                            else
                            {
                                fprintf(stderr,"Timer not initialized");
                                al_destroy_bitmap(difficulty[HARD_MODE].bitmap);
                                al_destroy_bitmap(difficulty[EASY_MODE].bitmap);
                                al_destroy_bitmap(difficulty[MEDIUM_MODE].bitmap);
                                al_destroy_event_queue(event_line);
                                al_destroy_display(display);
                                return 1;
                            }
                        }
                        else
                        {
                            fprintf(stderr,"Hard bitmap not initialized");
                            al_destroy_bitmap(difficulty[EASY_MODE].bitmap);
                            al_destroy_bitmap(difficulty[MEDIUM_MODE].bitmap);
                            al_destroy_event_queue(event_line);
                            al_destroy_display(display);
                            return 1;
                        }
                    }
                    else
                    {
                        fprintf(stderr,"Meduim bitmap not initialized");
                        al_destroy_bitmap(difficulty[EASY_MODE].bitmap);
                        al_destroy_event_queue(event_line);
                        al_destroy_display(display);
                        return 1;
                    }
                }
                else
                {
                    fprintf(stderr,"Easy bitmap not initialized");
                    al_destroy_event_queue(event_line);
                    al_destroy_display(display);
                    return 1;
                }
            }
            else
            {
                fprintf(stderr,"Event Queue not initialized");
                al_destroy_display(display);
                return 1;
            }
        }
        else
        {
            fprintf(stderr,"Display not initialized");
            return 1;
        }
    } 
    else
    {
        fprintf(stderr, "Allegro not initialized");
        return 1;
    }
    
    al_register_event_source(event_line,al_get_display_event_source(display));
    al_register_event_source(event_line,al_get_mouse_event_source());
    al_register_event_source(event_line, al_get_keyboard_event_source());
    al_register_event_source(event_line,al_get_timer_event_source(timer));
    
    
    al_set_target_bitmap(snek.bitmap);              // Cargo el color de la cabeza de la serpiente.
    al_clear_to_color(al_color_name("green"));      // Ahora es el mismo que el cuerpo pero despues va a haber que cambiarlo
    
    al_set_target_bitmap(al_get_backbuffer(display)); // Pongo la pantalla en blanco 
    al_clear_to_color(al_color_name("white"));
    
    al_set_target_bitmap(difficulty[EASY_MODE].bitmap); // Cargo el color del boton facil
    al_clear_to_color(al_color_name("white"));
    
    al_set_target_bitmap(difficulty[MEDIUM_MODE].bitmap);   //Cargo el color del boton medio
    al_clear_to_color(al_color_name("blue"));
    
    al_set_target_bitmap(difficulty[HARD_MODE].bitmap);     // Cargo el color del boton dificil
    al_clear_to_color(al_color_name("grey"));
    al_set_target_bitmap(al_get_backbuffer(display));
                                                            // Dibujo todos los botones de dificultad
    al_draw_bitmap(difficulty[EASY_MODE].bitmap,difficulty[EASY_MODE].position_x, difficulty[EASY_MODE].position_y, 0);
    al_draw_bitmap(difficulty[MEDIUM_MODE].bitmap,difficulty[MEDIUM_MODE].position_x, difficulty[MEDIUM_MODE].position_y, 0);
    al_draw_bitmap(difficulty[HARD_MODE].bitmap,difficulty[HARD_MODE].position_x, difficulty[HARD_MODE].position_y, 0);
    al_flip_display();
    
    al_start_timer(timer);
    
    printf ( "high score = %d \n",read_high_score());
    
    while (!close_screen)
    {
        ALLEGRO_EVENT event;
        if (al_get_next_event(event_line,&event))
        {
            switch (event.type)
            {
                case ALLEGRO_EVENT_KEY_DOWN :   // Detecta cuando se toca una tecla
                    
                    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)   //Si se toca escape, se termina el juego
                        close_screen = true;
                    else if(wait_key && mode_locked && (event.keyboard.keycode >= ALLEGRO_KEY_LEFT) && (event.keyboard.keycode <= ALLEGRO_KEY_DOWN))
                    {
                        if (valid_movement(event.keyboard.keycode,&active_keys))
                        {
                            manage_movement(&active_keys,UP, false);        //Borra la direccion en la que se estaba
                            manage_movement(&active_keys,DOWN, false);      //moviendo y la cambia por la nueva
                            manage_movement(&active_keys,LEFT, false);
                            manage_movement(&active_keys,RIGHT, false);
                            manage_movement(&active_keys,event.keyboard.keycode, true); 
                            wait_key = false;
                        }
                    }
                    printf(" UP = %d DOWN = %d LEFT = %d RIGHT = %d space = %d\n",active_keys.up,active_keys.down,active_keys.left,active_keys.right,active_keys.pause);
                    break;

                case ALLEGRO_EVENT_DISPLAY_CLOSE : close_screen = true; break; //Si se cierra la pantalla termina el juego
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : 
                    if (!mode_locked)               //Se elije cual fue el modo de juego elegido por el usuario y se establecen las
                    {                               // configuraciones necesarias
                        mode =button_pressed(event.mouse.x, event.mouse.y, difficulty, DIFFICULTY_BUTTONS);
                        switch (mode)
                        {
                            case EASY_MODE: speed = LOW_SPEED; growth = SLOW_GROWTH ;
                            printf("------ EASY MODE \n speed = %d      growth = %d\n", speed, growth);
                            mode_locked = true;
                            break;
                            case MEDIUM_MODE: speed = MID_SPEED; growth = MID_GROWTH ;
                            printf("------ MEDIUM MODE \n speed = %d      growth = %d\n", speed, growth);
                            mode_locked = true;
                            break;
                            case HARD_MODE: speed = HIGH_SPEED; growth = FAST_GROWTH ;
                            printf("------ HARD MODE \n speed = %d      growth = %d\n", speed, growth);
                            mode_locked = true;
                            break;
                        }
                    }
                    break; 
                case ALLEGRO_EVENT_TIMER :
                    
                    if (  mode_locked && !(event.timer.count % ((int)FPS / speed))) // Determina la velocidad del juego
                    {
                        if (!close_screen)
                        {
                            apply_movement(&snek, &active_keys,snek_body,lenght);
                            correct_movement(&snek);     
                            wait_key = true;
                            redraw = true;
                        }
                    } 
                    while (!food_exist)
                    {
                        
                        generate_food (&food);
                        food_exist = valid_placement(&food, &snek, snek_body, lenght);
                    }
                    break;
                    
            }
        }
        
        if (redraw && al_event_queue_is_empty(event_line) && mode_locked)
        {
            redraw = false;

            print_display( &snek,snek_body,NULL,&food,lenght+1);

            if (interception(snek.position_x,snek.position_y,(void *) snek_body,lenght))
            {
                printf("Game Over\n");
                close_screen = true;
            }
            else if ( interception(snek.position_x, snek.position_y, (void *) &food,1) )
            {
                ++score;
                food_exist = false;
                growth_copy = growth;
                 if (lenght == -1)
                    ++lenght;                
            }
            if (growth_copy > 0)
            {
                if (snek_body = manage_body (snek_body, lenght, &snek))
                    ++lenght;
                else
                    close_screen = true;
                --growth_copy;
            }
        }
    }
    if ( score > read_high_score() )
        write_high_score(score);
    printf("Score = %d/n", score);
    
   
    free(snek_body);
    printf("pap");
    al_destroy_bitmap(difficulty[HARD_MODE].bitmap);
    al_destroy_bitmap(difficulty[EASY_MODE].bitmap);
    al_destroy_bitmap(difficulty[MEDIUM_MODE].bitmap);
    al_destroy_bitmap(snek.bitmap);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_line);
    al_destroy_display(display);

    return (0);
}

