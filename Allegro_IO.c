/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Allegro_IO.c
 * Author: lucas
 * 
 * Created on June 8, 2017, 8:28 PM
 */

#include "Allegro_IO.h"
#include "Common_definitions.h"


void print_display (button * head,body * snek_body, void * background,body * food, int elementos)
{
    int counter;
    al_clear_to_color(al_color_name("hotpink"));
    
    al_draw_bitmap(head->bitmap,food->x, food->y,0);

    al_draw_bitmap(head->bitmap,head->position_x ,head->position_y,0);
    

    for (counter = 0 ; counter < elementos ; ++counter)
    {      
        al_draw_bitmap(head->bitmap,(snek_body + counter)->x ,(snek_body + counter)->y,0);
    }

    al_flip_display();
}


bool click_button(int mouse_x, int mouse_y, int button_x, int button_y , int lenght_x, int lenght_y )
{
    bool valid = false; 
    
    printf("button_x = %d < mouse_x = %d  < %d = button_x + lenght_x\n",button_x,mouse_x,button_x + lenght_x);
    printf("button_y = %d < mouse_y = %d  < %d = button_y + lenght_y\n",button_y,mouse_y,button_y + lenght_y);
    if ( (mouse_x >= button_x) && (mouse_x <= ( button_x + lenght_x) ))
    {
        if ((mouse_y >= button_y) && (mouse_y <= ( button_y + lenght_y) ))
        {
            valid = true;
        }
    }
    return valid;
}


int button_pressed (int mouse_x, int mouse_y, void * pointer2, int elements)
{
    button * pointer = pointer2;
    int counter;
    bool valid = false;
    
    for (counter = 0 ; !valid && (counter < (elements+1)) ; ++counter) // Se fija si se toco a algun boton
    {
        valid = click_button(mouse_x,mouse_y,(pointer + counter)->position_x,(pointer + counter)->position_y, (pointer + counter)->lenght_x, (pointer + counter)->lenght_y);
    }
    
    if (counter == elements + 1)   // Si no esta en la lista, es por que no toca a ningun boton
    {
        counter = -1;
    }
    else
    {
        --counter;
    }
    
    return counter;
}

void manage_movement ( valid_keys * active_keys, int key_typed, bool is_key_down)
{
    switch (key_typed)
    {
        case UP : active_keys->up = is_key_down; break;
        case DOWN : active_keys->down = is_key_down; break;
        case LEFT : active_keys->left = is_key_down; break;
        case RIGHT : active_keys->right = is_key_down; break;
        case PAUSE : active_keys->pause = is_key_down; break;
    }
}

int read_high_score (void)
{
	
	FILE * high_score = NULL;
	char line [4];
        int num = -1;

	if (! (high_score = fopen("score.txt", "r"))) // fopen
	{
		high_score = fopen("score.txt", "w");
   		fprintf(high_score, "0"); // fprintf
		fclose(high_score); // fclose
	}
	high_score = fopen("score.txt", "r");
	
        if ( !fgets(line, 4,high_score))
        {
            printf("NOPEBOPE");
        }
        else
        {
            num = convert_char (line);
        }
	
   	fclose(high_score); 

	return num;
}

void write_high_score (int score)
{
	FILE * high_score = NULL;
        char dest [5]={0,0,0,0,0};
        convert_int(score, dest);
	if ((high_score = fopen("score.txt", "w+")))
	{
		if ( fputs(dest,high_score) == EOF )
                {
                    
                }
		fclose(high_score);
	}
}