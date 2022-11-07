#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define MAX_num 10
typedef int status;
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct{  //链表的集合类型定义
    struct { 
		char name[30];
        LinkList L;    
    } elem[MAX_num]; 
    int length;
}LISTS;
LISTS Lists;
status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
status LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status SaveList(LinkList L,char FileName[]);
status LoadList(LinkList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
status LocateList(LISTS Lists,char ListName[]);
status InputList(LinkList &L);
status ListDeleteAll(LinkList &L, int &e);
status ListDeleteBack(LinkList &L, int &e); 
int cmp1(int a, int b);
int cmp2(int a, int b);
status ListSort(LinkList &L, int (*pcmp)(int a, int b));
status MergeList(LinkList L1, LinkList &L2);
int main(){
	char FileName[30],ListName[30];
	int e,pre,next,i,val,summ;
	e = pre = next = -1;
	int (*pf1)(int a, int b);
	int (*pf2)(int a, int b);
	pf1 = cmp1;
	pf2 = &cmp2;
	int i_num = 9;//正在操作的线性表 
	int op = 1;//菜单
	while(op){
		system("cls");	//清屏 
		printf("\n\n");
		printf("      Menu for Linked Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList         13. SaveList\n");
		printf("    	  2. DestroyList      14. LoadList\n");
		printf("    	  3. ClearList        15. AddList\n");
		printf("    	  4. ListEmpty        16. RemoveList\n");
		printf("    	  5. ListLength       17. LocateList\n");
		printf("    	  6. GetElem          18. ChooseList\n");
		printf("    	  7. LocateElem       19. InputList\n");
		printf("    	  8. PriorElem        20. ListDeleteAll\n");
		printf("    	  9. NextElem         21. ListDeleteBack\n");	
		printf("    	  10. ListInsert      22. ListSort\n");
		printf("    	  11. ListDelete      23  MergeList\n");
		printf("    	  12. ListTraverse\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0-23]:\n");
		scanf("%d", &op);
		switch(op){
			case 1://1是初始化链表 
				if(InitList(Lists.elem[i_num].L) == OK) {
					printf("请输入要保存的线性表的名称\n");
					scanf("%s",Lists.elem[i_num].name);
					printf("线性表创建成功\n"); 
				}
				else {
					printf("线性表已经存在\n"); 
					printf("线性表创建失败\n");
				}
				getchar();getchar();
				break; 
			case 2://2是销毁链表 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				} 
				if(DestroyList(Lists.elem[i_num].L) == OK){
					printf("线性表销毁成功\n"); 
					if(Lists.length != 0)
						Lists.length --; //线性表数目减一 
				}
				else printf("线性表销毁失败\n");
				getchar(); getchar();
				break;
			case 3://3是清空链表 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				if(ClearList(Lists.elem[i_num].L) == OK)
         			printf("线性表清空成功\n"); 
				else printf("线性表清空失败\n");
				getchar(); getchar();
				break;
			case 4://4是判断是否是空链表 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				if(ListEmpty(Lists.elem[i_num].L) == TRUE){
         			printf("线性表为空\n"); 
				}
				else printf("线性表不是空表\n");
				getchar(); getchar();
				break;
			case 5:
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				printf("线性表表长为: %d\n",ListLength(Lists.elem[i_num].L));
         		getchar(); getchar();
         		break;
         	case 6://6是获取元素 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				printf("请输入要取元素的位置:\n");
				scanf("%d",&i);
				if(GetElem(Lists.elem[i_num].L,i,e) == OK)
					printf("第%d个位置元素是:%d\n",i,e);
				else 
					printf("输入位置不合法\n");
				getchar(); getchar();
				break;
			case 7://7查找元素 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				printf("请输入数据元素的值：\n");
				scanf("%d", &e);
				if(i = LocateElem(Lists.elem[i_num].L,e)){
					printf("%d元素位于第%d个位置\n",e,i);
				} 
				else printf("%d元素在线性表中不存在\n",e);
				getchar(); getchar();
				break; 
			case 8://8是求数据元素的前驱
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				printf("请输入数据元素：\n");
				scanf("%d",&e);
				val = PriorElem(Lists.elem[i_num].L,e,pre);
				if(val == OK)
		 			printf("前驱元素为：%d\n",pre);
		 		else if(val == -2)
		 			printf("第一个元素不存在前驱元素！\n");
		 		else  printf("线性表中没有该元素！\n");
		 		getchar();getchar();
		 		break;
			case 9://9是求后继元素
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				} 
				printf("请输入数据元素：\n");
				scanf("%d",&e);
				val = NextElem(Lists.elem[i_num].L,e,next);
				if(val == OK) 
					printf("%d的后继元素是：%d",e,next);
				else if(val == ERROR)
					printf("该元素不存在后继元素");
				else 
					printf("线性表中没有该元素");
				getchar(); getchar();
				break;
			case 10://10是在链表中插入元素 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				printf("请输入您要插入的元素:\n");
         		scanf("%d",&e);
         		printf("请输入您要插入元素的位置:\n");
				scanf("%d",&i);
				val = ListInsert(Lists.elem[i_num].L,i,e);
				if(val == OK)
					printf("插入数据成功\n");
				else 
					printf("插入元素失败：\n");
				getchar(); getchar();
				break;
			case 11://11是从链表中删除元素 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
			 	}
				printf("请输入您要删除的元素的位置：\n");
				scanf("%d", &i);
				val = ListDelete(Lists.elem[i_num].L,i,e);
				if(val == OK){
					printf("删除的元素是：%d\n",e);
					printf("删除成功！\n");
				}
				else 
					printf("删除失败\n");
				getchar(); getchar();
				break;
			case 12://12是遍历链表 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
			 	}
			 	if(ListEmpty(Lists.elem[i_num].L) == TRUE )
         			printf("线性表是空表，没有数据元素\n");
				else if(ListTraverse(Lists.elem[i_num].L) == OK)
					printf("\n线性表遍历成功\n");
				else 
					printf("线性表遍历失败\n");
				getchar(); getchar();
				break;
			case 13://13是将链表保存到文件中  
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
			 	}
				printf("请输入您想保存的文件名：\n");
         		scanf("%s",FileName);
				val = SaveList(Lists.elem[i_num].L, FileName);
				if(val == OK) 
					printf("文件保存成功\n文件名是%s\n",FileName);
				else 
					printf("保存失败");
				getchar(); getchar();
				break;
			case 14:
				printf("请输入要加载的文件名：\n");
				scanf("%s",FileName);
				val = LoadList(Lists.elem[i_num].L, FileName); 
				if(val == OK) 
					printf("文件加载成功\n");
				else 
					printf("文件加载失败\n");
				getchar(); getchar();
				break;
			case 15:
				printf("请输入要加入的线性表的名称\n");
				scanf("%s",ListName); 
				val = AddList(Lists,ListName);
				if(val == OK)	
					printf("线性表%s成功加入线性表集合\n",ListName);
				else 
					printf("线性表集合中已经有名为%s的线性表\n线性表加入失败\n",ListName);
				getchar(); getchar();
				break;	
			case 16:
				printf("请输入要删除线性表的名称\n");
				scanf("%s",ListName);
				val = RemoveList(Lists,ListName);
				if(val == OK)
					printf("线性表%s删除成功\n", ListName);
				else
					printf("线性表集合中不存在%s线性表", ListName);
				getchar(); getchar();
				break;
			case 17://17是查找链表 
				printf("请输入要查找的线性表的名称：\n");
				scanf("%s",ListName);
				val = LocateList(Lists, ListName);
				if(val == 0)
					printf("线性表集合中不存在%s线性表\n", ListName);
				else
					printf("%s线性表位于线性表集合中第%d个位置\n",ListName,val);
				getchar(); getchar();
				break;
			case 18://18是选择操作的链表
				printf("请选择您要操作的线性表：\n"); 
				scanf("%d",&i_num);
				i_num --;
				printf("当前正在第%d个线性表进行操作\n",i_num+1); 
				getchar(); getchar();
				break;
			case 19://19是输入元素
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				} 
				if( !ListEmpty(Lists.elem[i_num].L)){
					printf("当前链表不是空表，请选择一个空链表进行输入操作\n");	
					getchar(); getchar();
					break;
				}	
				printf("请输入一系列以-1结尾的元素\n");
				val = InputList(Lists.elem[i_num].L);
				if(val == OK){
					printf("元素输入成功\n");
					getchar(); getchar();
					break;
				}
			case 20://20是删除链表中某个所有元素 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				printf("请输入要删除的数据元素：\n");
				scanf("%d", &e);
				val = ListDeleteAll(Lists.elem[i_num].L,e);
				if(val == 0)
					printf("该链表中没有%d元素\n",e);
				else 
					printf("删除成功！\n");
				getchar(); getchar();
				break;
			case 21://21是删除链表的最后一个元素 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				val = ListDeleteBack(Lists.elem[i_num].L, e);
				if(val == -2)
					printf("链表是空表，删除失败！\n");
				else
					printf("删除成功！");
				getchar(); getchar();
				break;	
			case 22://22是将链表中元素按照升序或者降序的方式进行排列 
				if(Lists.elem[i_num].L == NULL){
					printf("线性表不存在\n");
					getchar(); getchar();
					break; 
				}
				printf("将对链表进行排列，请输入您需要的排列的方式:\n(1代表升序排列，2代表降序排列)\n") ;
				int m;
				scanf("%d", &m);
				if(m == 1)
					val = ListSort(Lists.elem[i_num].L, pf1);
				else if(m == 2)
					val = ListSort(Lists.elem[i_num].L, pf2);
				else printf("输入错误，只能输入1或2\n");
				if(val == OK&&m == 1)
					printf("升序排列成功\n");
				if(val == OK&&m == 2) 
					printf("降序排列成功\n");
				if(val == ERROR)
					printf("链表中没有元素，请不要选择空链表进行排序操作\n");
				getchar(); getchar();
				break;	
			case 23:
				char listname1[30], listname2[30];
				int pos1, pos2;
				printf("请输入您想归并的两个线性表的名称：\n");
				scanf("%s",listname1);
				scanf("%s",listname2);
			 	pos1 = LocateList(Lists,listname1);//1
			 	pos2 = LocateList(Lists,listname2);//2
				if(!pos1 || !pos2){
			 		printf("您想归并的线性表不存在\n");
			 		getchar(); getchar();
			 		break;
				}
				val = MergeList(Lists.elem[pos1-1].L, Lists.elem[pos2-1].L);
				if(val)
				 	printf("线性表归并成功");
				else
					printf("线性表归并失败");
				getchar(); getchar();
				break;			
			case 0:
				break;	
		}
	}
	return 0;
}

