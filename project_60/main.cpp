#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL_mixer.h>
#include <string>
#include <fstream>
#include <time.h>
#include <math.h>
#include <conio.h>
using namespace std;
struct historyofplayer
{
    string playername;
    string m;
    string w;
    string d;
    string l;
    string gs;
    string gc;
    string gd;
    string p;
};
SDL_Renderer * m_renderer;
SDL_Window * m_window;
bool menu_bool=true;
bool league_bool=false;
bool setting_bool=false;
bool start_bool=false;
bool secondpage_bool=false;
bool gamepage_bool=false;
bool goal_bool=false;
bool gameend_bool=false;
bool music=true;
double dright_double=0,dleft_double=0;
int dright=0,dleft=0;
string playerleft_name,playerleft_matches,playerleft_wins,playerleft_draws,playerleft_loses,playerleft_gs,playerleft_gc,playerleft_gd,playerleft_points,playerleft_head="source//char1_left.png",playerleft_power="head fire ball",playerleft_theifpower;
string playerright_name,playerright_matches,playerright_wins,playerright_draws,playerright_loses,playerright_gs,playerright_gc,playerright_gd,playerright_points,playerright_head="source//char1_right.png",playerright_power="head fire ball",playerright_theifpower;
int game_fulltime=90,game_time,goal=5,x_selected_stadium=225,x_selected_goal=340,x_selected_time=480;
long long int time_at_first,time_of_now,start_time_of_power_of_right;
string stadium="source//stadium1.png";
int goal_player_left=0,goal_player_right=0;
historyofplayer history(string playername);
void outputtext(SDL_Renderer * m_renderer,int x,int y,int w,int h,int r,int g,int b,string s);
string inputtext(SDL_Renderer * m_renderer,int x,int y,int r_text,int g_text,int b_text,int r_back,int g_back,int b_back, int siz);
void image(SDL_Renderer * m_renderer,int x,int y,int w,int h,string s);
void menu(SDL_Renderer * m_renderer);
void league(SDL_Renderer * m_renderer);
void secondpage(SDL_Renderer *m_renderer);
void gameend(SDL_Renderer *m_renderer);
int to_int(string a)
{
    int x=0,i;
    for(i=0;i<a.size();i++)
    {
        x*=10;
        x+=a[i]-48;
    }
    return(x);
}
historyofplayer history(string inputplayername)
{
    historyofplayer historyofinputplayer;
    ifstream a("source//league.txt");
    int n,i;
    a>>n;
    string playername[n];
    string matches[n];
    string wins[n];
    string draws[n];
    string loses[n];
    string goalsscored[n];
    string goalsconceded[n];
    string goalsdiffrence[n];
    string points[n];
    for(i=0;i<n;i++)
    {
        a>>playername[i]>>matches[i]>>wins[i]>>draws[i]>>loses[i]>>goalsscored[i]>>goalsconceded[i]>>goalsdiffrence[i]>>points[i];
        if(playername[i]==inputplayername)
        {
            historyofinputplayer.playername=playername[i];
            historyofinputplayer.m=matches[i];
            historyofinputplayer.w=wins[i];
            historyofinputplayer.d=draws[i];
            historyofinputplayer.l=loses[i];
            historyofinputplayer.gs=goalsscored[i];
            historyofinputplayer.gc=goalsconceded[i];
            historyofinputplayer.gd=goalsdiffrence[i];
            historyofinputplayer.p=points[i];
            return(historyofinputplayer);
        }
    }
    ofstream b("source//league.txt");
    b<<(n+1)<<endl;
    for(i=0;i<n;i++)
    {
        b<<playername[i]<<endl<<matches[i]<<endl<<wins[i]<<endl<<draws[i]<<endl<<loses[i]<<endl<<goalsscored[i]<<endl<<goalsconceded[i]<<endl<<goalsdiffrence[i]<<endl<<points[i]<<endl;
    }
    b<<inputplayername<<endl<<"0"<<endl<<"0"<<endl<<"0"<<endl<<"0"<<endl<<"0"<<endl<<"0"<<endl<<"0"<<endl<<"0"<<endl;
    historyofinputplayer.playername=inputplayername;
    historyofinputplayer.m="0";
    historyofinputplayer.w="0";
    historyofinputplayer.d="0";
    historyofinputplayer.l="0";
    historyofinputplayer.gs="0";
    historyofinputplayer.gc="0";
    historyofinputplayer.gd="0";
    historyofinputplayer.p="0";
    return(historyofinputplayer);
}
void image(SDL_Renderer * m_renderer,int x,int y,int w,int h,string s)
{
    const char *imageaddres=s.c_str();
    SDL_Rect *image_rect=new SDL_Rect();
    image_rect->x=x;
    image_rect->y=y;
    image_rect->w=w;
    image_rect->h=h;
    SDL_Texture *image=IMG_LoadTexture(m_renderer,imageaddres);
    if(w==0 && h==0)
    {
        SDL_RenderCopy(m_renderer,image,NULL,NULL);
    }
    else
    {
        SDL_RenderCopy(m_renderer,image,NULL,image_rect);
    }
    SDL_DestroyTexture(image);
}
void menu(SDL_Renderer * m_renderer)
{
    Mix_Music *menu_sound = Mix_LoadMUS("source/menu_sound.mp3");
    Mix_VolumeMusic(30);
    if (music) Mix_PlayMusic(menu_sound,-1);
    music=false;
    game_time=game_fulltime;
    SDL_Event *event=new SDL_Event();
    bool playerleft_bool=false,playerright_bool=false;
    playerright_name="";
    playerleft_name="";
    dright=0;
    dleft=0;
    dright_double=0;
    dleft_double=0;
    SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
    SDL_RenderClear(m_renderer);
    image(m_renderer,0,0,0,0,"source//background1.png");
    image(m_renderer,170,390,430,80,"source//player button.png");
    image(m_renderer,770,390,430,80,"source//player button.png");
    image(m_renderer,510,570,320,120,"source//start2.png");
    image(m_renderer,230,120,600,200,"source//league.png");
    image(m_renderer,810,130,260,200,"source//setting.png");
    boxRGBA(m_renderer,200,500,520,560,0,255,0,255);
    outputtext(m_renderer,200,400,320,50,255,0,255,"player 1");
    boxRGBA(m_renderer,800,500,1120,560,0,255,0,255);
    outputtext(m_renderer,800,400,320,50,255,0,255,"player 2");
    outputtext(m_renderer,560,595,200,50,0,255,255,"start");
    while(menu_bool)
    {
    if(event->type==SDL_MOUSEBUTTONDOWN)
    {
    if(event->button.x>200 && event->button.x<520 && event->button.y>500 && event->button.y<560)
    {
    playerleft_name="";
    boxRGBA(m_renderer,200,500,520,560,0,255,0,255);
    outputtext(m_renderer,200,400,320,50,255,0,255,"player 1");
    playerleft_name=inputtext(m_renderer,200,500,0,0,0,0,255,0,40);
    playerleft_matches=history(playerleft_name).m;
    playerleft_wins=history(playerleft_name).w;
    playerleft_draws=history(playerleft_name).d;
    playerleft_loses=history(playerleft_name).l;
    playerleft_gs=history(playerleft_name).gs;
    playerleft_gc=history(playerleft_name).gc;
    playerleft_gd=history(playerleft_name).gd;
    playerleft_points=history(playerleft_name).p;
    playerleft_bool=true;
    }
    if(event->button.x>800 && event->button.x<1120 && event->button.y>500 && event->button.y<560)
    {
    playerright_name="";
    boxRGBA(m_renderer,800,500,1120,560,0,255,0,255);
    playerright_name=inputtext(m_renderer,800,500,0,0,0,0,255,0,40);
    playerright_matches=history(playerright_name).m;
    playerright_wins=history(playerright_name).w;
    playerright_draws=history(playerright_name).d;
    playerright_loses=history(playerright_name).l;
    playerright_points=history(playerright_name).p;
    playerright_gs=history(playerright_name).gs;
    playerright_gc=history(playerright_name).gc;
    playerright_gd=history(playerright_name).gd;
    playerright_bool=true;
    }
    if(event->button.x>=230 && event->button.x<=430 && event->button.y>=120 && event->button.y<=320)
    {
        menu_bool=false;
        league_bool=true;
    }
    if(event->button.x>510 && event->button.x<830 && event->button.y>570 && event->button.y<690 && playerleft_bool && playerright_bool)
    {
        menu_bool=false;
        secondpage_bool=true;
    }
    if(event->button.x>810 && event->button.x<1070 && event->button.y>130 && event->button.y<330)
    {
        menu_bool=false;
        setting_bool=true;
    }
    }
    if(event->type==SDL_KEYDOWN)
    {
        if(event->key.keysym.sym==SDLK_ESCAPE)
        {
            menu_bool=false;
        }
    }
      SDL_PollEvent(event);
      SDL_RenderPresent(m_renderer);
    }
}
void league(SDL_Renderer * m_renderer)
{
     SDL_Event *event=new SDL_Event();
     SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
     SDL_RenderClear(m_renderer);
     image(m_renderer,0,0,0,0,"source//background2.jpg");
     ifstream a("source//league.txt");
     int n,i;
     a>>n;
     string playername[n];
     string matches[n];
     string wins[n];
     string draws[n];
     string loses[n];
     string goalsscored[n];
     string goalsconceded[n];
     string goalsdiffrence[n];
     string points[n];
     boxRGBA(m_renderer,1,50,1279,(n+2)*50,255,255,254,200);
     image(m_renderer,500,600,200,100,"source//backbutton.png");
     for(i=0;i<n;i++)
     {
         a>>playername[i]>>matches[i]>>wins[i]>>draws[i]>>loses[i]>>goalsscored[i]>>goalsconceded[i]>>goalsdiffrence[i]>>points[i];
     }
     for(i=0;i<9;i++)
     {
         vlineRGBA(m_renderer,i*128,50,(n+2)*50,255,100,255,255);
     }
     vlineRGBA(m_renderer,1279,50,(n+2)*50,255,100,255,255);
     for(i=0;i<=n+1;i++)
     {
         hlineRGBA(m_renderer,0,1280,50+i*50,255,100,255,255);
     }
     outputtext(m_renderer,2,50,128,50,255,100,255,"pts");
     outputtext(m_renderer,128+4,50,120,50,255,100,255,"g d");
     outputtext(m_renderer,2*128+4,50,120,50,255,100,255,"g c");
     outputtext(m_renderer,3*128+4,50,120,50,255,100,255,"g s");
     outputtext(m_renderer,4*128+35,50,60,50,255,100,255,"L");
     outputtext(m_renderer,5*128+35,50,60,50,255,100,255,"D");
     outputtext(m_renderer,6*128+35,50,60,50,255,100,255,"W");
     outputtext(m_renderer,7*128+35,50,60,50,255,100,255,"M");
     outputtext(m_renderer,8*128+4,50,240,50,255,100,255,"player name");
     for(i=0;i<n;i++)
     {
         outputtext(m_renderer,8*128,(i+2)*50,240,50,255,100,255,playername[i]);
         outputtext(m_renderer,7*128+40,(i+2)*50+10,50,30,255,100,255,matches[i]);
         outputtext(m_renderer,6*128+40,(i+2)*50+10,50,30,255,100,255,wins[i]);
         outputtext(m_renderer,5*128+40,(i+2)*50+10,50,30,255,100,255,draws[i]);
         outputtext(m_renderer,4*128+40,(i+2)*50+10,50,30,255,100,255,loses[i]);
         outputtext(m_renderer,3*128+40,(i+2)*50+10,50,30,255,100,255,goalsscored[i]);
         outputtext(m_renderer,2*128+40,(i+2)*50+10,50,30,255,100,255,goalsconceded[i]);
         outputtext(m_renderer,1*128+40,(i+2)*50+10,50,30,255,100,255,goalsdiffrence[i]);
         outputtext(m_renderer,0*128+40,(i+2)*50+10,50,30,255,100,255,points[i]);
     }
     outputtext(m_renderer,550,610,120,50,0,255,255,"back");
     SDL_RenderPresent(m_renderer);
     while(league_bool)
     {
         SDL_PollEvent(event);
         if(event->type==SDL_MOUSEBUTTONDOWN)
         {
             if(event->button.x>=500 && event->button.x<=700 && event->button.y>=600 && event->button.y<=700)
             {
                 league_bool=false;
                 menu_bool=true;
             }
         }
     }
}
string inputtext(SDL_Renderer * m_renderer,int x,int y,int r_text,int g_text,int b_text,int r_back,int g_back,int b_back, int siz)
{
    SDL_Event *event=new SDL_Event();
    string s="";
    int i=0,L;
    while(event->key.keysym.sym!=SDLK_RETURN && i<8)
    {
        boxRGBA(m_renderer,x,y,x+i*siz,y+siz,r_back,g_back,b_back,255);
        if(SDL_PollEvent(event))
        {
        if(event->type==SDL_KEYDOWN && i!=8)
        {
        switch (event->key.keysym.sym)
        {
            case SDLK_a:
            s+="a";
            i++;
            break;
            case SDLK_b:
            s+="b";
            i++;
            break;
            case SDLK_c:
            s+="c";
            i++;
            break;
            case SDLK_d:
            s+="d";
            i++;
            break;
            case SDLK_e:
            s+="e";
            i++;
            break;
            case SDLK_f:
            s+="f";
            i++;
            break;
            case SDLK_g:
            s+="g";
            i++;
            break;
            case SDLK_h:
            s+="h";
            i++;
            break;
            case SDLK_i:
            s+="i";
            i++;
            break;
            case SDLK_j:
            s+="j";
            i++;
            break;
            case SDLK_k:
            s+="k";
            i++;
            break;
            case SDLK_l:
            s+="l";
            i++;
            break;
            case SDLK_m:
            s+="m";
            i++;
            break;
            case SDLK_n:
            s+="n";
            i++;
            break;
            case SDLK_o:
            s+="o";
            i++;
            break;
            case SDLK_p:
            s+="p";
            i++;
            break;
            case SDLK_q:
            s+="q";
            i++;
            break;
            case SDLK_r:
            s+="r";
            i++;
            break;
            case SDLK_s:
            s+="s";
            i++;
            break;
            case SDLK_t:
            s+="t";
            i++;
            break;
            case SDLK_u:
            s+="u";
            i++;
            break;
            case SDLK_v:
            s+="v";
            i++;
            break;
            case SDLK_w:
            s+="w";
            i++;
            break;
            case SDLK_x:
            s+="x";
            i++;
            break;
            case SDLK_y:
            s+="y";
            i++;
            break;
            case SDLK_z:
            s+="z";
            i++;
            break;
            case SDLK_0:
            s+="0";
            i++;
            break;
            case SDLK_1:
            s+="1";
            i++;
            break;
            case SDLK_2:
            s+="2";
            i++;
            break;
            case SDLK_3:
            s+="3";
            i++;
            break;
            case SDLK_4:
            s+="4";
            i++;
            break;
            case SDLK_5:
            s+="5";
            i++;
            break;
            case SDLK_6:
            s+="6";
            i++;
            break;
            case SDLK_7:
            s+="7";
            i++;
            break;
            case SDLK_8:
            s+="8";
            i++;
            break;
            case SDLK_9:
            s+="9";
            i++;
            break;
            case SDLK_BACKSPACE:
            L=s.size();
            if(L>0)
            {
                s=s.erase(L-1,1);
                i--;
            }
            break;
        }
        }
        outputtext(m_renderer,x,y,siz*i,siz,r_text,g_text,b_text,s);
        SDL_RenderPresent(m_renderer);
    }
    }
    return (s);
}
void outputtext(SDL_Renderer * m_renderer,int x,int y,int w,int h,int r,int g,int b,string s)
{
    const char *text=s.c_str();
    TTF_Font * text_font=TTF_OpenFont("source//playfair.otf",48);
    SDL_Color text_color={r,g,b};
    SDL_Surface * text_surface=TTF_RenderText_Solid(text_font,text,text_color);
    SDL_Texture * text_texture=SDL_CreateTextureFromSurface(m_renderer,text_surface);
    SDL_Rect * text_rect=new SDL_Rect{x,y,w,h};
    SDL_RenderCopy(m_renderer,text_texture,NULL,text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}
void setting(SDL_Renderer *m_renderer)
{
    SDL_Event *event=new SDL_Event();
    while(setting_bool)
    {
        SDL_PollEvent(event);
        SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
        SDL_RenderClear(m_renderer);
        image(m_renderer,0,0,0,0,"source//background2.jpg");
        image(m_renderer,100,20,300,150,"source//stadium1.png");
        image(m_renderer,500,20,300,150,"source//stadium2.png");
        image(m_renderer,900,20,300,150,"source//stadium3.png");
        image(m_renderer,x_selected_stadium,180,50,50,"source//selected.png");
        image(m_renderer,565,240,200,100,"source//start.png");
        outputtext(m_renderer,595,260,120,50,70,255,70,"goal");
        image(m_renderer,120,330,100,100,"source//player button.png");
        outputtext(m_renderer,125,345,80,50,0,0,0,"4");
        image(m_renderer,320,330,100,100,"source//player button.png");
        outputtext(m_renderer,325,345,80,50,0,0,0,"5");
        image(m_renderer,520,330,100,100,"source//player button.png");
        outputtext(m_renderer,525,345,80,50,0,0,0,"6");
        image(m_renderer,720,330,100,100,"source//player button.png");
        outputtext(m_renderer,725,345,80,50,0,0,0,"7");
        image(m_renderer,920,330,100,100,"source//player button.png");
        outputtext(m_renderer,925,345,80,50,0,0,0,"8");
        image(m_renderer,1120,330,100,100,"source//player button.png");
        outputtext(m_renderer,1125,345,80,50,0,0,0,"9");
        image(m_renderer,x_selected_goal,430,50,50,"source//selected.png");
        image(m_renderer,565,480,200,100,"source//start.png");
        outputtext(m_renderer,595,500,120,50,70,255,70,"time");
        image(m_renderer,120,580,200,100,"source//player button.png");
        outputtext(m_renderer,125,595,160,50,0,0,0,"60");
        image(m_renderer,420,580,200,100,"source//player button.png");
        outputtext(m_renderer,425,595,160,50,0,0,0,"90");
        image(m_renderer,720,580,200,100,"source//player button.png");
        outputtext(m_renderer,725,595,160,50,0,0,0,"120");
        image(m_renderer,1020,580,200,100,"source//player button.png");
        outputtext(m_renderer,1025,595,160,50,0,0,0,"150");
        image(m_renderer,x_selected_time,685,50,50,"source//selected.png");
        image(m_renderer,565,720,200,100,"source//backbutton.png");
        outputtext(m_renderer,600,730,140,50,0,255,255,"back");
        if(event->type==SDL_MOUSEBUTTONDOWN)
        {
            if(event->button.x>100 && event->button.x<400 && event->button.y>20 && event->button.y<170)
            {
                x_selected_stadium=225;
                stadium="source//stadium1.png";
            }
            if(event->button.x>500 && event->button.x<800 && event->button.y>20 && event->button.y<170)
            {
                x_selected_stadium=625;
                stadium="source//stadium2.png";
            }
            if(event->button.x>900 && event->button.x<1200 && event->button.y>20 && event->button.y<170)
            {
                x_selected_stadium=1025;
                stadium="source//stadium3.png";
            }
            if(event->button.x>120 && event->button.x<220 && event->button.y>330 && event->button.y<430)
            {
                x_selected_goal=140;
                goal=4;
            }
            if(event->button.x>320 && event->button.x<420 && event->button.y>330 && event->button.y<430)
            {
                x_selected_goal=340;
                goal=5;
            }
            if(event->button.x>520 && event->button.x<620 && event->button.y>330 && event->button.y<430)
            {
                x_selected_goal=540;
                goal=6;
            }
            if(event->button.x>720 && event->button.x<820 && event->button.y>330 && event->button.y<430)
            {
                x_selected_goal=740;
                goal=7;
            }
            if(event->button.x>920 && event->button.x<1020 && event->button.y>330 && event->button.y<430)
            {
                x_selected_goal=940;
                goal=8;
            }
            if(event->button.x>1120 && event->button.x<1220 && event->button.y>330 && event->button.y<430)
            {
                x_selected_goal=1140;
                goal=9;
            }
            if(event->button.x>120 && event->button.x<320 && event->button.y>580 && event->button.y<680)
            {
                x_selected_time=180;
                game_fulltime=60;
            }
            if(event->button.x>420 && event->button.x<620 && event->button.y>580 && event->button.y<680)
            {
                x_selected_time=480;
                game_fulltime=90;
            }
            if(event->button.x>720 && event->button.x<920 && event->button.y>580 && event->button.y<680)
            {
                x_selected_time=780;
                game_fulltime=120;
            }
            if(event->button.x>1020 && event->button.x<1220 && event->button.y>580 && event->button.y<680)
            {
                x_selected_time=1080;
                game_fulltime=150;
            }
            if(event->button.x>565 && event->button.x<765 && event->button.y>720 && event->button.y<800)
            {
                menu_bool=true;
                setting_bool=false;
            }
        }
        SDL_RenderPresent(m_renderer);
    }
}
void secondpage(SDL_Renderer *m_renderer)
{
    playerleft_head="source//char1_left.png";
    playerright_head="source//char1_right.png";
    SDL_Event *event=new SDL_Event();
    bool turn_bool=true;
    string addresschar1left="source//charbackselect.png",addresschar2left="source//charback.png",addresschar3left="source//charback.png",addresschar4left="source//charback.png",addresschar5left="source//charback.png";
    string addresschar1right="source//charbackselect.png",addresschar2right="source//charback.png",addresschar3right="source//charback.png",addresschar4right="source//charback.png",addresschar5right="source//charback.png";
    int button_x=160,button_y=60,select_x=340;
    while(secondpage_bool)
    {
    SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
    SDL_RenderClear(m_renderer);
    image(m_renderer,0,0,0,0,"source//background1.png");
    outputtext(m_renderer,150,20,80,50,255,255,255,"pts");
    outputtext(m_renderer,160,90,40,40,255,255,255,playerleft_points);
    outputtext(m_renderer,260,20,20,50,255,255,255,"l");
    outputtext(m_renderer,255,90,40,40,255,255,255,playerleft_loses);
    outputtext(m_renderer,320,20,20,50,255,255,255,"d");
    outputtext(m_renderer,315,90,40,40,255,255,255,playerleft_draws);
    outputtext(m_renderer,380,20,20,50,255,255,255,"w");
    outputtext(m_renderer,375,90,40,40,255,255,255,playerleft_wins);
    outputtext(m_renderer,440,20,20,50,255,255,255,"m");
    outputtext(m_renderer,435,90,40,40,255,255,255,playerleft_matches);
    outputtext(m_renderer,800,20,80,50,255,255,255,"pts");
    outputtext(m_renderer,810,90,40,40,255,255,255,playerright_points);
    outputtext(m_renderer,910,20,20,50,255,255,255,"l");
    outputtext(m_renderer,905,90,40,40,255,255,255,playerright_loses);
    outputtext(m_renderer,970,20,20,50,255,255,255,"d");
    outputtext(m_renderer,965,90,40,40,255,255,255,playerright_draws);
    outputtext(m_renderer,1030,20,20,50,255,255,255,"w");
    outputtext(m_renderer,1025,90,40,40,255,255,255,playerright_wins);
    outputtext(m_renderer,1090,20,20,50,255,255,255,"m");
    outputtext(m_renderer,1085,90,40,40,255,255,255,playerright_matches);
    image(m_renderer,350,550,200,200,"source//body_left.png");
    image(m_renderer,383,430,145,175,playerleft_head);
    image(m_renderer,750,540,200,210,"source//body_right.png");
    image(m_renderer,770,430,145,175,playerright_head);
    outputtext(m_renderer,370,370,150,50,255,255,255,playerleft_name);
    outputtext(m_renderer,590,530,70,50,255,255,255,"Vs");
    outputtext(m_renderer,770,370,150,50,255,255,255,playerright_name);

    image(m_renderer,15,30,100,130,addresschar1left);
    image(m_renderer,17,30,100,120,"source//char1_left.png");
    outputtext(m_renderer,31,132,70,20,255,255,255,"Head Fire Ball");
    image(m_renderer,15,170,100,130,addresschar2left);
    image(m_renderer,20,170,100,120,"source//char2_left.png");
    outputtext(m_renderer,31,275,70,20,255,255,255,"Kick Fire Ball");
    image(m_renderer,15,310,100,130,addresschar3left);
    image(m_renderer,18,310,100,120,"source//char3_left.png");
    outputtext(m_renderer,30,413,70,20,255,255,255,"Invisible Ball");
    image(m_renderer,15,450,100,130,addresschar4left);
    image(m_renderer,18,450,100,120,"source//char4_left.png");
    outputtext(m_renderer,31,552,70,20,255,255,255,"Punch");
    image(m_renderer,15,590,100,130,addresschar5left);
    image(m_renderer,15,590,100,120,"source//char5_left.png");
    outputtext(m_renderer,31,695,70,20,255,255,255,"Thief");

    image(m_renderer,1160,30,100,130,addresschar1right);
    image(m_renderer,1157,30,100,120,"source//char1_right.png");
    outputtext(m_renderer,1173,132,70,20,255,255,255,"Head Fire Ball");
    image(m_renderer,1160,170,100,130,addresschar2right);
    image(m_renderer,1160,170,100,120,"source//char2_right.png");
    outputtext(m_renderer,1175,275,70,20,255,255,255,"Kick Fire Ball");
    image(m_renderer,1160,310,100,130,addresschar3right);
    image(m_renderer,1157,310,100,120,"source//char3_right.png");
    outputtext(m_renderer,1175,413,70,20,255,255,255,"Invisible Ball");
    image(m_renderer,1160,450,100,130,addresschar4right);
    image(m_renderer,1163,450,100,120,"source//char4_right.png");
    outputtext(m_renderer,1175,552,70,20,255,255,255,"Punch");
    image(m_renderer,1160,590,100,130,addresschar5right);
    image(m_renderer,1160,590,100,120,"source//char5_right.png");
    outputtext(m_renderer,1175,695,70,20,255,255,255,"Thief");
    image(m_renderer,640-button_x/2,680-button_y/2,button_x,button_y,"source//play_button.png");
    if (button_x==160) turn_bool=false;
    if (!turn_bool) {button_x+=8;button_y+=3;}
    if (button_x==200) turn_bool=true;
    if (turn_bool) {button_x-=8;button_y-=3;}
        if (event->type==SDL_MOUSEBUTTONDOWN)
            {
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=15 && event->button.x<=115 && event->button.y>=30 && event->button.y<=160)
            {
                addresschar1left="source//charbackselect.png",addresschar2left="source//charback.png",addresschar3left="source//charback.png",addresschar4left="source//charback.png",addresschar5left="source//charback.png",playerleft_head="source//char1_left.png",playerleft_power="head fire ball";
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=15 && event->button.x<=115 && event->button.y>=170 && event->button.y<=300)
            {
                addresschar1left="source//charback.png",addresschar2left="source//charbackselect.png",addresschar3left="source//charback.png",addresschar4left="source//charback.png",addresschar5left="source//charback.png",playerleft_head="source//char2_left.png",playerleft_power="kick fire ball";
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=15 && event->button.x<=115 && event->button.y>=310 && event->button.y<=440)
            {
                addresschar1left="source//charback.png",addresschar2left="source//charback.png",addresschar3left="source//charbackselect.png",addresschar4left="source//charback.png",addresschar5left="source//charback.png",playerleft_head="source//char3_left.png",playerleft_power="invisible ball";
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=15 && event->button.x<=115 && event->button.y>=450 && event->button.y<=580)
            {
                addresschar1left="source//charback.png",addresschar2left="source//charback.png",addresschar3left="source//charback.png",addresschar4left="source//charbackselect.png",addresschar5left="source//charback.png",playerleft_head="source//char4_left.png",playerleft_power="punch";
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=15 && event->button.x<=115 && event->button.y>=590 && event->button.y<=720)
            {
                addresschar1left="source//charback.png",addresschar2left="source//charback.png",addresschar3left="source//charback.png",addresschar4left="source//charback.png",addresschar5left="source//charbackselect.png",playerleft_head="source//char5_left.png",playerleft_power="thief";
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=1160 && event->button.x<=1260 && event->button.y>=30 && event->button.y<=160)
            {
                addresschar1right="source//charbackselect.png",addresschar2right="source//charback.png",addresschar3right="source//charback.png",addresschar4right="source//charback.png",addresschar5right="source//charback.png",playerright_head="source//char1_right.png",playerright_power="head fire ball";;
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=1160 && event->button.x<=1260 && event->button.y>=170 && event->button.y<=300)
            {
                addresschar1right="source//charback.png",addresschar2right="source//charbackselect.png",addresschar3right="source//charback.png",addresschar4right="source//charback.png",addresschar5right="source//charback.png",playerright_head="source//char2_right.png",playerright_power="kick fire ball";
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=1160 && event->button.x<=1260 && event->button.y>=310 && event->button.y<=440)
            {
                addresschar1right="source//charback.png",addresschar2right="source//charback.png",addresschar3right="source//charbackselect.png",addresschar4right="source//charback.png",addresschar5right="source//charback.png",playerright_head="source//char3_right.png",playerright_power="invisible ball";
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=1160 && event->button.x<=1260 && event->button.y>=450 && event->button.y<=580)
            {
                addresschar1right="source//charback.png",addresschar2right="source//charback.png",addresschar3right="source//charback.png",addresschar4right="source//charbackselect.png",addresschar5right="source//charback.png",playerright_head="source//char4_right.png",playerright_power="punch";
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=1160 && event->button.x<=1260 && event->button.y>=590 && event->button.y<=720)
            {
                addresschar1right="source//charback.png",addresschar2right="source//charback.png",addresschar3right="source//charback.png",addresschar4right="source//charback.png",addresschar5right="source//charbackselect.png",playerright_head="source//char5_right.png",playerright_power="thief";
            }
            if (event->button.button==SDL_BUTTON_LEFT && event->button.x>=560 && event->button.x<=720 && event->button.y>=650 && event->button.y<=710)
            {
                secondpage_bool=false;
                gamepage_bool=true;
                time_at_first=time(NULL);
            }
            }
           if(event->type==SDL_KEYDOWN)
           {
           if(event->key.keysym.sym==SDLK_ESCAPE)
           {
              secondpage_bool=false;
              menu_bool=true;
           }
           }
      SDL_Delay(5);
      SDL_PollEvent(event);
      SDL_RenderPresent(m_renderer);
      }
}
void gameend(SDL_Renderer *m_renderer)
{
        SDL_Event *event=new SDL_Event();
        ifstream a("source//league.txt");
        int n,i;
        a>>n;
        string player_name[n];
        string player_matches[n];
        string player_wins[n];
        string player_draws[n];
        string player_loses[n];
        string player_gs[n];
        string player_gc[n];
        string player_gd[n];
        string player_points[n];
        for(i=0;i<n;i++)
        {
            a>>player_name[i];
            a>>player_matches[i];
            a>>player_wins[i];
            a>>player_draws[i];
            a>>player_loses[i];
            a>>player_gs[i];
            a>>player_gc[i];
            a>>player_gd[i];
            a>>player_points[i];
            if(player_name[i]==playerleft_name)
            {
                player_matches[i]=to_string(to_int(player_matches[i])+1);
                if(goal_player_left>goal_player_right)
                {
                    player_wins[i]=to_string(to_int(player_wins[i])+1);
                    player_points[i]=to_string(to_int(player_points[i])+3);
                }
                if(goal_player_left==goal_player_right)
                {
                    player_draws[i]=to_string(to_int(player_draws[i])+1);
                    player_points[i]=to_string(to_int(player_points[i])+1);
                }
                if(goal_player_left<goal_player_right)
                {
                    player_loses[i]=to_string(to_int(player_loses[i])+1);
                }
                player_gs[i]=to_string(to_int(player_gs[i])+goal_player_left);
                player_gc[i]=to_string(to_int(player_gc[i])+goal_player_right);
                player_gd[i]=to_string(to_int(player_gs[i])-to_int(player_gc[i]));

            }
            if(player_name[i]==playerright_name)
            {
                player_matches[i]=to_string(to_int(player_matches[i])+1);
                if(goal_player_right>goal_player_left)
                {
                    player_wins[i]=to_string(to_int(player_wins[i])+1);
                    player_points[i]=to_string(to_int(player_points[i])+3);
                }
                if(goal_player_right==goal_player_left)
                {
                    player_draws[i]=to_string(to_int(player_draws[i])+1);
                    player_points[i]=to_string(to_int(player_points[i])+1);
                }
                if(goal_player_right<goal_player_left)
                {
                    player_loses[i]=to_string(to_int(player_loses[i])+1);
                }
                player_gs[i]=to_string(to_int(player_gs[i])+goal_player_right);
                player_gc[i]=to_string(to_int(player_gc[i])+goal_player_left);
                player_gd[i]=to_string(to_int(player_gs[i])-to_int(player_gc[i]));
            }
    }
    ofstream b("source//league.txt");
    b<<n<<endl;
    for(i=0;i<n;i++)
    {
        b<<player_name[i]<<endl<<player_matches[i]<<endl<<player_wins[i]<<endl<<player_draws[i]<<endl<<player_loses[i]<<endl<<player_gs[i]<<endl<<player_gc[i]<<endl<<player_gd[i]<<endl<<player_points[i]<<endl;
    }
    while(gameend_bool)
    {
    SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
    SDL_RenderClear(m_renderer);
    SDL_PollEvent(event);
    image(m_renderer,0,0,0,0,"source//background2.jpg");
    image(m_renderer,670,170,260,140,"source//start2.png");
    image(m_renderer,970,170,260,140,"source//start2.png");
    image(m_renderer,722,292,150,150,"source//goal button.png");
    image(m_renderer,1022,292,150,150,"source//goal button.png");
    outputtext(m_renderer,720,190,140,80,0,255,255,playerleft_name);
    outputtext(m_renderer,1020,190,140,80,0,255,255,playerright_name);
    outputtext(m_renderer,770,340,50,50,0,0,0,to_string(goal_player_left));
    outputtext(m_renderer,1070,340,50,50,0,0,0,to_string(goal_player_right));
    image(m_renderer,850,500,200,100,"source//backbutton.png");
    outputtext(m_renderer,890,510,140,50,0,255,255,"to the menu");
    SDL_RenderPresent(m_renderer);
    if(event->type==SDL_MOUSEBUTTONDOWN)
    {
        if(event->button.x>=850 && event->button.x<=1050 && event->button.y>=500 && event->button.y<=600)
        {
            gameend_bool=false;
            gamepage_bool=false;
            menu_bool=true;
        }
    }
    }
    goal_player_left=0;
    goal_player_right=0;
}
void gamepage(SDL_Renderer *m_renderer)
{
     Mix_Music *game_Sound = Mix_LoadMUS("source/game_sound.mp3");
     Mix_Chunk *shoot = Mix_LoadWAV("source/shoot.wav");
     Mix_Chunk *goaleffect = Mix_LoadWAV("source/goal.wav");
     Mix_Chunk *foul = Mix_LoadWAV("source/foul.wav");
     Mix_VolumeChunk(shoot,128);
     Mix_VolumeChunk(goaleffect,50);
     Mix_VolumeChunk(foul,50);
     Mix_VolumeMusic(30);
     if (!music) Mix_PlayMusic(game_Sound,-1);
     music=true;
    if(goal_bool)
    {
      boxRGBA(m_renderer,0,0,1280,800,0,0,0,100);
      image(m_renderer,20,20,1200,700,"source//goal_picture.png");
      SDL_RenderPresent(m_renderer);
      SDL_Delay(1000);
      goal_bool=false;
    }
    SDL_Event *event=new SDL_Event();
    string ball_picture="source//ball1.png";
    string player_left_picture="source//body_leftplay.png";
    string player_right_picture="source//body_rightplay.png";
    int m=0;
    int resume_time=0;
    int x_left=140,dx_left=0,y_left=505,dy_left=0,x_right=1038,dx_right=0,y_right=505,dy_right=0;
    int x_ball=617,y_ball=50,dy_ball=0,dx_ball=0;
    int x_goalpost_left,x_goalpost_right,x_bullet_left=-100,x_bullet_right=1400;
    long long int start_time_of_invisible_ball,start_time_of_punch_left=0,start_time_of_punch_right=0;
    long long int start_time_headfireball_left=0,start_time_headfireball_right=0;
    long long int start_time_kickfireball_left=0,start_time_kickfireball_right=0;
    if (stadium=="source//stadium1.png")
    {
        x_goalpost_left=-2,x_goalpost_right=1208;
    }
    if (stadium=="source//stadium2.png")
    {
        x_goalpost_left=-4,x_goalpost_right=1212;
    }
    if (stadium=="source//stadium3.png")
    {
        x_goalpost_left=3,x_goalpost_right=1212;
    }
    bool shoot_right=false,shoot_left=false,invisibleball=false,punch_left=false,punch_right=false;
    bool head_fire_ball_left=false,head_fire_ball_right=false;
    bool kick_fire_ball_left=false,kick_fire_ball_right=false;
    bool kick_fire_ball_collision_left=false;
    bool kick_fire_ball_collision_right=false;
    bool left_freeze=false,right_freeze=false;
    while(gamepage_bool)
    {
    SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
    SDL_RenderClear(m_renderer);
    time_of_now=time(NULL)-resume_time;
    game_time=game_fulltime-(time_of_now-time_at_first);
    dleft_double+=0.4; //power
    dleft=dleft_double;
    int q;
    if(dleft>100)
    {
        dleft=100;
    }
    dright_double+=0.4;
    dright=dright_double;
    if(dright>100)
    {
        dright=100;
    }
    const Uint8* key = SDL_GetKeyboardState(NULL);
    image(m_renderer,0,0,0,0,stadium);
    image(m_renderer,355,-10,150,150,"source//goal button.png");
    image(m_renderer,768,-10,150,150,"source//goal button.png");
    outputtext(m_renderer,403,38,50,50,0,0,0,to_string(goal_player_left));
    outputtext(m_renderer,816,38,50,50,0,0,0,to_string(goal_player_right));
    image(m_renderer,20,20,150,80,"source//playernameingamepagebutton.png");
    outputtext(m_renderer,40,23,100,50,0,0,0,playerleft_name);
    image(m_renderer,1110,20,150,80,"source//playernameingamepagebutton.png");
    outputtext(m_renderer,1130,23,100,50,0,0,0,playerright_name);
    image(m_renderer,500,0,270,100,"source//timebutton.png");
    outputtext(m_renderer,585,30,100,30,0,0,0,to_string(game_time));
    image(m_renderer,160,10,200,100,"source//power button.png");
    image(m_renderer,910,10,200,100,"source//power button.png");
    outputtext(m_renderer,200,30,120,30,0,255,100,playerleft_power);
    outputtext(m_renderer,950,30,120,30,0,255,100,playerright_power);
    boxRGBA(m_renderer,200,70,300,75,0,0,0,255);
    boxRGBA(m_renderer,950,70,1050,75,0,0,0,255);
    boxRGBA(m_renderer,200,70,200+dleft,75,0,255,0,255);
    boxRGBA(m_renderer,950,70,950+dright,75,0,255,0,255);
    SDL_PumpEvents();
    if (key[SDL_SCANCODE_LEFT] && !(x_right-x_left<=40 && x_right-x_left>=0 && abs(y_left-y_right)<=100) && !right_freeze) dx_right=-30;
    if (key[SDL_SCANCODE_RIGHT] && !(x_left-x_right<=40 && x_left-x_right>=0 && abs(y_left-y_right)<=100) && !right_freeze) dx_right=+30;
    if (key[SDL_SCANCODE_UP] && y_right>=500 && !right_freeze) dy_right=-45;
    if (key[SDL_SCANCODE_L] && !right_freeze)
    {
        player_right_picture="source//body_rightshoot.png";
        shoot_right=true;
    }
    if (time(NULL)-start_time_of_punch_left<=5 || time(NULL)-start_time_headfireball_left<=5 || time(NULL)-start_time_kickfireball_left<=5)
    {
            image(m_renderer,x_right+40,y_right-100,20,40,"source//!.png");
    }
    else
    {
        right_freeze=false;
    }
    if (key[SDL_SCANCODE_K] && dright==100 && !right_freeze)
    {
        if(playerright_power=="invisible ball" && x_right-x_ball<=45 && x_right-x_ball>=-40 && ((y_ball-y_right>=25 && y_ball-y_right<=50) || (y_ball-y_right>=-30 && y_ball-y_right<=0)))
        {
            dx_ball=-50;
            dy_ball=-10;
            dright_double=0;
            invisibleball=true;
            start_time_of_invisible_ball=time(NULL);
        }
        if(playerright_power=="punch")
        {
            punch_right=true;
            dright_double=0;
            x_bullet_right=x_right;
        }
        if(playerright_power=="head fire ball" && y_ball<=410)
        {
            x_right=x_ball+70,y_right=y_ball+50,dx_ball=-120,dy_ball=10;
            head_fire_ball_right=true;
            dright_double=0;
        }
        if(playerright_power=="kick fire ball" && x_right-x_ball<=45 && x_right-x_ball>=-40 && y_ball-y_right>=25 && y_ball-y_right<=50)
        {
            dx_ball=-150;
            dy_ball=-15;
            dright_double=0;
            player_right_picture="source//body_rightshoot.png";
            kick_fire_ball_right=true;
        }
        if(playerright_power=="thief")
        {
            q=time(NULL)%4;
            switch (q)
            {
                 case 0:
                 if(x_right-x_ball<=45 && x_right-x_ball>=-40 && ((y_ball-y_right>=25 && y_ball-y_right<=50) || (y_ball-y_right>=-30 && y_ball-y_right<=0)))
                 {
                      dx_ball=-50;
                      dy_ball=-10;
                      dright_double=0;
                      invisibleball=true;
                      start_time_of_invisible_ball=time(NULL);
                 }
                 break;
                 case 1:
                 {
                      punch_right=true;
                      dright_double=0;
                      x_bullet_right=x_right;
                 }
                 break;
                 case 2:
                 if(y_ball<=410)
                 {
                      x_right=x_ball+70,y_right=y_ball+50,dx_ball=-120,dy_ball=10;
                      head_fire_ball_right=true;
                      dright_double=0;
                 }
                 break;
                 case 3:
                 if(x_right-x_ball<=45 && x_right-x_ball>=-40 && y_ball-y_right>=25 && y_ball-y_right<=50)
                 {
                      dx_ball=-150;
                      dy_ball=-15;
                      dright_double=0;
                      player_right_picture="source//body_rightshoot.png";
                      kick_fire_ball_right=true;
                 }
            }
        }
    }
    if (key[SDL_SCANCODE_A] && !(x_left-x_right<=40 && x_left-x_right>=0 && abs(y_left-y_right)<=100) && !left_freeze) dx_left=-30;
    if (key[SDL_SCANCODE_D] && !(x_right-x_left<=40 && x_right-x_left>=0 && abs(y_left-y_right)<=100)&& !left_freeze) dx_left=+30;
    if (key[SDL_SCANCODE_W] && y_left>=500 && !left_freeze) dy_left=-45;
    if (key[SDL_SCANCODE_F] && !left_freeze)
    {
        player_left_picture="source//body_leftshoot.png";
        shoot_left=true;
    }
    if (time(NULL)-start_time_of_punch_right<=5 || time(NULL)-start_time_headfireball_right<=5 || time(NULL)-start_time_kickfireball_right<=5)
    {
        image(m_renderer,x_left+30,y_left-100,20,40,"source//!.png");
    }
    else
    {
        left_freeze=false;
    }
    if (key[SDL_SCANCODE_G] && dleft==100)
    {
        if(playerleft_power=="invisible ball" && x_ball-x_left<=80 && x_ball-x_left>=40 && ((y_ball-y_left>=25 && y_ball-y_left<=50) || (y_ball-y_left<=0 && y_ball-y_left>=-30)))
        {
        dx_ball=40;
        dy_ball=-40;
        Mix_PlayChannel(-1,shoot,0);
        dleft_double=0;
        invisibleball=true;
        start_time_of_invisible_ball=time(NULL);
        }
        if(playerleft_power=="punch")
        {
            punch_left=true;
            dleft_double=0;
            x_bullet_left=x_left+96;
        }
        if (playerleft_power=="head fire ball" && y_ball<=410)
        {
            x_left=x_ball-70,y_left=y_ball+50,dx_ball=120,dy_ball=+10;
            head_fire_ball_left=true;
            dleft_double=0;
        }
        if(playerleft_power=="kick fire ball" && x_ball-x_left<=80 && x_ball-x_left>=40 && y_ball-y_left>=25 && y_ball-y_left<=50)
        {
            dx_ball=150;
            dy_ball=-15;
            dleft_double=0;
            player_left_picture="source//body_leftshoot.png";
            kick_fire_ball_left=true;
        }
        if(playerleft_power=="thief")
        {
            q=time(NULL)%4;
            switch (q)
            {
                  case 0:
                  if(x_ball-x_left<=80 && x_ball-x_left>=40 && ((y_ball-y_left>=0 && y_ball-y_left<=25) || (y_ball-y_left<=0 && y_ball-y_left>=-30)))
                  {
                         dx_ball=40;
                         dy_ball=-40;
                         Mix_PlayChannel(-1,shoot,0);
                         dleft_double=0;
                         invisibleball=true;
                         start_time_of_invisible_ball=time(NULL);
                  }
                  break;
                  case 1:
                          punch_left=true;
                          dleft_double=0;
                          x_bullet_left=x_left+96;
                  break;
                  case 2:
                  if (y_ball<=410)
                  {
                          x_left=x_ball-70,y_left=y_ball+50,dx_ball=120,dy_ball=+10;
                          head_fire_ball_left=true;
                          dleft_double=0;
                  }
                  case 3:
                  if(x_ball-x_left<=80 && x_ball-x_left>=40 && y_ball-y_left>=25 && y_ball-y_left<=50)
                  {
                           dx_ball=150;
                           dy_ball=-15;
                           dleft_double=0;
                           player_left_picture="source//body_leftshoot.png";
                           kick_fire_ball_left=true;
                   }
            }
        }
    }
    if(y_ball<535)
    {
    dy_ball+=4;
    }
    if(y_ball>=535)
    {
        dy_ball=-0.6*abs(dy_ball);
    }
    if(x_ball<=0)
    {
        dx_ball=abs(dx_ball);
    }
    if(x_ball>=1250)
    {
        dx_ball=-abs(dx_ball);
    }
    if(y_ball-530>=0 && dx_ball!=0)
    {
        dx_ball*=0.9;
        m++;
    }
    if(dx_ball<-2)
    {
    switch(m%4)
    {
    case 0:
    ball_picture="source//ball1.png";
    break;
    case 1:
    ball_picture="source//ball2.png";
    break;
    case 2:
    ball_picture="source//ball3.png";
    break;
    case 3:
    ball_picture="source//ball4.png";
    break;
    }
    }
    if(dx_ball>2)
    {
    switch(m%4)
    {
    case 0:
    ball_picture="source//ball1.png";
    break;
    case 1:
    ball_picture="source//ball4.png";
    break;
    case 2:
    ball_picture="source//ball3.png";
    break;
    case 3:
    ball_picture="source//ball2.png";
    break;
    }
    }
    if(m==100)
    {
        m=0;
    }
    if (head_fire_ball_left && x_right-x_ball>=30 && x_right-x_ball<=5 && y_ball-y_right>=-20 && y_ball-y_right<=100)
    {
        x_right+=200,head_fire_ball_left=false,dx_ball=-0.6*abs(dx_ball),start_time_headfireball_left=time(NULL);
        right_freeze=true;
    }
    if (head_fire_ball_left && x_ball>=1150)
    {
         head_fire_ball_left=false,dx_ball*=0.6;
    }
    if (head_fire_ball_right && x_ball-x_left>=60 && x_ball-x_left<=5 && y_ball-y_left>=-20 && y_ball-y_left<=100)
    {
        x_left-=200,head_fire_ball_right=false,dx_ball=0.6*abs(dx_ball),start_time_headfireball_right=time(NULL);
        left_freeze=true;
    }
    if (head_fire_ball_right && x_ball<=80)
    {
         head_fire_ball_left=false,dx_ball*=0.6;
    }
    if (kick_fire_ball_left && x_right-x_ball<=60 && x_right-x_ball>=-60 && y_ball-y_right>=-20 && y_ball-y_right<=100)
    {
        x_right+=200,dx_ball=-0.6*abs(dx_ball),start_time_kickfireball_left=time(NULL);
        kick_fire_ball_collision_right=true;
        right_freeze=true;
    }
    if (kick_fire_ball_left && x_ball>=1150)
    {
         kick_fire_ball_left=false,dx_ball*=0.6;
    }
    if (kick_fire_ball_right && x_ball-x_left<=80 && x_ball-x_left>=-40 && y_ball-y_left>=-20 && y_ball-y_left<=100)
    {
        x_left-=200,dx_ball=0.6*abs(dx_ball),start_time_kickfireball_right=time(NULL);
        kick_fire_ball_collision_left=true;
        left_freeze=true;
    }
    if(x_ball-x_left<=80 && x_ball-x_left>=-10 && y_ball-y_left<=100 && y_ball-y_left>=-90 && !kick_fire_ball_left && !kick_fire_ball_right)
    {
        dx_ball=abs(dx_ball)+dx_left;
    }
    if(x_left-x_ball<=35 && x_left-x_ball>=10 && y_ball-y_left<=100 && y_ball-y_left>=-90 && !kick_fire_ball_left && !kick_fire_ball_right)
    {
        dx_ball=-abs(dx_ball)+dx_left;
    }
    if(x_right-x_ball<=45 && x_right-x_ball>=-45 && y_ball-y_right<=100 && y_ball-y_right>=-90 && !kick_fire_ball_left && !kick_fire_ball_right)
    {
        dx_ball=-abs(dx_ball)+dx_right;
        if (dx_ball>0)
            dx_ball=0;
    }
    if(x_ball-x_right<=80 && x_ball-x_right>=45 && y_ball-y_right<=100 && y_ball-y_right>=-90 && !kick_fire_ball_left && !kick_fire_ball_right)
    {
        dx_ball=abs(dx_ball)+dx_right;
    }
    if(x_ball-x_right<=60 && x_ball-x_right>=-20&& y_right-y_ball>=0 && y_right-y_ball<=100 && !kick_fire_ball_left && !kick_fire_ball_right)
    {
        dy_ball=-dy_ball+2*dy_right;
    }
    if(kick_fire_ball_collision_left)
    {
        dx_ball*=0.9;
    }
    if(kick_fire_ball_collision_right)
    {
        dx_ball*=0.9;
    }
    if(dx_ball==0)
    {
        kick_fire_ball_collision_left=false;
        kick_fire_ball_collision_right=false;
        kick_fire_ball_left=false;
        kick_fire_ball_right=false;
    }
    if(shoot_left && x_ball-x_left<=80 && x_ball-x_left>=40 && y_ball-y_left>=0 && y_ball-y_left<=25)
    {
        dx_ball=40;
        dy_ball=-40;
        Mix_PlayChannel(-1,shoot,0);
    }
    if(y_ball<=0)
    {
        dy_ball=abs(dy_ball);
    }
    if(shoot_right && x_right-x_ball<=40 && x_right-x_ball>=0 && y_ball-y_right>=0 && y_ball-y_right<=25)
    {
        dx_ball=-40;
        dy_ball=-40;
        Mix_PlayChannel(-1,shoot,0);
    }
    if(shoot_left && x_ball-x_left<=80 && x_ball-x_left>=40 && y_ball-y_left>=25 && y_ball-y_left<=50)
    {
        dx_ball=50;
        dy_ball=-15;
        Mix_PlayChannel(-1,shoot,0);

    }
    if(shoot_right && x_right-x_ball<=40 && x_right-x_ball>=0 && y_ball-y_right>=25 && y_ball-y_right<=50)
    {
        dx_ball=-50;
        dy_ball=-15;
        Mix_PlayChannel(-1,shoot,0);
    }
    if(shoot_right && x_right-x_ball<=40 && x_right-x_ball>=0 && y_ball-y_right>=50 && y_ball-y_right<=75)
    {
        dx_ball=-40;
        dy_ball=40;
        Mix_PlayChannel(-1,shoot,0);
    }
    if(shoot_left && x_ball-x_left<=80 && x_ball-x_left>=40 && y_ball-y_left>=50 && y_ball-y_left<=75)
    {
        dx_ball=40;
        dy_ball=40;
        Mix_PlayChannel(-1,shoot,0);
    }
    if(y_right<=500)
    {
        dy_right+=8;
    }
    if(y_left<=500)
    {
        dy_left+=8;
    }
    if(x_ball<=80 && y_ball>=275)
    {
        gamepage_bool=false;
        goal_bool=true;
        goal_player_right++;
        dleft_double+=40;
        Mix_PlayChannel(-1,goaleffect,0);
    }
    if(x_ball<=80 && y_ball<=270)  Mix_PlayChannel(-1,foul,0);
    if(x_ball>=1200 && y_ball>=275)
    {
        gamepage_bool=false;
        goal_bool=true;
        goal_player_left++;
        dright_double+=40;
        Mix_PlayChannel(-1,goaleffect,0);
    }
    if(x_ball>=1200 && y_ball<=270)  Mix_PlayChannel(-1,foul,0);
    if(x_ball>=1150 && y_ball>=230 && y_ball<=280)
    {
        dx_ball=-abs(dx_ball);  Mix_PlayChannel(-1,foul,0);
    }
    if(x_ball<=110 && y_ball>=230 && y_ball<=280)
    {
        dx_ball=abs(dx_ball);    Mix_PlayChannel(-1,foul,0);
    }
    if(game_time<=0 || goal_player_left==goal || goal_player_right==goal || (goal_player_left==(goal-1) && goal_player_right==(goal-1)))
    {
        gamepage_bool=false;
        gameend_bool=true;
    }
    y_ball+=dy_ball;
    x_ball+=dx_ball;
    x_right+=dx_right;
    x_left+=dx_left;
    y_right+=dy_right;
    y_left+=dy_left;
    dx_left=0;
    dx_right=0;
    if(y_right>=500)
    {
        dy_right=0;y_right=505;
    }
    if(y_left>=500)
    {
        dy_left=0;y_left=505;
    }
    image(m_renderer,600,700,80,80,"source//pause button.png");
    if(!invisibleball)
    {
    image(m_renderer,x_ball,y_ball,46,46,ball_picture);
    }
    image(m_renderer,x_left,y_left,90,90,player_left_picture);
    image(m_renderer,x_left+5,y_left-65,72,88,playerleft_head);
    image(m_renderer,x_right,y_right,90,90,player_right_picture);
    image(m_renderer,x_right+13,y_right-65,72,88,playerright_head);
    image(m_renderer,x_goalpost_right,278,70,355,"source//goalpost_right.png");
    image(m_renderer,x_goalpost_left,278,70,355,"source//goalpost_left.png");
    if (punch_left && x_bullet_left-x_left<=150) image(m_renderer,x_left,y_left,100,50,"source/gun.png");
    if (punch_left) {image(m_renderer,x_bullet_left,y_left+18,10,5,"source/bullet.png");x_bullet_left+=45;}
    if (x_bullet_left>=x_right) {start_time_of_punch_left=time(NULL);punch_left=false;x_bullet_left=-100;right_freeze=true;}
    if (punch_right && x_right-x_bullet_right<=105) image(m_renderer,x_right,y_right,100,50,"source/gun1.png");
    if (punch_right) {image(m_renderer,x_bullet_right,y_right+18,10,5,"source/bullet1.png");x_bullet_right-=45;}
    if (x_bullet_right<=x_left+80) {start_time_of_punch_right=time(NULL);punch_right=false;x_bullet_right=1400;left_freeze=true;}
    if(time(NULL)-start_time_of_invisible_ball>=5)
    {
        invisibleball=false;
    }
    if(player_left_picture!="source//body_leftplay.png")
    {
        player_left_picture="source//body_leftplay.png";
        shoot_left=false;
    }
    if(player_right_picture=="source//body_rightshoot.png")
    {
        player_right_picture="source//body_rightplay.png";
        shoot_right=false;
    }
    if (event->type==SDL_MOUSEBUTTONDOWN)
    {
            if (event->button.x>=600 && event->button.x<=680 && event->button.y>=700 && event->button.y<=780)
            {
                 long long int pause_time=time(NULL);
                 bool pause_bool=true;
                 boxRGBA(m_renderer,0,0,1280,800,0,0,0,200);
                 image(m_renderer,550,360,80,80,"source//resume button.png");
                 image(m_renderer,650,360,80,80,"source//exit button.png");
                 SDL_RenderPresent(m_renderer);
                 while(pause_bool)
                 {
                     SDL_PollEvent(event);
                     if(event->type==SDL_MOUSEBUTTONDOWN)
                     {
                         if(event->button.x>=550 && event->button.x<=630 && event->button.y>=360 && event->button.y<=440)
                         {
                             resume_time+=(time(NULL)-pause_time);
                             pause_bool=false;
                         }
                         if(event->button.x>=650 && event->button.x<=730 && event->button.y>=360 && event->button.y<=440)
                         {
                             pause_bool=false;
                             gamepage_bool=false;
                             menu_bool=true;
                         }
                     }
                 }
            }
    }
    SDL_RenderPresent(m_renderer);
    SDL_PollEvent(event);
    }
}
int main( int argc, char * argv[] )
{
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;
    TTF_Init();
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( 1280, 800, WND_flags, &m_window, &m_renderer );
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048);
    SDL_RaiseWindow(m_window);
    SDL_Event *event=new SDL_Event();
    while(event->key.keysym.sym!=SDLK_ESCAPE)
    {
    SDL_PollEvent(event);
    if(menu_bool)
    {
       menu(m_renderer);
    }
    if(setting_bool)
    {
       setting(m_renderer);
    }
    if(league_bool)
    {
       league(m_renderer);
    }
    if(secondpage_bool)
    {
       secondpage(m_renderer);
    }
    if(gamepage_bool)
    {
       gamepage(m_renderer);
    }
    if(goal_bool)
    {
        gamepage_bool=true;
    }
    if(gameend_bool)
    {
        gameend(m_renderer);
    }
    }
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
	IMG_Quit();
	SDL_Quit();
    return 0;

}
