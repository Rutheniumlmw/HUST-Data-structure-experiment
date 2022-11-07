#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<queue> 
#include<iostream>
#include<math.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAX_num 10 
using namespace std;
typedef int status;
typedef int KeyType; 
typedef struct {
     KeyType  key;
     char others[20];
} TElemType; //二叉树结点类型定义
typedef struct BiTNode{    //二叉链表结点的定义
      TElemType data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
typedef struct{  //树的集合类型定义
    struct { 
		char name[30];
        BiTree T;    
    }elem[MAX_num]; 
    int length;
}TREES;
TREES Trees;

status MakeChild(BiTree &t, TElemType definition[]);
status CreateBiTree(BiTree &T,TElemType definition[]);
status ClearBiTree(BiTree &T); 
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
int cntkey(BiTree T,KeyType e);
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
void dfs(BiTree u,BiTree &ans,KeyType e);
status DeleteNode(BiTree &T,KeyType e);
void visit(BiTree T);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
status SaveBiTree(BiTree T, char *FileName);
status creatBitree(BiTree &T, TElemType dataa[]);
status LoadBiTree(BiTree &T,  char FileName[]);
status AddBiTree(TREES &Trees, char BiTreeName[], TElemType definition[]); 
status RemoveBiTree(TREES &Trees,char BiTreeName[]);
status LocateBiTree(TREES Trees,char BiTreeName[]);
void PrintNodeByLevel(BiTree root);
void Build(BiTree &root, int L1, int R1, int L2, int R2);

TElemType value;
int i = 0;
int in_order[10], post_order[10], n;
int main(){
	//system("COLOR F0"); 
	int op = 1, e = -1, val = -1, LR = -1, flag = -1;
	int j = 0;
	int i_num = 9; 
	char BiTreeName[20];
	TElemType definition[100];
	BiTNode *p = NULL;
	while(op){
		system("cls");	//清屏 
		printf("\n\n");
		printf("         Menu for Binary Tree On Binary Linked List \n");
		printf("------------------------------------------------------------\n");
		printf("          1. CreateBiTree       11. PostOrderTraverse\n");
		printf("          2. ClearBiTree        12. LevelOrderTraverse\n");
		printf("    	  3. BiTreeDepth        13. SaveBiTree\n");
		printf("    	  4. LocateNode         14. LoadBiTree\n");
		printf("    	  5. Assign             15. AddBiTree\n");
		printf("    	  6. GetSibling         16. RemoveBiTree\n");
		printf("    	  7. InsertNode         17. LocateBiTree\n");
		printf("    	  8. DeleteNode         18. ChooseBiTree\n");
		printf("    	  9. PreOrderTraverse   19. EmptyBiTree\n");	
		printf("    	  10. InOrderTraverse   20. PrintBiTree\n");
		printf("    	  0. Exit               21. BuildTree\n");
		printf("------------------------------------------------------------\n");
		printf("    请选择你的操作[0-21]:\n");
		i = 0;
		scanf("%d", &op);
		switch(op){	
			case 1://1是创建树 
				if(Trees.elem[i_num].T != NULL){
					printf("不可重复生成二叉树");
					getchar(); getchar();
					break;
				}
				printf("请按照先序输入结点的关键字和数据\n（以关键字为-1的结点结尾）\n");
				j = 0, flag = 1;
				do {
					scanf("%d%s",&definition[j].key,definition[j].others);
				} while (definition[j++].key != -1);
				if(j == 1)
					flag = 0;
				val = CreateBiTree(Trees.elem[i_num].T, definition);
				if(val == ERROR) printf("关键字不唯一");
				else if(!flag) printf("空树");
				else printf("成功生成二叉树"); 
				getchar(); getchar();
				break;
				
			case 2://2是销毁树 
				if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				if(ClearBiTree(Trees.elem[i_num].T) == OK)
					printf("二叉树销毁成功\n"); 	
				else 
					printf("二叉树销毁失败\n");
				getchar(); getchar();
				break;
				
			case 3://3是求树深度
				if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("树的深度为: %d\n",BiTreeDepth(Trees.elem[i_num].T));
         		getchar(); getchar();
         		break;
         		
			case 4://4是查找结点
				if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("请输入您要查找结点的关键字：\n");
				scanf("%d", &e);
				p = LocateNode(Trees.elem[i_num].T,e);
				if(p == NULL)
					printf("您要查找的结点在二叉树中不存在\n");
				else{
					printf("您要查找的结点关键字和数据分别是：\n"); 
					visit(p);
				} 
				getchar(); getchar();
				break;
				
			case 5://5是结点赋值
				if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("请输入您想要赋值结点的关键字：\n");
				scanf("%d", &e);
				printf("请输入关键字：\n");
				scanf("%d", &value.key);
				printf("请输入数据：\n");
				scanf("%s",value.others);
				val = Assign(Trees.elem[i_num].T,e,value);
				if(val == OK)
					printf("赋值成功");
				else if(val == ERROR)
					printf("没有找到要赋值的结点");
				else
					printf("您输入的关键字不合法"); 
				getchar(); getchar();
				break;
					
			case 6://6是获得兄弟结点 
				if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				} 
				printf("请输入您想要找兄弟结点的结点的关键字:\n");
				scanf("%d", &e); 
				p = GetSibling(Trees.elem[i_num].T,e);
				if(p == NULL) printf("没有找到兄弟节点\n");
				else{
					printf("兄弟节点的关键字和数据分别是:\n");
					visit(p);
				} 
				getchar(); getchar();
				break;
				
			case 7:// 7是插入节点
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				 }
				 printf("请输入您要插入位置的结点的关键字:\n");
				 scanf("%d", &e);
				 printf("请输入待插入结点的关键字:\n");
				 scanf("%d", &value.key);
				 printf("请输入待插入结点的数据：\n");
				 scanf("%s", value.others);
				 printf("请输入插入的位置：\n（0代表左，1代表右）\n");
				 scanf("%d", &LR);
				 val = InsertNode(Trees.elem[i_num].T, e, LR, value);
				 if(val == OK) printf("插入成功\n");
				 else printf("插入失败\n");
				 getchar(); getchar();
				 break;
				  
			case 8://8是删除结点
				if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("请输入要删除结点的关键字：\n");
				scanf("%d", &e);
				val = DeleteNode(Trees.elem[i_num].T,e);
				if(val == OK) printf("删除成功！\n");
				else printf("删除失败\n");
				getchar(); getchar();
				break;
				
			case 9://9是先序遍历
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("先序遍历:\n");
				PreOrderTraverse(Trees.elem[i_num].T,visit);
				printf("\n遍历成功\n"); 
				getchar(); getchar();
				break;
				 
			case 10://10是中序遍历 非递归 
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("中序遍历:\n");
				InOrderTraverse(Trees.elem[i_num].T,visit);
				printf("\n遍历成功\n"); 
				getchar(); getchar();
				break;
				
			case 11://11是后序遍历
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("后序遍历:\n");
				PostOrderTraverse(Trees.elem[i_num].T,visit);
				printf("\n遍历成功\n"); 
				getchar(); getchar();
				break;
				
			case 12://12是按层遍历
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("按层遍历:\n");
				LevelOrderTraverse(Trees.elem[i_num].T,visit);
				printf("\n遍历成功\n");
				getchar(); getchar();
				break;
				
			case 13://13是保存文件
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("请输入您想保存的文件名：\n");
         		scanf("%s",BiTreeName);
				val = SaveBiTree(Trees.elem[i_num].T, BiTreeName);
				if(val == OK) 
					printf("文件保存成功\n文件名是%s\n",BiTreeName);
				else 
					printf("保存失败");
				getchar(); getchar();
				break;
				
			case 14://14是加载文件
				if (Trees.elem[i_num].T != NULL){
	   				printf("二叉树已经存在！\n");
	   				getchar();getchar();
	   				break;
				}  
				printf("请输入要加载的文件名：\n");
				scanf("%s", BiTreeName);
				val = LoadBiTree(Trees.elem[i_num].T, BiTreeName);
				if(val == OK) printf("加载成功");
				else printf("加载失败");
				getchar(); getchar();
				break; 
				
			case 15:
				printf("请输入树的名字\n");
				scanf("%s", BiTreeName);
				printf("请按照先序输入结点的关键字和数据\n（以关键字为-1的结点结尾）\n");
				j = 0, flag = 1;
				do {
					scanf("%d%s",&definition[j].key,definition[j].others);
				} while (definition[j++].key != -1);
				if(j == 1)
					flag = 0;
				val = AddBiTree(Trees, BiTreeName, definition);
				if(val == ERROR) printf("创建树失败");
				else if(!flag) printf("空树");
				else printf("%s成功加入树集合", BiTreeName); 
				getchar(); getchar();
				break; 
				
			case 16:
				printf("请输入要删除树的名称\n");
				scanf("%s",BiTreeName);
				val = RemoveBiTree(Trees,BiTreeName);
				if(val == OK)
					printf("树%s删除成功\n", BiTreeName);
				else
					printf("树集合中不存在%s树", BiTreeName);
				getchar(); getchar();
				break;
			
			case 17:
				printf("请输入要查找的树的名称：\n");
				scanf("%s",BiTreeName);
				val = LocateBiTree(Trees, BiTreeName);
				if(val == 0)
					printf("树集合中不存在%s树\n", BiTreeName);
				else
					printf("%s树位于树集合中第%d个位置\n", BiTreeName, val);
				getchar(); getchar();
				break;
				
			case 18:
				printf("请选择您要操作的树的序号：\n"); 
				scanf("%d",&i_num);
				i_num --;
				printf("当前正在第%d个树进行操作\n",i_num+1); 
				getchar(); getchar();
				break;

			case 19:
				if(Trees.elem[i_num].T == NULL)
					printf("二叉树为空");
				else
					printf("二叉树不是空树"); 
				getchar(); getchar();
				break;
			case 20:
				if (Trees.elem[i_num].T == NULL){
	   				printf("二叉树不存在！\n");
	   				getchar();getchar();
	   				break;
				}
				PrintNodeByLevel(Trees.elem[i_num].T);
				getchar(); getchar();
				break;
			
			case 21:
				if (Trees.elem[i_num].T != NULL){
	   				printf("二叉树已经存在！\n");
	   				getchar();getchar();
	   				break;
				}
				printf("请输入结点个数：\n");
				scanf("%d", &n);
				printf("请输入中序序列：\n"); 
				for(int i = 1; i <= n; i++) scanf("%d", &in_order[i]);
				printf("请输入后序序列：\n"); 
				for(int i = 1; i <= n; i++) scanf("%d", &post_order[i]);
				Build(Trees.elem[i_num].T, 1, n, 1, n);
				printf("建树成功！\n"); 
				getchar(); getchar();
				break;
				
			case 0:
				printf("欢迎再次使用"); 
				break;	
		}
	}
}