/***************************************************************
*函数名称：IntiaList
*函数功能：构造一个空的线性表
*函数参数：线性表L 
*注释：初始条件是线性表L不存在已存在；操作结果是构造一个空的线性表。若线性表已经存在，返回INFEASIBLE
*返回值类型：status类型
*时间复杂度：O(1) 
****************************************************************/
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L!= NULL)
        return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));//动态分配
	if(L == NULL)
		exit(OVERFLOW);//如果没有足够的空间，创建失败
	L->data = 0;
	L->next = NULL;//创建带有表头节点的链表，表头节点的数据域值为0
	return OK;

}

/***************************************************************
*函数名称：DestoryList
*函数功能：销毁线性表
*函数参数：线性表L 
*注释：初始条件是线性表L已存在；操作结果是销毁线性表L
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL)//表未初始化 不能销毁 
        return INFEASIBLE;
    LinkList p,q;
    p = L;
    while(p){//利用循环释放空间 
        q = p->next;
        free(p);
        p = q;
    }
    L = NULL; 
    return OK;
}

/***************************************************************
*函数名称：ClearList
*函数功能：清空顺序表
*函数参数：线性表L 
*注释：初始条件是线性表L已存在；操作结果是将L重置为空表。
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
   
    if(L == NULL) //表不存在 
        return INFEASIBLE;
    LinkList p, q;
    p = L->next;//销毁头结点之后的节点 
    while(p){
        q = p->next;
        free(p);
        p = q;
    }  
    L->next = NULL;
    return OK;

}

/***************************************************************
*函数名称：ListEmpty
*函数功能：判断线性表是否为空
*函数参数：线性表L 
*注释：初始条件是线性表L已存在；操作结果是若L为空表则返回TRUE,否则返回FALSE。
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)//表不存在 
        return INFEASIBLE;
    if(L->next==NULL)//头结点后是否有 
        return TRUE;
    else
        return FALSE;
}

/***************************************************************
*函数名称：ListLength
*函数功能：求线性表的表长
*函数参数：线性表L 
*注释：初始条件是线性表已存在；操作结果是返回L中数据元素的个数。
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    
    if(L == NULL) return INFEASIBLE;
    LinkList p, q;
    int length = 0;
    p = L->next;//从头结点之后的第一个节点开始计数 
    while(p){
        length++;
        p = p->next;
    }
    return length;//返回表长 

}

/***************************************************************
*函数名称：GetElem
*函数功能：得到某一个元素的值
*函数参数:线性表L，获取元素的位置，存储元素的e 
*注释：初始条件是线性表已存在，1≤i≤ListLength(L)；操作结果是用e返回L中第i个数据元素的值
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(i < 1)
        return ERROR;//位置不合法 
    LinkList p = L->next;
    int cnt = 1;
    while(p && cnt<i){
        p = p->next;
        cnt++;
    }
    if(!p||cnt>i)
        return ERROR;//位置不合法 
    else {
        e = p->data;//找到了 赋值 
        return OK;
    }
}

/***************************************************************
*函数名称：LocateElem
*函数功能：查找元素
*函数参数：线性表L，带查找元素e 
*注释：初始条件是线性表已存在；操作结果是返回L中第1个与e相等 
       的数据元素的位序，若这样的数据元素不存在，则返回值为0。
*返回值类型：int类型
*时间复杂度：O(n)
****************************************************************/
status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L ==NULL)
        return INFEASIBLE;
    int i = 0;
    LinkList p = L->next;
    while(p){
        i++;
        if(p->data == e){
            return i;//找到了，返回序号 
        }
        p = p->next;
    }
    return ERROR;
}

