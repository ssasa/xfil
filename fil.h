/* xfil.h - xfil v2.02 */

/*  here are the path's that you have to modify  */
#ifndef VMS
#define HOME                    "./"
#define bitmapsPath             "./bitmaps"
#else
#define HOME                    "XFIL_DIR:"
#define bitmapsPath             "XFIL_DIR:"
#endif  /* VMS */


/* #define FontName             "9x15"  ****you can try with this one : */
#define FontName "-ADOBE-NEW CENTURY SCHOOLBOOK-MEDIUM-R-NORMAL--*-140-*-*-P-*"

#define NO_ROW                  6
#define NO_COL                  7
#define NO_ROWCOL               (NO_ROW * NO_COL)
#define BIT_H                   30
#define BIT_W                   30
#define MaxWRow                 (NO_ROW + 6)
#define MaxWCol                 (NO_COL + 2)
#define Height                  (MaxWRow * BIT_H)
#define Width                   (MaxWCol * BIT_W)


#define NO                              0
#define YES                             1
#define FAST_INT int
#define MAXBUF  80


#define forever                         while(1)

enum {  NoPlayer,Player_A,Player_B,AIn,BIn,
		UpLeft,Up,UpRight,
		Left,Right,
		DownLeft,Down,DownRight,
		Floor,Plus,Minus,StartLeft,StartRight,QuitLeft,QuitRight };

extern int      main_field      [NO_ROW][NO_COL],
			CurDepth,
			MaxDepth,
			CurPlayer,
			CurIterPos,
			( *fil_test200 [NO_ROW][NO_COL] ) (void);
extern char map [MaxWRow][MaxWCol],
			buf[MAXBUF+1];
extern long win_field [NO_ROWCOL][NO_COL];
extern unsigned int width,height;


void    InitScreen(unsigned int,char *[]),
		EndScreen(void),
		ClearWinField(void),
		ClearMainField(void),
		UnsetFig(int),
		Iter(void),
		LoadOneBitmap(char *,Pixmap *),
		LoadBitmaps(void),
		ClearScreen(void),
		RedrawScreen(void),
		DrawScreen(void),
		PrintThink(void),
/*		MapChar(register char,register int,register int), */
		DrawString(int,int,char *),
		Highlight(void),
		Unhighlight(void);
int             PlayFil(void);
int   SetFig(int),
		BestMove(void),
		HumanMove(void),
		PlayingB(void);
/* Pixmap get_obj_adr(char); */

FAST_INT        fil_test_00(void), fil_test_01(void), fil_test_02(void),
			fil_test_03(void), fil_test_04(void), fil_test_05(void),
			fil_test_06(void),
			fil_test_10(void), fil_test_11(void), fil_test_12(void),
			fil_test_13(void), fil_test_14(void), fil_test_15(void),
			fil_test_16(void),
			fil_test_20(void), fil_test_21(void), fil_test_22(void),
			fil_test_23(void), fil_test_24(void), fil_test_25(void),
			fil_test_26(void),
			fil_test_30(void), fil_test_31(void), fil_test_32(void),
			fil_test_33(void), fil_test_34(void), fil_test_35(void),
			fil_test_36(void),
			fil_test_40(void), fil_test_41(void), fil_test_42(void),
			fil_test_43(void), fil_test_44(void), fil_test_45(void),
			fil_test_46(void),
			fil_test_50(void), fil_test_51(void), fil_test_52(void),
			fil_test_53(void), fil_test_54(void), fil_test_55(void),
			fil_test_56(void);
