#ifndef _TROOPER_CONSTANTS_
#define _TROOPER_CONSTANTS_

//
// Living Entities
//
#define ENTITY_ANIMATION_IDLE  0
#define ENTITY_ANIMATION_RUNNING  1
#define ENTITY_ANIMATION_ATTACK  2

#define ENTITY_ANIMATION_DELAY 100

#define ENTITY_FACING_SOUTH 1
#define ENTITY_FACING_NORTH -1
#define ENTITY_FACING_EAST 2
#define ENTITY_FACING_WEST -2


//
// Trooper
//

#define TROOPER_SPRITE_SIZE_SMALL 24
#define TROOPER_BODY_SPRITE_SIZE_HALF 24
#define TROOPER_BODY_SPRITE_SIZE 48

#define TROOPER_ANIMATION_DELAY 99

//
// Animation Effects
//

#define ANIMATION_DELAY_NORMAL 99
#define ANIMATION_DELAY_QUICK 33

#define ANIMATION_EFFECT_BLEEDING 1
#define ANIMATION_EFFECT_STOP_BLEEDING -1
#define ANIMATION_EFFECT_MUZZLE_FLASH 2
#define ANIMATION_EFFECT_STOP_MUZZLE_FLASH -2

//
// Projectiles
//

#define BULLET_SPRITESHEET_NUMBER_OF_COLUMNS 1
#define BULLET_SPRITE_HEIGHT 16
#define BULLET_SPRITE_WIDTH 48

#endif