#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
 {
 int fino;
 int x,y;
 long double nu;
 char* ch;
 int ty;
 } el;
 
typedef struct
 {
 char* fina;
 int fino;
 int roco;
 int coco;
 } fi;

typedef struct
 {
 char* vana;
 long double nu;
 char* ch;
 int ty;
 } va;

typedef struct
 {
 int x,y;
 char* ch;
 } sel;

el* els;
fi* fis;
va* vas;
sel* sels;
int i,j,k;
int t = 0;
int fino = 1;
int vt = 0;
int st = 0;

void call(char* na);
void make(char* na);
long double nv(char* na, int x, int y);
char* cv(char* na, int x, int y);
int su(char* na, int x, int y, int ty, long double nu, char* ch);
void save(char* na);


int main(void)
{
els = malloc(sizeof(el)*(1));
els[0].ch = malloc(sizeof(char)*(1));
fis = malloc(sizeof(fi)*(1));
vas = malloc(sizeof(va)*(1));
sels = malloc(sizeof(sel)*(1));

call("raw1.txt");
su("raw1",5,5,1,0.0000001,"\0");
su("raw1",3,2,2,0,"edcba");


save("raw1.txt");


for(i=0; i<t; i++)
{
printf("%.15Lf, %d\n", els[i].nu,els[i].ty);
}

for(i=0; i<st; i++)
{
printf("%s, %ld\n", sels[i].ch,strlen(sels[i].ch));
}

free(els);
free(fis);
free(vas);
free(sels);

return 0;
}


void call(char* na)
 {
 FILE *fp;
 fp = fopen(na, "r");
 if(fp==NULL){printf("no file\n"); exit(0);}
 int a1 = 0;
 int a2 = 0;
 char b;
 int d = 0;
 int e = 0;
 while(fscanf(fp, "%c", &b)!=EOF)
  {
  if(b=='`'){e=e+1;}
  if(b=='|' && e%2==0)
   {
   if(d==0){a1 = a1+1;}
   else{a2 = a2+1;}
   e = 0;
   }
  if((b=='\n'||b=='\r') && e%2==0)
   {
   if(d==0){a1 = a1+1;}
   else{a2 = a2+1;}
   if(d!=0 && a1!=a2)
    {
    printf("row col err\n");
    goto ed;
    }
   a2 = 0;
   d = d+1;
   e = 0;
   }
  }
 if(!((b=='\n'||b=='\r')&&e%2==0)) //마지막 행 자동으로 개행처리 안될때 대비하는 코드
  {
  if(d!=0 && a1!=a2)
    {
    printf("row col err\n");
    goto ed;
    }
   a2 = 0;
   d = d+1;
   e = 0;
  }
  
 fclose(fp);
 
 fp = fopen(na, "r");
 int a = t;
 d = 0;
 e = 0;
 int x = 1;
 int y = 1;
 int poco = 0;
 int popl = 1;
 int poyn = 0;
 long double nu = 0;
 els = realloc(els, sizeof(el)*(a+1));
 els[a].ch = realloc(els[a].ch, sizeof(char)*(d+1));
 els[a].ch[0] = '\0';
 while(fscanf(fp, "%c", &b)!=EOF)
  {
  if(b=='`'){e=e+1;}
  if((b=='|'||b=='\n'||b=='\r') && e%2==0)
   {
   els[a].fino = fino;
   els[a].x = x;
   els[a].y = y;
   a = a+1;
   els = realloc(els, sizeof(el)*(a+1));
   d = 0;
   els[a].ch = malloc(sizeof(char)*(d+1));
   els[a].ch[0] = '\0';
   e = 0;
   if(b=='|'){y=y+1;}
   if(b=='\n'||b=='\r'){y=y-a1+1; x=x+1;}
   }
  else
   {
   els[a].ch[d] = b;
   d = d+1;
   els[a].ch = realloc(els[a].ch, sizeof(char)*(d+1));
   els[a].ch[d] = '\0';
   } 
  }

  for(i=0; i<(a-t); i++)
   {
   els[i+t].ty = 2;
   for(j=0; j<strlen(els[i+t].ch); j++)
    {
    if(els[i+t].ch[j]=='.'){poco=poco+1;}
    if(poco>1 || (j!=0&&els[i+t].ch[j]=='-') || (els[i+t].ch[j]!='0'&&els[i+t].ch[j]!='1'&&els[i+t].ch[j]!='2'&&els[i+t].ch[j]!='3'&&els[i+t].ch[j]!='4'&&els[i+t].ch[j]!='5'&&els[i+t].ch[j]!='6'&&els[i+t].ch[j]!='7'&&els[i+t].ch[j]!='8'&&els[i+t].ch[j]!='9'&&els[i+t].ch[j]!='.'&&els[i+t].ch[j]!='-'))
     {
     els[i+t].nu = 0; 
     els[i+t].ty = 2;
     break;
     }
    else
     {
     if(els[i+t].ch[j]=='.'){poyn=1;}
     if(els[i+t].ch[j]!='.' && els[i+t].ch[j]!='-' && poyn==0)
      {
      nu = nu*10 + (els[i+t].ch[j]-'0');
      }
     if(els[i+t].ch[j]!='.' && els[i+t].ch[j]!='-' && poyn==1)
      {
      nu = nu + (els[i+t].ch[j]-'0')/pow(10,popl);
      popl = popl+1;
      } 
     els[i+t].ty = 1; 
     }  
    }
   if(els[i+t].ch[0]!='-' && els[i+t].ty==1){els[i+t].nu = nu; strcpy(els[i+t].ch, "\0");}
   if(els[i+t].ch[0]=='-' && els[i+t].ty==1){els[i+t].nu = nu*(-1); strcpy(els[i+t].ch, "\0");}
   if(els[i+t].ty==1){els[i+t].nu=floor(els[i+t].nu*pow(10,15))/pow(10,15);}
   poyn = 0;
   poco = 0;
   popl = 1;
   nu = 0;
   }
 t = a;
 
 fis = realloc(fis, sizeof(fi)*fino);
 //fis[fino-1].fina = malloc(sizeof(char)*strlen(na));
 //strcpy(fis[fino-1].fina, na);
 fis[fino-1].fina = malloc(sizeof(char)*(strlen(na)-3));
 for(i=0; i<(strlen(na)-4); i++)
  {
  fis[fino-1].fina[i] = na[i];
  }
 fis[fino-1].fina[i] = '\0';
 fis[fino-1].fino = fino;
 if(a1!=0){fis[fino-1].roco = t/a1;} else{fis[fino-1].roco = 0;}
 fis[fino-1].coco = a1;
 fino = fino+1;
 
 ed:
 fclose(fp);
 }


