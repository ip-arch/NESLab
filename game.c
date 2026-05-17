#include "map.h"

#include "pad.h"
#include "ppu.h"
#include "apu.h"

#define SHOTNUM 5


unsigned char player_g[]={0x9E,0x9E,0x19,0x19};
unsigned char player_a[]={0x00,0x40,0x80,0x80};
unsigned char player_color=0x36;


unsigned char shot_g=0x02;//'上矢印'
unsigned char shot_a=0x01;//反転なし
unsigned char shot_color=0x39;

unsigned char enemy_g[]={0x80,0x80,0x80,0x80};
unsigned char enemy_color=0x34;

unsigned char haikei_color=0x0f;


char count=0;

void disp_count(){
	char d1,d0;
	d0=count%10;
	d1=(count/10)%10;
	enqueueBG(26,2,'0'+d1);
	enqueueBG(27,2,'0'+d0);
}

#include "game.h"

int main(){
	unsigned char prev_a=0;
	unsigned char scr_offset=128;

	init();

	player_x=40;  //自機の横座標
	player_y=200; //自機の縦座標


	enqueueBG(20,2,'E');
	enqueueBG(21,2,'N');
	enqueueBG(22,2,'E');
	enqueueBG(23,2,'M');
	enqueueBG(24,2,'Y');
	enqueueBG(25,2,':');
	

	while(1){
		waitvblank();
		ppu_off();
		update_sprite_all();
		setBG_queue();
		set_scroll();
		ppu_on();

		if(judge_hit()){
		//---------------敵に弾があたった時----------------//
			sound3(1,4,15);

		}

		//---------------画面の敵が全ていなくなった時----------------//
		if(count==0){
			sound2(5,1,0x34);
			break; //ゲームを終わる
		}


		fetch_keys();

		//---------------上ボタンが押された時----------------//
		if(keys[BT_UP]==1){
			//player_y-=1;
		}
		
		//---------------下ボタンが押された時----------------//
		if(keys[BT_DOWN]==1){
			//player_y+=1;
		}
		
		//---------------左ボタンが押された時----------------//
		if(keys[BT_LEFT]==1){
			player_x-=1;
		}
		
		//---------------右ボタンが押された時----------------//
		if(keys[BT_RIGHT]==1){
			player_x+=1;
		}
		
		//----------------Aボタンが押された時----------------//
		if(keys[BT_A]==1){

			//----------------弾を発射する----------------//
			if(shot()){
				sound1(1,2,0x7e);
			}
		}

		//----------------STARTボタンが押された時----------------//
		if(keys[BT_START]==1){

		}


		move_shot(1);
		move_player();
	}
	

	
	//----------------画面を元に戻す---------------//
	ppu_off();
	clear_BG();
	clear_SP();

	//----------------メッセージを表示---------------//
	enqueueBG(15,15,'E');
	enqueueBG(16,15,'N');
	enqueueBG(17,15,'D');

	waitvblank();
	setBG_queue();
	setBG_queue();
	set_scroll();
	ppu_on();


	while(1){
		waitvblank();
		fetch_keys();

		//----------------STARTボタンが押された時----------------//
		if(keys[BT_START]==1){
			return 0; //始めに戻る
		}
	}
	
	return 0;
}

