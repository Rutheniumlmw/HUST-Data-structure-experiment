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
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct{  //����ļ������Ͷ���
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
	int i_num = 9;//���ڲ��������Ա� 
	int op = 1;//�˵�
	while(op){
		system("cls");	//���� 
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
		printf("    ��ѡ����Ĳ���[0-23]:\n");
		scanf("%d", &op);
		switch(op){
			case 1://1�ǳ�ʼ������ 
				if(InitList(Lists.elem[i_num].L) == OK) {
					printf("������Ҫ��������Ա������\n");
					scanf("%s",Lists.elem[i_num].name);
					printf("���Ա����ɹ�\n"); 
				}
				else {
					printf("���Ա��Ѿ�����\n"); 
					printf("���Ա���ʧ��\n");
				}
				getchar();getchar();
				break; 
			case 2://2���������� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				} 
				if(DestroyList(Lists.elem[i_num].L) == OK){
					printf("���Ա����ٳɹ�\n"); 
					if(Lists.length != 0)
						Lists.length --; //���Ա���Ŀ��һ 
				}
				else printf("���Ա�����ʧ��\n");
				getchar(); getchar();
				break;
			case 3://3��������� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				if(ClearList(Lists.elem[i_num].L) == OK)
         			printf("���Ա���ճɹ�\n"); 
				else printf("���Ա����ʧ��\n");
				getchar(); getchar();
				break;
			case 4://4���ж��Ƿ��ǿ����� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				if(ListEmpty(Lists.elem[i_num].L) == TRUE){
         			printf("���Ա�Ϊ��\n"); 
				}
				else printf("���Ա��ǿձ�\n");
				getchar(); getchar();
				break;
			case 5:
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				printf("���Ա��Ϊ: %d\n",ListLength(Lists.elem[i_num].L));
         		getchar(); getchar();
         		break;
         	case 6://6�ǻ�ȡԪ�� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				printf("������ҪȡԪ�ص�λ��:\n");
				scanf("%d",&i);
				if(GetElem(Lists.elem[i_num].L,i,e) == OK)
					printf("��%d��λ��Ԫ����:%d\n",i,e);
				else 
					printf("����λ�ò��Ϸ�\n");
				getchar(); getchar();
				break;
			case 7://7����Ԫ�� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				printf("����������Ԫ�ص�ֵ��\n");
				scanf("%d", &e);
				if(i = LocateElem(Lists.elem[i_num].L,e)){
					printf("%dԪ��λ�ڵ�%d��λ��\n",e,i);
				} 
				else printf("%dԪ�������Ա��в�����\n",e);
				getchar(); getchar();
				break; 
			case 8://8��������Ԫ�ص�ǰ��
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				printf("����������Ԫ�أ�\n");
				scanf("%d",&e);
				val = PriorElem(Lists.elem[i_num].L,e,pre);
				if(val == OK)
		 			printf("ǰ��Ԫ��Ϊ��%d\n",pre);
		 		else if(val == -2)
		 			printf("��һ��Ԫ�ز�����ǰ��Ԫ�أ�\n");
		 		else  printf("���Ա���û�и�Ԫ�أ�\n");
		 		getchar();getchar();
		 		break;
			case 9://9������Ԫ��
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				} 
				printf("����������Ԫ�أ�\n");
				scanf("%d",&e);
				val = NextElem(Lists.elem[i_num].L,e,next);
				if(val == OK) 
					printf("%d�ĺ��Ԫ���ǣ�%d",e,next);
				else if(val == ERROR)
					printf("��Ԫ�ز����ں��Ԫ��");
				else 
					printf("���Ա���û�и�Ԫ��");
				getchar(); getchar();
				break;
			case 10://10���������в���Ԫ�� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				printf("��������Ҫ�����Ԫ��:\n");
         		scanf("%d",&e);
         		printf("��������Ҫ����Ԫ�ص�λ��:\n");
				scanf("%d",&i);
				val = ListInsert(Lists.elem[i_num].L,i,e);
				if(val == OK)
					printf("�������ݳɹ�\n");
				else 
					printf("����Ԫ��ʧ�ܣ�\n");
				getchar(); getchar();
				break;
			case 11://11�Ǵ�������ɾ��Ԫ�� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
			 	}
				printf("��������Ҫɾ����Ԫ�ص�λ�ã�\n");
				scanf("%d", &i);
				val = ListDelete(Lists.elem[i_num].L,i,e);
				if(val == OK){
					printf("ɾ����Ԫ���ǣ�%d\n",e);
					printf("ɾ���ɹ���\n");
				}
				else 
					printf("ɾ��ʧ��\n");
				getchar(); getchar();
				break;
			case 12://12�Ǳ������� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
			 	}
			 	if(ListEmpty(Lists.elem[i_num].L) == TRUE )
         			printf("���Ա��ǿձ�û������Ԫ��\n");
				else if(ListTraverse(Lists.elem[i_num].L) == OK)
					printf("\n���Ա�����ɹ�\n");
				else 
					printf("���Ա����ʧ��\n");
				getchar(); getchar();
				break;
			case 13://13�ǽ������浽�ļ���  
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
			 	}
				printf("���������뱣����ļ�����\n");
         		scanf("%s",FileName);
				val = SaveList(Lists.elem[i_num].L, FileName);
				if(val == OK) 
					printf("�ļ�����ɹ�\n�ļ�����%s\n",FileName);
				else 
					printf("����ʧ��");
				getchar(); getchar();
				break;
			case 14:
				printf("������Ҫ���ص��ļ�����\n");
				scanf("%s",FileName);
				val = LoadList(Lists.elem[i_num].L, FileName); 
				if(val == OK) 
					printf("�ļ����سɹ�\n");
				else 
					printf("�ļ�����ʧ��\n");
				getchar(); getchar();
				break;
			case 15:
				printf("������Ҫ��������Ա������\n");
				scanf("%s",ListName); 
				val = AddList(Lists,ListName);
				if(val == OK)	
					printf("���Ա�%s�ɹ��������Ա���\n",ListName);
				else 
					printf("���Ա������Ѿ�����Ϊ%s�����Ա�\n���Ա����ʧ��\n",ListName);
				getchar(); getchar();
				break;	
			case 16:
				printf("������Ҫɾ�����Ա������\n");
				scanf("%s",ListName);
				val = RemoveList(Lists,ListName);
				if(val == OK)
					printf("���Ա�%sɾ���ɹ�\n", ListName);
				else
					printf("���Ա����в�����%s���Ա�", ListName);
				getchar(); getchar();
				break;
			case 17://17�ǲ������� 
				printf("������Ҫ���ҵ����Ա�����ƣ�\n");
				scanf("%s",ListName);
				val = LocateList(Lists, ListName);
				if(val == 0)
					printf("���Ա����в�����%s���Ա�\n", ListName);
				else
					printf("%s���Ա�λ�����Ա����е�%d��λ��\n",ListName,val);
				getchar(); getchar();
				break;
			case 18://18��ѡ�����������
				printf("��ѡ����Ҫ���������Ա�\n"); 
				scanf("%d",&i_num);
				i_num --;
				printf("��ǰ���ڵ�%d�����Ա���в���\n",i_num+1); 
				getchar(); getchar();
				break;
			case 19://19������Ԫ��
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				} 
				if( !ListEmpty(Lists.elem[i_num].L)){
					printf("��ǰ�����ǿձ���ѡ��һ������������������\n");	
					getchar(); getchar();
					break;
				}	
				printf("������һϵ����-1��β��Ԫ��\n");
				val = InputList(Lists.elem[i_num].L);
				if(val == OK){
					printf("Ԫ������ɹ�\n");
					getchar(); getchar();
					break;
				}
			case 20://20��ɾ��������ĳ������Ԫ�� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				printf("������Ҫɾ��������Ԫ�أ�\n");
				scanf("%d", &e);
				val = ListDeleteAll(Lists.elem[i_num].L,e);
				if(val == 0)
					printf("��������û��%dԪ��\n",e);
				else 
					printf("ɾ���ɹ���\n");
				getchar(); getchar();
				break;
			case 21://21��ɾ����������һ��Ԫ�� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				val = ListDeleteBack(Lists.elem[i_num].L, e);
				if(val == -2)
					printf("�����ǿձ�ɾ��ʧ�ܣ�\n");
				else
					printf("ɾ���ɹ���");
				getchar(); getchar();
				break;	
			case 22://22�ǽ�������Ԫ�ذ���������߽���ķ�ʽ�������� 
				if(Lists.elem[i_num].L == NULL){
					printf("���Ա�����\n");
					getchar(); getchar();
					break; 
				}
				printf("��������������У�����������Ҫ�����еķ�ʽ:\n(1�����������У�2����������)\n") ;
				int m;
				scanf("%d", &m);
				if(m == 1)
					val = ListSort(Lists.elem[i_num].L, pf1);
				else if(m == 2)
					val = ListSort(Lists.elem[i_num].L, pf2);
				else printf("�������ֻ������1��2\n");
				if(val == OK&&m == 1)
					printf("�������гɹ�\n");
				if(val == OK&&m == 2) 
					printf("�������гɹ�\n");
				if(val == ERROR)
					printf("������û��Ԫ�أ��벻Ҫѡ�����������������\n");
				getchar(); getchar();
				break;	
			case 23:
				char listname1[30], listname2[30];
				int pos1, pos2;
				printf("����������鲢���������Ա�����ƣ�\n");
				scanf("%s",listname1);
				scanf("%s",listname2);
			 	pos1 = LocateList(Lists,listname1);//1
			 	pos2 = LocateList(Lists,listname2);//2
				if(!pos1 || !pos2){
			 		printf("����鲢�����Ա�����\n");
			 		getchar(); getchar();
			 		break;
				}
				val = MergeList(Lists.elem[pos1-1].L, Lists.elem[pos2-1].L);
				if(val)
				 	printf("���Ա�鲢�ɹ�");
				else
					printf("���Ա�鲢ʧ��");
				getchar(); getchar();
				break;			
			case 0:
				break;	
		}
	}
	return 0;
}