status MakeChild(BiTree &t, TElemType definition[])
{
    KeyType n = definition[i].key;
    if(n == 0){//边界条件 
        t = NULL;
        i ++;
    }
    else if(n != -1){
        if( !(t=(BiTNode*)malloc(sizeof(BiTNode))) ) exit(OVERFLOW);
        t->data = definition[i];
		i ++;
        MakeChild(t->lchild, definition);//递归 
        MakeChild(t->rchild, definition);
    }
    return OK;
}

/***************************************************************
*函数名称：CreateBiTree
*函数功能：构造一棵二叉树 
*函数参数：二叉树T 先序序列definition 
*注释：初始条件是二叉树T不存在，操作结果是构造一棵二叉树。若二叉树已经存在，返回INFEASIBLE
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。*/
{
    if(T != NULL) return  INFEASIBLE;
	int flag[1000]={0};//关键字数组 
    for(int k = 0; k < 100; k++){
        int temp = definition[k].key;
        if(temp == -1) break;//结束标志 
        flag[temp] ++;
    }
    for(int k = 1; k < 1000; k++){
        if(flag[k] > 1)return ERROR;//关键字是否重复 
    }
    MakeChild(T, definition);//递归造树 
    return OK;
}

/***************************************************************
*函数名称：ClearBiTree
*函数功能：销毁二叉树
*函数参数：二叉树T
*注释：初始条件是二叉树T已存在；操作结果是销毁二叉树T
*返回值类型：status类型
*时间复杂度：O(1)
****************************************************************/
status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    if (T) {
		if (T->lchild)
			ClearBiTree(T->lchild);
		if (T->rchild)
			ClearBiTree(T->rchild);
		free(T);
		T = NULL;//使用递归依次释放左子树、右子树、根节点指针
	}
	return OK;
}

