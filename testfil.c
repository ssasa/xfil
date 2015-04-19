/* testfil.c - xfil v2.02 */

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include"fil.h"


#define MF(a,b)         main_field[a][b]
#define CP                      CurPlayer
#define RT                      return(YES);


#define HIF1(ca,d) {if(MF(ca,d+1)==CP && MF(ca,d+2)==CP && MF(ca,d+3)==CP)RT}
#define HIF2(ea,f) {if(MF(ea,f-1)==CP && MF(ea,f+1)==CP && MF(ea,f+2)==CP)RT}
#define HIF3(ga,h) {if(MF(ga,h-2)==CP && MF(ga,h-1)==CP && MF(ga,h+1)==CP)RT}
#define HIF4(ia,j) {if(MF(ia,j-3)==CP && MF(ia,j-2)==CP && MF(ia,j-1)==CP)RT}

#define VIF1(ka,l) {if(MF(ka+1,l)==CP && MF(ka+2,l)==CP && MF(ka+3,l)==CP)RT}
#define VIF2(ma,n) {if(MF(ma-1,n)==CP && MF(ma+1,n)==CP && MF(ma+2,n)==CP)RT}
#define VIF3(oa,p) {if(MF(oa-2,p)==CP && MF(oa-1,p)==CP && MF(oa+1,p)==CP)RT}
#define VIF4(qa,r) {if(MF(qa-3,r)==CP && MF(qa-2,r)==CP && MF(qa-1,r)==CP)RT}

#define BIF1(s,t) {if(MF(s+1,t+1)==CP && MF(s+2,t+2)==CP && MF(s+3,t+3)==CP)RT}
#define BIF2(u,v) {if(MF(u-1,v-1)==CP && MF(u+1,v+1)==CP && MF(u+2,v+2)==CP)RT}
#define BIF3(z,w) {if(MF(z-2,w-2)==CP && MF(z-1,w-1)==CP && MF(z+1,w+1)==CP)RT}
#define BIF4(x,y) {if(MF(x-3,y-3)==CP && MF(x-2,y-2)==CP && MF(x-1,y-1)==CP)RT}

#define SIF1(k,c) {if(MF(k+1,c-1)==CP && MF(k+2,c-2)==CP && MF(k+3,c-3)==CP)RT}
#define SIF2(m,e) {if(MF(m-1,e+1)==CP && MF(m+1,e-1)==CP && MF(m+2,e-2)==CP)RT}
#define SIF3(o,g) {if(MF(o-2,g+2)==CP && MF(o-1,g+1)==CP && MF(o+1,g-1)==CP)RT}
#define SIF4(q,i) {if(MF(q-3,i+3)==CP && MF(q-2,i+2)==CP && MF(q-1,i+1)==CP)RT}


#define HIF0____(af,bf)         /**/
#define HIF_1___(ab,bb)         HIF1(ab,bb)
#define HIF__2__(ag,bg)         HIF2(ag,bg)
#define HIF___3_(ah,bh)         HIF3(ah,bh)
#define HIF____4(mb,nb)         HIF4(mb,nb)
#define HIF_12__(cb,db)         HIF1(cb,db) HIF2(cb,db)
#define HIF__23_(ai,bi)         HIF2(ai,bi) HIF3(ai,bi)
#define HIF___34(kb,lb)         HIF3(kb,lb) HIF4(kb,lb)
#define HIF_123_(eb,fb)         HIF1(eb,fb) HIF2(eb,fb) HIF3(eb,fb)
#define HIF__234(ib,jb)         HIF2(ib,jb) HIF3(ib,jb) HIF4(ib,jb)
#define HIF_1234(gb,hb)         HIF1(gb,hb) HIF2(gb,hb) HIF3(gb,hb) HIF4(gb,hb) 

#define VIF0____(af,bf)         /**/
#define VIF_1___(ac,bc)         VIF1(ac,bc)
#define VIF__2__(ag,bg)         VIF2(ag,bg)
#define VIF___3_(ah,bh)         VIF3(ah,bh)
#define VIF____4(mc,nc)         VIF4(mc,nc)
#define VIF_12__(cc,dc)         VIF1(cc,dc) VIF2(cc,dc)
#define VIF__23_(ai,bi)         VIF2(ai,bi) VIF3(ai,bi)
#define VIF___34(kc,lc)         VIF3(kc,lc) VIF4(kc,lc)
#define VIF_123_(ec,fc)         VIF1(ec,fc) VIF2(ec,fc) VIF3(ec,fc)
#define VIF__234(ic,jc)         VIF2(ic,jc) VIF3(ic,jc) VIF4(ic,jc)
#define VIF_1234(gc,hc)         VIF1(gc,hc) VIF2(gc,hc) VIF3(gc,hc) VIF4(gc,hc)

