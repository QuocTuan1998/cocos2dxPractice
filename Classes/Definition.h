
#ifndef __DEFINITION_H__
#define __DEFINITION_H__


#define WIDTH_SIZE 480 
#define HEIGHT_SIZE 800
#define DEFAULT_INTERVAL 40

#define IMAGE_BACKGROUND_DEFAULT "ui/backgroundMenu.png"
#define IMAGE_BACKGROUND_GAME_PLAY "ui/backgroundGamePlay.png"
#define IMAGE_BACKGROUND_STAR "ui/backgroundStar.png"
#define IMAGE_BACKGROUND_ATTACKED "ui/backgroundAttacked.png"
#define IMAGE_HEALTH_BAR "ui/healthBar.png" 

#define IMAGE_METEOR "meteor/meteor.png"

#define IMAGE_SPACE_SHIP "playerShip/player.png"

#define IMAGE_BULLET_SHIP "laser/laserRed.png"


#define IMAGE_ENEMY_SHIP "enemyShip/enemyShip.png"

#define IMAGE_BULLET_ENEMY "laser/laserGreen.png"

#define IMAGE_HEALTH "item/health.png"
#define IMAGE_SHEILD "item/shield.png"


#define PADDING_MENU_ITEM 100

#define TIME_SPLASH 1.5
#define TIME_TRASITION 0.5
#define TIME_SCROLL_BACKGROUND 2.5
#define TIME_DELAY_SHIP_ATTACKED 0.3
#define PLAYER_SHIP_DURATION 1

#define HEALTH_PLAYER_SHIP 100


#define NUM_OF_BULLET_SHIP 100
#define NUM_OF_BULLET_ENEMY 5
#define NUM_OF_METEOR 30
#define NUM_OF_ENEMY 15


#define METEOR_ROTATE_MIN 90
#define METEOR_ROTATE_MAX 180
#define METEOR_ROTATE_DURATION_MIN 1
#define METEOR_ROTATE_DURATION_MAX 3
#define METEOR_SCALE_MIN 0.2
#define METEOR_SCALE_MAX 0.8
#define METEOR_SPEED_X_MIN 2
#define METEOR_SPEED_X_MAX 5
#define METEOR_SPEED_Y_MIN 6
#define METEOR_SPEED_Y_MAX 15

#define ENEMY_SPEED_MIN 3
#define ENEMY_SPEED_MAX 5
#define ENEMY_SCALE_MIN 0.3
#define ENEMY_SCALE_MAX 1.0
#define ENEMY_HEALTH_MAX 7
#define ENEMY_MOVE_DURATION_MIN 3
#define ENEMY_MOVE_DURATION_MAX 6

#define NUM_OF_BULLET_FRAME_SHIP 5
#define NUM_OF_BULLET_FRAME_ENEMY 30

#define NUM_OF_METEOR_FRAME 20
#define NUM_OF_ENEMY_FRAME 30

#define BULLET_SHIP_SPEED 50
#define BULLET_ENEMY_SPEED_MIN 5
#define BULLET_ENEMY_SPEED_MAX 10
#define METEOR_SPEED 5

#define BULLET_SHIP 1
#define BULLET_ENEMY 2

#define ENEMY_EXPLOSION_PLIST "animation/explosions.plist"
#define METEOR_EXPLOSION_PLIST "animation/meteors.plist"

#define NUM_OF_ANIMATION_FRAME_ENEMY 19
#define NUM_OF_ANIMATION_FRAME_METEOR 2

#define SOUND_BULLET_SHIP "sound/playerBullet.mp3"
#define SOUND_ENEMY_EXPLOSION "sound/enemyExplosion.mp3"
#endif // __DEFINITION_H__
