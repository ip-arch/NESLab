
#define BT_A 0
#define BT_B 1
#define BT_SELECT 2
#define BT_START 3
#define BT_UP 4
#define BT_DOWN  5
#define BT_LEFT 6
#define BT_RIGHT 7

int score=0;

char keys[8];

unsigned char input_key(char sel){
	unsigned char key;
	char i;
	key=0;
	if(!sel){
		*(PAD1)=0x01;
		*(PAD1)=0x00;
		for(i=0;i<8;i++){
			key=key<<1;
			key+=*(PAD1);
		}
	}else{
		*(PAD2)=0x01;
		*(PAD2)=0x00;
		for(i=0;i<8;i++)
			key=(key<<1)+(*(PAD2)&0x01);
	}
	return key;
}

void fetch_keys(){
	char i;
	*PAD1=1;
	*PAD1=0;
	for(i=0;i<8;i++){
		keys[i]=*PAD1&0x01;
	}
	return;
}
