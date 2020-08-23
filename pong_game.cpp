#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include<stdio.h>
#include<curses.h>
#include<sys/select.h>
#include<termio.h>
#include<stropts.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define HIDE_CURSOR() printf("\033[?25l")//隐藏光标
using namespace std;

//gotoxy in windows
/*
void gotoxy(){
	COORD coord = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
*/

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}




void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}



int main(){
	//1.初始化数据
	auto WIDTH{ 100 }, HEIGHT{ 30 };//窗口长度
        auto ball_x{ WIDTH/2 },ball_y{ HEIGHT/2 }, ball_vec_x {0},ball_vec_y {0};//球位置和速度
        auto paddle_w{4},paddle_h{10}; //挡板的长度
        auto paddle1_x{1},paddle1_y{HEIGHT/2 - paddle_h/2},paddle1_vec{3};//挡板1位置及速度
        auto paddle2_x{WIDTH - paddle_w},paddle2_y{HEIGHT/2 - paddle_h/2},paddle2_vec{3};//挡板2位置及速度
        auto score1{0},score2{0},score1_x{ paddle_w + 8 }, score1_y{ 2 },score2_x{ WIDTH -8 - paddle_w }, score2_y{ 2 };//双方得分	

	srand((unsigned)time(0));
	ball_vec_x = rand() % 3 + 1;
	ball_vec_y = rand() % 3 + 1;
	if(rand()% 2 == 1)ball_vec_x = -ball_vec_x;
	if(rand()% 2 == 1)ball_vec_y = -ball_vec_y;
     
        while(true){
		//1.处理事件
		char key;
		if(kbhit()!= 0){
			key = getch();
		        if((key == 'w') && paddle1_y > paddle1_vec)
				paddle1_y -= paddle1_vec;
		        else if ((key == 's') && paddle1_y + paddle1_vec +paddle_h < HEIGHT)
		                paddle1_y += paddle1_vec;
		        else if((key == 'i') && paddle2_y > paddle2_vec)
                                paddle2_y -= paddle2_vec;
		        else if ((key ==  'k') && paddle2_y + paddle2_vec +paddle_h < HEIGHT)
                                paddle2_y += paddle2_vec;
		}	
		//2.更新数据
		ball_x += ball_vec_x;
		ball_y += ball_vec_y;
		string s1 {to_string(score1)}, s2{to_string(score2)};
		if (ball_y < 0 || ball_x >= HEIGHT)//与上下墙碰撞,改变垂直速度
			ball_vec_y = -ball_vec_y;
                if (ball_x < paddle_w && ball_y >= paddle1_y && ball_y < paddle1_y + paddle_h)
		{ //和左挡板碰撞，改变水平速度的方向
			ball_vec_x = -ball_vec_x;
		}
		else if (ball_x > WIDTH - paddle_w && ball_y >= paddle2_y
			&& ball_y < paddle2_y + paddle_h)
		{ //和右挡板碰撞，改变水平速度的方向
			ball_vec_x = -ball_vec_x;
		}
                bool is_out{ false };              //是否跑出沟渠的bool标志
		if (ball_x < 0) { score2 += 1; is_out = true; }
		else if (ball_x > WIDTH ) { score1 += 1; is_out = true; }
		if (is_out) {                  //跑出左右沟渠，球回到中心并以新的随机速度出发
			ball_x = WIDTH / 2; ball_y = HEIGHT / 2;
			ball_vec_x = rand() % 3 + 1;
			ball_vec_y = rand() % 3 + 1;
			if (rand() % 2 == 1) ball_vec_x = -ball_vec_x;
			if (rand() % 2 == 1) ball_vec_y = -ball_vec_y;
		}
	        gotoxy (0,0);//定位到0,0 相当于清空屏幕
                HIDE_CURSOR();//隐藏光标
		
		//3.绘制场景
	
	        //3.1绘制背景
	
	        //3.1.1绘制顶部墙
		for (auto x = 0; x <= WIDTH; x++)
			cout << "=";
		cout << "\n";
        
	        //3.1.2绘制三条竖线,挡板以及球
	        for (auto y = 0; y <= HEIGHT; y++){
			for (auto x = 0; x <= WIDTH; x++){
				if (x == ball_x && y == ball_y )
					cout << "O";
				else if (y >= paddle1_y && y < paddle1_y+ paddle_h && x >= paddle1_x && x < paddle1_x+ paddle_w)
				        cout << "*";
			        else if (y >= paddle2_y && y < paddle2_y+ paddle_h && x >= paddle2_x && x < paddle2_x+ paddle_w)
				        cout << "*";
                                else if (x == score1_x && y == score1_y){
					cout << s1;
					while (x < score1_x + s1.size()) x++;
					x--;
				}
				else if (x == score2_x && y == score2_y){
					cout << s2;
                                        while (x < score2_x + s2.size()) x++;
                                        x--;
                                }
			        else if (x == 0 || x == WIDTH/2 || x == WIDTH)
				        cout << "|";
			        else cout << " ";
			}
			cout << "\n";
		}
	        //3.1.3绘制底部
		for (auto x = 0; x <= WIDTH; x++)
			cout << "=";
		cout << "\n";
	}
	return 0;
}

