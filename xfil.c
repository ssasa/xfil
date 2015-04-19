/* xfil v2.02 */
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include"fil.h"

char *windowName = "XFil  v2.01 - a logic game";
char *iconName = "XFil v2.01";

Display *display;
Window window;
XColor foreground,background,exact_return,cursor;
Pixmap  BlankPix,PlayerAPix,PlayerBPix,AInPix,BInPix,
		UpLeftPix,UpPix,UpRightPix,LeftPix,RightPix,
		DownLeftPix,DownPix,DownRightPix,
		FloorPix,PlusPix,MinusPix,
		StartLeftPix,StartRightPix,
		QuitLeftPix,QuitRightPix,
		WorkPixmap,IconPix;
GC      gc;
unsigned int width,height;

#define screenNumber            DefaultScreen(display)
#define rootWindow                      RootWindow(display,screenNumber)
#define displayWidth            DisplayWidth(display,screenNumber)
#define displayHeight           DisplayHeight(display,screenNumber)
#define blackPixel                      BlackPixel(display,screenNumber)
#define whitePixel                      WhitePixel(display,screenNumber)
#define defaultGC                       DefaultGC(display,screenNumber)
#define defaultColormap         DefaultColormap(display,screenNumber)
#define defaultDepth            DefaultDepth(display,screenNumber)
#define defaultVisual           DefaultVisual(display,screenNumber)
#define borderWidth                     1
#define minWidth                        width
#define maxWidth                        width
#define minHeight                       height
#define maxHeight                       height
#define forever                         while(1)


static void doCreateWindows(void);
static void doCreateGraphicsContext(void);
static void doLoadFont(void);
static void doWMHints(unsigned int,char *[]);
static void doMapWindows(void);
static void doCreatePixmap(void);

void InitScreen(argc,argv)
	unsigned int argc;
	char *argv[];
{
	width = Width;
	height = Height;

	if ( !(display = XOpenDisplay(NULL)) ) {
		fprintf(stderr,"Can't open display\n");
		exit(1);
	}
	XSynchronize(display,1);

	doCreateWindows();

	doCreateGraphicsContext();
	XSetForeground(display,gc,foreground.pixel);

	doCreatePixmap();

	doLoadFont();

	doWMHints(argc,argv);

	LoadBitmaps();

	ClearScreen();

	doMapWindows();

	RedrawScreen();

	return;
}

static void doCreateWindows(void)
{
	int windowX;
	int windowY;
	int i;
	XSetWindowAttributes xswa,sxswa;
	windowX = (displayWidth - width)>>1;
	windowY = (displayHeight - height)>>1;

	XAllocNamedColor(display,defaultColormap,"black",
						&foreground,&exact_return);
	XAllocNamedColor(display,defaultColormap,"red",
						&background,&exact_return);

	xswa.event_mask = ExposureMask | ButtonPressMask | KeyPressMask;
	xswa.background_pixel = background.pixel;
	sxswa.event_mask = ButtonPressMask | EnterWindowMask | LeaveWindowMask;

	window = XCreateWindow(display,rootWindow,
							windowX,windowY,width,height,borderWidth,
							defaultDepth,
							InputOutput,CopyFromParent,
							CWEventMask | CWBackPixel,&xswa);
	return;
}

static void doCreateGraphicsContext(void)
{
	XGCValues xgcv;

	xgcv.foreground = foreground.pixel;
	xgcv.background = background.pixel;
	xgcv.function = GXcopy;

	gc = XCreateGC(display,window,
					GCFunction | GCForeground | GCBackground,&xgcv);

	return;
}

static void doCreatePixmap(void)
{
	WorkPixmap = XCreatePixmap(display,window,width,height,defaultDepth);
	return;
}



static void doLoadFont(void)
{
	Font font;

	font = XLoadFont(display, FontName);
	XSetFont(display,gc,font);

	return;
}

static void doWMHints(argc,argv)
	unsigned int argc;
	char *argv[];
{
	XSizeHints xsh;
	XWMHints xwmh;

	xsh.x = 0;
	xsh.y = 0;
	xsh.width = width;
	xsh.height = height;
	xsh.min_width = minWidth;
	xsh.min_height = minHeight;
	xsh.max_width = maxWidth;
	xsh.max_height = maxHeight;
	xsh.flags = PPosition | PSize | PMinSize | PMaxSize;

	xwmh.initial_state = NormalState;
	xwmh.input = True;
	xwmh.flags = StateHint | InputHint;

	LoadOneBitmap("icon.xbm",&IconPix);

	XSetNormalHints(display,window,&xsh);
	XSetWMHints(display,window,&xwmh);

	XSetStandardProperties( display,window,
							windowName,
							iconName,
							IconPix,
							argv,argc,&xsh);



	return;
}

static void doMapWindows(void)
{
	XMapWindow(display,window);

	return;
}