#define BIF0____(af,bf)         /**/
#define BIF_1___(ad,bd)         BIF1(ad,bd)
#define BIF__2__(ag,bg)         BIF2(ag,bg)
#define BIF___3_(ah,bh)         BIF3(ah,bh)
#define BIF____4(md,nd)         BIF4(md,nd)
#define BIF_12__(cd,dd)         BIF1(cd,dd) BIF2(cd,dd)
#define BIF__23_(ai,bi)         BIF2(ai,bi) BIF3(ai,bi)
#define BIF___34(kd,ld)         BIF3(kd,ld) BIF4(kd,ld)
#define BIF_123_(ed,fd)         BIF1(ed,fd) BIF2(ed,fd) BIF3(ed,fd)
#define BIF__234(id,jd)         BIF2(id,jd) BIF3(id,jd) BIF4(id,jd)
#define BIF_1234(gd,hd)         BIF1(gd,hd) BIF2(gd,hd) BIF3(gd,hd) BIF4(gd,hd)

#define SIF0____(af,bf)         /**/
#define SIF_1___(ae,be)         SIF1(ae,be)
#define SIF__2__(ag,bg)         SIF2(ag,bg)
#define SIF___3_(ah,bh)         SIF3(ah,bh)
#define SIF____4(me,ne)         SIF4(me,ne)
#define SIF_12__(ce,de)         SIF1(ce,de) SIF2(ce,de)
#define SIF__23_(ai,bi)         SIF2(ai,bi) SIF3(ai,bi)
#define SIF___34(ke,le)         SIF3(ke,le) SIF4(ke,le)
#define SIF_123_(ee,fe)         SIF1(ee,fe) SIF2(ee,fe) SIF3(ee,fe)
#define SIF__234(ie,je)         SIF2(ie,je) SIF3(ie,je) SIF4(ie,je)
#define SIF_1234(ge,he)         SIF1(ge,he) SIF2(ge,he) SIF3(ge,he) SIF4(ge,he)


#define TF(name,aaa,bbb,hif,vif,bif,sif)        FAST_INT fil_test_##name (void) { \
								HIF##hif (aaa,bbb) \
								VIF##vif (aaa,bbb) \
								BIF##bif (aaa,bbb) \
								SIF##sif (aaa,bbb); return( NO );}

TF(00,0,0,_1___,_1___,_1___,0____)
TF(01,0,1,_12__,_1___,_1___,0____)
TF(02,0,2,_123_,_1___,_1___,0____)
TF(03,0,3,_1234,_1___,_1___,_1___)
TF(04,0,4,__234,_1___,0____,_1___)
TF(05,0,5,___34,_1___,0____,_1___)
TF(06,0,6,____4,_1___,0____,_1___)

TF(10,1,0,_1___,_12__,_1___,0____)
TF(11,1,1,_12__,_12__,_12__,0____)
TF(12,1,2,_123_,_12__,_12__,__2__)
TF(13,1,3,_1234,_12__,_12__,_12__)
TF(14,1,4,__234,_12__,__2__,_12__)
TF(15,1,5,___34,_12__,0____,_12__)
TF(16,1,6,____4,_12__,0____,_1___)

TF(20,2,0,_1___,_123_,_1___,0____)
TF(21,2,1,_12__,_123_,_12__,___3_)
TF(22,2,2,_123_,_123_,_123_,__23_)
TF(23,2,3,_1234,_123_,_123_,_123_)
TF(24,2,4,__234,_123_,__23_,_123_)
TF(25,2,5,___34,_123_,___3_,_12__)
TF(26,2,6,____4,_123_,0____,_1___)

TF(30,3,0,_1___,__234,0____,____4)
TF(31,3,1,_12__,__234,__2__,___34)
TF(32,3,2,_123_,__234,__23_,__234)
TF(33,3,3,_1234,__234,__234,__234)
TF(34,3,4,__234,__234,__234,__23_)  /* !err */
TF(35,3,5,___34,__234,___34,__2__)
TF(36,3,6,____4,__234,____4,0____)

TF(40,4,0,_1___,___34,0____,____4)
TF(41,4,1,_12__,___34,0____,___34)
TF(42,4,2,_123_,___34,___3_,___34)
TF(43,4,3,_1234,___34,___34,___34)
TF(44,4,4,__234,___34,___34,___3_)
TF(45,4,5,___34,___34,___34,0____)
TF(46,4,6,____4,___34,____4,0____)

TF(50,5,0,_1___,____4,0____,____4)
TF(51,5,1,_12__,____4,0____,____4)
TF(52,5,2,_123_,____4,0____,____4)
TF(53,5,3,_1234,____4,____4,____4)
TF(54,5,4,__234,____4,____4,0____)
TF(55,5,5,___34,____4,____4,0____)
TF(56,5,6,____4,____4,____4,0____)
