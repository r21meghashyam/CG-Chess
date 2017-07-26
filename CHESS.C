#include<graphics.h>
#include<math.h>
int	startx,
	midx,
	endx,
	starty,
	midy,
	endy,
	blocksize,
	pointcol,
	pointrow,
	turn,
	movemode,
	paths[21];

typedef struct {
	char type;
	int color;
	int haspawn;
	}pawn;
pawn map[8][8];

int row(int value){
   return starty + value*blocksize;
}
int col(int value){
	return startx + value*blocksize;
}
int center(int value){
	return value + blocksize/2;
}

void setblock(int r,int c,char t,int col){
	map[r][c].type=t;
	map[r][c].color=col;
	map[r][c].haspawn=1;

}
void clearblock(int r,int c, pawn p){
	int color;
	color = r%2==c%2?WHITE:BLACK;
	setfillstyle(SOLID_FILL,color);
	bar(col(c),row(r),col(c)+blocksize,row(r)+blocksize);
	p.type='N';
	p.haspawn=0;

}
void init(){
	int	graphdevice,
		graphmode,
		side,
		i,j,
		rowno,
		player[2];
	graphdevice = DETECT;
	initgraph(&graphdevice,&graphmode,"");

	endx = midx = getmaxx()+1;
	endy = midy = getmaxy()+1;

	if(midx>midy){
		startx = (midx-midy)/2;
		endx = startx+midy;
		blocksize = midy/8;
	}
	else{
		starty = (midy-midx)/2;
		endy = starty+midx;
		blocksize = midx/9;
	}

	player[0]=WHITE;
	player[1]=player[0]==WHITE?BLACK:WHITE;
	turn = WHITE;
	movemode=0;
	for(side=0;side<2;side++){
		//solilders
		for(i=0;i<8;i++){
			rowno= side==0?1:6;
			setblock(rowno,i,'S',player[side]);
		}
		rowno = side==0?0:7;  //0 1 2 (3 4) 5 6 7
		for(i=0;i<2;i++){     //
			 //bishop
			 setblock(rowno,i==0?7-2:2,'B',player[side]);
			//knight
			 setblock(rowno,i==0?7-1:1,'H',player[side]);
			 //Elephant
			 setblock(rowno,i==0?7-0:0,'E',player[side]);

		}

	}
	if(player[1]==BLACK){
		setblock(0,3,'Q',WHITE);
		setblock(0,4,'K',WHITE);
		setblock(7,3,'Q',BLACK);
		setblock(7,4,'K',BLACK);
	}
	else{
		setblock(0,3,'K',BLACK);
		setblock(0,4,'Q',BLACK);
		setblock(7,3,'K',WHITE);
		setblock(7,4,'Q',WHITE);

	}

}

