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
        if(joypad() & J_A){
            player.gravity = -player.gravity;
        }
        player.y += player.gravity;
        move_sprite(0,player.x,player.y);
        wait_vbl_done();

    }
}