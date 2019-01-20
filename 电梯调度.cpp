#include<iostream>
#include<stdlib.h>
using namespace std;
/*�˿͵Ľṹ��*/
struct passenger
{
    char name;
    int start;
    int end;
    int dir;
};

/*����ṹ*/
typedef struct LNode
{
    passenger P;
    struct LNode *next;
}LNode, *LinkList;

/*���ڵ�LN���뵽����C�У����뵽ͷ������*/
void Insert(LNode *C, LNode *LN)
{
    LN->next = C->next;
    C->next = LN;
}

/*ɾ��LN��ĵ�һ���ڵ�*/
void del(LNode *LN)
{
    LNode *next2 = LN->next;
    LN->next = next2->next;
    free(next2);
}

/*������C�в��ҵ���LN�ڵ���ͬ�Ľڵ㣬��ɾ��*/
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

/*�ж������Ƿ�Ϊ��*/
bool isempty(LinkList L)
{
    if (L->next == NULL)
        return 1;
    else
        return 0;
}

/*���������з���Ϊdirʱ��
��C��Ҫ������ݵĽڵ�ȫ�������A�У����ս�����ݵ�˳����
��������Ӧ�Ĵ����B�У������뿪���ݵ�˳����*/
void Insert2(LinkList A, LinkList B, LinkList C, int dir, int floor)
{
    for (LNode *p = C->next; p != NULL; p = p->next)
    {
        if (dir == 1 && p->P.start >= floor && p->P.dir == 1)
        {//���ҳ�C�з�����ͬ����ʼ¥���ڵ����Ϸ������нڵ� 
            LNode *r = (LNode*)malloc(sizeof(LNode));
            LNode *s = (LNode*)malloc(sizeof(LNode));
            r->P = p->P;
            s->P = p->P;
            for (LNode *q = A; ; q = q->next)
            {//���ýڵ����A�У�ȷ������ʼ¥��Ϊ����ķ�ʽ 
                if (q->next == NULL || q->next->P.start >= r->P.start)
                {
                    Insert(q, r);
                    break;
                }
            }
            for (LNode *q = B; ; q = q->next)
            {//���ýڵ����B�У�ȷ����Ŀ��¥��Ϊ����ķ�ʽ 
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
{//ȷ����������ʻ�������ͣ����¥�� 
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
    C->next = NULL;//CΪ�洢���еĳ˿���Ϣ������ 
    LinkList A = (LNode*)malloc(sizeof(LNode));
    A->next = NULL;//AΪ�洢ĳ����ʻ�����ϣ��ϵ��ݵ����г˿���Ϣ 
    LinkList B = (LNode*)malloc(sizeof(LNode));
    B->next = NULL;//BΪA�г˿͵İ��µ���˳������ 
    int floor;//��¼����ѡ�����з���ʱ���ڵ�¥�� 
    int dir;//��¼�������еķ��� 
    cout << "�������������¥�㣺";
    while (cin >> floor)
    {
        /*����˿���Ϣ����������,�������еĳ�ʼ�������ֻҪ�Ϸ��г˿�������*/
        cout << "����������˿ʹ��š���ʼ¥�㡢Ŀ��¥�㡢��ʻ����" << endl;
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
        /*while(cin>>str)����ڽ�������ʱʹ����Ctrl+Z������cin�û��Ѿ����������룬
        Ϊ���ó����������У�����cin.clear()��cin����������״̬λ��λ*/
        cin.clear();
        /*ģ�������ʻ����*/
        while (!isempty(C))
        {//�г˿�δ�������� 
            Insert2(A, B, C, dir, floor);//��C�����������ĳ˿ͷ���A��B�� 
                                         /*�˿�����*/
            if (isempty(B))
                floor = finds(floor, C, dir);
            while (!isempty(B))
            {//ģ�������ĳ���ض�������ʻ�Ĺ��� 
                if (dir == 1)
                {//��������������ʻʱ 
                    if ((A->next == NULL) || (A->next->P.start > B->next->P.end))
                    {//�����ݵ���� 
                        cout << "��ǰ¥��Ϊ" << B->next->P.end << "��"
                            << B->next->P.name << "������" << endl;
                        finddel(B->next, C);//ɾ��C�ж�Ӧ�ĳ˿���Ϣ 
                        del(B);//ɾ�������иó˿͵���Ϣ 
                    }
                    else
                    {//�����ݵ���� 
                        cout << "��ǰ¥��Ϊ" << A->next->P.start << "��"
                            << A->next->P.name << "������" << endl;
                        del(A);//ɾ�������иó˿͵���Ϣ
                    }
                }
                else
                {//��������������ʻʱ 
                    if ((A->next == NULL) || (A->next->P.start < B->next->P.end))
                    {
                        cout << "��ǰ¥��Ϊ" << B->next->P.end << "��"
                            << B->next->P.name << "������" << endl;
                        finddel(B->next, C);
                        del(B);
                    }
                    else
                    {
                        cout << "��ǰ¥��Ϊ" << A->next->P.start << "��"
                            << A->next->P.name << "������" << endl;
                        del(A);
                    }
                }
                if (B->next != NULL && B->next->next == NULL)
                {
                    floor = finds(B->next->P.end, C, dir);

                }
            }
            dir = !dir;//�ı���ʻ����
        }
        /**/
        cout << endl << endl;
        cout << "�������������¥�㣺";
    }
    system("pause");
}
