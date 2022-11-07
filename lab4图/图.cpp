#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAX_num 20
const int N = 25;
const int INF = 0x3f3f3f3f;
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
     KeyType  key;
     char others[20];
} VertexType; //�������Ͷ���
typedef struct ArcNode {         //�������Ͷ���
        int adjvex;              //����λ�ñ�� 
     struct ArcNode  *nextarc;       //��һ������ָ��
} ArcNode;
typedef struct VNode{                //ͷ��㼰���������Ͷ���
        VertexType data;           //������Ϣ
     ArcNode *firstarc;           //ָ���һ����
} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //�ڽӱ�����Ͷ���
    AdjList vertices;          //ͷ�������
    int vexnum,arcnum;         //������������
    GraphKind  kind;        //ͼ������
} ALGraph;

typedef struct{  //ͼ�ļ������Ͷ���
    struct { 
		char name[30];
        ALGraph G;    
    }elem[MAX_num]; //20��ͼ 
    int length;
}GRAPHS;
GRAPHS Graphs;

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
int cnt(ALGraph G, KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
void visit(VertexType v);
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
void dfs(ALGraph G, int pos, void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
status createCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
status AddGraph(GRAPHS &Graphs, char GraphName[],VertexType V[],KeyType VR[][2]);
status RemoveGraph(GRAPHS &Graphs,char GraphName[]); 
status LocateGraph(GRAPHS &Graphs,char GraphName[]); 
void Change(ALGraph G);
void Floyd(int v, int u);
void printfpath(int u, int v, int path[][N]);

int visited[25] = {0}; //������� 
VertexType V[30];//�������� 
KeyType VR[100][2];//������ 
int map[N][N], path[N][N];//ͼ���ڽӾ�������·�� 
int i_num = 9;//ȫ�ֱ��� 

int main(){
	system("COLOR F0");//�׵׺��� 
	int op = 1, key, key1 , i = 0, j, val = -1, loc, loc1;
	VertexType v, w, u;//���� 
	char FileName[20], GraphName[20];
	while(op){
		system("cls");	//���� 
		printf("\n\n");
		printf("         Menu for Undirected Graph On Chain Structure \n");
		printf("------------------------------------------------------------\n");
		printf("          1. CreateCraph       11. DFSTraverse\n");
		printf("          2. DestroyGraph      12. BFSTraverse\n");
		printf("    	  3. LocateVex         13. SaveGraph\n");
		printf("    	  4. PutVex            14. LoadGraph\n");
		printf("    	  5. FirstAdjVex       15. EmptyGraph\n");
		printf("    	  6. NextAdjVex        16. AddGraph\n");
		printf("    	  7. InsertVex         17. RemoveGraph\n");
		printf("    	  8. DeleteVex         18. LocateGraph\n");
		printf("    	  9. InsertArc         19. ChooseGraph\n");	
		printf("    	  10. DeleteArc        20. Floyd\n");
		printf("    	  0. Exit\n");
		printf("------------------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0-20]:\n");
		scanf("%d",&op);//�˵� 
		switch(op){
			case 1://����ͼ
				if(Graphs.elem[i_num].G.vexnum != 0){//���ݽڵ����ж�ͼ�Ƿ�Ϊ�� 
					printf("ͼ�Ѵ��ڣ�\n");
					getchar(); getchar();
					break; 
				}
				printf("�����붥��ؼ��ֺ����ݣ�\n");
				i = 0;
				do {
    				scanf("%d%s",&V[i].key,V[i].others);
				} while(V[i++].key!=-1);
				i = 0;
				printf("������ߣ�\n"); 
				do {
    				scanf("%d%d",&VR[i][0],&VR[i][1]);
   				} while(VR[i++][0]!=-1);
   				val = CreateCraph(Graphs.elem[i_num].G, V, VR);
   				if(val == OK) printf("ͼ�����ɹ���\n");
   				else printf("ͼ����ʧ�ܣ�\n");//�ؼ��ֲ��Ϸ����߶��������Ϸ� 
				getchar(); getchar();
				break;
				
			case 2://����ͼ 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�\n");
					getchar(); getchar();
					break; 
				}
				val = DestroyGraph(Graphs.elem[i_num].G);
				if(val == OK) printf("ͼ���ٳɹ�\n");
				else printf("����ʧ��\n"); 
				getchar(); getchar();
				break;
				
			case 3://���Ҷ��� 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�\n");
					getchar(); getchar();
					break; 
				}
				printf("������Ҫ���Ҷ���Ĺؼ��֣�\n");
				scanf("%d", &key);
				val = LocateVex(Graphs.elem[i_num].G, key);
				if(val == -1) printf("Ҫ���ҽ����ͼ�в�����\n");
				else printf("�����ͼ�ĵ�%d��λ��\n", val);
				getchar(); getchar();
				break;
				
			case 4://���㸳ֵ 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				printf("������Ҫ��ֵ����ؼ��֣�\n");
				scanf("%d", &key);
				printf("������ؼ��ֺ����ݣ�");
				scanf("%d %s", &v.key, v.others);
				val = PutVex(Graphs.elem[i_num].G, key, v) ;
				if(val == OK) printf("��ֵ�ɹ���\n");
				else printf("��ֵʧ��!\n");
				getchar(); getchar();
				break;
				
			case 5://��һ�ڽӵ� 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				printf("������ؼ��֣�\n");
				scanf("%d", &key);
				val = FirstAdjVex(Graphs.elem[i_num].G, key);
				if(val != ERROR) printf("��һ�ڽӵ���ͼ��%d��λ��\n", val);
				else printf("����ʧ��\n");
				getchar(); getchar();
				break;
				
			case 6://��һ�ٽ�� 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				printf("�����������ؼ��֣�\n");
				scanf("%d %d", &key, &key1);
				val = NextAdjVex(Graphs.elem[i_num].G, key ,key1);
				if(val == -1) printf("����ʧ��\n");
				else printf("��һ�ٽ����ͼ�ĵ�%d��λ��\n",val);
				getchar(); getchar();
				break;
				
			case 7://���붥�� 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				printf("������Ҫ���붥��Ĺؼ��ֺ����ݣ�\n");
				scanf("%d %s", &v.key, v.others);
				val = InsertVex(Graphs.elem[i_num].G, v);
				if(val == OK) printf("���붥��ɹ�\n");
				else printf("����ʧ��!\n"); 
				getchar(); getchar();
				break;
				
			case 8://ɾ������ 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				printf("������Ҫɾ������Ĺؼ��֣�\n");
				scanf("%d", &key);
				val = DeleteVex(Graphs.elem[i_num].G, key);
				if(val == OK) printf("����ɾ���ɹ���\n");
				else printf("����ɾ��ʧ��\n");
				getchar(); getchar();
				break;
				
			case 9:
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				printf("�����������ؼ��֣�\n");
				scanf("%d %d", &key, &key1);
				val = InsertArc(Graphs.elem[i_num].G, key, key1);
				if(val == OK) printf("������ɹ���\n");
				else printf("������ʧ��\n");
				getchar(); getchar();
				break;
				
			case 10://ɾ���� 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				printf("�����������ؼ��֣�\n");
				scanf("%d %d", &key, &key1);
				val = DeleteArc(Graphs.elem[i_num].G, key, key1);
				if(val == OK) printf("��ɾ���ɹ���\n");
				else printf("��ɾ��ʧ��\n");
				getchar(); getchar();
				break;
				
			case 11://���� 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				memset(visited, 0, sizeof(visited));
				printf("ͼ��������ȱ���Ϊ��\n");
				DFSTraverse(Graphs.elem[i_num].G, visit);
				getchar(); getchar();
				break;
				
			case 12://����
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				} 
				memset(visited, 0, sizeof(visited));
				printf("ͼ�Ĺ�����ȱ���Ϊ��\n");
				BFSTraverse(Graphs.elem[i_num].G, visit);
				getchar(); getchar();
				break;
				
			case 13://�����ļ� 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				printf("���������뱣����ļ�����\n");
         		scanf("%s",FileName);
				val = SaveGraph(Graphs.elem[i_num].G, FileName);
				if(val == OK) 
					printf("�ļ�����ɹ�\n�ļ�����%s\n",FileName);
				else 
					printf("����ʧ��");
				getchar(); getchar();
				break;
				
			case 14://�����ļ�
			 	if(Graphs.elem[i_num].G.vexnum != 0){
					printf("ͼ�Ѵ��ڣ�");
					getchar(); getchar();
					break; 
				}
				printf("������Ҫ���ص��ļ�����\n");
				scanf("%s", FileName);
				val = LoadGraph(Graphs.elem[i_num].G, FileName);
				if(val == OK) printf("���سɹ�");
				else printf("����ʧ��");
				getchar(); getchar();
				break;
				
			case 15://�п� 
				if(Graphs.elem[i_num].G.vexnum == 0) printf("ͼΪ�գ�\n");
				else printf("ͼ��Ϊ�գ�\n");
				getchar(); getchar();
				break; 
				
			case 16://��ͼ 
				printf("������Ҫ�����ͼ�����֣�\n");
				scanf("%s", GraphName);
				printf("�����붥��ؼ��ֺ����ݣ�\n");
				i = 0;
				do {
    				scanf("%d%s",&V[i].key,V[i].others);
				} while(V[i++].key!=-1);
				i = 0;
				printf("������ߣ�\n"); 
				do {
    				scanf("%d%d",&VR[i][0],&VR[i][1]);
   				} while(VR[i++][0]!=-1);
   				val = AddGraph(Graphs, GraphName, V, VR);
   				if(val == OK) printf("ͼ�ɹ�����ͼ���ϣ�\n");
   				else printf("����ʧ�ܣ�\n");
				getchar(); getchar();
				break;
			
			case 17://ɾͼ
				printf("������Ҫɾ��ͼ������\n");
				scanf("%s",GraphName);
				val = RemoveGraph(Graphs, GraphName);
				if(val == OK)
					printf("ͼ%sɾ���ɹ�\n", GraphName);
				else
					printf("ͼ�����в�����%sͼ", GraphName);
				getchar(); getchar();
				break;
			
			case 18://��ͼ
				printf("������Ҫ���ҵ�ͼ�����ƣ�\n");
				scanf("%s",GraphName);
				val = LocateGraph(Graphs, GraphName);
				if(val == 0)
					printf("ͼ�����в�����%sͼ\n", GraphName);
				else
					printf("%sͼλ��ͼ�����е�%d��λ��\n", GraphName, val);
				getchar(); getchar();
				break; 
				
			case 19://ѡͼ 
				printf("��ѡ����Ҫ������ͼ����ţ�\n"); 
				scanf("%d", &i_num);
				i_num --;
				printf("��ǰ���ڵ�%d��ͼ���в���\n",i_num+1); 
				getchar(); getchar();
				break;	 
			
			case 20://floyd
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("ͼ�����ڣ�");
					getchar(); getchar();
					break; 
				}
				memset(map, INF, sizeof(map));//����ڽӾ��� 
				memset(path, -1, sizeof(path));//������·�� 
				printf("�����������ؼ��֣�\n");
				scanf("%d %d", &key, &key1);
				loc = LocateVex(Graphs.elem[i_num].G,key), loc1 = LocateVex(Graphs.elem[i_num].G,key1);
				if(loc==-1||loc1==-1){
					printf("�ؼ��ֲ��Ϸ���\n");
					getchar(); getchar();
					break;
				}
				Change(Graphs.elem[i_num].G);
				Floyd(loc, loc1);
				if(map[loc][loc1] == INF) printf("No Solution!");
				else {
					printf("���·�������ǣ�%d\n", map[loc][loc1]);
					printf("���·���ǣ�\n"); 
					printfpath(loc, loc1, path); 	
				} 
				getchar(); getchar();
				break;
				
			case 0:
				printf("����ʹ�ý�������ӭ�ٴ�ʹ�ã�\n"); 
				break;	
				
			default:
				printf("��ѡ����ȷ�Ĺ��ܣ�[0-20]\n");
				getchar(); getchar();
				break;
		}
	} 
	return 0;
} 