/***************************************************************
*�������ƣ�IntiaList
*�������ܣ�����һ���յ����Ա�
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա�L�������Ѵ��ڣ���������ǹ���һ���յ����Ա������Ա��Ѿ����ڣ�����INFEASIBLE
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1) 
****************************************************************/
status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    if(L!= NULL)
        return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));//��̬����
	if(L == NULL)
		exit(OVERFLOW);//���û���㹻�Ŀռ䣬����ʧ��
	L->data = 0;
	L->next = NULL;//�������б�ͷ�ڵ��������ͷ�ڵ��������ֵΪ0
	return OK;

}

/***************************************************************
*�������ƣ�DestoryList
*�������ܣ��������Ա�
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status DestroyList(LinkList &L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    if(L == NULL)//��δ��ʼ�� �������� 
        return INFEASIBLE;
    LinkList p,q;
    p = L;
    while(p){//����ѭ���ͷſռ� 
        q = p->next;
        free(p);
        p = q;
    }
    L = NULL; 
    return OK;
}

/***************************************************************
*�������ƣ�ClearList
*�������ܣ����˳���
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status ClearList(LinkList &L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
   
    if(L == NULL) //������ 
        return INFEASIBLE;
    LinkList p, q;
    p = L->next;//����ͷ���֮��Ľڵ� 
    while(p){
        q = p->next;
        free(p);
        p = q;
    }  
    L->next = NULL;
    return OK;

}

/***************************************************************
*�������ƣ�ListEmpty
*�������ܣ��ж����Ա��Ƿ�Ϊ��
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE��
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status ListEmpty(LinkList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L == NULL)//������ 
        return INFEASIBLE;
    if(L->next==NULL)//ͷ�����Ƿ��� 
        return TRUE;
    else
        return FALSE;
}

/***************************************************************
*�������ƣ�ListLength
*�������ܣ������Ա�ı�
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ���������Ƿ���L������Ԫ�صĸ�����
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    
    if(L == NULL) return INFEASIBLE;
    LinkList p, q;
    int length = 0;
    p = L->next;//��ͷ���֮��ĵ�һ���ڵ㿪ʼ���� 
    while(p){
        length++;
        p = p->next;
    }
    return length;//���ر� 

}

/***************************************************************
*�������ƣ�GetElem
*�������ܣ��õ�ĳһ��Ԫ�ص�ֵ
*��������:���Ա�L����ȡԪ�ص�λ�ã��洢Ԫ�ص�e 
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(1)
****************************************************************/
status GetElem(LinkList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L == NULL)
        return INFEASIBLE;
    if(i < 1)
        return ERROR;//λ�ò��Ϸ� 
    LinkList p = L->next;
    int cnt = 1;
    while(p && cnt<i){
        p = p->next;
        cnt++;
    }
    if(!p||cnt>i)
        return ERROR;//λ�ò��Ϸ� 
    else {
        e = p->data;//�ҵ��� ��ֵ 
        return OK;
    }
}

