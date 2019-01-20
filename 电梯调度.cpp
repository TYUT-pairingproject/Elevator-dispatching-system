#include<iostream>
#include<stdlib.h>
using namespace std;
/*乘客的结构体*/
struct passenger
{
    char name;
    int start;
    int end;
    int dir;
};

/*链表结构*/
typedef struct LNode
{
    passenger P;
    struct LNode *next;
}LNode, *LinkList;

/*将节点LN插入到链表C中，插入到头结点后面*/
void Insert(LNode *C, LNode *LN)
{
    LN->next = C->next;
    C->next = LN;
}

/*删除LN后的第一个节点*/
void del(LNode *LN)
{
    LNode *next2 = LN->next;
    LN->next = next2->next;
    free(next2);
}

/*在链表C中查找到与LN节点相同的节点，并删除*/
void finddel(LNode *LN, LinkList C)
{
    for (LNode *p = C; p->next != NULL; p = p->next)
    {
        if (p->next->P.name == LN->P.name)
        {
            del(p);
            break;
        }
    }
}

/*判断链表是否为空*/
bool isempty(LinkList L)
{
    if (L->next == NULL)
        return 1;
    else
        return 0;
}

/*当电梯运行方向为dir时，
将C中要进入电梯的节点全部存放至A中，按照进入电梯的顺序存放
并将其相应的存放在B中，按照离开电梯的顺序存放*/
void Insert2(LinkList A, LinkList B, LinkList C, int dir, int floor)
{
    for (LNode *p = C->next; p != NULL; p = p->next)
    {
        if (dir == 1 && p->P.start >= floor && p->P.dir == 1)
        {//查找出C中方向相同且起始楼层在电梯上方的所有节点 
            LNode *r = (LNode*)malloc(sizeof(LNode));
            LNode *s = (LNode*)malloc(sizeof(LNode));
            r->P = p->P;
            s->P = p->P;
            for (LNode *q = A; ; q = q->next)
            {//将该节点插入A中，确保其起始楼层为升序的方式 
                if (q->next == NULL || q->next->P.start >= r->P.start)
                {
                    Insert(q, r);
                    break;
                }
            }
            for (LNode *q = B; ; q = q->next)
            {//将该节点插入B中，确保其目标楼层为升序的方式 
                if (q->next == NULL || q->next->P.end >= s->P.end)
                {
                    Insert(q, s);
                    break;
                }
            }
        }
        else if (dir == 0 && p->P.start <= floor && p->P.dir == 0)
        {
            LNode *r = (LNode*)malloc(sizeof(LNode));
            LNode *s = (LNode*)malloc(sizeof(LNode));
            r->P = p->P;
            s->P = p->P;
            for (LNode *q = A; ; q = q->next)
            {
                if (q->next == NULL || q->next->P.start <= r->P.start)
                {
                    Insert(q, r);
                    break;
                }
            }

            for (LNode *q = B; ; q = q->next)
            {
                if (q->next == NULL || q->next->P.end <= s->P.end)
                {
                    Insert(q, s);
                    break;
                }
            }
        }
    }
}

int finds(int m, LinkList C, int dir)
{//确定出电梯行驶方向最后停留的楼层 
    if (dir == 1)
    {
        for (LNode *p = C->next; p != NULL; p = p->next)
        {
            if (m<p->P.start)
                m = p->P.start;
        }
    }
    else
    {
        for (LNode *p = C->next; p != NULL; p = p->next)
        {
            if (m>p->P.start)
                m = p->P.start;
        }
    }
    return m;
}

int main()
{
    LinkList C = (LNode*)malloc(sizeof(LNode));
    C->next = NULL;//C为存储所有的乘客信息的链表 
    LinkList A = (LNode*)malloc(sizeof(LNode));
    A->next = NULL;//A为存储某个行驶方向上，上电梯的所有乘客信息 
    LinkList B = (LNode*)malloc(sizeof(LNode));
    B->next = NULL;//B为A中乘客的按下电梯顺序排列 
    int floor;//记录电梯选择运行方向时所在的楼层 
    int dir;//记录电梯运行的方向 
    cout << "请输入电梯所在楼层：";
    while (cin >> floor)
    {
        /*输入乘客信息并创建链表,电梯运行的初始方向根据只要上方有乘客则向上*/
        cout << "请依次输入乘客代号、起始楼层、目标楼层、行驶方向：" << endl;
        char a;
        dir = 0;
        while (cin >> a)
        {
            LinkList x = (LNode*)malloc(sizeof(LNode));
            x->P.name = a;
            cin >> x->P.start >> x->P.end >> x->P.dir;
            Insert(C, x);
            if (x->P.start >= floor)
                dir = 1;
        }
        /*while(cin>>str)语句在结束输入时使用了Ctrl+Z，告诉cin用户已经结束了输入，
        为了让程序正常运行，调用cin.clear()让cin的所有条件状态位复位*/
        cin.clear();
        /*模拟电梯行驶过程*/
        while (!isempty(C))
        {//有乘客未乘坐电梯 
            Insert2(A, B, C, dir, floor);//将C中满足条件的乘客放入A、B中 
                                         /*乘客上下*/
            if (isempty(B))
                floor = finds(floor, C, dir);
            while (!isempty(B))
            {//模拟电梯往某个特定方向行驶的过程 
                if (dir == 1)
                {//当电梯是向上行驶时 
                    if ((A->next == NULL) || (A->next->P.start > B->next->P.end))
                    {//出电梯的情况 
                        cout << "当前楼层为" << B->next->P.end << "，"
                            << B->next->P.name << "出电梯" << endl;
                        finddel(B->next, C);//删除C中对应的乘客信息 
                        del(B);//删除链表中该乘客的信息 
                    }
                    else
                    {//进电梯的情况 
                        cout << "当前楼层为" << A->next->P.start << "，"
                            << A->next->P.name << "进电梯" << endl;
                        del(A);//删除链表中该乘客的信息
                    }
                }
                else
                {//当电梯是向下行驶时 
                    if ((A->next == NULL) || (A->next->P.start < B->next->P.end))
                    {
                        cout << "当前楼层为" << B->next->P.end << "，"
                            << B->next->P.name << "出电梯" << endl;
                        finddel(B->next, C);
                        del(B);
                    }
                    else
                    {
                        cout << "当前楼层为" << A->next->P.start << "，"
                            << A->next->P.name << "进电梯" << endl;
                        del(A);
                    }
                }
                if (B->next != NULL && B->next->next == NULL)
                {
                    floor = finds(B->next->P.end, C, dir);

                }
            }
            dir = !dir;//改变行驶方向
        }
        /**/
        cout << endl << endl;
        cout << "请输入电梯所在楼层：";
    }
    system("pause");
}