/***************************************************************
*�������ƣ�CreateCraph
*�������ܣ���������ͼ 
*����������ͼG ���㼯V���߼�VR 
*ע�ͣ���ʼ������ͼG�����ڣ���������ǹ�������ͼ����ͼ�Ѿ����ڣ�����ERROR
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    int i = 0, j = 0;
	ArcNode *p;
	VertexType v;
	G.vexnum = 0;
	G.arcnum = 0;
    int arrkey[50] = {0};
    v.key = V[0].key;
    strcpy(v.others, V[0].others);
	while(v.key != -1){
		for(int m = 0; m < G.vexnum; m++){
            if(v.key == arrkey[m]) return ERROR;//�Ƿ��йؼ����ظ� 
        }
		G.vertices[G.vexnum].data = v;
		G.vertices[G.vexnum].firstarc = NULL; //���㸳ֵ 
        arrkey[G.vexnum] = v.key;//ͳ�ƹؼ��� 
        G.vexnum ++;//������+1 
        i++;
        v.key = V[i].key;//��һ������ 
        strcpy(v.others, V[i].others);
	} 
    if(G.vexnum>20||G.vexnum<1)  return ERROR;//���������Ϸ� 
	G.kind = UDG;//ͼ������ 
	int a, b;
    int k = 0;
    a = VR[0][0];
    b = VR[0][1];
	while(a!=-1&&b!=-1){
		G.arcnum ++;//��+1 
		int loca = LocateVex(G, a);
        int locb = LocateVex(G, b);//�ҵ����� 
        if(loca==-1||locb==-1) return ERROR;//û�ҵ����� 
		
        p = (ArcNode *)malloc(sizeof(ArcNode));//���ӱ� 
		p->nextarc = G.vertices[loca].firstarc;
        p->adjvex = locb;
		G.vertices[loca].firstarc = p;

        p = (ArcNode *)malloc(sizeof(ArcNode));//���ӱ� 
		p->nextarc = G.vertices[locb].firstarc;
        p->adjvex = loca;
		G.vertices[locb].firstarc = p;

		k++;//������һ���� 
        a = VR[k][0];
        b = VR[k][1];
	}
	return OK;
}

/***************************************************************
*�������ƣ�DestroyGraph
*�������ܣ�����ͼ
*����������ͼG
*ע�ͣ���ʼ������ͼG���������������ͼG
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n2)
****************************************************************/
status DestroyGraph(ALGraph &G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
	ArcNode *p, *q;//�����͵�ָ��p,q
	for(int i = 0; i < G.vexnum; i++){
        p = G.vertices[i].firstarc;//pָ���i���ڵ�� ��һ�������ڸýڵ��ָ��
	    while(p){
	        q = p->nextarc;
	        free(p);
	        p = q;
	    }
	}
	G.vexnum = 0;//��ͼ������Ŀ,������Ϊ0
	G.arcnum = 0;
	return OK;
}