/***************************************************************
*函数名称：PriorElem
*函数功能：求元素的前驱
*函数参数：线性表L,待查找e，存储e的前驱pre 
*注释：初始条件是线性表L已存在；操作结果是若e是L的数据元素，且不是第一个，
       则用pre返回它的前驱，函数返回OK，否则操作失败，函数返回ERROR。
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    LinkList p, q;
    p = L->next;
    if(p == NULL)
        return ERROR;//空表 
    else
        q = p->next;
    if(p->data == e)
        return -2;//第一个元素没前驱 
    while(q){
        if(q->data == e){//找到了 
            pre = p->data;
            return OK;
        }
        p = p->next;
        q = q->next;
    }
    return ERROR;//表中不存在该元素 

}

/***************************************************************
*函数名称：NextElem
*函数功能：求后继节点
*函数参数：线性表L，所查找元素e，存储e的后继元素的变量next 
*输入输出：初始条件是线性表L已存在；操作结果是若e是L的数据元素，且不是最后一个，
           则用next返回它的后继,函数返回OK，否则操作失败，返回ERROR。
*返回值类型：status类型
时间复杂度：O(n) 
****************************************************************/
status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    LinkList p, q;
    int flag = 0;
    p = L->next;
    if(p == NULL)
        return ERROR;
    else
        q = p->next;
    while(q){
        if(p->data == e){
            next = q->data;
            flag = 1;
            break;
        }
        p = p->next;
        q = q->next;
    }
    if(q == NULL)
        return -2;//最后一个元素没有后继 
    if(flag)
        return OK;
    else 
        return ERROR;
}