/***************************************************************
*函数名称：BiTreeDepth
*函数功能：求二叉树深度 
*函数参数：二叉树T 
*注释：初始条件是二叉树已存在；操作结果是返回二叉树的深度 
*返回值类型：status类型
*时间复杂度：O(logn)
****************************************************************/
int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    int depth = 0;
	if(T)
	{
		int lchilddepth = BiTreeDepth(T->lchild);
		int rchilddepth = BiTreeDepth(T->rchild);
		depth = ( lchilddepth >= rchilddepth ? (lchilddepth+1) : (rchilddepth+1));
	}
	//使用递归,得到左右子树的深度,并比较大小,之后返回最大的深度
	return depth;
}

/***************************************************************
*函数名称：LocateNode
*函数功能：查找结点 
*函数参数：二叉树T，待查找结点的关键字 
*注释：初始条件是二叉树已存在；操作结果是返回T中关键字为e的结点的指针 
       若不存在，返回NULL 
*返回值类型：BiTree类型
*时间复杂度：O(n)
****************************************************************/
BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    if (!T) return ERROR;   //若二叉树为空,返回ERROR
	BiTNode *st[50], *p;//栈 
	int top = 0;  
	st[top++] = T;
	while (top != 0){
		p = st[--top]; //先序遍历
		if (p->data.key == e){
            return p;
        }
		else {
			if(p->rchild != NULL) 
				st[top++] = p->rchild;//右儿子入栈 
			if(p->lchild != NULL)
				st[top++] = p->lchild;//左儿子入栈 
		}
	}
	return NULL;//没找到 
}