/***************************************************************
*�������ƣ�LocateVex
*�������ܣ����Ҷ���
*����������ͼG�������Ҷ���Ĺؼ��� 
*ע�ͣ���ʼ������ͼG�Ѵ��ڣ���������Ƿ���G�йؼ���Ϊu�Ķ����λ�� 
       �������ڣ�����-1
*����ֵ���ͣ�int����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
int LocateVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    for(int i = 0; i < G.vexnum; i++){
		if(u == G.vertices[i].data.key)//�жϽڵ�ؼ����Ƿ���ͬ
		return i;//������ҳɹ�������i��ֵ
	}
	return -1;
}

/***************************************************************
*�������ƣ�cnt
*�������ܣ�ͳ�ƹؼ��ֳ��ֵĴ��� 
*����������ͼG�������ҵĹؼ��� 
*ע�ͣ���ʼ������ͼG�Ѵ��ڣ���������Ƿ���G�йؼ���Ϊu�Ĵ��� 
*����ֵ���ͣ�int����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
int cnt(ALGraph G, KeyType u)//ͳ�ƹؼ��ֳ��ִ��� 
{
    int num = 0;
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == u) 
            num++;
    }
    return num;
}

/***************************************************************
*�������ƣ�PutVex
*�������ܣ����㸳ֵ 
*����������ͼG������ֵ����Ĺؼ��� ���������� 
*ע�ͣ���ʼ������ͼG�Ѵ��ڣ����ؼ��ֺϷ����ɹ���ֵ���ؼ��ֲ��Ϸ�������-1 
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    int loc = LocateVex(G, u);
    if(loc == -1) return ERROR;
    int keynum = cnt(G, value.key);
    if(keynum != 0) return ERROR;//�ؼ����ظ� 
    G.vertices[loc].data = value;
    return OK;
}

/***************************************************************
*�������ƣ�FirstAdjVex
*�������ܣ����Ҷ���ĵ�һ�ڽӵ� 
*����������ͼG�������Ҷ���Ĺؼ���
*ע�ͣ���ʼ������ͼG�Ѵ��ڣ����е�һ�ڽӵ㣬���ظö����λ�����ޣ�����-1 
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
int FirstAdjVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    int loc = LocateVex(G, u);
    if(loc == -1) return ERROR;//��㲻���� 
    ArcNode *p = G.vertices[loc].firstarc;
    if(p) return p->adjvex;
    else return ERROR;
}

/***************************************************************
*�������ƣ�NextAdjVex
*�������ܣ����Ҷ������һ�ڽӵ� 
*����������ͼG�������Ҷ���Ĺؼ��֣�w�Ĺؼ��� 
*ע�ͣ���ʼ������ͼG�Ѵ��ڣ������ڽӵ㣬���ظö����λ�����ޣ�����-1 
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n2)
****************************************************************/
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
    ArcNode *p;
	int v1 = LocateVex(G, v);//�ҵ����� 
	int w1 = LocateVex(G, w);
	if(v1 == -1 || w1 == -1)
	return -1;
	p = G.vertices[v1].firstarc;
	while (p && p->adjvex != w1){
		p = p->nextarc;//��w����һ�ڽӵ� 
	}
	if(!p) return -1;
	if(!p->nextarc) return -1;
	else return p->nextarc->adjvex;
}   