/***************************************************************
*函数名称：ListInsert
*函数功能：插入元素
*函数参数：线性表L，待插入位置i，待插入元素e 
*注释：初始条件是线性表L已存在且非空，1≤i≤ListLength(L)+1；
*      操作结果是在L的第i个位置之前插入新的数据元素e
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(i < 0)
        return ERROR;
    int cnt = 1;
    LinkList p = L;
    LinkList q;
    while(p&&cnt<i){
        p=p->next;
        cnt++;
    }
    if(!p||cnt>i)
        return ERROR;
    q = (LinkList) malloc(sizeof(LNode));
    q->next = p->next;
    q->data = e;
    p->next = q;
    return OK;
}

/***************************************************************
*函数名称：ListDelete
*函数功能：删除元素
*函数参数：线性表L,待删除位置，存储待删除元素e 
*注释：初始条件是线性表L已存在且非空，1≤i≤ListLength(L)；
*      操作结果：删除L的第i个数据元素，用e返回其值。
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    if(i<1) return ERROR;
    int cnt = 1;
    LinkList p = L;
    LinkList q = p->next;
    while(q&&cnt<i){
        p = p->next;
        q = q->next;
        cnt++;
    }
    if(cnt<i||!q)//位置不合法 
        return ERROR;
    e = q->data;
    p->next = q->next;//改变指针域 
    free(q);//释放空间 
    return OK;
}

/***************************************************************
*函数名称：ListTrabverse
*函数功能：遍历顺序表
*函数参数：线性表L 
*注释：输出顺序表的值
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
    LinkList p = L->next;
    while(p){
        if(p->next == NULL)
            printf("%d",p->data);
        else
            printf("%d ",p->data);
        p = p->next;
    }
    return OK;
}

/***************************************************************
*函数名称：SaveList
*函数功能：保存线性表
*函数参数： 线性表L,字符数组 FileName 
*注释：将线性表保存到文件中，
*返回值类型：status类型
*时间复杂度O(n) 
****************************************************************/
status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if(L == NULL)
        return INFEASIBLE;
	FILE *fp;
	if((fp = fopen(FileName, "w")) == NULL) return ERROR;
	LinkList p = L->next;
	while(p){
		fprintf(fp, "%d ", p->data);
		p = p->next;
	}
	fclose(fp);
	return OK;
}

