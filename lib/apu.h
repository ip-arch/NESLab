unsigned char calc_length(unsigned char time){
	switch(time){
		case 1:
			return 0x90;
		case 2:
			return 0xA0;
		case 3:
			return 0xD0;
		case 4:
			return 0xB0;
		case 5:
			return 0xC0;
		default:
			return 0x00;
	}
}
void stop_sq1(){
	*(APU_CHANNEL)&=0xFE;
}
void stop_noise(){
	*(APU_CHANNEL)&=0xF7;
}

void ch_sq1(unsigned char length,unsigned char freq,unsigned char volume,unsigned char duty,char sweep){

	
	*(APU_CHANNEL)|=0x01;
	if(length==0) *(APU_SQU1)=(duty<<6)|(volume&0x0f)|0x30;
	else *(APU_SQU1)=(duty<<6)|(volume&0x0f)|0x10;

	if(sweep&0x80){
		*(APU_SQU1+1)=0xD0|(-sweep)&0x07;
	}else if(sweep>0){
		*(APU_SQU1+1)=0xD8|sweep&0x07;
	}else{
		*(APU_SQU1+1)=0x00;
	}
	*(APU_SQU1+2)=freq;
	*(APU_SQU1+3)=calc_length(length);
}

void ch_sq2(unsigned char length,unsigned char freq,unsigned char volume,unsigned char duty,char sweep){

	
	*(APU_CHANNEL)|=0x02;
	if(length==0) *(APU_SQU2)=(duty<<6)|(volume&0x0f)|0x30;
	else *(APU_SQU2)=(duty<<6)|(volume&0x0f)|0x10;

	if(sweep&0x80){
		*(APU_SQU2+1)=0xD0|(-sweep)&0x07;
	}else if(sweep>0){
		*(APU_SQU2+1)=0xD8|sweep&0x07;
	}else{
		*(APU_SQU2+1)=0x00;
	}
	*(APU_SQU2+2)=freq;
	*(APU_SQU2+3)=calc_length(length);
}

void ch_noise(unsigned char length,unsigned char volume,unsigned char pattern){

	*(APU_CHANNEL)|=0x08;
	if(length==0) *(APU_NOISE)=(volume&0x0f)|0x30;
	else *(APU_NOISE)=(volume&0x0f)|0x10;

	*(APU_NOISE+2)=pattern&0x0F;
	*(APU_NOISE+3)=calc_length(length);
}