void make(char* na)
 {
 FILE *fp;
 fp = fopen(na, "r");
 if(fp!=NULL){printf("already file\n"); exit(0);}
 //fp는 널인상태에서 fclose하면 덤프오류남
 fis = realloc(fis, sizeof(fi)*fino);
 //fis[fino-1].fina = malloc(sizeof(char)*strlen(na));
 //strcpy(fis[fino-1].fina, na);
 fis[fino-1].fina = malloc(sizeof(char)*(strlen(na)-3));
 for(i=0; i<(strlen(na)-4); i++)
  {
  fis[fino-1].fina[i] = na[i];
  }
 fis[fino-1].fina[i] = '\0';
 fis[fino-1].fino = fino;
 fis[fino-1].roco = 0;
 fis[fino-1].coco = 0;
 fino = fino+1;
 }
 
 
long double nv(char* na, int x, int y)
 {
 int err = 0;
 if(x!=0 && y!=0)
  {
  for(i=0; i<(fino-1); i++)
   {
   if(strcmp(fis[i].fina, na)==0)
    {
    goto fi;
    }
   }
  err = 1;
  printf("no file or no x,y in var\n");
  goto ed;
  fi:
  for(j=0; j<t; j++)
   {
   if(els[j].fino==fis[i].fino && els[j].x==x && els[j].y==y && els[j].ty==1)
    {
    return els[j].nu;
    }
   else if(els[j].fino==fis[i].fino && els[j].x==x && els[j].y==y && els[j].ty!=1 && els[j].ch[0]=='\0')
    {
    return 0;
    }
   else if(els[j].fino==fis[i].fino && els[j].x==x && els[j].y==y && els[j].ty!=1 && els[j].ch[0]!='\0')
    {
    err = 1;
    printf("not num\n");
    goto ed;
    }
   }
  goto ed;
  }
   
 else if(x==0 && y==0)
  {
  for(i=0; i<vt; i++)
   {
   if(strcmp(vas[i].vana,na)==0 && vas[i].ty==1)
    {
    return vas[i].nu;
    }
   else if(strcmp(vas[i].vana,na)==0 && vas[i].ty!=1)
    {
    err = 1;
    printf("not num\n");
    goto ed;
    }
   }
  err = 1; 
  printf("no var\n");
  goto ed;
  }
   
 else
  {
  printf("no x,y\n"); 
  err = 1; 
  goto ed;
  }
  
 ed:
 if(err==1){exit(0);}
 else{return 0;}
 }


