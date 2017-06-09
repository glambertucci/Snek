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
#define MID_GROWTH  (2)
#define FAST_GROWTH (3)

#define SPEED(a) (a)

#define DIFFICULTY_BUTTONS (3)

int main(void) 
{
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_line = NULL;
    ALLEGRO_TIMER * timer = NULL;
    
    button difficulty[3];
    button snek;
    valid_keys active_keys = {false,false,false,false,false};
    
    bool mode_locked = false;
    char mode = 0;
    int speed = 0, growth = 0;
    
    bool close_screen = false;
    bool redraw = false;
    
    
    init_coord((void *) &(difficulty[EASY_MODE]) , true, NULL);
    init_coord((void *) &(difficulty[MEDIUM_MODE]) , true, NULL);
    init_coord((void *) &(difficulty[HARD_MODE]) ,  true, NULL);
    init_coord((void *) &snek, false, NULL);
    printf("1");
    
    if (al_init())
    {
        if ( ( display = al_create_display(DISPLAY_W, DISPLAY_H)))
        {
            printf("2");
            if (event_line = al_create_event_queue())
            {
                printf("3");
                if (difficulty[EASY_MODE].bitmap = al_create_bitmap(difficulty[EASY_MODE].lenght_x,difficulty[EASY_MODE].lenght_y) )
                {
                    printf("4");
                    if (difficulty[MEDIUM_MODE].bitmap = al_create_bitmap(difficulty[MEDIUM_MODE].lenght_x, difficulty[MEDIUM_MODE].lenght_y))
                    {
                        printf("5");
                        if (difficulty[HARD_MODE].bitmap = al_create_bitmap(difficulty[HARD_MODE].lenght_x, difficulty[HARD_MODE].lenght_y))
                        {  
                            printf("6");
                            if (timer = al_create_timer(1 / FPS))
                            {
                                printf("7");
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
    
    
    al_set_target_bitmap(snek.bitmap);
    al_clear_to_color(al_color_name("green"));
    
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_color_name("hotpink"));
    
    al_set_target_bitmap(difficulty[EASY_MODE].bitmap);
    al_clear_to_color(al_color_name("white"));
    
    al_set_target_bitmap(difficulty[MEDIUM_MODE].bitmap);
    al_clear_to_color(al_color_name("blue"));
    
    al_set_target_bitmap(difficulty[HARD_MODE].bitmap);
    al_clear_to_color(al_color_name("grey"));
    al_set_target_bitmap(al_get_backbuffer(display));
    
    al_draw_bitmap(difficulty[EASY_MODE].bitmap,difficulty[EASY_MODE].position_x, difficulty[EASY_MODE].position_y, 0);
    al_draw_bitmap(difficulty[MEDIUM_MODE].bitmap,difficulty[MEDIUM_MODE].position_x, difficulty[MEDIUM_MODE].position_y, 0);
    al_draw_bitmap(difficulty[HARD_MODE].bitmap,difficulty[HARD_MODE].position_x, difficulty[HARD_MODE].position_y, 0);
    al_flip_display();
    
    al_start_timer(timer);
    
    while (!close_screen)
    {
        ALLEGRO_EVENT event;
        if (al_get_next_event(event_line,&event))
        {
            switch (event.type)
            {
                case ALLEGRO_EVENT_KEY_DOWN : 
                    
                    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                        close_screen = true;
                    else if(mode_locked)
                    {
                        manage_movement(&active_keys,UP, false);
                        manage_movement(&active_keys,DOWN, false);
                        manage_movement(&active_keys,LEFT, false);
                        manage_movement(&active_keys,RIGHT, false);
                        manage_movement(&active_keys,PAUSE, false);
                        manage_movement(&active_keys,event.keyboard.keycode, true); 
                    }
                    printf(" UP = %d DOWN = %d LEFT = %d RIGHT = %d space = %d\n",active_keys.up,active_keys.down,active_keys.left,active_keys.right,active_keys.pause);
                    break;

                case ALLEGRO_EVENT_DISPLAY_CLOSE : close_screen = true; break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : 
                    if (!mode_locked)
                    {
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
                    
                    if ( mode_locked && !(event.timer.count % ((int)FPS / speed)))
                    {
                        apply_movement(&snek, &active_keys);
                        correct_movement(&snek);
                        redraw = true;
                    }
                    break;
                    
            }
        }
        
        if (redraw && al_event_queue_is_empty(event_line) && mode_locked)
        {
            redraw = false;
            print_display((void *) &snek,NULL,1);
        }
    }
    
   
    
    al_destroy_bitmap(difficulty[HARD_MODE].bitmap);
    al_destroy_bitmap(difficulty[EASY_MODE].bitmap);
    al_destroy_bitmap(difficulty[MEDIUM_MODE].bitmap);
    al_destroy_bitmap(snek.bitmap);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_line);
    al_destroy_display(display);

    return (0);
}