/***************************************************************
*函数名称：LoadList
*函数功能：加载文件
*函数参数：线性表L,字符数组FileName 
*注释：加载文件
*返回值类型：status类型
*时间复杂度:O(n) 
****************************************************************/
status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{

    if(L != NULL)
        return INFEASIBLE;
	FILE *fp;
	if((fp = fopen(FileName, "r")) == NULL)
		return ERROR;
	L = (LinkList)malloc(sizeof(LNode));
	LinkList p = L;
	int dataa;
	while(1){
		if(fscanf(fp, "%d ", &dataa) == EOF)
			break;
		p->next = (LinkList)malloc(sizeof(LNode));
        p->next->data = dataa;
        p = p->next; 
	}
	p->next = NULL;
	fclose(fp);
	return OK;
}

/***************************************************************
*函数名称：AddList
*函数功能：Lists中增加一个名称为ListName的空线性表
*函数参数：线性表集合Lists，字符数组ListName 
*注释：初始条件是有Lists线性表集合 
*返回值类型：status类型
*时间复杂度: 
****************************************************************/
status AddList(LISTS &Lists,char ListName[])
// 在Lists中增加一个名称为ListName的空线性表
{
    if(strlen(ListName) > 30 ) return ERROR;//名字太长了 
    for(int i = 0; i < Lists.length; i++){
    	if(!strcmp(ListName,Lists.elem[i].name))
    		return ERROR;
	}
    strcpy(Lists.elem[Lists.length].name,ListName); //保存空线性表的名字 
    int flag = InitList(Lists.elem[Lists.length].L);//创建空线性表 
    if(flag) {//成功创建空表 
    	Lists.length ++;//线性表个数 +1
    	return OK;
	}
    else return ERROR;//增加失败 
}

/***************************************************************
*函数名称：RemoveList
*函数功能：Lists中删除一个名称为ListName的空线性表
/函数参数：线性表集合Lists，字符数组ListName 
*注释：初始条件是有Lists线性表集合 
*返回值类型：status类型
*时间复杂度:
****************************************************************/
status RemoveList(LISTS &Lists,char ListName[])
{
	if(Lists.length == 0) return ERROR;//如果有0个表，没法删 
    int flag = 0;//判断是否删除成功 
    for(int i = 0; i < Lists.length; i++){
        if(strcmp(ListName,Lists.elem[i].name) == 0){//找到名字叫 ListName的线性表 
            for(int j = i; j < Lists.length-1; j++){//移动线性表，结构可以直接赋值 
                Lists.elem[j] = Lists.elem[j+1];
            }
            Lists.length -- ;//线性表数量-1
            flag = 1;//删除成功 
            break;
        }
        else continue;//继续找 
    }
    if(flag) return OK;//成功删除 
    else return ERROR;//没找到 
}

/***************************************************************
*函数名称：LocateList
*函数功能：Lists中查找一个名称为ListName的空线性表
*函数参数：线性表集合Lists，字符数组ListName 
*注释：初始条件是有Lists线性表集合 
*返回值类型：status类型
*时间复杂度:O(n)
****************************************************************/
status LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    int loc = -1,flag = 0;//loc记录位置，flag记录是否有 ListName线性表 
    for(int i = 0; i < Lists.length; i++){
        if(strcmp(ListName,Lists.elem[i].name) == 0){//找到 ListName线性表
            flag = 1;
            loc = i;
            break;
        }
        else continue;//这个不是，找下一个 
    }
    if(flag) return loc + 1;//找到返回逻辑位置 
    else return 0;//没找到返回0 
}

