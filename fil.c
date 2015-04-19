/* xfil.c - xfil v2.02 */

#include<stdio.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/keysym.h>
#include<time.h>
#include<limits.h>
#include "fil.h"

void MapChar(register char,register int,register int);

#define NextPlayer      (3-CurPlayer)
#define MAX(a,b) ( (a > b) ? (a) : (b) )
#define FirstToPlay ((rand() % 2)+1)


int main_field  [NO_ROW][NO_COL],
	CurDepth,
	MaxDepth,
	OldMaxDepth,
	CurPlayer,
	CurIterPos;
FAST_INT        ( *fil_test200 [NO_ROW][NO_COL] ) (void) = {
		{       fil_test_00, fil_test_01, fil_test_02, fil_test_03,
			fil_test_04, fil_test_05, fil_test_06   },
		{       fil_test_10, fil_test_11, fil_test_12, fil_test_13,
			fil_test_14, fil_test_15, fil_test_16   },
		{       fil_test_20, fil_test_21, fil_test_22, fil_test_23,
			fil_test_24, fil_test_25, fil_test_26   },
		{       fil_test_30, fil_test_31, fil_test_32, fil_test_33,
			fil_test_34, fil_test_35, fil_test_36   },
		{       fil_test_40, fil_test_41, fil_test_42, fil_test_43,
			fil_test_44, fil_test_45, fil_test_46   },
		{       fil_test_50, fil_test_51, fil_test_52, fil_test_53,
			fil_test_54, fil_test_55, fil_test_56   }       };
char buf [MAXBUF+1],
			map [MaxWRow][MaxWCol] ={
			{NO,NO,NO,NO,NO,NO,NO,NO,NO},
			{UpLeft,Up,Up,Up,Up,Up,Up,Up,UpRight},
			{Left,Floor,Floor,Floor,Floor,Floor,Floor,Floor,Right},
			{Left,Floor,Floor,Floor,Floor,Floor,Floor,Floor,Right},
			{Left,Floor,Floor,Floor,Floor,Floor,Floor,Floor,Right},
			{Left,Floor,Floor,Floor,Floor,Floor,Floor,Floor,Right},
			{Left,Floor,Floor,Floor,Floor,Floor,Floor,Floor,Right},
			{Left,Floor,Floor,Floor,Floor,Floor,Floor,Floor,Right},
			{DownLeft,Down,Down,Down,Down,Down,Down,Down,DownRight},
			{NO,Minus,Plus,NO,StartLeft,StartRight,QuitLeft,QuitRight,NO},
			{NO,NO,NO,NO,NO,NO,NO,NO,NO}};
long win_field  [NO_ROWCOL][NO_COL];
extern Display *display;
extern Window window;
XEvent report;
KeySym keysym;
XComposeStatus compose;
int Demo;

#ifdef VMS
int
#else
void
#endif
 main(argc,argv)
	unsigned int argc;
	char *argv[];
{
	int Again;
	InitScreen(argc,argv);
	srand(time((time_t) NULL) % 13577);
	CurPlayer=FirstToPlay;
	MaxDepth=4;
	Demo = YES;
	Again = YES;
	forever {
		ClearScreen();
		ClearMainField();
		DrawScreen();
		if( ! PlayFil() )
			break;
		RedrawScreen();
		if( Demo == YES )
			continue;
		forever {
			XNextEvent(display, &report);
			switch (report.type) {
				case ButtonPress:
				case Expose:
					RedrawScreen();
				break;
				case KeyPress:
					RedrawScreen();
					buf[0] = (char) NULL;
					(void) XLookupString(&report.xkey,buf,1,&keysym,&compose);
					switch(keysym) {
						case XK_Q:
						case XK_q:
							Again = NO;
							goto InLoop;
						break;
						case XK_S:
						case XK_s:
							goto InLoop;
						break;
						case XK_KP_Subtract:
						case XK_minus:
							if( MaxDepth > 2 ) {
								--MaxDepth;
								PrintThink();
							}
						break;
						case XK_KP_Add:
						case XK_plus:
						case XK_equal:
							if( MaxDepth < 10 ) {
								++MaxDepth;
								PrintThink();
							}
						break;
					}
				break;
			}
		}
InLoop:
		if( Again == NO )
			break;
	}
	EndScreen();
	return;
}

void Iter(void)
{
	register int i,j;
	for(j=0;j < NO_COL;++j) {
		if( CurDepth == 0 )
			CurIterPos = j;
		if( (i = SetFig(j)) == -1)
			continue;
		if( (* fil_test200 [i][j]) () == YES) {
			++ win_field [CurDepth][CurIterPos];
		} else if(CurDepth < MaxDepth) {
					++ CurDepth;
					CurPlayer=NextPlayer;
					Iter();
					CurPlayer=NextPlayer;
					-- CurDepth;
				}
		UnsetFig(j);
	}
	return;
}

int SetFig(i)
	int i;
{
	int j;
	if( main_field [0][i] != NoPlayer )
		return( -1 );
	for(j=1; j < NO_ROW && main_field [j][i] == NoPlayer ;++j) ;
	main_field [j-1][i] = CurPlayer;
	return( j-1 );
}

void UnsetFig(i)
	int i;
{
	int j;
	for(j=0; j < NO_ROW && main_field [j][i] == NoPlayer ;++j) ;
	main_field [j][i] = NoPlayer;
	return;
}

void ClearWinField(void)
{
	int i,j;
	for(i=0; i < NO_ROWCOL ;++i)
		for(j=0; j < NO_COL ;++j)
			win_field [i][j] = 0l ;
	return;
}