void drawboard(){
	int i,j;
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	//draw vertical lines
	for(i=startx;i<=endx;i+=blocksize)
		line(i,starty,i,endy);
	//draw horizontal lines
	for(i=starty;i<=endy;i+=blocksize)
		line(startx,i,endx,i);
	//fill colors
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(i%2==j%2)
				floodfill(center(col(i)),center(row(j)),WHITE);
}
void drawpawn(int r,int c,pawn p){
	int i,j,bordercolor,x,y;
	bordercolor=p.color==WHITE?DARKGRAY:LIGHTGRAY;
	setcolor(bordercolor);
	setfillstyle(SOLID_FILL,p.color);
	x=center(col(c));
	y=center(row(r));

	switch(p.type){
	case 'K':
		rectangle(x-2,y-27,x+2,y-20);
		rectangle(x-8,y-24,x+8,y-22);
	case 'Q':
		rectangle(x-12,y-20,x+12,y-15);
		floodfill(x,y-17,bordercolor);
		rectangle(x-5,y-15,x+5,y+10);
		floodfill(x,y,bordercolor);
		rectangle(x-10,y+10,x+10,y+15);
		floodfill(x,y+12,bordercolor);
		for(i=x-12;i<x+12;i+=6)
			for(j=i;j<i+3;j++)
				line(j,y-20,j,y-17);

		break;
	case 'E':
		rectangle(x-15,y-15,x+15,y-10);
		floodfill(x-14,y-14,bordercolor);
		rectangle(x-10,y-10,x+10,y+10);
		floodfill(x+5,y+5,bordercolor);
		rectangle(x-15,y+10,x+15,y+15);
		floodfill(x-14,y+11,bordercolor);
		for(i=x-15;i<x+15;i+=2)
			line(i,y-15,i,y-13);
		break;
	case 'H':
		rectangle(x+5,y-25,x+10,y-20);
		floodfill(x+7,y-22,bordercolor);
		rectangle(x-20,y-20,x+10,y-5);
		floodfill(x-19,y-14,bordercolor);
		rectangle(x-10,y-5,x+10,y+10);
		floodfill(x+5,y+5,bordercolor);
		rectangle(x-15,y+10,x+15,y+15);
		floodfill(x-14,y+11,bordercolor);
		break;
	case 'S':
		rectangle(x-10,y-15,x+10,y-10);
		floodfill(x,y-12,bordercolor);
		rectangle(x-5,y-10,x+5,y+10);
		floodfill(x,y,bordercolor);
		rectangle(x-10,y+10,x+10,y+15);
		floodfill(x,y+12,bordercolor);
		for(i=x-10;i<x+10;i+=2)
			line(i,y-15,i,y-13);
		break;
	case 'B':
		arc(x,y-15,350,190,10);
		rectangle(x-10,y-15,x+10,y-10);
		floodfill(x,y-12,bordercolor);
		floodfill(x,y-24,bordercolor);
		rectangle(x-5,y-10,x+5,y+10);
		floodfill(x,y,bordercolor);
		rectangle(x-10,y+10,x+10,y+15);
		floodfill(x,y+12,bordercolor);
		for(i=x-10;i<x+10;i+=2)
			line(i,y-15,i,y-13);
		break;

	}


}
void selector(r,c){
	int pr,pc;
	pr=pointrow;
	pc=pointcol;
	switch(map[pr][pc].type){
		case 'S':
		case 'K':
		case 'Q':
		case 'E':
		case 'H':
		case 'B':
		case 'X':clearblock(pr,pc,map[pr][pc]);break;
	}
	switch(map[pr][pc].type){
		case 'S':
		case 'K':
		case 'Q':
		case 'E':
		case 'H':
		case 'B':drawpawn(pr,pc,map[pr][pc]);
	}
	if(c==8)c=0;
	else if(c==-1)c=7;
	if(r==8)r=0;
	else if(r==-1)r=7;
	pointcol=pc=c;
	pointrow=pr=r;
	setfillstyle(SOLID_FILL,4);
	bar(col(pointcol),row(pointrow),col(pointcol)+blocksize,row(pointrow)+blocksize);
	switch(map[pr][pc].type){
		case 'S':
		case 'K':
		case 'Q':
		case 'E':
		case 'H':
		case 'B':drawpawn(pr,pc,map[pr][pc]);break;
		default: map[pr][pc].type='X';
	}
}
void render(){
	int i,j;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(map[i][j].haspawn==1)
				drawpawn(i,j,map[i][j]);
			else if(map[i][j].haspawn!=1 && map[i][j].type!='N')
				clearblock(i,j,map[i][j]);

	selector(pointrow,pointcol);
	/*
	for(i=0;i<8;i++)   {
		for(j=0;j<8;j++)
			printf("%d%d%c%d ",i,j,map[i][j].type,map[i][j].color);
		printf("\n");
	} */

}
void colorblock(int i, int j){
	clearblock(i,j,map[i][j]);

	drawpawn(i,j,map[i][j]);
}
void select(){
	if(turn=map[pointrow][pointcol].color){

	}
}
void main(){
	int ch,i,j;
	init();
	pointcol=4;
	pointrow=4;
	drawboard();
	render();

	while(1){
		if(kbhit()){
			ch = getch();
			switch(ch){
			case 13:select();break;
			case 27:cleardevice();
				exit(0);
			case 77: selector(pointrow,pointcol+1);break;
			case 75: selector(pointrow,pointcol-1);break;
			case 72: selector(pointrow-1,pointcol);break;
			case 80: selector(pointrow+1,pointcol);break;
			}


			render();
		}
	}


}