void EndScreen(void)
{
	XFreePixmap(display,PlayerAPix);
	XFreePixmap(display,PlayerBPix);
	XFreePixmap(display,AInPix);
	XFreePixmap(display,BInPix);
	XFreePixmap(display,FloorPix);
	XFreePixmap(display,LeftPix);
	XFreePixmap(display,RightPix);
	XFreePixmap(display,UpPix);
	XFreePixmap(display,DownPix);
	XFreePixmap(display,UpLeftPix);
	XFreePixmap(display,DownLeftPix);
	XFreePixmap(display,UpRightPix);
	XFreePixmap(display,DownRightPix);
	XFreePixmap(display,BlankPix);
	XFreePixmap(display,PlusPix);
	XFreePixmap(display,MinusPix);
	XFreePixmap(display,StartLeftPix);
	XFreePixmap(display,StartRightPix);
	XFreePixmap(display,QuitLeftPix);
	XFreePixmap(display,QuitRightPix);
	XFreePixmap(display,WorkPixmap);
	XFreePixmap(display,IconPix);

	XFreeGC(display,gc);

	XUnmapWindow(display,window);
	XDestroyWindow(display,window);

	XCloseDisplay(display);
	return;
}

void LoadOneBitmap(name,pixmap)
	char *name;
	Pixmap *pixmap;
{
	unsigned int Null1,Null2;
	int Null3,Null4;
	chdir(bitmapsPath);
	if( XReadBitmapFile(display,window,name,&Null1,&Null2,pixmap,
								&Null3,&Null4) != BitmapSuccess ) {
			fprintf(stderr,"\nUnable to load: %s/%s.\n",bitmapsPath,name);
			exit(1);
	}
	chdir(HOME);
	return;
}

void LoadBitmaps(void)
{
	LoadOneBitmap("playerafig.xbm",&PlayerAPix);
	LoadOneBitmap("playerbfig.xbm",&PlayerBPix);
	LoadOneBitmap("wallwithafig.xbm",&AInPix);
	LoadOneBitmap("wallwithbfig.xbm",&BInPix);
	LoadOneBitmap("wallwithoutab.xbm",&FloorPix);
	LoadOneBitmap("leftwall.xbm",&LeftPix);
	LoadOneBitmap("rightwall.xbm",&RightPix);
	LoadOneBitmap("upwall.xbm",&UpPix);
	LoadOneBitmap("downwall.xbm",&DownPix);
	LoadOneBitmap("leftupwall.xbm",&UpLeftPix);
	LoadOneBitmap("leftdownwall.xbm",&DownLeftPix);
	LoadOneBitmap("rightupwall.xbm",&UpRightPix);
	LoadOneBitmap("rightdownwall.xbm",&DownRightPix);
	LoadOneBitmap("nothing.xbm",&BlankPix);
	LoadOneBitmap("plus.xbm",&PlusPix);
	LoadOneBitmap("minus.xbm",&MinusPix);
	LoadOneBitmap("startleft.xbm",&StartLeftPix);
	LoadOneBitmap("startright.xbm",&StartRightPix);
	LoadOneBitmap("quitleft.xbm",&QuitLeftPix);
	LoadOneBitmap("quitright.xbm",&QuitRightPix);

	return;
}

void ClearScreen(void)
{
	int i,j;
	XFillRectangle(display,WorkPixmap,gc,0,0,width,height);
	for(i=2; i < (NO_ROW+2) ; ++i)
		for(j=1; j < (NO_COL+1) ; ++j)
			XCopyPlane(display,FloorPix,WorkPixmap,gc,
						0,0,BIT_W,BIT_H,BIT_W*j,BIT_H*i,1);
	return;
}

void RedrawScreen(void)
{
	XCopyArea(display,WorkPixmap,window,gc,0,0,width,height,0,0);
	XFlush(display);
}

Pixmap get_obj_adr(c)
	register char c;
{
	switch(c) {
		case Player_A:  return( PlayerAPix );
		case Player_B:  return( PlayerBPix );
		case AIn:               return( AInPix );
		case BIn:               return( BInPix );
		case UpLeft:    return( UpLeftPix );
		case Up:                return( UpPix );
		case UpRight:   return( UpRightPix );
		case Left:              return( LeftPix );
		case Right:             return( RightPix );
		case DownLeft:  return( DownLeftPix );
		case Down:              return( DownPix );
		case DownRight: return( DownRightPix );
		case Floor:             return( FloorPix );
		case Plus:              return( PlusPix );
		case Minus:             return( MinusPix );
		case StartLeft: return( StartLeftPix );
		case StartRight:return( StartRightPix );
		case QuitLeft:  return( QuitLeftPix );
		case QuitRight: return( QuitRightPix );
		default:
			return( BlankPix );
	}
	return;
}

void MapChar(c,i,j)
	register char c;
	register int i,j;
{
	register int offset_col,offset_row;
/*	Pixmap this,get_obj_adr(char);  */
        Pixmap this;
	offset_col = BIT_W * j;
	offset_row = BIT_H * i;
	this = get_obj_adr(c);
	XCopyPlane(display,this,WorkPixmap,gc,0,0,BIT_W,BIT_H,
				offset_col,offset_row,1);
	XFlush(display);
	return;
}


void DrawScreen(void)
{
/*	void MapChar(register char,register int,register int); */
	register int i,j;
	for(i=0; i < MaxWRow ;++i)
		for(j=0; j < MaxWCol ;++j)
			MapChar(map [i][j],i,j);
	PrintThink();
	return;
}


void PrintThink(void)
{
	sprintf(buf,"Level:%3d                       ",MaxDepth);
	DrawString(10,(MaxWRow-1)*BIT_H,buf);
	return;
}

void DrawString(x,y,text)
	int x,y;
	char *text;
{
	int x_offset,y_offset;
	x_offset = x;
	y_offset = y;

	XDrawImageString(display,WorkPixmap,gc,x_offset,y_offset,text,strlen(text));

	RedrawScreen();

	return;
}