/***************************************************************
*函数名称：Assign
*函数功能：结点赋值 
*函数参数：二叉树T，待赋值结点的关键字 ，结点数据 
*注释：初始条件是二叉树已存在；
*返回值类型：status类型
*时间复杂度：O(n)
****************************************************************/
status Assign(BiTree &T,KeyType e,TElemType value)
//结点赋值。
{
    int cnt = 0;
    BiTNode *pos = NULL;
    if (!T) return ERROR;  
	BiTNode *st[50], *p;
	int top = 0;  
	st[top++] = T;
	while (top != 0){
		p = st[--top]; 
        if(p->data.key == value.key)
            cnt ++;//关键字是否合法 
		if (p->data.key == e){
            pos = p;//找到节点 
        }
		else {
			if(p->rchild != NULL)
				st[top++] = p->rchild;
			if(p->lchild != NULL)
				st[top++] = p->lchild;
		}
	}
	if(pos == NULL) return ERROR;//没找到 
    if(cnt==0||(cnt==1&&pos->data.key==value.key)){
        pos->data = value;//找到且关键字合法 
        return OK;
    }
    else return -1;//关键字不合法 
}

/***************************************************************
*函数名称：GetSibling
*函数功能：找兄弟结点 
*函数参数：二叉树T，待查找结点的关键字 
*注释：初始条件是二叉树已存在；
*返回值类型：BiTree类型
*时间复杂度：O(n)
****************************************************************/
BiTNode* GetSibling(BiTree T,KeyType e)
{
    BiTNode* p = NULL;
	if (T)
	{
		if (T->rchild!=NULL&&T->rchild->data.key == e)//如果右孩子不为空并且节点的值符合,那么便返回左孩子的指针
		return T->lchild;
        if (T->lchild!=NULL&&T->lchild->data.key == e)//如果右孩子不为空并且节点的值符合,那么便返回左孩子的指针
		return T->rchild;
		p = GetSibling(T->lchild, e);
		if (p != NULL) return p;
		p = GetSibling(T->rchild, e);
		if (p != NULL) return p;
	}
	return NULL;
}