/***************************************************************
*�������ƣ�InsertVex
*�������ܣ����붥�� 
*����������ͼG�������붥�� 
*ע�ͣ���ʼ������ͼG�Ѵ��ڣ����ؼ��ֺϷ����ɹ����룬���Ϸ�����ERROR 
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
status InsertVex(ALGraph &G,VertexType v)
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    int keynum = cnt(G, v.key);
    if(keynum != 0) return ERROR;//�ؼ��ֲ��Ϸ� 
    if(G.vexnum == 20) return ERROR;//���������Ϸ� 
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum ++;
    return OK;
}

/***************************************************************
*�������ƣ�DeleteVex
*�������ܣ�ɾ������ 
*����������ͼG,��ɾ������ؼ���
*ע�ͣ���ʼ������ͼG�Ѵ���
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status DeleteVex(ALGraph &G,KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
	if(G.vexnum == 1) return ERROR;
    int i, j;
	ArcNode *p, *q;
	j = LocateVex(G, v);
	if(j == -1) return ERROR;
	p = G.vertices[j].firstarc;
	while(p){
	    q = p;
	    p = p->nextarc;
	    free(q);
	    G.arcnum--;
	}
	G.vexnum--;
	for(i = j; i < G.vexnum; i++)
	    G.vertices[i] = G.vertices[i+1];//�ƶ����� 
	for(i = 0; i < G.vexnum; i++){
		p = G.vertices[i].firstarc;
		while(p){
			if(p->adjvex == j){
				if(p == G.vertices[i].firstarc){
					G.vertices[i].firstarc = p->nextarc;
					free(p);
					p = G.vertices[i].firstarc;
				}
				else{
					q->nextarc = p->nextarc;
					free(p);
					p = q->nextarc;
				}
			}
			else{
				if(p->adjvex > j)//��1 
				p->adjvex --;
				q = p;
				p = p->nextarc;
			}
		}
	}
	return OK;
}

/***************************************************************
*�������ƣ�InsertArc
*�������ܣ������ 
*����������ͼG��������������Ĺؼ��� 
*ע�ͣ���ʼ������ͼG�Ѵ��ڣ������Ѵ��ڣ�����ʧ�ܣ�����ERROR 
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n)
****************************************************************/
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    int locv = LocateVex(G, v);
    int locw = LocateVex(G, w);
    if(locv==-1||locw==-1) return ERROR;
    ArcNode *q=G.vertices[locv].firstarc;
    int flag = 0;
    while(q){
        if(G.vertices[q->adjvex].data.key ==  G.vertices[locw].data.key){
            flag = 1;
            break;
        }
        q = q->nextarc;
    }
    if(flag) return ERROR;
    ArcNode *p;
    p = (ArcNode *)malloc(sizeof(ArcNode));
    p->nextarc = G.vertices[locv].firstarc;
    p->adjvex = locw;
	G.vertices[locv].firstarc = p;
    p = (ArcNode *)malloc(sizeof(ArcNode));
	p->nextarc = G.vertices[locw].firstarc;
    p->adjvex = locv;
	G.vertices[locw].firstarc = p; 
    G.arcnum++;
    return OK;
}
   
