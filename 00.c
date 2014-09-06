/*---------这是一个简单的小动画，模拟电视机屏保-------------
    在visual studio 2010下编写，调试 通过。
    由于图形绘制的相关教材都是在turbo上的调试的，turbo上的
<graphics.h>头文件在vs下并没有，所以我上网搜索了相关解决方法，
最后发现了EGE（Easy Graphics Engine）这个开源项目，他们所提供
的graphics.h在 vs 2010下很好的替代了 turbo 的 graphics.h 。
在看完项目主页上的入门教材及简单例子后，我仿照他们的框架写了这
个小动画。
感谢EGE项目组<http://tcgraphics.sourceforge.net/>
---------------------------------------------------------*/



#include <graphics.h>
#include<stdio.h>

//定义一个结构体，相关属性写在这个结构体里
struct AniObj
{
    float x, y;
	float dx, dy;
	int r;
	//樱花瓣相关变量

	float x1,y1;
	float dx1, dy1;
	int r1;
	//圆圈相关变量

	int p;//计数器

    int alpha, da;
    PIMAGE img;
};

//定义速度基准值，base_speed是最低速度，base_speed+randspeed是最高速度
const float base_speed = 0.5f;
const float randspeed = 2.5f;

//自定义函数，用来返回一个0 - m之间的浮点数
float myrand(float m)
{
    // randomf() 返回一个 0 到 1 之间的随机浮点数
    return (float)(randomf() * m);
}

//初始化，设置坐标，速度方向，透明度，创建IMAGE等
void initobj(AniObj* obj)
{
    // random(n) 返回一个 0 到 n 之间的随机整数(unsigned)
	//樱花相关属性变量初始化
	obj->x = myrand((float)getwidth());
    obj->y = myrand((float)getheight());
    obj->r = random(2) + 1;
    obj->dx = (int)random(2) * 2 - 1; 
    obj->dy = 0 ;
    obj->alpha = random(250) + 2;
    obj->da = (int)random(2) * 2 - 1;

	//圆圈相关属性变量初始化
	obj->x1=100;
	obj->y1=100;
	obj->r1=60;
	obj->dx1=2;
	obj->dy1=3;

	obj->p=1;//计数器初始化

    obj->img = newimage(obj->r * 2, obj->r * 2);

    setcolor(EGERGB(250,99,71), obj->img);//图形边缘颜色
    setfillcolor(EGERGB(250,99,71), obj->img);//图形填充色

    fillellipse(obj->r, obj->r, obj->r, obj->r, obj->img);
}

//更新位置等相关属性
void updateobj(AniObj* obj)
{
    // 当前位置 + 速度
    obj->x += obj->dx;
    obj->y += obj->dy;
	obj->dx = myrand(2); 
	obj->dy = myrand(3); 

	if (obj->x >= ege::getwidth()  - obj->r * 2) 
		(obj->x= myrand(getwidth()),obj->y=myrand(getheight())); //樱花碰右
	if (obj->y >= ege::getheight() - obj->r * 2) 
		(obj->x= myrand(getwidth()),obj->y=myrand(getheight())); //樱花碰下
	
	obj->x1 += obj->dx1;
	obj->y1 += obj->dy1;

	if (obj->x1 < obj->r1) 
	{
		obj->dx1 = myrand(randspeed) + base_speed;
		obj->p++;
	}//圈碰左
	if (obj->y1 < obj->r1) 
	{
		obj->dy1 = myrand(randspeed) + base_speed; 
		obj->p++;
	}//圈碰上
	if (obj->x1 >= ege::getwidth()  - obj->r1) 
	{
		obj->dx1 = -(myrand(randspeed) + base_speed);
		obj->p++;
	}//圈碰右
	if (obj->y1 >= ege::getheight() - obj->r1) 
	{
		obj->dy1 = -(myrand(randspeed) + base_speed); 
		obj->p++;
	}//圈碰下
    
	// 改变alpha值
    obj->alpha += obj->da;
    if (obj->alpha <= 0) 
		obj->da = 1;
    if (obj->alpha >= 0xFF) 
		obj->da = -1;
}

//根据属性值绘画
void drawobj(AniObj* obj)
{
    putimage_alphatransparent(NULL, obj->img, obj->x, obj->y, BLACK, (unsigned char)obj->alpha);

}

//释放这个对象时调用
void releaseobj(AniObj* obj)
{
    delimage(obj->img);
}

void mainloop()
{
    const int MAXOBJ = 1200;//同屏樱花数目
    AniObj obj[MAXOBJ]; //定义对象数组
    int n;
	char num[20];

    for (n = 0; n < MAXOBJ; ++n)
    {
        initobj(&obj[n]); //初始化
    }

    for ( ; is_run(); delay_fps(60) )
    {
        for (n = 0; n < MAXOBJ; ++n)
        {
            updateobj(&obj[n]); //更新位置
        }

        cleardevice();
        for (n = 0; n < MAXOBJ; ++n)
        {
            drawobj(&obj[n]); //绘画
        }

	//切换文字显示功能块
		if ((obj->p) % 2 == 0)
		{	char title[] = "XXXX";
			outtextxy(obj->x1-20, obj->y1-5, title);
		}
		else
		{	char title[] = "XXXXXXX";
			outtextxy(obj->x1-45, obj->y1-5, title);
		}

		sprintf(num, " %d ", obj->p);
		outtextxy(obj->x1-10, obj->y1+30, num);//计数器

		circle(obj->x1,obj->y1,obj->r1);//绘制圆圈
	}

    for (n = 0; n < MAXOBJ; ++n)
	{
		 releaseobj(&obj[n]); //释放
	}
}

int main(void)
{	
    setinitmode(INIT_ANIMATION);
    // 图形初始化，窗口尺寸480x640
    initgraph(480, 640);
	setcaption("XXXX by Fan");
	// 随机数初始化
    randomize();
    // 程序主循环
    mainloop();
    // 关闭绘图设备
    closegraph();
    return 0;
}