int cntkey(BiTree T,KeyType e){
    if(T == NULL) return 0;
	int cnt = 0;
    if(e == T->data.key)
    	cnt ++;
    if(T->rchild)
    	cnt += cntkey(T->rchild, e);
    if(T->lchild)
    	cnt += cntkey(T->rchild, e);
	return cnt;   
}

/***************************************************************
*函数名称：InsertNode
*函数功能：插入结点
*函数参数：二叉树T，待插入结点的关键字， 位置LR，结点c 
*注释：初始条件是二叉树T已存在，操作结果是在结点后插入新结点 
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
//插入结点。
{
    if(T == NULL) ERROR;
    BiTree p = NULL;
    if(LR == -1){//插入头结点 
        p = (BiTree)malloc(sizeof(BiTNode));
        p->data = c;
        p->rchild = T;
        p->lchild = NULL;
        T = p;
        return OK;
    }
    p = LocateNode(T, e);//找到位置 
    int cnt = cntkey(T, c.key);//关键字是否合法 
    if(cnt != 0) return ERROR;
    if(p == NULL) return ERROR;//找不到节点 
    if(LR == 0){//左边 
        BiTree q = (BiTree)malloc(sizeof(BiTNode));
        q->data = c;
        q->rchild = p->lchild;
        q->lchild = NULL;
        p->lchild = q;
        return OK;
    }
    else{//右边 
        BiTree q = (BiTree)malloc(sizeof(BiTNode));
        q->data = c;
        q->rchild = p->lchild;
        q->lchild = NULL;
        p->rchild = q;
        return OK;
    }
	return OK;
}

void dfs(BiTree u,BiTree &ans,KeyType e)//找父亲 
{
	if(u == NULL) return ;
	if(u->lchild != NULL)	{
		if(u->lchild->data.key == e)
			ans=u;
		else dfs(u->lchild, ans, e);
	}
	if(u->rchild != NULL){
		if(u->rchild->data.key == e)
			ans=u;
		else dfs(u->rchild, ans, e);
	}
}

/***************************************************************
*函数名称：DeleteNode
*函数功能：删除节点
*函数参数：二叉树T,待删除结点关键字
*注释：初始条件是二叉树T已存在
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status DeleteNode(BiTree &T,KeyType e)
//删除结点。
{
    if(T == NULL) 
		return ERROR;
    BiTNode *p = LocateNode(T, e);//p是待删除结点 
    if(p == NULL) 
		return ERROR;
    int cnt = 0;//几个儿子 
    if(p->rchild) cnt++;
    if(p->lchild) cnt++;
    BiTNode *rnode = p->lchild, *del, *q = NULL;
    dfs(T, q, e);//找父亲 
    if(q == NULL){//根节点 
        del = T;
		if(cnt == 2){
            while(rnode->rchild) rnode = rnode->rchild;
            rnode->rchild = T->rchild;
            T = T->lchild;
        }
        if(cnt == 1){
			if(T->lchild)
                T = T->lchild;
            if(T->rchild)
                T = T->rchild;
        }
		free(del);
        return OK;
    }
    if(cnt == 0){//叶子节点 
        if(q->lchild&&q->lchild->data.key == e) 
        	q->lchild = NULL;
        if(q->rchild&&q->rchild->data.key == e)
        	q->rchild = NULL;
        free(p);
        return OK;
    }
    if(cnt == 1){//一个儿子 
        if(p->lchild){
            if(q->lchild == p)
                q->lchild = p->lchild;
            else
                q->rchild = p->lchild;
        }
        if(p->rchild){
            if(q->lchild == p)
                q->lchild = p->rchild;
            else    
                q->rchild = p->rchild;
        }
        free(p);
    }
    if(cnt == 2){//俩儿子 
        if(q->lchild == p)
            q->rchild = p->lchild;
        if(q->rchild == p)
            q->rchild = p->lchild;
        while(rnode->rchild) rnode = rnode->rchild;
        rnode->rchild = p->rchild;
        free(p);
    }
    return OK;
}

void visit(BiTree T){//打印结点 
    printf(" %d,%s",T->data.key,T->data.others);
}

/***************************************************************
*函数名称：PreOrderTraverse
*函数功能：先序遍历
*函数参数：二叉树T,函数指针
*注释：初始条件是二叉树T已存在
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    if(T == NULL)
        return OK;
    visit(T);
    if(T->lchild)
        PreOrderTraverse(T->lchild, visit);
    if(T->rchild) 
        PreOrderTraverse(T->rchild, visit);
    return OK;
}

/***************************************************************
*函数名称：InOrderTraverse
*函数功能：中序遍历
*函数参数：二叉树T,函数指针
*注释：初始条件是二叉树T已存在
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
    int top = 0;
    BiTree st[50]; //栈 
    BiTNode *p;
    st[top++] = T;
    while(top != 0){
        while(p = st[top-1]) st[top++] = p->lchild;
        top --;
        if(top != 0){
            p = st[top-1];
            top--;
            visit(p);
            st[top++] = p->rchild;
        }
    }
    return OK;
}

/***************************************************************
*函数名称：PostOrderTraverse
*函数功能：后遍历
*函数参数：二叉树T,函数指针
*注释：初始条件是二叉树T已存在
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    if(T != NULL){
        if(T->lchild)//递归 
            PostOrderTraverse(T->lchild, visit);
        if(T->rchild)
            PostOrderTraverse(T->rchild, visit); 
        visit(T);
        return OK;
    }
}

/***************************************************************
*函数名称：LevelOrderTraverse
*函数功能：按层遍历
*函数参数：二叉树T,函数指针
*注释：初始条件是二叉树T已存在
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    BiTree st[50];//队列 
    int head = 0, tail = 0, len = 50;//头尾指针 队列长度 
    BiTree p;
    st[tail++] = T;
    while(head != tail){//队列不为空 
        p = st[head];
        head ++;//出队列 
        if(p->lchild)
            st[tail++] = p->lchild;
        if(p->rchild)
            st[tail++] = p->rchild;
        visit(p);
    }
    return OK;
}

/***************************************************************
*函数名称：SaveBiTree
*函数功能：保存二叉树
*函数参数： 二叉树T,字符数组 FileName 
*注释：将二叉树保存到文件中，
*返回值类型：status类型
*时间复杂度O(n) 
****************************************************************/
status SaveBiTree(BiTree T, char *FileName)
//将二叉树的结点数据写入到文件FileName中
{

    FILE *fp;
    if((fp=fopen(FileName, "w")) == NULL) return ERROR; 
    if(T == NULL) return ERROR;
    int key = 0;//空结点的关键字 
	char ch[20];
    ch[0] = '#';//空结点的数据 
    BiTree st[50];//栈 
    int top = 0;
    st[top++] = T;
    BiTree p;
    while(top != 0){
        p = st[--top];//先序遍历 
        if(p != NULL){
            fprintf(fp, "%d ", p->data.key);
            fprintf(fp, "%s ", p->data.others);
            st[top++] = p->rchild;//入栈 
            st[top++] = p->lchild;
        }
        else{
            fprintf(fp, "%d ", key);
            fprintf(fp, "%s ", ch);
        }
    }
    fclose(fp);
    return OK;
}
status creatBitree(BiTree &T, TElemType dataa[]){
    KeyType n = dataa[i].key;
    if(n == 0){
        T = NULL;
        i++;
    }
    else {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = dataa[i];
        i++;
        creatBitree(T->lchild, dataa);
        creatBitree(T->rchild, dataa); 
    }
    return OK;
}