/***************************************************************
*�������ƣ�DeleteArc
*�������ܣ�ɾ���� 
*����������ͼG,��ɾ����������������Ĺؼ��� 
*ע�ͣ���ʼ������ͼG�Ѵ���
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    int locv = LocateVex(G, v);
    int locw = LocateVex(G, w);//�ҵ����� 
    if(locv==-1||locw==-1) return ERROR;
    ArcNode *q, *p;
    int flag1 = 0, flag2 = 0;//�Ƿ��ǵ�һ�ڽӵ� 
    
    q = G.vertices[locv].firstarc;
    if(q->adjvex == locw){//�ǵ�һ�ڽӵ� 
        G.vertices[locv].firstarc = NULL;
        free(q);
        flag1 = 1;
    }
    q = G.vertices[locw].firstarc;
    if(q->adjvex == locv){//�ǵ�һ�ڽӵ� 
        G.vertices[locw].firstarc = NULL;
        free(q);
        flag2 = 1;
    }

    if(!flag1){
        q = G.vertices[locv].firstarc;
        if(q) p = q->nextarc;
        while (p && p->adjvex != locw){
		    p = p->nextarc;
            q = q->nextarc;
	    }
        if(!p||!q) return ERROR;
        q->nextarc = p->nextarc;
        free(p);
    }

    if(!flag2){
        q = G.vertices[locw].firstarc;
        if(q) p = q->nextarc;
        while (p && p->adjvex != locv){
		    p = p->nextarc;
            q = q->nextarc;
	    }
        if(!p||!q) return ERROR;
        q->nextarc = p->nextarc;
        free(p);
    }

    G.arcnum -- ;//����-1 
    return OK;
}   

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}


void dfs(ALGraph G, int pos, void (*visit)(VertexType)){
    for(int i = pos; i < G.vexnum; i++){
        int vv = LocateVex(G, G.vertices[i].data.key);
        if(visited[vv] == 0){
            visited[vv] = 1;
            visit(G.vertices[i].data);
            if(G.vertices[i].firstarc){
                int loc = G.vertices[i].firstarc->adjvex;
                dfs(G, loc, visit);
            }
        }
        else return;
    }
} 

/***************************************************************
*�������ƣ�DFSTraverse
*�������ܣ�������ȱ������ 
*����������ͼG
*ע�ͣ���ʼ������ͼG�Ѵ���
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    dfs(G, 0, visit);//�ӵ�0������������ 
    return OK;
}

/***************************************************************
*�������ƣ�BFSTraverse
*�������ܣ�������ȱ������ 
*����������ͼG
*ע�ͣ���ʼ������ͼG�Ѵ���
*����ֵ���ͣ�status����
*ʱ�临�Ӷȣ�O(n) 
****************************************************************/
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    int queue[50];//���� 
    int front = 0, tail = 0;//ͷβ 
    ArcNode *p = NULL;
    int loc = -1;
    for(int i = 0; i < G.vexnum; i++){
        if(visited[i] != 1) {
            queue[tail++] = i;//����� 
            visited[i] = 1;
        } 
        while(front != tail){
            loc = queue[front++];//������
            visit(G.vertices[loc].data);
            p = G.vertices[loc].firstarc;
            while(p){
                if(visited[p->adjvex] != 1){
                    queue[tail++] = p->adjvex;
                    visited[p->adjvex] = 1;
                }
                p = p->nextarc;
            }
        }
    }
    return OK;
}

status createCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
{
    int i = 0, j = 0;
	ArcNode *p;
	VertexType v;
	G.vexnum = 0;
	G.arcnum = 0;
    int arrkey[50] = {0};
    v.key = V[0].key;
    strcpy(v.others, V[0].others);
	while(v.key != -1){
		for(int m = 0; m < G.vexnum; m++){
            if(v.key == arrkey[m]) return ERROR;
        }
		G.vertices[G.vexnum].data = v;
		G.vertices[G.vexnum].firstarc = NULL; 
        arrkey[G.vexnum] = v.key;
        G.vexnum ++;
        i++;
        v.key = V[i].key;
        strcpy(v.others, V[i].others);
	} 
    if(G.vexnum>20||G.vexnum<1)  return ERROR;
	G.kind = UDG;
	int a, b;
    int k = 0;
    a = VR[0][0];
    b = VR[0][1];
	while(a!=-1&&b!=-1){
		G.arcnum ++;
		int loca = LocateVex(G, a);
        int locb = LocateVex(G, b);
        if(loca==-1||locb==-1) return ERROR;
		
        p = (ArcNode *)malloc(sizeof(ArcNode));
		p->nextarc = G.vertices[loca].firstarc;
        p->adjvex = locb;
		G.vertices[loca].firstarc = p;

		k++;
        a = VR[k][0];
        b = VR[k][1];
	}
	return OK;
}

