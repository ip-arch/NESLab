#define PLAYER0 0
#define PLAYER1 4
#define PLAYER2 8
#define PLAYER3 12
#define SHOT 16

#define SP_Y 0
#define SP_G 1
#define SP_A 2
#define SP_X 3

#define ENEMY_BG ((unsigned char *)0x200)

unsigned char shot_wait=0;//弾連続発射待ち時間

 
int player_x=40;//自機の横座標
int player_y=200;//自機の縦座標
void waitvblank(void);

//sound
void sound1(unsigned char length,char sweep,unsigned char freq_count){

	unsigned char swe;
	switch(sweep){
		case 0:
			swe=0;
			break;
		case 1:
			swe=-5;
			break;
		case 2:
			swe=5;
			break;
	}
	ch_sq1(length,freq_count,0x0F,0x02,swe);

}

void sound2(unsigned char length,char sweep,unsigned char freq_count){

	unsigned char swe;
	switch(sweep){
		case 0:
			swe=0;
			break;
		case 1:
			swe=-5;
			break;
		case 2:
			swe=5;
			break;
	}
	ch_sq2(length,freq_count,0x0F,0x02,swe);

}

void sound3(unsigned char length,unsigned char pattern,unsigned char volume){

	ch_noise(length,volume,pattern);

}

int bg_address_x(unsigned char x){
	return (x>>3);
}
int bg_address_y(unsigned char y){
	return (y>>3);
}

void set_enemy(unsigned char x,unsigned char y,unsigned char cha_data,unsigned char num){
	if(y<12){
		ENEMY_BG[((y-4)<<5)+x]=num;
		enqueueBG(x,y,cha_data);
	}
}

unsigned char get_enemy(unsigned char x,unsigned char y){
	if(y<12){
		return ENEMY_BG[((y-4)<<5)+x];
	}else{
		return 0xff;
	}
}

void del_enemy(unsigned char x,unsigned char y,unsigned char num){
	set_enemy(x,y,0,0);
	if(num==2){
		set_enemy(x,y-1,0,0);
		set_enemy(x+1,y,0,0);
		set_enemy(x+1,y-1,0,0);
	}else if(num==3){
		set_enemy(x,y-1,0,0);
		set_enemy(x-1,y,0,0);
		set_enemy(x-1,y-1,0,0);
	}else if(num==1){
		set_enemy(x,y+1,0,0);
		set_enemy(x-1,y,0,0);
		set_enemy(x-1,y+1,0,0);
	}else if(num==0){
		set_enemy(x,y+1,0,0);
		set_enemy(x+1,y,0,0);
		set_enemy(x+1,y+1,0,0);
	}
}
	

void init_player(){
	SP_DATA[0]=player_y;
	SP_DATA[1]=player_g[0];
	SP_DATA[2]=player_a[0];
	SP_DATA[3]=player_x;

	SP_DATA[4]=player_y;
	SP_DATA[5]=player_g[1];
	SP_DATA[6]=player_a[1];
	SP_DATA[7]=player_x+8;

	SP_DATA[8]=player_y+8;
	SP_DATA[9]=player_g[2];
	SP_DATA[10]=player_a[2];
	SP_DATA[11]=player_x;

	SP_DATA[12]=player_y+8;
	SP_DATA[13]=player_g[3];
	SP_DATA[14]=player_a[3];
	SP_DATA[15]=player_x+8;
}
void reset_shot(char num){
	SP_DATA[SHOT+num+SP_Y]=248;
	SP_DATA[SHOT+num+SP_X]=0;
}


