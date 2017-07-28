#include<graphics.h>
#include<math.h>
#include<string.h>
int	startx,
	midx,
	endx,
	starty,
	midy,
	endy,
	cellsize,
	pc,
	pr,
	turn,
	cpr,
	cpc,
	pawnup,
	player[2],
	paths[21];

typedef struct {
	char pawn;
	int pawncolor;
	int cellcolor;
	}cell;
cell map[8][8];

int row(int value){
   return starty + value*cellsize;
}
int col(int value){
	return startx + value*cellsize;
}
int center(int value){
	return value + cellsize/2;
}

void setcell(int r,int c,char p,int col){
	map[r][c].pawn=p;
	map[r][c].pawncolor=col;
}
void clearcell(int r,int c){
	int color;
	color = r%2==c%2?WHITE:BLACK;
	setfillstyle(SOLID_FILL,color);
	bar(col(c),row(r),col(c)+cellsize,row(r)+cellsize);
	map[r][c].pawn='N';
	map[r][c].pawncolor=-1;
	map[r][c].cellcolor=color;
	//printf("clearcell={%d,%d,%d}",r,c,map[r][c].pawncolor);
}
void init(){
	int	graphdevice,
		graphmode,
		side,
		i,j,
		rowno;
	graphdevice = DETECT;
	pawnup=0;
	initgraph(&graphdevice,&graphmode,"");

	endx = midx = getmaxx()+1;
	endy = midy = getmaxy()+1;

	if(midx>midy){
		startx = (midx-midy)/2;
		endx = startx+midy;
		cellsize = midy/8;
	}
	else{
		starty = (midy-midx)/2;
		endy = starty+midx;
		cellsize = midx/9;
	}

	player[0]=WHITE;
	player[1]=player[0]==WHITE?BLACK:WHITE;
	turn = WHITE;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++){
			map[i][j].pawn='N';
			map[i][j].pawncolor=-1;

		}
	for(side=0;side<2;side++){
		//solilders
		for(i=0;i<8;i++){
			rowno= side==0?1:6;
			setcell(rowno,i,'S',player[side]);
		}
		rowno = side==0?0:7;  //0 1 2 (3 4) 5 6 7
		for(i=0;i<2;i++){     //
			 //bishop
			 setcell(rowno,i==0?7-2:2,'B',player[side]);
			//knight
			 setcell(rowno,i==0?7-1:1,'H',player[side]);
			 //Elephant
			 setcell(rowno,i==0?7-0:0,'E',player[side]);

		}
	outtextxy(0,10,"WHITE");
	outtextxy(endx+10,10,"BLACK");
	}
	if(player[1]==BLACK){
		setcell(0,3,'Q',WHITE);
		setcell(0,4,'K',WHITE);
		setcell(7,3,'Q',BLACK);
		setcell(7,4,'K',BLACK);
	}
	else{
		setcell(0,3,'K',BLACK);
		setcell(0,4,'Q',BLACK);
		setcell(7,3,'K',WHITE);
		setcell(7,4,'Q',WHITE);

	}

}

void drawboard(){
	int i,j;
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	//draw vertical lines
	for(i=startx;i<=endx;i+=cellsize)
		line(i,starty,i,endy);
	//draw horizontal lines
	for(i=starty;i<=endy;i+=cellsize)
		line(startx,i,endx,i);
	//fill colors
	for(i=0;i<8;i++)
		for(j=0;j<8;j++){
			map[i][j].cellcolor=BLACK;
			if(i%2==j%2){
				floodfill(center(col(i)),center(row(j)),WHITE);
				map[i][j].cellcolor=WHITE;
			}
		}

}