/***************************************************************
*函数名称：LoadBiTree
*函数功能：加载文件
*函数参数：二叉树T,字符数组FileName 
*注释：加载文件
*返回值类型：status类型
*时间复杂度:O(n) 
****************************************************************/
status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    if(T != NULL) return ERROR;
    FILE *fp;
    if((fp=fopen(FileName, "r")) == NULL) return ERROR; 
    int key;
	char ch[10];
    BiTNode *p;
    BiTNode *q;
    int k = 0;
    TElemType dataa[50];
    while(1){
        if(fscanf(fp, "%d ", &key) == EOF)
            break;
	    fscanf(fp, "%s ", ch);//从文件读数据 
        dataa[k].key = key;
        strcpy(dataa[k].others, ch);
        k++;
    }
    creatBitree(T, dataa);//造树 
    fclose(fp);
	return OK;
}

/***************************************************************
*函数名称：AddBiTree
*函数功能：Trees中增加一个名称为BiTreeName的二叉树 
*函数参数：树集合Trees，字符数组BiTreeName，二叉树结点数组definition 
*注释：初始条件是有Trees树集合
*返回值类型：status类型
*时间复杂度: O(n)
****************************************************************/
status AddBiTree(TREES &Trees, char BiTreeName[],TElemType definition[]){
	if(strlen(BiTreeName) > 30 ) return ERROR;//名字太长了 
    for(int i = 0; i < Trees.length; i++){
    	if(!strcmp(BiTreeName,Trees.elem[i].name))
    		return ERROR;
	}
	int flag1 = CreateBiTree(Trees.elem[Trees.length].T, definition);
    if(flag1 == OK) {//成功创建树 
    	strcpy(Trees.elem[Trees.length].name,BiTreeName); //保存树的名字
    	Trees.length ++;//树数 +1
    	return OK;
	}
    else return ERROR;//增加失败
}

