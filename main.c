#include <stdio.h>
#include <gb/gb.h>
const unsigned char player_sprite[] = {
    0x00, 0x00, 0x3C, 0x42, 0x81, 0xA5, 0x81, 0x42,
    0x3C
};
struct GamePlayer {
    uint8_t x;
    uint8_t y;
    int8_t speed;
};
struct GamePlayer player;
void main(void) {
    player.x = 40;
    player.y = 70;
    player.speed = 2;
    set_sprite_data(0,1,player_sprite);
    set_sprite_tile(0,0);
    SHOW_SPRITES;
    SHOW_BKG;
    while(1) {
        
        // Main game loop
        if (joypad() & J_RIGHT){
            player.x +=1;
        }
        if(joypad()& J_LEFT){
            player.x -=1;
        }
        move_sprite(0,player.x,player.y);
        wait_vbl_done();

    }
}