void drawcell(int r,int c){
	int i,j,bordercolor,x,y;
	bordercolor=map[r][c].pawncolor==WHITE?DARKGRAY:LIGHTGRAY;
	setcolor(bordercolor);
	setfillstyle(SOLID_FILL,map[r][c].pawncolor);
	x=center(col(c));
	y=center(row(r));

	switch(map[r][c].pawn){
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
void colorcell(int r,int c, int clr){
	setcolor(0);
	setfillstyle(SOLID_FILL,clr);
	bar(col(c),row(r),col(c)+cellsize,row(r)+cellsize);
	rectangle(col(c),row(r),col(c)+cellsize,row(r)+cellsize);
	if(clr!=4)
		map[r][c].cellcolor=clr;

}
int getbc(int r,int c){
	return r%2==c%2?WHITE:BLACK;
}
void selector(int r,int c){
	colorcell(pr,pc,map[pr][pc].cellcolor);
	drawcell(pr,pc);
	if(c==8)c=0;
	else if(c==-1)c=7;
	if(r==8)r=0;
	else if(r==-1)r=7;
	pc=c;
	pr=r;
	colorcell(pr,pc,4);
	drawcell(pr,pc);
}
void render(){
	int i,j;
	char str[100],ch[1];
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)            {
			if(map[i][j].pawn!='N')
				drawcell(i,j);
			//else if(map[i][j].haspawn!=1 && map[i][j].type!='N')
			  //	clearblock(i,j,map[i][j]);

			/*itoa(i,str,36);
			strcat(str,",");
			itoa(j,ch,36);
			strcat(str,ch);
			outtextxy(col(i)+10,row(j)+blocksize/2,str);
			  */		     }
	selector(pr,pc);

	/*for(i=0;i<8;i++)   {
		for(j=0;j<8;j++)
			printf("%d%d%c%d ",i,j,map[i][j].pawn,map[i][j].pawncolor);
		printf("\n");
	}                    */

}

void knight(int r,int c){
	if(map[r][c].pawncolor!=turn&&r>=0&&c>=0&&r<8&&c<8)
		colorcell(r,c,3);
}
void select(){
	cell p;
	int i,j,op;
	if(pawnup==0){

		if(turn==map[pr][pc].pawncolor){

			p=map[pr][pc];
			colorcell(pr,pc,12);
			cpr=pr;
			cpc=pc;
			op=turn==0?15:0;
			switch(p.pawn){


				case 'Q':
					for(i=pr+1,j=pc+1;i<8&&j<8;i++,j++)
						if(map[i][j].pawncolor==turn)
							break;
						else if(map[i][j].pawncolor==op){
							colorcell(i,j,3);
							break;
						}
						else
							colorcell(i,j,3);
					for(i=pr+1,j=pc-1;i<8&&j>=0;i++,j--)
						if(map[i][j].pawncolor==turn)
							break;
						else if(map[i][j].pawncolor==op){
							colorcell(i,j,3);
							break;
						}
						else
							colorcell(i,j,3);
				case 'E':

					for(i=pr+1;i<8;i++)
						if(map[i][pc].pawncolor==turn){
							break;
							}
						else if(map[i][pc].pawncolor==op){
							colorcell(i,pc,3);
							break;
						}
						else
							colorcell(i,pc,3);

					for(i=pr-1;i>=0;i--)
						if(map[i][pc].pawncolor==turn)
							break;
						else if(map[i][pc].pawncolor==op){
							colorcell(i,pc,3);
							break;
						}
						else
							colorcell(i,pc,3);
					for(i=pc+1;i<8;i++)
						if(map[pr][i].pawncolor==turn)
							break;
						else if(map[pr][i].pawncolor==op){
							colorcell(pr,i,3);
							break;
						}
						else
							colorcell(pr,i,3);
					for(i=pc-1;i>=0;i--)
						if(map[pr][i].pawncolor==turn)
							break;
						else if(map[pr][i].pawncolor==op){
							colorcell(pr,i,3);
							break;
						}
						else
							colorcell(pr,i,3);
					break;

				case 'S':
					if(player[0]==turn){
						if(pr==1)
							colorcell(pr+2,pc,3);
						if(map[pr+1][pc].pawn=='N')
							colorcell(pr+1,pc,3);
						if(map[pr+1][pc+1].pawncolor==op)
							colorcell(pr+1,pc+1,3);
						if(map[pr+1][pc-1].pawncolor==op)
							colorcell(pr+1,pc-1,3);
					}
					else{
						if(pr==6)
							colorcell(pr-2,pc,3);
						if(map[pr-1][pc].pawn=='N')
							colorcell(pr-1,pc,3);
						if(map[pr-1][pc-1].pawncolor==op)
							colorcell(pr-1,pc-1,3);
						if(map[pr-1][pc+1].pawncolor==op)
							colorcell(pr-1,pc+1,3);
					}


					break;
				case 'B':for(i=pr+1,j=pc+1;i<8&&j<8;i++,j++)
						if(map[i][j].pawncolor==turn)
							break;
						else if(map[i][j].pawncolor==op){
							colorcell(i,j,3);
							break;
						}
						else
							colorcell(i,j,3);
					for(i=pr+1,j=pc-1;i<8&&j>=0;i++,j--)
						if(map[i][j].pawncolor==turn)
							break;
						else if(map[i][j].pawncolor==op){
							colorcell(i,j,3);
							break;
						}else
							colorcell(i,j,3);
					break;
				case 'H':
					knight(pr-2,pc-1);
					knight(pr-2,pc+1);
					knight(pr-1,pc-2);
					knight(pr-1,pc+2);
					knight(pr+1,pc-2);
					knight(pr+1,pc+2);
					knight(pr+2,pc-1);
					knight(pr+2,pc+1);

			}
			pawnup=1;
		}
	}
	else{

		if(map[pr][pc].cellcolor==3)
			{
			map[pr][pc].pawn=map[cpr][cpc].pawn;
			map[pr][pc].pawncolor=map[cpr][cpc].pawncolor;
			drawcell(pr,pc);
			clearcell(cpr,cpc);
			turn=turn==0?15:0;
			}
		colorcell(cpr,cpc,getbc(cpr,cpc));
		for(i=0;i<8;i++)
			for(j=0;j<8;j++)
				if(map[i][j].cellcolor==3)
					colorcell(i,j,getbc(i,j));
		pawnup=0;
	}
}
void main(){
	int ch,i,j;
	init();
	pc=4;
	pr=4;
	drawboard();
	render();

	while(1){
		if(kbhit()){
			ch = getch();
			switch(ch){
			case 13:select();break;
			case 27:cleardevice();
				exit(0);
			case 77: selector(pr,pc+1);break;
			case 75: selector(pr,pc-1);break;
			case 72: selector(pr-1,pc);break;
			case 80: selector(pr+1,pc);break;
			}


			render();
		}
	}


}