/***************************************************************
*函数名称：RemoveBiTree
*函数功能：Trees中删除一个名称为BiTreeName的二叉树 
*函数参数：树集合Trees，字符数组BiTreeName
*注释：初始条件是有Trees树集合 
*返回值类型：status类型
*时间复杂度: O(n)
****************************************************************/
status RemoveBiTree(TREES &Trees,char BiTreeName[])
{
	if(Trees.length == 0) return ERROR;//如果有0个树，没法删 
    int flag = 0;//判断是否删除成功 
    for(int i = 0; i < Trees.length; i++){
        if(strcmp(BiTreeName,Trees.elem[i].name) == 0){//找到名字叫 BiTreeName的树 
            for(int j = i; j < Trees.length-1; j++){//移动树，结构可以直接赋值 
                Trees.elem[j] = Trees.elem[j+1];
            }
            Trees.length -- ;//树数量-1
            flag = 1;//删除成功 
            break;
        }
        else continue;//继续找 
    }
    if(flag) return OK;//成功删除 
    else return ERROR;//没找到 
}

/***************************************************************
*函数名称：LocateBiTree
*函数功能：Trees中查找一个名称为BiTreeName的二叉树 
*函数参数：树集合Trees，字符数组BiTreeName
*注释：初始条件是有Trees树集合 
*返回值类型：status类型
*时间复杂度: O(n)
****************************************************************/
status LocateBiTree(TREES Trees,char BiTreeName[])
// 在Trees中查找一个名称为BiTreeName的树，成功返回逻辑序号，否则返回0
{
    int loc = -1,flag = 0;//loc记录位置，flag记录是否有 BiTreeName树
    for(int i = 0; i < Trees.length; i++){
        if(strcmp(BiTreeName,Trees.elem[i].name) == 0){//找到 BiTreeName树
            flag = 1;
            loc = i;
            break;
        }
        else continue;//这个不是，找下一个 
    }
    if(flag) return loc + 1;//找到返回逻辑位置 
    else return 0;//没找到返回0 
}

