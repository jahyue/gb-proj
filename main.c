#include <stdio.h>
#include <gb/gb.h>
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
uint8_t buttonheld = 0;
void main(void) {
    player.x = 40;
    player.y = 70;
    player.speed = 2;
    player.gravity = 1;
    set_sprite_data(0,1,player_sprite);
    set_sprite_tile(0,0);
    SHOW_SPRITES;
    SHOW_BKG;
    while(1) {
        if((joypad() & J_A) && !buttonheld){
            player.gravity = -player.gravity;
            buttonheld = 1;
        }
        if(!(joypad()& J_A)){
            buttonheld = 0;
        }
        player.y += (player.speed * player.gravity);
        if(player.y < 17){player.y =17;}
        if(player.y > 150){player.y =150;}
        move_sprite(0,player.x,player.y);
        wait_vbl_done();

    }
}