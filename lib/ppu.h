void waitvblank(void);
unsigned char scr_x;
unsigned char scr_y;
unsigned char ppu_ctrl=0x00;
char bg_fifo_num=0;
unsigned char BG_palette[4][4]={
	{0x0f,0x0f,0x0f,0x30},
	{0x0f,0x0f,0x0f,0x0f},
	{0x0f,0x0f,0x0f,0x0f},
	{0x0f,0x0f,0x0f,0x0f}};
unsigned char SP_palette[4][4]={
	{0x0f,0x0f,0x0f,0x30},
	{0x0f,0x0f,0x0f,0x13},
	{0x0f,0x0f,0x0f,0x24},
	{0x0f,0x0f,0x0f,0x36}};
unsigned char base_color=0x0f;

void ppu_on(){
	*(PPU+1)=0x1e;
	*(PPU)=ppu_ctrl;
}
void ppu_off(){
	*(PPU+1)=0x00;
}
void set_scroll(){
	*(PPU+5)=scr_x;
	*(PPU+5)=scr_y;
}
int xy_to_addr(unsigned char x,unsigned char y){
	return 0x2000+((x&0x20)<<5)+(x&0x1F)+((y&0x1F)<<5);
}


void clear_queue(){
	unsigned char i;
	for(i=0;i<0xFF;i++) *(BG_FIFO+i)=0;
}
void enqueueBG(unsigned char x,unsigned char y,unsigned char chr_no){
	int ad;
	if(bg_fifo_num<120){
		ad=0x2000+((x&0x20)<<5)+(x&0x1F)+((y&0x1F)<<5);
		*(BG_FIFO+bg_fifo_num)=(unsigned char)(ad>>8);
		*(BG_FIFO+bg_fifo_num+1)=(unsigned char)(ad&0xFF);
		*(BG_FIFO+bg_fifo_num+2)=chr_no;
		bg_fifo_num+=3;
	}
}
unsigned char setBG_queue(){
	unsigned char limit=0;
	while(bg_fifo_num>0){
		bg_fifo_num-=3;
		*(PPU+6)=*(BG_FIFO+bg_fifo_num);
		*(PPU+6)=*(BG_FIFO+bg_fifo_num+1);
		*(PPU+7)=*(BG_FIFO+bg_fifo_num+2);
		limit++;
		if(limit==2) return 1;
	}
	return 0;
}


void setBG(unsigned char x,unsigned char y,unsigned char chr_no){
	int ad;
	//ad=xy_to_addr(x,y);
	ad=0x2000+((x&0x20)<<5)+(x&0x1F)+((y&0x1F)<<5);
	*(PPU+6)=(char)(ad>>8);
	*(PPU+6)=(char)(ad&0xFF);
	*(PPU+7)=chr_no;
	//set_scroll();
}


unsigned char getBG(unsigned char x,unsigned char y){
	int ad;
	char tmp;
	ad=0x2000+((x&0x20)<<5)+(x&0x1F)+((y&0x1F)<<5);
	*(PPU+6)=(char)(ad>>8);
	*(PPU+6)=(char)(ad&0xFF);
	set_scroll();
	tmp=*(PPU+7);
	return *(PPU+7);
}

void update_sprite(unsigned char num){
	unsigned char tmp;
	tmp=num<<2;
	*(PPU+3)=tmp;
	*(PPU+4)=SP_DATA[0+tmp];
	*(PPU+4)=SP_DATA[1+tmp];
	*(PPU+4)=SP_DATA[2+tmp];
	*(PPU+4)=SP_DATA[3+tmp];
}
void update_sprite_all(){
	*(DMA)=SP_ADDR;
}

void palette_change_all(){
	unsigned char i,j;
	*(PPU+6)=0x3f;
	*(PPU+6)=0x00;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			*(PPU+7)=BG_palette[i][j];
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			*(PPU+7)=SP_palette[i][j];
	*(PPU+6)=0x3f;
	*(PPU+6)=0x10;
	*(PPU+7)=base_color;
	set_scroll();
}
void palette_change_BG(unsigned char num){
	unsigned char i;
	*(PPU+6)=0x3f;
	*(PPU+6)=num<<2;
	for(i=0;i<4;i++)
		*(PPU+7)=BG_palette[num][i];
	set_scroll();
}
void palette_change_SP(unsigned char num){
	unsigned char i;
	*(PPU+6)=0x3f;
	*(PPU+6)=(num<<2)+0x11;
	for(i=0;i<4;i++)
		*(PPU+7)=BG_palette[num][i];
	set_scroll();
}
void clear_BG(){
	int i;
	waitvblank();
	ppu_off();
	clear_queue();
	*(PPU+6)=0x20;
	*(PPU+6)=0x00;
	for(i=0;i<0x1000;i++){
		*(PPU+7)=0;
	}
	waitvblank();
	ppu_on();
}
void clear_SP(){
	int i;
	for(i=0;i<0x100;i++){
		SP_DATA[i]=0;
	}
	waitvblank();
	ppu_off();
	update_sprite_all();
	ppu_on();
}
