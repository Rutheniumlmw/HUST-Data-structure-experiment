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
} TElemType; //������������Ͷ���
typedef struct BiTNode{    //����������Ķ���
      TElemType data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
typedef struct{  //���ļ������Ͷ���
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
		system("cls");	//���� 
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
		printf("    ��ѡ����Ĳ���[0-21]:\n");
		i = 0;
		scanf("%d", &op);
		switch(op){	
			case 1://1�Ǵ����� 
				if(Trees.elem[i_num].T != NULL){
					printf("�����ظ����ɶ�����");
					getchar(); getchar();
					break;
				}
				printf("�밴������������Ĺؼ��ֺ�����\n���Թؼ���Ϊ-1�Ľ���β��\n");
				j = 0, flag = 1;
				do {
					scanf("%d%s",&definition[j].key,definition[j].others);
				} while (definition[j++].key != -1);
				if(j == 1)
					flag = 0;
				val = CreateBiTree(Trees.elem[i_num].T, definition);
				if(val == ERROR) printf("�ؼ��ֲ�Ψһ");
				else if(!flag) printf("����");
				else printf("�ɹ����ɶ�����"); 
				getchar(); getchar();
				break;
				
			case 2://2�������� 
				if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				if(ClearBiTree(Trees.elem[i_num].T) == OK)
					printf("���������ٳɹ�\n"); 	
				else 
					printf("����������ʧ��\n");
				getchar(); getchar();
				break;
				
			case 3://3���������
				if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("�������Ϊ: %d\n",BiTreeDepth(Trees.elem[i_num].T));
         		getchar(); getchar();
         		break;
         		
			case 4://4�ǲ��ҽ��
				if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("��������Ҫ���ҽ��Ĺؼ��֣�\n");
				scanf("%d", &e);
				p = LocateNode(Trees.elem[i_num].T,e);
				if(p == NULL)
					printf("��Ҫ���ҵĽ���ڶ������в�����\n");
				else{
					printf("��Ҫ���ҵĽ��ؼ��ֺ����ݷֱ��ǣ�\n"); 
					visit(p);
				} 
				getchar(); getchar();
				break;
				
			case 5://5�ǽ�㸳ֵ
				if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("����������Ҫ��ֵ���Ĺؼ��֣�\n");
				scanf("%d", &e);
				printf("������ؼ��֣�\n");
				scanf("%d", &value.key);
				printf("���������ݣ�\n");
				scanf("%s",value.others);
				val = Assign(Trees.elem[i_num].T,e,value);
				if(val == OK)
					printf("��ֵ�ɹ�");
				else if(val == ERROR)
					printf("û���ҵ�Ҫ��ֵ�Ľ��");
				else
					printf("������Ĺؼ��ֲ��Ϸ�"); 
				getchar(); getchar();
				break;
					
			case 6://6�ǻ���ֵܽ�� 
				if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				} 
				printf("����������Ҫ���ֵܽ��Ľ��Ĺؼ���:\n");
				scanf("%d", &e); 
				p = GetSibling(Trees.elem[i_num].T,e);
				if(p == NULL) printf("û���ҵ��ֵܽڵ�\n");
				else{
					printf("�ֵܽڵ�Ĺؼ��ֺ����ݷֱ���:\n");
					visit(p);
				} 
				getchar(); getchar();
				break;
				
			case 7:// 7�ǲ���ڵ�
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				 }
				 printf("��������Ҫ����λ�õĽ��Ĺؼ���:\n");
				 scanf("%d", &e);
				 printf("�������������Ĺؼ���:\n");
				 scanf("%d", &value.key);
				 printf("�����������������ݣ�\n");
				 scanf("%s", value.others);
				 printf("����������λ�ã�\n��0������1�����ң�\n");
				 scanf("%d", &LR);
				 val = InsertNode(Trees.elem[i_num].T, e, LR, value);
				 if(val == OK) printf("����ɹ�\n");
				 else printf("����ʧ��\n");
				 getchar(); getchar();
				 break;
				  
			case 8://8��ɾ�����
				if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("������Ҫɾ�����Ĺؼ��֣�\n");
				scanf("%d", &e);
				val = DeleteNode(Trees.elem[i_num].T,e);
				if(val == OK) printf("ɾ���ɹ���\n");
				else printf("ɾ��ʧ��\n");
				getchar(); getchar();
				break;
				
			case 9://9���������
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("�������:\n");
				PreOrderTraverse(Trees.elem[i_num].T,visit);
				printf("\n�����ɹ�\n"); 
				getchar(); getchar();
				break;
				 
			case 10://10��������� �ǵݹ� 
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("�������:\n");
				InOrderTraverse(Trees.elem[i_num].T,visit);
				printf("\n�����ɹ�\n"); 
				getchar(); getchar();
				break;
				
			case 11://11�Ǻ������
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("�������:\n");
				PostOrderTraverse(Trees.elem[i_num].T,visit);
				printf("\n�����ɹ�\n"); 
				getchar(); getchar();
				break;
				
			case 12://12�ǰ������
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("�������:\n");
				LevelOrderTraverse(Trees.elem[i_num].T,visit);
				printf("\n�����ɹ�\n");
				getchar(); getchar();
				break;
				
			case 13://13�Ǳ����ļ�
			 	if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("���������뱣����ļ�����\n");
         		scanf("%s",BiTreeName);
				val = SaveBiTree(Trees.elem[i_num].T, BiTreeName);
				if(val == OK) 
					printf("�ļ�����ɹ�\n�ļ�����%s\n",BiTreeName);
				else 
					printf("����ʧ��");
				getchar(); getchar();
				break;
				
			case 14://14�Ǽ����ļ�
				if (Trees.elem[i_num].T != NULL){
	   				printf("�������Ѿ����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}  
				printf("������Ҫ���ص��ļ�����\n");
				scanf("%s", BiTreeName);
				val = LoadBiTree(Trees.elem[i_num].T, BiTreeName);
				if(val == OK) printf("���سɹ�");
				else printf("����ʧ��");
				getchar(); getchar();
				break; 
				
			case 15:
				printf("��������������\n");
				scanf("%s", BiTreeName);
				printf("�밴������������Ĺؼ��ֺ�����\n���Թؼ���Ϊ-1�Ľ���β��\n");
				j = 0, flag = 1;
				do {
					scanf("%d%s",&definition[j].key,definition[j].others);
				} while (definition[j++].key != -1);
				if(j == 1)
					flag = 0;
				val = AddBiTree(Trees, BiTreeName, definition);
				if(val == ERROR) printf("������ʧ��");
				else if(!flag) printf("����");
				else printf("%s�ɹ�����������", BiTreeName); 
				getchar(); getchar();
				break; 
				
			case 16:
				printf("������Ҫɾ����������\n");
				scanf("%s",BiTreeName);
				val = RemoveBiTree(Trees,BiTreeName);
				if(val == OK)
					printf("��%sɾ���ɹ�\n", BiTreeName);
				else
					printf("�������в�����%s��", BiTreeName);
				getchar(); getchar();
				break;
			
			case 17:
				printf("������Ҫ���ҵ��������ƣ�\n");
				scanf("%s",BiTreeName);
				val = LocateBiTree(Trees, BiTreeName);
				if(val == 0)
					printf("�������в�����%s��\n", BiTreeName);
				else
					printf("%s��λ���������е�%d��λ��\n", BiTreeName, val);
				getchar(); getchar();
				break;
				
			case 18:
				printf("��ѡ����Ҫ������������ţ�\n"); 
				scanf("%d",&i_num);
				i_num --;
				printf("��ǰ���ڵ�%d�������в���\n",i_num+1); 
				getchar(); getchar();
				break;

			case 19:
				if(Trees.elem[i_num].T == NULL)
					printf("������Ϊ��");
				else
					printf("���������ǿ���"); 
				getchar(); getchar();
				break;
			case 20:
				if (Trees.elem[i_num].T == NULL){
	   				printf("�����������ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				PrintNodeByLevel(Trees.elem[i_num].T);
				getchar(); getchar();
				break;
			
			case 21:
				if (Trees.elem[i_num].T != NULL){
	   				printf("�������Ѿ����ڣ�\n");
	   				getchar();getchar();
	   				break;
				}
				printf("�������������\n");
				scanf("%d", &n);
				printf("�������������У�\n"); 
				for(int i = 1; i <= n; i++) scanf("%d", &in_order[i]);
				printf("������������У�\n"); 
				for(int i = 1; i <= n; i++) scanf("%d", &post_order[i]);
				Build(Trees.elem[i_num].T, 1, n, 1, n);
				printf("�����ɹ���\n"); 
				getchar(); getchar();
				break;
				
			case 0:
				printf("��ӭ�ٴ�ʹ��"); 
				break;	
		}
	}
}

status MakeChild(BiTree &t, TElemType definition[])
{
    KeyType n = definition[i].key;
    if(n == 0){//�߽����� 
        t = NULL;
        i ++;
    }
    else if(n != -1){
        if( !(t=(BiTNode*)malloc(sizeof(BiTNode))) ) exit(OVERFLOW);
        t->data = definition[i];
		i ++;
        MakeChild(t->lchild, definition);//�ݹ� 
        MakeChild(t->rchild, definition);
    }
    return OK;
}

/***************************************************************
*�������ƣ�CreateBiTree
*�������ܣ�����һ�ö����� 
*����������������T ��������definition 
*ע�ͣ���ʼ�����Ƕ�����T�����ڣ���������ǹ���һ�ö����������������Ѿ����ڣ�����INFEASIBLE
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status CreateBiTree(BiTree &T,TElemType definition[])
/*���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK��
�������ͬ�Ĺؼ��֣�����ERROR��*/
{
    if(T != NULL) return  INFEASIBLE;
	int flag[1000]={0};//�ؼ������� 
    for(int k = 0; k < 100; k++){
        int temp = definition[k].key;
        if(temp == -1) break;//������־ 
        flag[temp] ++;
    }
    for(int k = 1; k < 1000; k++){
        if(flag[k] > 1)return ERROR;//�ؼ����Ƿ��ظ� 
    }
    MakeChild(T, definition);//�ݹ����� 
    return OK;
}

/***************************************************************
*�������ƣ�ClearBiTree
*�������ܣ����ٶ�����
*����������������T
*ע�ͣ���ʼ�����Ƕ�����T�Ѵ��ڣ�������������ٶ�����T
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status ClearBiTree(BiTree &T)
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
    if (T) {
		if (T->lchild)
			ClearBiTree(T->lchild);
		if (T->rchild)
			ClearBiTree(T->rchild);
		free(T);
		T = NULL;//ʹ�õݹ������ͷ��������������������ڵ�ָ��
	}
	return OK;
}

/***************************************************************
*�������ƣ�BiTreeDepth
*�������ܣ����������� 
*����������������T 
*ע�ͣ���ʼ�����Ƕ������Ѵ��ڣ���������Ƿ��ض���������� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(logn)
****************************************************************/
int BiTreeDepth(BiTree T)
//�������T�����
{
    int depth = 0;
	if(T)
	{
		int lchilddepth = BiTreeDepth(T->lchild);
		int rchilddepth = BiTreeDepth(T->rchild);
		depth = ( lchilddepth >= rchilddepth ? (lchilddepth+1) : (rchilddepth+1));
	}
	//ʹ�õݹ�,�õ��������������,���Ƚϴ�С,֮�󷵻��������
	return depth;
}

/***************************************************************
*�������ƣ�LocateNode
*�������ܣ����ҽ�� 
*����������������T�������ҽ��Ĺؼ��� 
*ע�ͣ���ʼ�����Ƕ������Ѵ��ڣ���������Ƿ���T�йؼ���Ϊe�Ľ���ָ�� 
       �������ڣ�����NULL 
*����ֵ���ͣ�BiTree����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
BiTNode* LocateNode(BiTree T,KeyType e)
//���ҽ��
{
    if (!T) return ERROR;   //��������Ϊ��,����ERROR
	BiTNode *st[50], *p;//ջ 
	int top = 0;  
	st[top++] = T;
	while (top != 0){
		p = st[--top]; //�������
		if (p->data.key == e){
            return p;
        }
		else {
			if(p->rchild != NULL) 
				st[top++] = p->rchild;//�Ҷ�����ջ 
			if(p->lchild != NULL)
				st[top++] = p->lchild;//�������ջ 
		}
	}
	return NULL;//û�ҵ� 
}

/***************************************************************
*�������ƣ�Assign
*�������ܣ���㸳ֵ 
*����������������T������ֵ���Ĺؼ��� ��������� 
*ע�ͣ���ʼ�����Ƕ������Ѵ��ڣ�
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
status Assign(BiTree &T,KeyType e,TElemType value)
//��㸳ֵ��
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
            cnt ++;//�ؼ����Ƿ�Ϸ� 
		if (p->data.key == e){
            pos = p;//�ҵ��ڵ� 
        }
		else {
			if(p->rchild != NULL)
				st[top++] = p->rchild;
			if(p->lchild != NULL)
				st[top++] = p->lchild;
		}
	}
	if(pos == NULL) return ERROR;//û�ҵ� 
    if(cnt==0||(cnt==1&&pos->data.key==value.key)){
        pos->data = value;//�ҵ��ҹؼ��ֺϷ� 
        return OK;
    }
    else return -1;//�ؼ��ֲ��Ϸ� 
}

/***************************************************************
*�������ƣ�GetSibling
*�������ܣ����ֵܽ�� 
*����������������T�������ҽ��Ĺؼ��� 
*ע�ͣ���ʼ�����Ƕ������Ѵ��ڣ�
*����ֵ���ͣ�BiTree����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
BiTNode* GetSibling(BiTree T,KeyType e)
{
    BiTNode* p = NULL;
	if (T)
	{
		if (T->rchild!=NULL&&T->rchild->data.key == e)//����Һ��Ӳ�Ϊ�ղ��ҽڵ��ֵ����,��ô�㷵�����ӵ�ָ��
		return T->lchild;
        if (T->lchild!=NULL&&T->lchild->data.key == e)//����Һ��Ӳ�Ϊ�ղ��ҽڵ��ֵ����,��ô�㷵�����ӵ�ָ��
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
*�������ƣ�InsertNode
*�������ܣ�������
*����������������T����������Ĺؼ��֣� λ��LR�����c 
*ע�ͣ���ʼ�����Ƕ�����T�Ѵ��ڣ�����������ڽ�������½�� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
//�����㡣
{
    if(T == NULL) ERROR;
    BiTree p = NULL;
    if(LR == -1){//����ͷ��� 
        p = (BiTree)malloc(sizeof(BiTNode));
        p->data = c;
        p->rchild = T;
        p->lchild = NULL;
        T = p;
        return OK;
    }
    p = LocateNode(T, e);//�ҵ�λ�� 
    int cnt = cntkey(T, c.key);//�ؼ����Ƿ�Ϸ� 
    if(cnt != 0) return ERROR;
    if(p == NULL) return ERROR;//�Ҳ����ڵ� 
    if(LR == 0){//��� 
        BiTree q = (BiTree)malloc(sizeof(BiTNode));
        q->data = c;
        q->rchild = p->lchild;
        q->lchild = NULL;
        p->lchild = q;
        return OK;
    }
    else{//�ұ� 
        BiTree q = (BiTree)malloc(sizeof(BiTNode));
        q->data = c;
        q->rchild = p->lchild;
        q->lchild = NULL;
        p->rchild = q;
        return OK;
    }
	return OK;
}

void dfs(BiTree u,BiTree &ans,KeyType e)//�Ҹ��� 
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
*�������ƣ�DeleteNode
*�������ܣ�ɾ���ڵ�
*����������������T,��ɾ�����ؼ���
*ע�ͣ���ʼ�����Ƕ�����T�Ѵ���
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status DeleteNode(BiTree &T,KeyType e)
//ɾ����㡣
{
    if(T == NULL) 
		return ERROR;
    BiTNode *p = LocateNode(T, e);//p�Ǵ�ɾ����� 
    if(p == NULL) 
		return ERROR;
    int cnt = 0;//�������� 
    if(p->rchild) cnt++;
    if(p->lchild) cnt++;
    BiTNode *rnode = p->lchild, *del, *q = NULL;
    dfs(T, q, e);//�Ҹ��� 
    if(q == NULL){//���ڵ� 
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
    if(cnt == 0){//Ҷ�ӽڵ� 
        if(q->lchild&&q->lchild->data.key == e) 
        	q->lchild = NULL;
        if(q->rchild&&q->rchild->data.key == e)
        	q->rchild = NULL;
        free(p);
        return OK;
    }
    if(cnt == 1){//һ������ 
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
    if(cnt == 2){//������ 
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

void visit(BiTree T){//��ӡ��� 
    printf(" %d,%s",T->data.key,T->data.others);
}

/***************************************************************
*�������ƣ�PreOrderTraverse
*�������ܣ��������
*����������������T,����ָ��
*ע�ͣ���ʼ�����Ƕ�����T�Ѵ���
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
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
*�������ƣ�InOrderTraverse
*�������ܣ��������
*����������������T,����ָ��
*ע�ͣ���ʼ�����Ƕ�����T�Ѵ���
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    int top = 0;
    BiTree st[50]; //ջ 
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
*�������ƣ�PostOrderTraverse
*�������ܣ������
*����������������T,����ָ��
*ע�ͣ���ʼ�����Ƕ�����T�Ѵ���
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    if(T != NULL){
        if(T->lchild)//�ݹ� 
            PostOrderTraverse(T->lchild, visit);
        if(T->rchild)
            PostOrderTraverse(T->rchild, visit); 
        visit(T);
        return OK;
    }
}

/***************************************************************
*�������ƣ�LevelOrderTraverse
*�������ܣ��������
*����������������T,����ָ��
*ע�ͣ���ʼ�����Ƕ�����T�Ѵ���
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    BiTree st[50];//���� 
    int head = 0, tail = 0, len = 50;//ͷβָ�� ���г��� 
    BiTree p;
    st[tail++] = T;
    while(head != tail){//���в�Ϊ�� 
        p = st[head];
        head ++;//������ 
        if(p->lchild)
            st[tail++] = p->lchild;
        if(p->rchild)
            st[tail++] = p->rchild;
        visit(p);
    }
    return OK;
}

/***************************************************************
*�������ƣ�SaveBiTree
*�������ܣ����������
*���������� ������T,�ַ����� FileName 
*ע�ͣ������������浽�ļ��У�
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�O(n) 
****************************************************************/
status SaveBiTree(BiTree T, char *FileName)
//���������Ľ������д�뵽�ļ�FileName��
{

    FILE *fp;
    if((fp=fopen(FileName, "w")) == NULL) return ERROR; 
    if(T == NULL) return ERROR;
    int key = 0;//�ս��Ĺؼ��� 
	char ch[20];
    ch[0] = '#';//�ս������� 
    BiTree st[50];//ջ 
    int top = 0;
    st[top++] = T;
    BiTree p;
    while(top != 0){
        p = st[--top];//������� 
        if(p != NULL){
            fprintf(fp, "%d ", p->data.key);
            fprintf(fp, "%s ", p->data.others);
            st[top++] = p->rchild;//��ջ 
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
*�������ƣ�LoadBiTree
*�������ܣ������ļ�
*����������������T,�ַ�����FileName 
*ע�ͣ������ļ�
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n) 
****************************************************************/
status LoadBiTree(BiTree &T,  char FileName[])
//�����ļ�FileName�Ľ�����ݣ�����������
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
	    fscanf(fp, "%s ", ch);//���ļ������� 
        dataa[k].key = key;
        strcpy(dataa[k].others, ch);
        k++;
    }
    creatBitree(T, dataa);//���� 
    fclose(fp);
	return OK;
}

/***************************************************************
*�������ƣ�AddBiTree
*�������ܣ�Trees������һ������ΪBiTreeName�Ķ����� 
*����������������Trees���ַ�����BiTreeName���������������definition 
*ע�ͣ���ʼ��������Trees������
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�: O(n)
****************************************************************/
status AddBiTree(TREES &Trees, char BiTreeName[],TElemType definition[]){
	if(strlen(BiTreeName) > 30 ) return ERROR;//����̫���� 
    for(int i = 0; i < Trees.length; i++){
    	if(!strcmp(BiTreeName,Trees.elem[i].name))
    		return ERROR;
	}
	int flag1 = CreateBiTree(Trees.elem[Trees.length].T, definition);
    if(flag1 == OK) {//�ɹ������� 
    	strcpy(Trees.elem[Trees.length].name,BiTreeName); //������������
    	Trees.length ++;//���� +1
    	return OK;
	}
    else return ERROR;//����ʧ��
}

/***************************************************************
*�������ƣ�RemoveBiTree
*�������ܣ�Trees��ɾ��һ������ΪBiTreeName�Ķ����� 
*����������������Trees���ַ�����BiTreeName
*ע�ͣ���ʼ��������Trees������ 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�: O(n)
****************************************************************/
status RemoveBiTree(TREES &Trees,char BiTreeName[])
{
	if(Trees.length == 0) return ERROR;//�����0������û��ɾ 
    int flag = 0;//�ж��Ƿ�ɾ���ɹ� 
    for(int i = 0; i < Trees.length; i++){
        if(strcmp(BiTreeName,Trees.elem[i].name) == 0){//�ҵ����ֽ� BiTreeName���� 
            for(int j = i; j < Trees.length-1; j++){//�ƶ������ṹ����ֱ�Ӹ�ֵ 
                Trees.elem[j] = Trees.elem[j+1];
            }
            Trees.length -- ;//������-1
            flag = 1;//ɾ���ɹ� 
            break;
        }
        else continue;//������ 
    }
    if(flag) return OK;//�ɹ�ɾ�� 
    else return ERROR;//û�ҵ� 
}

/***************************************************************
*�������ƣ�LocateBiTree
*�������ܣ�Trees�в���һ������ΪBiTreeName�Ķ����� 
*����������������Trees���ַ�����BiTreeName
*ע�ͣ���ʼ��������Trees������ 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�: O(n)
****************************************************************/
status LocateBiTree(TREES Trees,char BiTreeName[])
// ��Trees�в���һ������ΪBiTreeName�������ɹ������߼���ţ����򷵻�0
{
    int loc = -1,flag = 0;//loc��¼λ�ã�flag��¼�Ƿ��� BiTreeName��
    for(int i = 0; i < Trees.length; i++){
        if(strcmp(BiTreeName,Trees.elem[i].name) == 0){//�ҵ� BiTreeName��
            flag = 1;
            loc = i;
            break;
        }
        else continue;//������ǣ�����һ�� 
    }
    if(flag) return loc + 1;//�ҵ������߼�λ�� 
    else return 0;//û�ҵ�����0 
}

/***************************************************************
*�������ƣ�PrintNodeByLevel
*�������ܣ������δ�ӡ�� 
*����������������root 
*ע�ͣ�root���� 
*����ֵ���ͣ�void 
*ʱ�临�Ӷ�: O(n)
****************************************************************/
void PrintNodeByLevel(BiTree root) {
	if(root == NULL) return; 
    queue<BiTree> Q;//������ 
    queue<char *> C; //�ַ������� 
    Q.push(root);//������� 
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
*�������ƣ�Build
*�������ܣ�������������򽨶����� 
*����������������root������������������� 
*ע�ͣ��������������������Ϊȫ�ֱ��� 
*����ֵ���ͣ�void 
*ʱ�临�Ӷ�: O(n)
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
	
	