/***************************************************************
*函数名称：PrintNodeByLevel
*函数功能：按树形打印树 
*函数参数：二叉树root 
*注释：root存在 
*返回值类型：void 
*时间复杂度: O(n)
****************************************************************/
void PrintNodeByLevel(BiTree root) {
	if(root == NULL) return; 
    queue<BiTree> Q;//树队列 
    queue<char *> C; //字符串队列 
    Q.push(root);//根入队列 
    Q.push(0);
    int prenull = 0;
    BiTree fw = (BiTree)malloc(sizeof(BiTNode));
    int height = BiTreeDepth(root);
    int numh = BiTreeDepth(root);
    for(int i = 1; i <= numh+22; i++) printf(" ");
    do {
        BiTree node = Q.front();
        Q.pop();
        if(node == fw) cout << "   ";
        else if (node) {
        	numh = BiTreeDepth(node);
        	printf("%d  ", node->data.key);
            if (node->lchild) {
                Q.push(node->lchild);
                C.push("/ ");
            }
            else {
            	Q.push(fw);
				C.push(" ");
				prenull ++;
			}
            if (node->rchild) {
                Q.push(node->rchild);
                C.push("\\");
            }
            else{
            	C.push(" ");
            	Q.push(fw);
            	prenull ++;
			}
        }
        else if (!Q.empty()) {
			cout << endl;
			for(int i = 1; i <= numh+21; i++) printf(" ");
            //for(int i = 0; i <= prenull; i++) cout << " ";
			while(C.size() != 0) {
                printf("%s ", C.front());
                C.pop();
            }
			Q.push(0);
            cout << endl;
            for(int i = 1; i <= numh+20; i++) printf(" ");
            //for(int i = 0; i <= prenull-2; i++) cout << " ";
        }
    } while (!Q.empty());
}

/***************************************************************
*函数名称：Build
*函数功能：根据中序与后序建二叉树 
*函数参数：二叉树root，先序序列与后序序列 
*注释：中序序列与后序序列设为全局变量 
*返回值类型：void 
*时间复杂度: O(n)
****************************************************************/
void Build(BiTree &root, int L1, int R1, int L2, int R2){
	if(L1 > R1) {
		root = NULL;
		return;
	}
	root = (BiTree)malloc(sizeof(BiTNode));
	root->data.key = post_order[R2];
	int p = L1;
	while(in_order[p] != post_order[R2]) p++;
	int cnt = p-L1;
	Build(root->lchild, L1, p-1, L2, L2+cnt-1);
	Build(root->rchild, p+1, R1, L2+cnt, R2-1);
	return;
}

void build(BiTree &root, int L1, int R1, int L2, int R2){
	if(L1 > R1) {
		root = NULL;
		return;
	}
	root = (BiTree)malloc(sizeof(BiTNode));
	root->data.key = post_order[L2];
	int p = L1;
	while(in_order[p] != post_order[L2]) p++;	
	
	build(root->lchild, L1, p-1, L2+1, p-L1+L2);
	build(root->rchild, p+1, R1, p-L1+L2+1, R2);
	return;
	
	
}
	
	