void ClearMainField(void)
{
	int i,j;
	for(i=0; i < NO_ROW ;++i)
		for(j=0; j < NO_COL ;++j)
			main_field [i][j] = NoPlayer ;
	for(i=2; i < (NO_ROW + 2) ; ++i)
		for(j=1; j < (NO_COL + 1); ++j)
			map [i][j] = Floor;
	return;
}

int PlayFil(void)
{
	int i,j;
	int fig_left;
	OldMaxDepth = MaxDepth ;
	fig_left=NO_ROWCOL;
	forever {
		if( Demo == YES &&
			XCheckWindowEvent(display,window,
				ButtonPressMask| KeyPressMask,&report) == True ) {
						Demo = NO;
						XPutBackEvent(display,&report);
						return(1);
		}
		CurPlayer=NextPlayer;
		--fig_left;
		if(fig_left < 0) {
			DrawString(10,(MaxWRow-1)*BIT_H,"No winner(A word from Mario) !");
			break;
		}
		switch( fig_left ) {
			case 22:
				OldMaxDepth = MaxDepth ;
			case 17:
			case 15:
			case 13:
				if( fig_left == 13 )
					++ MaxDepth;
			case 12:
			case 11:
			case 10:
			case 9:
				++ MaxDepth;
				PrintThink();
			break;
		}
		if( CurPlayer == Player_A ) {
			if( Demo == NO ) {
				while( (i = SetFig(j = HumanMove())) == -1 ) ;
				if( j == -2)
					return( NO );
				else if( j == -3 )
					return( YES );
				MapChar(AIn,i+2,j+1);
				RedrawScreen();
				if( (* fil_test200 [i][j]) () == YES ) {
					DrawString(10,(MaxWRow-1)*BIT_H,"You won this time !");
					break;
				}
				continue;
			} else {
				if( PlayingB() == -1)
					break;
				continue;
			}
		} else if( CurPlayer == Player_B ) {
			if( PlayingB() == -1)
				break;
			continue;
		}
		fprintf(stderr,"\nImpossiblle !!!");
	}
	MaxDepth = OldMaxDepth ;
	return( YES );
}

int PlayingB(void)
{
	int i,j;
	CurDepth=0;
	ClearWinField();
	if( Demo == NO ) {
		Iter();
	} else {
		if( Demo == NO ) {
			MaxDepth = OldMaxDepth;
			return( -1 );
		}
	}
	i = SetFig( j = BestMove() );
	MapChar(((Demo == YES && CurPlayer == Player_A)?(AIn):(BIn)),i+2,j+1);
	RedrawScreen();
	if( (* fil_test200 [i][j]) () == YES ) {
		DrawString(10,(MaxWRow-1)*BIT_H,"I won this time !!!");
		return(-1);
	}
	return(1);
}

int HumanMove(void)
{
	static int i=NO_COL/2;
	MapChar(Player_A,0,i+1);
	RedrawScreen();

	forever {
		XNextEvent(display, &report);
			switch (report.type) {
				case ButtonPress:
				case Expose:
					RedrawScreen();
				break;
				case KeyPress:
					MapChar(NoPlayer,0,i+1);
					RedrawScreen();
					buf[0] = (char) NULL;
					(void) XLookupString(&report.xkey,buf,1,&keysym,&compose);
					switch(keysym) {
						case XK_Left:
							if( i > 0 ) {
								--i;
							}
						break;
						case XK_Right:
							if( i < (NO_COL-1) ) {
								++i;
							}
						break;  
						case XK_Down:
						case XK_Return:
							return(i);
						break;
						case XK_KP_Subtract:
						case XK_minus:
							if( MaxDepth > 2 ) {
								--MaxDepth;
								PrintThink();
							}
						break;
						case XK_KP_Add:
						case XK_plus:
						case XK_equal:
							if( MaxDepth < 10 ) {
								++MaxDepth;
								PrintThink();
							}
						break;
						case XK_Q:
						case XK_q:
							return( -2 );
						break;
						case XK_S:
						case XK_s:
							return( -3 );
						break;
					}
					MapChar(Player_A,0,i+1);
					RedrawScreen();
				break;
				default:
				break;
			}

	}
	return(-1);
}

int BestMove(void)
{
	int i,j,a,flag[NO_COL],no_next=0,best=0,depth;
	long cur_max;
	for(i=1; i <= NO_ROWCOL ;i += 2)
		for(j=0; j < NO_COL ;++j)
			win_field [i][j] *= -1l ;
	for(i=0; i < NO_COL ; ++i)
		flag [i] = (( main_field [0][i] == NoPlayer ) ? (YES) : (NO));
	for(depth=0; depth <= MaxDepth ; ++depth) {
		cur_max = LONG_MIN;
		for(i=0; i < NO_COL ; ++i)
			if( flag [i] == YES )
				cur_max = MAX( cur_max , win_field [depth][i] );
		for(i=0 , no_next=0; i < NO_COL ; ++i)
			if( flag[i] == YES ) {
				if( win_field [depth][i] == cur_max ) {
					++ no_next;
					best=i;
				} else
					flag [i] = NO;
			}
		if( no_next == 1 )
			return( best );
	}
	j = rand() % no_next;
	for(i=0 , a=0; i < NO_COL ; ++i)
		if( flag [i] == YES ) {
			if( a == j )
				return( i );
			else
				++a ;
		}
	return( rand() % NO_COL );
}