/***************************************************************
*�������ƣ�LocateElem
*�������ܣ�����Ԫ��
*�������������Ա�L��������Ԫ��e 
*ע�ͣ���ʼ���������Ա��Ѵ��ڣ���������Ƿ���L�е�1����e��� 
       ������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0��
*����ֵ���ͣ�int����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
status LocateElem(LinkList L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    if(L ==NULL)
        return INFEASIBLE;
    int i = 0;
    LinkList p = L->next;
    while(p){
        i++;
        if(p->data == e){
            return i;//�ҵ��ˣ�������� 
        }
        p = p->next;
    }
    return ERROR;
}

/***************************************************************
*�������ƣ�PriorElem
*�������ܣ���Ԫ�ص�ǰ��
*�������������Ա�L,������e���洢e��ǰ��pre 
*ע�ͣ���ʼ���������Ա�L�Ѵ��ڣ������������e��L������Ԫ�أ��Ҳ��ǵ�һ����
       ����pre��������ǰ������������OK���������ʧ�ܣ���������ERROR��
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L == NULL)
        return INFEASIBLE;
    LinkList p, q;
    p = L->next;
    if(p == NULL)
        return ERROR;//�ձ� 
    else
        q = p->next;
    if(p->data == e)
        return -2;//��һ��Ԫ��ûǰ�� 
    while(q){
        if(q->data == e){//�ҵ��� 
            pre = p->data;
            return OK;
        }
        p = p->next;
        q = q->next;
    }
    return ERROR;//���в����ڸ�Ԫ�� 

}

/***************************************************************
*�������ƣ�NextElem
*�������ܣ����̽ڵ�
*�������������Ա�L��������Ԫ��e���洢e�ĺ��Ԫ�صı���next 
*�����������ʼ���������Ա�L�Ѵ��ڣ������������e��L������Ԫ�أ��Ҳ������һ����
           ����next�������ĺ��,��������OK���������ʧ�ܣ�����ERROR��
*����ֵ���ͣ�status����
ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status NextElem(LinkList L,ElemType e,ElemType &next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
        return -2;//���һ��Ԫ��û�к�� 
    if(flag)
        return OK;
    else 
        return ERROR;
}

/***************************************************************
*�������ƣ�ListInsert
*�������ܣ�����Ԫ��
*�������������Ա�L��������λ��i��������Ԫ��e 
*ע�ͣ���ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)+1��
*      �����������L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status ListInsert(LinkList &L,int i,ElemType e)
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
*�������ƣ�ListDelete
*�������ܣ�ɾ��Ԫ��
*�������������Ա�L,��ɾ��λ�ã��洢��ɾ��Ԫ��e 
*ע�ͣ���ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)��
*      ���������ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status ListDelete(LinkList &L,int i,ElemType &e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
    if(cnt<i||!q)//λ�ò��Ϸ� 
        return ERROR;
    e = q->data;
    p->next = q->next;//�ı�ָ���� 
    free(q);//�ͷſռ� 
    return OK;
}

/***************************************************************
*�������ƣ�ListTrabverse
*�������ܣ�����˳���
*�������������Ա�L 
*ע�ͣ����˳����ֵ
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status ListTraverse(LinkList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
*�������ƣ�SaveList
*�������ܣ��������Ա�
*���������� ���Ա�L,�ַ����� FileName 
*ע�ͣ������Ա��浽�ļ��У�
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�O(n) 
****************************************************************/
status SaveList(LinkList L,char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
*�������ƣ�LoadList
*�������ܣ������ļ�
*�������������Ա�L,�ַ�����FileName 
*ע�ͣ������ļ�
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n) 
****************************************************************/
status LoadList(LinkList &L,char FileName[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
*�������ƣ�AddList
*�������ܣ�Lists������һ������ΪListName�Ŀ����Ա�
*�������������Ա���Lists���ַ�����ListName 
*ע�ͣ���ʼ��������Lists���Ա��� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�: 
****************************************************************/
status AddList(LISTS &Lists,char ListName[])
// ��Lists������һ������ΪListName�Ŀ����Ա�
{
    if(strlen(ListName) > 30 ) return ERROR;//����̫���� 
    for(int i = 0; i < Lists.length; i++){
    	if(!strcmp(ListName,Lists.elem[i].name))
    		return ERROR;
	}
    strcpy(Lists.elem[Lists.length].name,ListName); //��������Ա������ 
    int flag = InitList(Lists.elem[Lists.length].L);//���������Ա� 
    if(flag) {//�ɹ������ձ� 
    	Lists.length ++;//���Ա���� +1
    	return OK;
	}
    else return ERROR;//����ʧ�� 
}

/***************************************************************
*�������ƣ�RemoveList
*�������ܣ�Lists��ɾ��һ������ΪListName�Ŀ����Ա�
/�������������Ա���Lists���ַ�����ListName 
*ע�ͣ���ʼ��������Lists���Ա��� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:
****************************************************************/
status RemoveList(LISTS &Lists,char ListName[])
{
	if(Lists.length == 0) return ERROR;//�����0����û��ɾ 
    int flag = 0;//�ж��Ƿ�ɾ���ɹ� 
    for(int i = 0; i < Lists.length; i++){
        if(strcmp(ListName,Lists.elem[i].name) == 0){//�ҵ����ֽ� ListName�����Ա� 
            for(int j = i; j < Lists.length-1; j++){//�ƶ����Ա��ṹ����ֱ�Ӹ�ֵ 
                Lists.elem[j] = Lists.elem[j+1];
            }
            Lists.length -- ;//���Ա�����-1
            flag = 1;//ɾ���ɹ� 
            break;
        }
        else continue;//������ 
    }
    if(flag) return OK;//�ɹ�ɾ�� 
    else return ERROR;//û�ҵ� 
}

/***************************************************************
*�������ƣ�LocateList
*�������ܣ�Lists�в���һ������ΪListName�Ŀ����Ա�
*�������������Ա���Lists���ַ�����ListName 
*ע�ͣ���ʼ��������Lists���Ա��� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n)
****************************************************************/
status LocateList(LISTS Lists,char ListName[])
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{
    int loc = -1,flag = 0;//loc��¼λ�ã�flag��¼�Ƿ��� ListName���Ա� 
    for(int i = 0; i < Lists.length; i++){
        if(strcmp(ListName,Lists.elem[i].name) == 0){//�ҵ� ListName���Ա�
            flag = 1;
            loc = i;
            break;
        }
        else continue;//������ǣ�����һ�� 
    }
    if(flag) return loc + 1;//�ҵ������߼�λ�� 
    else return 0;//û�ҵ�����0 
}

/************************************************************
*�������ƣ�InputList
*�������ܣ��ڿ����Ա�������Ԫ�� 
*�������������Ա�L 
*ע�ͣ���ʼ���������Ա�L������Ϊ�� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n) 
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
*�������ƣ�ListDeleteAll
*�������ܣ���������ɾ�����е�Ԫ��e 
*�������������Ա�L ����ɾ��Ԫ��e 
*ע�ͣ���ʼ���������Ա�L����
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n) 
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
*�������ƣ�ListDeleteBack
*�������ܣ���������ɾ�����һ��Ԫ�أ����һ��Ԫ�ظ�ֵ��e 
*�������������Ա�L ��e 
*ע�ͣ���ʼ���������Ա�L�����Ҳ�Ϊ�ձ� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n) 
****************************************************************/
status ListDeleteBack(LinkList &L, int &e){
	if(L == NULL)
        return INFEASIBLE;
    LinkList p = L->next;
    if(p == NULL)
    	return -2;//�ձ� 
    LinkList q = L;
    while(p->next){//�ҵ����һ���ڵ� 
    	p = p->next;
    	q = q->next;
	}
	e = p->data;//��ֵ��e 
	free(p);//�ͷſռ� 
	q->next = NULL;//�޸�ָ���� 
	return OK;
} 

/************************************************************
*�������ƣ�cmp
*�������ܣ������ȽϺ��� 
*���������� ����int���͵��� 
*ע�ͣ��� 
*����ֵ���ͣ�int����
*ʱ�临�Ӷ�:O(1) 
****************************************************************/
int cmp1(int a, int b){
	return a > b;
} 
int cmp2(int a, int b){
	return a < b;
}
 
/************************************************************
*�������ƣ�ListSort
*�������ܣ��������е�Ԫ�ذ���������߽���ķ�ʽ�������� 
*�������������Ա�L������ָ��pcmp 
*ע�ͣ���ʼ���������Ա�L�����Ҳ�Ϊ�ձ� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n2) 
****************************************************************/
status ListSort(LinkList &L, int (*pcmp)(int a, int b)){
	if(L == NULL)
		return INFEASIBLE;
	LinkList p = L->next;
	LinkList q = L->next;
	LinkList r;
	int t = -1;//�м���� 
	if(!p)
		return ERROR;
	for(; q; q = q->next){
		for(p = L->next; p&&p->next; p = p->next){
			r = p->next; //p�ĺ�̽�� 
			if(pcmp(p->data, r->data)){//�ȽϹ��� 
				t = r->data;
				r->data = p->data;
				p->data = t;
			}
		}
	}
	return OK;
}

/************************************************************
*�������ƣ�MergeList
*�������ܣ�����������������ķ�ʽ�鲢 
*�������������Ա�L1�����Ա�L2
*ע�ͣ���ʼ���������Ա�L1��L2�����Ҳ�Ϊ�ձ� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n2) 
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