char* cv(char* na, int x, int y)
 {
 int err = 0;
 if(x!=0 && y!=0)
  {
  for(i=0; i<(fino-1); i++)
   {
   if(strcmp(fis[i].fina, na)==0)
    {
    goto fi;
    }
   }
  err = 1;
  printf("no file or no x,y in var\n");
  goto ed;
  fi:
  for(j=0; j<t; j++)
   {
   if(els[j].fino==fis[i].fino && els[j].x==x && els[j].y==y && els[j].ty==2)
    {
    return els[j].ch;
    }
   else if(els[j].fino==fis[i].fino && els[j].x==x && els[j].y==y && els[j].ty!=2)
    {
    err = 1;
    printf("not char\n");
    goto ed;
    }
   }
   goto ed;
   }
   
 else if(x==0 && y==0)
  {
  for(i=0; i<vt; i++)
   {
   if(strcmp(vas[i].vana,na)==0 && vas[i].ty==2)
    {
    return vas[i].ch;
    }
   else if(strcmp(vas[i].vana,na)==0 && vas[i].ty!=2)
    {
    err = 1;
    printf("not char\n");
    goto ed;
    }
   }
  err = 1; 
  printf("no var\n");
  goto ed;
  }
   
 else
  {
  printf("no x,y\n"); 
  err = 1; 
  goto ed;
  }
 
 ed:
 if(err==1){exit(0);}
 else{return '\0';}  
 }
 
 
int su(char* na, int x, int y, int ty, long double nu, char* ch)
 {
 int err = 0;
 int a = t;
 if(ty!=1 && ty!=2)
  {
  err = 1;
  printf("no type\n");
  goto ed; 
  }
  
 if(x!=0 && y!=0)
  {
  for(i=0; i<(fino-1); i++)
   {
   if(strcmp(fis[i].fina, na)==0)
    {
    goto fi;
    }
   }
  err = 1;
  printf("no file or no x,y in var\n");
  goto ed; 
  fi:
  for(j=0; j<a; j++)
   {
   if(els[j].fino==fis[i].fino && els[j].x==x && els[j].y==y && ty==1)
    {
    els[j].nu = nu;
    strcpy(els[j].ch, "\0");
    els[j].ty = ty;
    return 0;
    }
   else if(els[j].fino==fis[i].fino && els[j].x==x && els[j].y==y && ty==2)
    {
    els[j].nu = 0;
    strcpy(els[j].ch, ch);
    els[j].ty = ty;
    return 0;
    } 
   }
  els = realloc(els, sizeof(el)*(a+1));
  els[a].ch = malloc(sizeof(char)*(1));
  if(ty==1)
   {
   els[a].nu = nu;
   strcpy(els[a].ch, "\0");
   els[a].ty = ty;
   els[a].x = x;
   els[a].y = y;
   els[a].fino = fis[i].fino;
   }
  if(ty==2)
   {
   els[a].nu = 0;
   strcpy(els[a].ch, ch);
   els[a].ty = ty;
   els[a].x = x;
   els[a].y = y;
   els[a].fino = fis[i].fino;
   }
  if(y > fis[i].roco){fis[i].roco=y;}
  if(x > fis[i].coco){fis[i].coco=x;}
  t = a+1;
  }

 else if(x==0 && y==0)
  {
  for(i=0; i<vt; i++)
   {
   if(strcmp(vas[i].vana,na)==0 && ty==1)
    {
    vas[i].nu = nu;
    strcpy(vas[i].ch, "\0");
    vas[i].ty = ty;
    return 0;
    }
   if(strcmp(vas[i].vana,na)==0 && ty==2)
    {
    vas[i].nu = 0;
    strcpy(vas[i].ch, ch);
    vas[i].ty = ty;
    return 0;
    }
   }
  vas = realloc(vas, sizeof(va)*(vt+1));
  vas[vt].vana = malloc(sizeof(char)*(1));
  vas[vt].ch = malloc(sizeof(char)*(1));
  strcpy(vas[vt].vana, na);
  if(ty==1)
   {
   vas[vt].nu = nu;
   strcpy(vas[vt].ch, "\0");
   vas[vt].ty = ty;
   }
  if(ty==2)
   {
   vas[vt].nu = 0;
   strcpy(vas[vt].ch, ch);
   vas[vt].ty = ty;
   }
  vt = vt+1;
  }
    
 else
  {
  printf("no x,y\n"); 
  err = 1; 
  goto ed;
  }
  
 ed:
 if(err==1){exit(0);}
 else{return 0;}    
 }
 
 