/***************************************************************
*�������ƣ�SaveGraph
*�������ܣ�����ͼ
*���������� ͼG,�ַ����� FileName 
*ע�ͣ���ͼ���浽�ļ��У�
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�O(n) 
****************************************************************/
status SaveGraph(ALGraph G, char FileName[])
//��ͼ������д�뵽�ļ�FileName��
{
    FILE *fp;
    if((fp = fopen(FileName, "w")) == NULL) return ERROR;
    fprintf(fp, "%d ", G.vexnum);
    fprintf(fp, "%d ", G.arcnum);//���涥�����뻡��
    for(int i = 0; i < G.vexnum; i++){//������
        fprintf(fp, "%d ", G.vertices[i].data.key);
        fprintf(fp, "%s ", G.vertices[i].data.others);
    }
    int keyflag = -1;
    char othersflag[10] = "nil";
    fprintf(fp, "%d ", keyflag);//�������
    fprintf(fp, "%s ", othersflag);
    int stack[50][2];
    int top = 0;
    int key1 = 0, key2 = 0;
    ArcNode *p = NULL;
    for(int i = 0; i < G.vexnum; i++){
        p = G.vertices[i].firstarc;
        while (p){
		    stack[top][0] = G.vertices[i].data.key;
            stack[top][1] = G.vertices[p->adjvex].data.key;
            top++;
            p = p->nextarc;
	    }
        while(top != 0){
            key1 = stack[top-1][0];
            key2 = stack[top-1][1];
            top -- ;
            fprintf(fp, "%d ", key1);
            fprintf(fp, "%d ", key2);
        }
    }
    fprintf(fp, "%d ", keyflag);//������
    fprintf(fp, "%d ", keyflag);
    fclose(fp);
    return OK;
}

/***************************************************************
*�������ƣ�LoadGraph
*�������ܣ������ļ�
*����������ͼG,�ַ�����FileName 
*ע�ͣ������ļ�
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�:O(n) 
****************************************************************/
status LoadGraph(ALGraph &G, char FileName[])
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    FILE *fp;
    fp = fopen(FileName, "r");
    int vexnum = -1, arcnum = -1, k = 0;
    VertexType V[25];
    KeyType VR[200][2];
    int key1 = -1, key2 = -1;
    fscanf(fp, "%d ", &vexnum);
    fscanf(fp, "%d ", &arcnum);
    for(int i = 0; i <= vexnum; i++){
        fscanf(fp, "%d ", &V[i].key);
        fscanf(fp, "%s ", V[i].others);
    }
    fscanf(fp, "%d ", &key1);
    fscanf(fp, "%d ", &key2);
    while(key1!=-1&&key2!=-1){
            VR[k][0] = key1;
            VR[k][1] = key2;
            k++;
        fscanf(fp, "%d ", &key1);
        fscanf(fp, "%d ", &key2);
    }
    createCraph(G,V,VR);
    return OK;
}

/***************************************************************
*�������ƣ�AddGraph
*�������ܣ�Graphs������һ������ΪGraphName��ͼ
*����������ͼ����Graphs���ַ�����GraphName�����㼯V���߼�VR 
*ע�ͣ���ʼ��������Graphsͼ����
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�: O(n)
****************************************************************/
status AddGraph(GRAPHS &Graphs, char GraphName[],VertexType V[],KeyType VR[][2])
{
	if(strlen(GraphName) > 30 ) return ERROR;//����̫���� 
    for(int i = 0; i < Graphs.length; i++){
    	if(!strcmp(GraphName, Graphs.elem[i].name))
    		return ERROR;
	}
	int flag1 = CreateCraph(Graphs.elem[Graphs.length].G, V, VR);
    if(flag1 == OK) {//�ɹ�����ͼ 
    	strcpy(Graphs.elem[Graphs.length].name,GraphName); //����ͼ������
    	Graphs.length ++;//ͼ�� +1
    	return OK;
	}
    else return ERROR;//����ʧ��	
}

