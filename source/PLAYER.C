/*////////////////////////////////////////////////////////////////////////////*/

typedef struct _PLAYER_
{
    U8 sprite_slot; // The starting sprite slot in OAM for the meta-sprite data.
    U8 sprite_num;  // The number of sprites that make up the meta-sprite.
    U8 x, y;        // Current (X,Y) position in the world.

} PLAYER;

GLOBAL PLAYER player;

INTERNAL void player_update ()
{
    // ...
}

INTERNAL void player_init ()
{
    player.sprite_slot = 0x00;
    player.sprite_num  = 0x04;

    // @Temporary

    for (i=0; i<player.sprite_num; ++i) {
        set_sprite_tile(player.sprite_slot+i, i+1);
    }

    player.x = 48 + (TILE_WIDTH     );
    player.y = 48 + (TILE_HEIGHT * 2);

    move_sprite(player.sprite_slot+0, player.x,            player.y            );
    move_sprite(player.sprite_slot+1, player.x+TILE_WIDTH, player.y            );
    move_sprite(player.sprite_slot+2, player.x,            player.y+TILE_HEIGHT);
    move_sprite(player.sprite_slot+3, player.x+TILE_WIDTH, player.y+TILE_HEIGHT);
}

/*////////////////////////////////////////////////////////////////////////////*/