void save(char* na)
 {
 
 char* sana;
 sana = malloc(sizeof(char)*(strlen(na)-3));
 for(i=0; i<(strlen(na)-4); i++)
  {
  sana[i] = na[i];
  }
 sana[i] = '\0';
 for(i=0; i<(fino-1); i++)
  {
  if(strcmp(fis[i].fina, sana)==0)
   {
   break;
   }
  }
 sels = realloc(sels, sizeof(sel)*(fis[i].roco*fis[i].coco)); 
 while(st<(fis[i].roco*fis[i].coco))
  {
  sels[st].x = st/fis[i].coco+1;
  sels[st].y = st%fis[i].coco+1;
  sels[st].ch = malloc(sizeof(char)*(1));
  sels[st].ch[0] = '\0';
  st = st+1;
  }
 
 for(j=0; j<t; j++)
  {   
  if(els[j].fino == fis[i].fino)
   {
   if(els[j].ty == 1)
    {
    int ip = (int)els[j].nu;
    long double pp = els[j].nu - ip;
    int ipco = 0;
    int ppco = 15;
    if(ip==0){ipco=1;}
    if(els[j].nu<0){pp=pp*(-1);}
    while(ip!=0)
     {
     ip = ip/10;
     ipco = ipco+1;
     }
    for(k=0; k<15; k++)
     {
     if((long long int)(pp*pow(10,15-k))%10==0){ppco=ppco-1;}
     else{break;}
     }
    ip = (int)els[j].nu;
    if(els[j].nu<0){ipco=ipco+1;}
    sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch = realloc(sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch, sizeof(char)*(ipco+1));
    for(k=0; k<ipco; k++)
     {
     if(k==0&&els[j].nu<0)
      {
      sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch[k] = '-';
      ip = ip*(-1);
      continue;
      }
      sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch[k] = (int)(ip/pow(10,ipco-1-k)) + '0';
      ip = ip-(int)(ip/pow(10,ipco-1-k))*pow(10,ipco-1-k);
     }
    sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch[k] = '\0'; 
    if(ppco!=0)
     {
     sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch = realloc(sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch, sizeof(char)*(ipco+ppco+2));
     sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch[k] = '.';
     if(ppco>10){ppco=10;}
     for(k=0; k<ppco; k++)
      {
      sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch[k+ipco+1] = (int)(pp*10) + '0';
      pp = pp*10-(int)(pp*10); 
      }
     sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch[k+ipco+1] = '\0'; 
     }
    }
   if(els[j].ty == 2)
    {
    strcpy(sels[(els[j].x-1)*fis[i].coco+els[j].y-1].ch,els[j].ch);
    }   
   }
  }
 
 
 FILE *fp;
 fp = fopen(na, "w");
 for(j=0; j<st; j++)
  {
  fprintf(fp, "%s", sels[j].ch);
  if(j%fis[i].coco+1 == fis[i].coco)
   {
   fprintf(fp, "%s", "\n");
   }
  else
   {
   if(j==st-1){break;}
   else{fprintf(fp, "%s", "|");}
   } 
  }
 fprintf(fp, "%s", "\n");
 fprintf(fp, "%.10Lf", els[11].nu); 
 fclose(fp);
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