/***************************************************************
*�������ƣ�RemoveGraph
*�������ܣ�Graphs��ɾ��һ������ΪGraphName��ͼ
*����������ͼ����Graphs���ַ�����GraphName
*ע�ͣ���ʼ��������Graphsͼ���� 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�: O(n)
****************************************************************/
status RemoveGraph(GRAPHS &Graphs,char GraphName[])
{
	if(Graphs.length == 0) return ERROR;//�����0����û��ɾ 
    int flag = 0;//�ж��Ƿ�ɾ���ɹ� 
    for(int i = 0; i < Graphs.length; i++){
        if(strcmp(GraphName,Graphs.elem[i].name) == 0){//�ҵ����ֽ� GraphName��ͼ 
            for(int j = i; j < Graphs.length-1; j++){//�ƶ�ͼ���ṹ����ֱ�Ӹ�ֵ 
                Graphs.elem[j] = Graphs.elem[j+1];
            }
            Graphs.length -- ;//ͼ����-1
            flag = 1;//ɾ���ɹ� 
            break;
        }
        else continue;//������ 
    }
    if(flag) return OK;//�ɹ�ɾ�� 
    else return ERROR;//û�ҵ� 
}

/***************************************************************
*�������ƣ�LocateGraph
*�������ܣ�Graphs�в���һ������ΪGraphName�Ķ����� 
*����������������Graphs���ַ�����GraphName
*ע�ͣ���ʼ��������Graphs������ 
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�: O(n)
****************************************************************/
status LocateGraph(GRAPHS &Graphs,char GraphName[])
// ��Graphs�в���һ������ΪGraphName��ͼ���ɹ������߼���ţ����򷵻�0
{
    int loc = -1,flag = 0;//loc��¼λ�ã�flag��¼�Ƿ��� GraphNameͼ
    for(int i = 0; i < Graphs.length; i++){
        if(strcmp(GraphName,Graphs.elem[i].name) == 0){//�ҵ� GraphNameͼ
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
*�������ƣ�Change
*�������ܣ����ڽӱ�ͼGת�����ڽӾ��� 
*����������ͼG 
*ע�ͣ���ʼ��������ͼG����
*����ֵ���ͣ�status����
*ʱ�临�Ӷ�: O(n)
****************************************************************/
void Change(ALGraph G){
//���ڽӱ�ת�����ڽӾ��� 
	memset(map, INF, sizeof(map));
	for(int i = 0; i < G.vexnum; i++) 
		map[i][i] = 0;//��ʼ�� 
	ArcNode *p;
	for(int i = 0; i < G.vexnum; i++){
		p = G.vertices[i].firstarc;
		while(p){
			map[i][p->adjvex] = map[p->adjvex][i] = 1;//����ͼ �ߵ�Ȩֵ��1 
			p=p->nextarc;
		}
	}
}
/***************************************************************
*�������ƣ�Floyd
*�������ܣ���������������֮������· 
*��������������ؼ��� 
*ע�ͣ���ʼ�����ǹؼ��ֺϷ� 
*����ֵ���ͣ�void
*ʱ�临�Ӷ�: O(n3)
****************************************************************/
void Floyd(int v, int u){
//��Դ���· 
	int x, y, w = 1;
	int n = Graphs.elem[i_num].G.vexnum;
	for(int k = 0; k < n; k++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(map[i][k]+map[k][j] < map[i][j]){
					map[i][j] = map[i][k]+map[k][j];
					path[i][j] = k;
				}
			}
		}
	}
	return ;
}

/***************************************************************
*�������ƣ�printfpath
*�������ܣ���ӡ���·���ĳ��� 
*��������������ؼ��� ·������path 
*ע�ͣ���ʼ�����ǹؼ��ֺϷ� 
*����ֵ���ͣ�void
*ʱ�临�Ӷ�: O(n)
****************************************************************/
void printfpath(int u, int v, int path[][N]){//��ӡ·�� 
	if(path[u][v] == -1){
		int key =  Graphs.elem[i_num].G.vertices[u].data.key;
		int key1 =  Graphs.elem[i_num].G.vertices[v].data.key;
		printf("<%d,%d> ", key, key1);
	}
	else{
		int mid = path[u][v];
		printfpath(u, mid, path);
		printfpath(mid, v, path); 
	}
}





