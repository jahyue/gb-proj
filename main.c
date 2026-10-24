#include <stdint.h>
#include <stdbool.h>
#include <gb/gb.h>
#include <gbdk/console.h>
#include <gb/drawing.h>
#include <stdlib.h>
#include <rand.h>

#define STATE_TITLE     0
#define STATE_READY     1
#define STATE_PLAYING   2
#define STATE_GAME_OVER 3
unsigned char player_sprite[] =
{
    0xFF,0xFF,0x81,0x81,0x81,0x81,0xA5,0xA5,0x81,0x81,0x99,0x99,0x81,0x81,0xFF,0xFF,
};

unsigned char PipesetTiles[] =
{
    0xFF,0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
    0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
    0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0xFF,0xFF,
};
unsigned char PipesetMap[] =
{
    0x00,0x01,0x02,
};
struct GamePlayer {
    uint8_t x;
    uint8_t y;
    int8_t speed;
    int8_t gravity;
};

struct GamePlayer player;

uint16_t score = 0;
void main(void) {
    uint8_t gap_row = 7;
    bool buttonheld = false;
    uint16_t gamestate = STATE_TITLE;
    player.x = 40;
    player.y = 70;
    player.speed = 2;
    player.gravity = 1;
    set_sprite_data(1,3,PipesetTiles);
    
    set_sprite_data(0,1,player_sprite);
    set_sprite_tile(0,0);
    
uint8_t pipe_x = 160;
    for (int i = 1; i < gap_row; i++) {
    uint8_t tile;

    if (i == gap_row-1) {
        tile = 3; 
    } else if(i == 1){
        tile = 1;
    } else {
        tile = 2;  
    }

    set_sprite_tile(i, tile);
    move_sprite(i, pipe_x, (i * 8) + 16);
}

for (int i = gap_row + 6; i < 18; i++) {
    uint8_t tile;

    if (i == gap_row + 6) {
        tile = 1; 
    } else if(i == 17){
        tile = 3;
    } else {
        tile = 2;  
    }

    set_sprite_tile(i, tile);
    move_sprite(i, pipe_x, (i * 8) + 16);
}
    color(BLACK, WHITE, SOLID); // Set foreground, background, and mode
    SHOW_SPRITES;   
    SHOW_BKG;   
    
    while(1) {
         if(joypad() & J_START){
            gamestate = STATE_PLAYING;
            gotogxy(4,9);
        gprintf("           ");
        }
       
        if((joypad() & J_A) && !buttonheld && gamestate == 1){
            set_sprite_prop(0, S_FLIPY);
            player.gravity = -player.gravity;
            if(player.gravity == -1){

                  set_sprite_prop(0, S_FLIPY);
            }else{
                set_sprite_prop(0, 0);
            }
            buttonheld = true;
        }
        if(!(joypad()& J_A)){
            buttonheld = false;
        }
        if(gamestate == STATE_PLAYING){
        line(0, 8, 159, 8);      // Draw a line
        player.y += (player.speed * player.gravity);
        if(player.y < 24){player.y =24;}
        if(player.y > 152){player.y = 152;}
        if (pipe_x > 8) {
        pipe_x--;
    } else {
        pipe_x = 160;
        gap_row = 9;
    }
        for (int i = 1; i < gap_row; i++) {
            move_sprite(i, pipe_x, (i * 8) + 16);
}

        for (int i = gap_row + 6; i < 18; i++) {
            move_sprite(i, pipe_x, (i * 8) + 16);
}           
        SHOW_SPRITES;
         
        }
        move_sprite(0,player.x,player.y);
        if(gamestate == STATE_PLAYING){
        gotogxy(0,0);
        gprintf("score: %u", (unsigned int)score);
        }else{
        HIDE_SPRITES;
        gotogxy(4,9);
        gprintf("Press Start");
        
        }
        wait_vbl_done();

    }
}