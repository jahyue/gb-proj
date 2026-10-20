#include <stdint.h>
#include <stdbool.h>
#include <gb/gb.h>
#include <gbdk/console.h>
#include <gb/drawing.h>
const unsigned char player_sprite[] = {
    0x3C,0x3C,0x42,0x42,0x85,0x85,0x81,0x81,
    0xA5,0xA5,0x81,0x81,0x42,0x42,0x3C,0x3C
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
    line(0, 10, 159, 10);      // Draw a line
    SHOW_SPRITES;
    SHOW_BKG;
    
    while(1) {
         if(joypad() & J_START){
            gamestate = 1;
            gotogxy(4,9);
        gprintf("           ");
        }
       
        if((joypad() & J_A) && !buttonheld && gamestate == 1){
            player.gravity = -player.gravity;
            buttonheld = true;
        }
        if(!(joypad()& J_A)){
            buttonheld = false;
        }
        if(gamestate ==1){
        player.y += (player.speed * player.gravity);
        if(player.y < 27){player.y =27;}
        if(player.y > 154){player.y =154;}
        
        }
        move_sprite(0,player.x,player.y);
        score++;
        if(gamestate == 1){
        gotogxy(0,0);
        gprintf("score: %u", (unsigned int)score);
        }else{
        gotogxy(4,9);
        gprintf("Press Start");
        
        }
        wait_vbl_done();

    }
}