/************************************************************
*函数名称：InputList
*函数功能：在空线性表中输入元素 
*函数参数：线性表L 
*注释：初始条件是线性表L存在且为空 
*返回值类型：status类型
*时间复杂度:O(n) 
****************************************************************/
status InputList(LinkList &L){
	if(L == NULL)
		return INFEASIBLE;
	int num = 0;
	LinkList p = L;
	LinkList q;
	while(1){
		scanf("%d", &num);
		if(num == -1)
			break;
		q = (LinkList)malloc(sizeof(LNode));
		q->next = NULL;
		q->data = num;
		p->next = q;
		p = q;
	}
	return OK;
}

/************************************************************
*函数名称：ListDeleteAll
*函数功能：在链表中删除所有的元素e 
*函数参数：线性表L ，待删除元素e 
*注释：初始条件是线性表L存在
*返回值类型：status类型
*时间复杂度:O(n) 
****************************************************************/
status ListDeleteAll(LinkList &L, int &e){
	if(L == NULL)
        return INFEASIBLE;
    LinkList p = L->next;
    LinkList q = L;
    LinkList r; 
    int flag = 0;
    while(p){
    	if(p->data == e){
    		q->next = p->next;
    		r = p;
    		p = p->next;
			free(r);
    		flag = 1;
		}
 		else {
			p = p->next;
			q = q->next;
		}
	}
	if(!flag)
		return ERROR;
	else return OK;	
}

/************************************************************
*函数名称：ListDeleteBack
*函数功能：在链表中删除最后一个元素，最后一个元素赋值给e 
*函数参数：线性表L ，e 
*注释：初始条件是线性表L存在且不为空表 
*返回值类型：status类型
*时间复杂度:O(n) 
****************************************************************/
status ListDeleteBack(LinkList &L, int &e){
	if(L == NULL)
        return INFEASIBLE;
    LinkList p = L->next;
    if(p == NULL)
    	return -2;//空表 
    LinkList q = L;
    while(p->next){//找到最后一个节点 
    	p = p->next;
    	q = q->next;
	}
	e = p->data;//赋值给e 
	free(p);//释放空间 
	q->next = NULL;//修改指针域 
	return OK;
} 

/************************************************************
*函数名称：cmp
*函数功能：辅助比较函数 
*函数参数： 两个int类型的数 
*注释：无 
*返回值类型：int类型
*时间复杂度:O(1) 
****************************************************************/
int cmp1(int a, int b){
	return a > b;
} 
int cmp2(int a, int b){
	return a < b;
}
 
/************************************************************
*函数名称：ListSort
*函数功能：将链表中的元素按照升序或者降序的方式进行排序 
*函数参数：线性表L，函数指针pcmp 
*注释：初始条件是线性表L存在且不为空表 
*返回值类型：status类型
*时间复杂度:O(n2) 
****************************************************************/
status ListSort(LinkList &L, int (*pcmp)(int a, int b)){
	if(L == NULL)
		return INFEASIBLE;
	LinkList p = L->next;
	LinkList q = L->next;
	LinkList r;
	int t = -1;//中间变量 
	if(!p)
		return ERROR;
	for(; q; q = q->next){
		for(p = L->next; p&&p->next; p = p->next){
			r = p->next; //p的后继结点 
			if(pcmp(p->data, r->data)){//比较规则 
				t = r->data;
				r->data = p->data;
				p->data = t;
			}
		}
	}
	return OK;
}

/************************************************************
*函数名称：MergeList
*函数功能：将两个链表按照升序的方式归并 
*函数参数：线性表L1，线性表L2
*注释：初始条件是线性表L1，L2存在且不为空表 
*返回值类型：status类型
*时间复杂度:O(n2) 
****************************************************************/
status MergeList(LinkList L1, LinkList &L2){
	if(L1==NULL || L2==NULL)
		return INFEASIBLE;
	LinkList p1, p2, r;
	p1 = L1->next;
	int t;
	ListSort(L2, cmp1);
	while(p1){
		t = p1->data;
		p2 = L2;
		while(p2->next!=NULL && t > p2->next->data) p2=p2->next;
		r = (LinkList)malloc(sizeof(LNode));
		r->data = t;
		r->next = p2->next;
		p2->next = r;
		p1 = p1->next;
	}
	return OK;
} 





