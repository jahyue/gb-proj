#include <stdint.h>
#include <stdbool.h>
#include <gb/gb.h>
#include <gbdk/console.h>
#include <gb/drawing.h>
unsigned char player_sprite[] =
{
    0xFF,0xFF,0x81,0x81,0x81,0x81,0xA5,0xA5,0x81,0x81,0x99,0x99,0x81,0x81,0xFF,0xFF,
};
unsigned char PipeSetTiles[] =
{
    0xFF,0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
    0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
    0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0xFF,0xFF,
};

unsigned char PipeSetMap[] =
{
    0x00,
    0x01,
    0x02,
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
    bool buttonheld = false;
    uint16_t gamestate = 0;
    player.x = 40;
    player.y = 70;
    player.speed = 1;
    player.gravity = 1;
    set_sprite_data(0,1,player_sprite);
    set_sprite_tile(0,0);
    color(BLACK, WHITE, SOLID); // Set foreground, background, and mode
    
    SHOW_SPRITES;
    SHOW_BKG;
    
    while(1) {
         if(joypad() & J_START){
            gamestate = 1;
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
        if(gamestate ==1){
        line(0, 8, 159, 8);      // Draw a line
        player.y += (player.speed * player.gravity);
        if(player.y < 24){player.y =24;}
        if(player.y > 152){player.y = 152;}
        SHOW_SPRITES;
        }
        move_sprite(0,player.x,player.y);
        score++;
        if(gamestate == 1){
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