void move_player(){
	SP_DATA[PLAYER0+SP_Y]=player_y;
	SP_DATA[PLAYER0+SP_X]=player_x;

	SP_DATA[PLAYER1+SP_Y]=player_y;
	SP_DATA[7]=player_x+8;

	SP_DATA[8]=player_y+8;
	SP_DATA[11]=player_x;

	SP_DATA[12]=player_y+8;
	SP_DATA[15]=player_x+8;
}
void move_shot(unsigned char num){
	char i;
	if(shot_wait!=0){
		shot_wait--;
	}
	for(i=0;i<SHOTNUM*4;i+=4){
		if(SP_DATA[SHOT+i]>8&&SP_DATA[SHOT+i]<240){
			SP_DATA[SHOT+i]-=num;
		}else{
			reset_shot(i);
		}
	}
}
	

void set_shot(char num){
	SP_DATA[SHOT+num+SP_Y]=player_y-8;
	SP_DATA[SHOT+num+SP_G]=shot_g;
	SP_DATA[SHOT+num+SP_A]=shot_a;
	SP_DATA[SHOT+num+SP_X]=player_x+4;
}


unsigned char shot(){
	char i;
	if(shot_wait!=0){
		return 0;
	}
	for(i=0;i<SHOTNUM*4;i+=4){
		if(SP_DATA[SHOT+i+SP_Y]==248){
			set_shot(i);
			shot_wait=16;
			return 1;
		}
	}
}


unsigned char judge(char num){
	unsigned char del_x,del_y;
	char gazou;
	unsigned char flag=0;
	if(SP_DATA[SHOT+num+SP_Y]<100){
		//スプライトがいる場所のバックグラウンド座標を取得(x)
		del_x=bg_address_x(SP_DATA[SHOT+num+SP_X]+4);
		//スプライトがいる場所のバックグラウンド座標を取得(y)
		del_y=bg_address_y(SP_DATA[SHOT+num+SP_Y]);
		//スプライトの場所の画像取得する
		//gazou=getBG(del_x,del_y);
		gazou=get_enemy(del_x,del_y);
		if(gazou==1){
			//スプライトの位置を初期化して画面から消す
			reset_shot(num);
			del_enemy(del_x,del_y,0);
			count--;
			disp_count();
			flag=1;
		}else if(gazou==2){
			//スプライトの位置を初期化して画面から消す
			reset_shot(num);
			del_enemy(del_x,del_y,1);
			count--;
			disp_count();
			flag=1;
		}else if(gazou==3){
			//スプライトの位置を初期化して画面から消す
			reset_shot(num);
			del_enemy(del_x,del_y,2);
			count--;
			disp_count();
			flag=1;
		}else if(gazou==4){
			del_enemy(del_x,del_y,3);
			//スプライトの位置を初期化して画面から消す
			reset_shot(num);
			count--;
			disp_count();
			flag=1;
		}
	}
	return flag;
}

unsigned char judge_hit(){
	char i;
	unsigned char flag=0;

	
	for(i=0;i<SHOTNUM*4;i+=4){
		flag|=judge(i);
	}
	
	set_scroll();
	return flag;
}


void init(){
	unsigned char x,y;
	BG_palette[0][3]=enemy_color;
	SP_palette[0][3]=player_color;
	SP_palette[1][3]=shot_color;
	base_color=haikei_color;
	ppu_ctrl=0x00;
	ppu_off();
	palette_change_all();
	clear_BG();
	clear_SP();
	scr_x=0;
	scr_y=0;
	init_player();
	for(x=0;x<SHOTNUM;x++){
		reset_shot(x);
	}

	for(x=0;x<0xFF;x++) ENEMY_BG[x]=0;
	ppu_off();

	for(y=4;y<11;y=y+3){
		for(x=1;x<32;x=x+4){
			set_enemy(x,y,enemy_g[0],1);
			set_enemy(x+1,y,enemy_g[1],2);
			set_enemy(x,y+1,enemy_g[2],3);
			set_enemy(x+1,y+1,enemy_g[3],4);
			count++;
			setBG_queue();
			setBG_queue();
		}
	}
	disp_count();
	setBG_queue();
	setBG_queue();


	set_scroll();
	waitvblank();
	ppu_on();
}


