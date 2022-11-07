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
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
        int adjvex;              //顶点位置编号 
     struct ArcNode  *nextarc;       //下一个表结点指针
} ArcNode;
typedef struct VNode{                //头结点及其数组类型定义
        VertexType data;           //顶点信息
     ArcNode *firstarc;           //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;          //头结点数组
    int vexnum,arcnum;         //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;

typedef struct{  //图的集合类型定义
    struct { 
		char name[30];
        ALGraph G;    
    }elem[MAX_num]; //20个图 
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

int visited[25] = {0}; //标记数组 
VertexType V[30];//顶点数组 
KeyType VR[100][2];//边数组 
int map[N][N], path[N][N];//图的邻接矩阵和最短路径 
int i_num = 9;//全局变量 

int main(){
	system("COLOR F0");//白底黑字 
	int op = 1, key, key1 , i = 0, j, val = -1, loc, loc1;
	VertexType v, w, u;//顶点 
	char FileName[20], GraphName[20];
	while(op){
		system("cls");	//清屏 
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
		printf("    请选择你的操作[0-20]:\n");
		scanf("%d",&op);//菜单 
		switch(op){
			case 1://创建图
				if(Graphs.elem[i_num].G.vexnum != 0){//根据节点数判断图是否为空 
					printf("图已存在！\n");
					getchar(); getchar();
					break; 
				}
				printf("请输入顶点关键字和数据：\n");
				i = 0;
				do {
    				scanf("%d%s",&V[i].key,V[i].others);
				} while(V[i++].key!=-1);
				i = 0;
				printf("请输入边：\n"); 
				do {
    				scanf("%d%d",&VR[i][0],&VR[i][1]);
   				} while(VR[i++][0]!=-1);
   				val = CreateCraph(Graphs.elem[i_num].G, V, VR);
   				if(val == OK) printf("图创建成功！\n");
   				else printf("图创建失败！\n");//关键字不合法或者顶点数不合法 
				getchar(); getchar();
				break;
				
			case 2://销毁图 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！\n");
					getchar(); getchar();
					break; 
				}
				val = DestroyGraph(Graphs.elem[i_num].G);
				if(val == OK) printf("图销毁成功\n");
				else printf("销毁失败\n"); 
				getchar(); getchar();
				break;
				
			case 3://查找顶点 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！\n");
					getchar(); getchar();
					break; 
				}
				printf("请输入要查找顶点的关键字：\n");
				scanf("%d", &key);
				val = LocateVex(Graphs.elem[i_num].G, key);
				if(val == -1) printf("要查找结点在图中不存在\n");
				else printf("结点在图的第%d个位置\n", val);
				getchar(); getchar();
				break;
				
			case 4://顶点赋值 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				printf("请输入要赋值顶点关键字：\n");
				scanf("%d", &key);
				printf("请输入关键字和数据：");
				scanf("%d %s", &v.key, v.others);
				val = PutVex(Graphs.elem[i_num].G, key, v) ;
				if(val == OK) printf("赋值成功！\n");
				else printf("赋值失败!\n");
				getchar(); getchar();
				break;
				
			case 5://第一邻接点 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				printf("请输入关键字：\n");
				scanf("%d", &key);
				val = FirstAdjVex(Graphs.elem[i_num].G, key);
				if(val != ERROR) printf("第一邻接点在图的%d个位置\n", val);
				else printf("查找失败\n");
				getchar(); getchar();
				break;
				
			case 6://下一临界点 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				printf("请输入两个关键字：\n");
				scanf("%d %d", &key, &key1);
				val = NextAdjVex(Graphs.elem[i_num].G, key ,key1);
				if(val == -1) printf("查找失败\n");
				else printf("下一临界点在图的第%d个位置\n",val);
				getchar(); getchar();
				break;
				
			case 7://插入顶点 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				printf("请输入要插入顶点的关键字和数据：\n");
				scanf("%d %s", &v.key, v.others);
				val = InsertVex(Graphs.elem[i_num].G, v);
				if(val == OK) printf("插入顶点成功\n");
				else printf("插入失败!\n"); 
				getchar(); getchar();
				break;
				
			case 8://删除顶点 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				printf("请输入要删除顶点的关键字：\n");
				scanf("%d", &key);
				val = DeleteVex(Graphs.elem[i_num].G, key);
				if(val == OK) printf("顶点删除成功！\n");
				else printf("顶点删除失败\n");
				getchar(); getchar();
				break;
				
			case 9:
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				printf("请输入两个关键字：\n");
				scanf("%d %d", &key, &key1);
				val = InsertArc(Graphs.elem[i_num].G, key, key1);
				if(val == OK) printf("弧插入成功！\n");
				else printf("弧插入失败\n");
				getchar(); getchar();
				break;
				
			case 10://删除弧 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				printf("请输入两个关键字：\n");
				scanf("%d %d", &key, &key1);
				val = DeleteArc(Graphs.elem[i_num].G, key, key1);
				if(val == OK) printf("弧删除成功！\n");
				else printf("弧删除失败\n");
				getchar(); getchar();
				break;
				
			case 11://深搜 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				memset(visited, 0, sizeof(visited));
				printf("图的深度优先遍历为：\n");
				DFSTraverse(Graphs.elem[i_num].G, visit);
				getchar(); getchar();
				break;
				
			case 12://广搜
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				} 
				memset(visited, 0, sizeof(visited));
				printf("图的广度优先遍历为：\n");
				BFSTraverse(Graphs.elem[i_num].G, visit);
				getchar(); getchar();
				break;
				
			case 13://保存文件 
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				printf("请输入您想保存的文件名：\n");
         		scanf("%s",FileName);
				val = SaveGraph(Graphs.elem[i_num].G, FileName);
				if(val == OK) 
					printf("文件保存成功\n文件名是%s\n",FileName);
				else 
					printf("保存失败");
				getchar(); getchar();
				break;
				
			case 14://加载文件
			 	if(Graphs.elem[i_num].G.vexnum != 0){
					printf("图已存在！");
					getchar(); getchar();
					break; 
				}
				printf("请输入要加载的文件名：\n");
				scanf("%s", FileName);
				val = LoadGraph(Graphs.elem[i_num].G, FileName);
				if(val == OK) printf("加载成功");
				else printf("加载失败");
				getchar(); getchar();
				break;
				
			case 15://判空 
				if(Graphs.elem[i_num].G.vexnum == 0) printf("图为空！\n");
				else printf("图不为空！\n");
				getchar(); getchar();
				break; 
				
			case 16://加图 
				printf("请输入要保存的图的名字：\n");
				scanf("%s", GraphName);
				printf("请输入顶点关键字和数据：\n");
				i = 0;
				do {
    				scanf("%d%s",&V[i].key,V[i].others);
				} while(V[i++].key!=-1);
				i = 0;
				printf("请输入边：\n"); 
				do {
    				scanf("%d%d",&VR[i][0],&VR[i][1]);
   				} while(VR[i++][0]!=-1);
   				val = AddGraph(Graphs, GraphName, V, VR);
   				if(val == OK) printf("图成功加入图集合！\n");
   				else printf("加入失败！\n");
				getchar(); getchar();
				break;
			
			case 17://删图
				printf("请输入要删除图的名称\n");
				scanf("%s",GraphName);
				val = RemoveGraph(Graphs, GraphName);
				if(val == OK)
					printf("图%s删除成功\n", GraphName);
				else
					printf("图集合中不存在%s图", GraphName);
				getchar(); getchar();
				break;
			
			case 18://找图
				printf("请输入要查找的图的名称：\n");
				scanf("%s",GraphName);
				val = LocateGraph(Graphs, GraphName);
				if(val == 0)
					printf("图集合中不存在%s图\n", GraphName);
				else
					printf("%s图位于图集合中第%d个位置\n", GraphName, val);
				getchar(); getchar();
				break; 
				
			case 19://选图 
				printf("请选择您要操作的图的序号：\n"); 
				scanf("%d", &i_num);
				i_num --;
				printf("当前正在第%d个图进行操作\n",i_num+1); 
				getchar(); getchar();
				break;	 
			
			case 20://floyd
				if(Graphs.elem[i_num].G.vexnum == 0){
					printf("图不存在！");
					getchar(); getchar();
					break; 
				}
				memset(map, INF, sizeof(map));//清空邻接矩阵 
				memset(path, -1, sizeof(path));//清空最短路径 
				printf("请输入两个关键字：\n");
				scanf("%d %d", &key, &key1);
				loc = LocateVex(Graphs.elem[i_num].G,key), loc1 = LocateVex(Graphs.elem[i_num].G,key1);
				if(loc==-1||loc1==-1){
					printf("关键字不合法！\n");
					getchar(); getchar();
					break;
				}
				Change(Graphs.elem[i_num].G);
				Floyd(loc, loc1);
				if(map[loc][loc1] == INF) printf("No Solution!");
				else {
					printf("最短路径长度是：%d\n", map[loc][loc1]);
					printf("最短路径是：\n"); 
					printfpath(loc, loc1, path); 	
				} 
				getchar(); getchar();
				break;
				
			case 0:
				printf("本次使用结束，欢迎再次使用！\n"); 
				break;	
				
			default:
				printf("请选择正确的功能！[0-20]\n");
				getchar(); getchar();
				break;
		}
	} 
	return 0;
} 


/***************************************************************
*函数名称：CreateCraph
*函数功能：构造无向图 
*函数参数：图G 顶点集V，边集VR 
*注释：初始条件是图G不存在，操作结果是构造无向图。若图已经存在，返回ERROR
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
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
            if(v.key == arrkey[m]) return ERROR;//是否有关键字重复 
        }
		G.vertices[G.vexnum].data = v;
		G.vertices[G.vexnum].firstarc = NULL; //顶点赋值 
        arrkey[G.vexnum] = v.key;//统计关键字 
        G.vexnum ++;//顶点数+1 
        i++;
        v.key = V[i].key;//下一个顶点 
        strcpy(v.others, V[i].others);
	} 
    if(G.vexnum>20||G.vexnum<1)  return ERROR;//顶点数不合法 
	G.kind = UDG;//图的类型 
	int a, b;
    int k = 0;
    a = VR[0][0];
    b = VR[0][1];
	while(a!=-1&&b!=-1){
		G.arcnum ++;//边+1 
		int loca = LocateVex(G, a);
        int locb = LocateVex(G, b);//找到顶点 
        if(loca==-1||locb==-1) return ERROR;//没找到顶点 
		
        p = (ArcNode *)malloc(sizeof(ArcNode));//增加边 
		p->nextarc = G.vertices[loca].firstarc;
        p->adjvex = locb;
		G.vertices[loca].firstarc = p;

        p = (ArcNode *)malloc(sizeof(ArcNode));//增加边 
		p->nextarc = G.vertices[locb].firstarc;
        p->adjvex = loca;
		G.vertices[locb].firstarc = p;

		k++;//读入下一条边 
        a = VR[k][0];
        b = VR[k][1];
	}
	return OK;
}

/***************************************************************
*函数名称：DestroyGraph
*函数功能：销毁图
*函数参数：图G
*注释：初始条件是图G；操作结果是销毁图G
*返回值类型：status类型
*时间复杂度：O(n2)
****************************************************************/
status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
	ArcNode *p, *q;//边类型的指针p,q
	for(int i = 0; i < G.vexnum; i++){
        p = G.vertices[i].firstarc;//p指向第i个节点的 第一条依附于该节点的指针
	    while(p){
	        q = p->nextarc;
	        free(p);
	        p = q;
	    }
	}
	G.vexnum = 0;//将图顶点数目,边数置为0
	G.arcnum = 0;
	return OK;
}

/***************************************************************
*函数名称：LocateVex
*函数功能：查找顶点
*函数参数：图G，待查找顶点的关键字 
*注释：初始条件是图G已存在；操作结果是返回G中关键字为u的顶点的位置 
       若不存在，返回-1
*返回值类型：int类型
*时间复杂度：O(n)
****************************************************************/
int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    for(int i = 0; i < G.vexnum; i++){
		if(u == G.vertices[i].data.key)//判断节点关键字是否相同
		return i;//如果查找成功，返回i的值
	}
	return -1;
}

/***************************************************************
*函数名称：cnt
*函数功能：统计关键字出现的次数 
*函数参数：图G，待查找的关键字 
*注释：初始条件是图G已存在；操作结果是返回G中关键字为u的次数 
*返回值类型：int类型
*时间复杂度：O(n)
****************************************************************/
int cnt(ALGraph G, KeyType u)//统计关键字出现次数 
{
    int num = 0;
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == u) 
            num++;
    }
    return num;
}

/***************************************************************
*函数名称：PutVex
*函数功能：顶点赋值 
*函数参数：图G，待赋值顶点的关键字 ，顶点数据 
*注释：初始条件是图G已存在；若关键字合法，成功赋值，关键字不合法，返回-1 
*返回值类型：status类型
*时间复杂度：O(n)
****************************************************************/
status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    int loc = LocateVex(G, u);
    if(loc == -1) return ERROR;
    int keynum = cnt(G, value.key);
    if(keynum != 0) return ERROR;//关键字重复 
    G.vertices[loc].data = value;
    return OK;
}

/***************************************************************
*函数名称：FirstAdjVex
*函数功能：查找顶点的第一邻接点 
*函数参数：图G，待查找顶点的关键字
*注释：初始条件是图G已存在；若有第一邻接点，返回该顶点的位序。若无，返回-1 
*返回值类型：status类型
*时间复杂度：O(n)
****************************************************************/
int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    int loc = LocateVex(G, u);
    if(loc == -1) return ERROR;//结点不存在 
    ArcNode *p = G.vertices[loc].firstarc;
    if(p) return p->adjvex;
    else return ERROR;
}

/***************************************************************
*函数名称：NextAdjVex
*函数功能：查找顶点的下一邻接点 
*函数参数：图G，待查找顶点的关键字，w的关键字 
*注释：初始条件是图G已存在；若有邻接点，返回该顶点的位序。若无，返回-1 
*返回值类型：status类型
*时间复杂度：O(n2)
****************************************************************/
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    ArcNode *p;
	int v1 = LocateVex(G, v);//找到顶点 
	int w1 = LocateVex(G, w);
	if(v1 == -1 || w1 == -1)
	return -1;
	p = G.vertices[v1].firstarc;
	while (p && p->adjvex != w1){
		p = p->nextarc;//找w的下一邻接点 
	}
	if(!p) return -1;
	if(!p->nextarc) return -1;
	else return p->nextarc->adjvex;
}   

/***************************************************************
*函数名称：InsertVex
*函数功能：插入顶点 
*函数参数：图G，待插入顶点 
*注释：初始条件是图G已存在；若关键字合法，成功插入，不合法返回ERROR 
*返回值类型：status类型
*时间复杂度：O(n)
****************************************************************/
status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    int keynum = cnt(G, v.key);
    if(keynum != 0) return ERROR;//关键字不合法 
    if(G.vexnum == 20) return ERROR;//顶点数不合法 
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum ++;
    return OK;
}

/***************************************************************
*函数名称：DeleteVex
*函数功能：删除顶点 
*函数参数：图G,待删除顶点关键字
*注释：初始条件是图G已存在
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
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
	    G.vertices[i] = G.vertices[i+1];//移动顶点 
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
				if(p->adjvex > j)//减1 
				p->adjvex --;
				q = p;
				p = p->nextarc;
			}
		}
	}
	return OK;
}

/***************************************************************
*函数名称：InsertArc
*函数功能：插入边 
*函数参数：图G，边连接两顶点的关键字 
*注释：初始条件是图G已存在；若边已存在，插入失败，返回ERROR 
*返回值类型：status类型
*时间复杂度：O(n)
****************************************************************/
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
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
*函数名称：DeleteArc
*函数功能：删除边 
*函数参数：图G,待删除边连接两个顶点的关键字 
*注释：初始条件是图G已存在
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    int locv = LocateVex(G, v);
    int locw = LocateVex(G, w);//找到顶点 
    if(locv==-1||locw==-1) return ERROR;
    ArcNode *q, *p;
    int flag1 = 0, flag2 = 0;//是否是第一邻接点 
    
    q = G.vertices[locv].firstarc;
    if(q->adjvex == locw){//是第一邻接点 
        G.vertices[locv].firstarc = NULL;
        free(q);
        flag1 = 1;
    }
    q = G.vertices[locw].firstarc;
    if(q->adjvex == locv){//是第一邻接点 
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

    G.arcnum -- ;//边数-1 
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
*函数名称：DFSTraverse
*函数功能：深度优先遍历结点 
*函数参数：图G
*注释：初始条件是图G已存在
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    dfs(G, 0, visit);//从第0个结点进行深搜 
    return OK;
}

/***************************************************************
*函数名称：BFSTraverse
*函数功能：广度优先遍历结点 
*函数参数：图G
*注释：初始条件是图G已存在
*返回值类型：status类型
*时间复杂度：O(n) 
****************************************************************/
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int queue[50];//队列 
    int front = 0, tail = 0;//头尾 
    ArcNode *p = NULL;
    int loc = -1;
    for(int i = 0; i < G.vexnum; i++){
        if(visited[i] != 1) {
            queue[tail++] = i;//入队列 
            visited[i] = 1;
        } 
        while(front != tail){
            loc = queue[front++];//出队列
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
*函数名称：SaveGraph
*函数功能：保存图
*函数参数： 图G,字符数组 FileName 
*注释：将图保存到文件中，
*返回值类型：status类型
*时间复杂度O(n) 
****************************************************************/
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE *fp;
    if((fp = fopen(FileName, "w")) == NULL) return ERROR;
    fprintf(fp, "%d ", G.vexnum);
    fprintf(fp, "%d ", G.arcnum);//保存顶点数与弧数
    for(int i = 0; i < G.vexnum; i++){//保存结点
        fprintf(fp, "%d ", G.vertices[i].data.key);
        fprintf(fp, "%s ", G.vertices[i].data.others);
    }
    int keyflag = -1;
    char othersflag[10] = "nil";
    fprintf(fp, "%d ", keyflag);//顶点结束
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
    fprintf(fp, "%d ", keyflag);//弧结束
    fprintf(fp, "%d ", keyflag);
    fclose(fp);
    return OK;
}

/***************************************************************
*函数名称：LoadGraph
*函数功能：加载文件
*函数参数：图G,字符数组FileName 
*注释：加载文件
*返回值类型：status类型
*时间复杂度:O(n) 
****************************************************************/
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
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
*函数名称：AddGraph
*函数功能：Graphs中增加一个名称为GraphName的图
*函数参数：图集合Graphs，字符数组GraphName，顶点集V，边集VR 
*注释：初始条件是有Graphs图集合
*返回值类型：status类型
*时间复杂度: O(n)
****************************************************************/
status AddGraph(GRAPHS &Graphs, char GraphName[],VertexType V[],KeyType VR[][2])
{
	if(strlen(GraphName) > 30 ) return ERROR;//名字太长了 
    for(int i = 0; i < Graphs.length; i++){
    	if(!strcmp(GraphName, Graphs.elem[i].name))
    		return ERROR;
	}
	int flag1 = CreateCraph(Graphs.elem[Graphs.length].G, V, VR);
    if(flag1 == OK) {//成功创建图 
    	strcpy(Graphs.elem[Graphs.length].name,GraphName); //保存图的名字
    	Graphs.length ++;//图数 +1
    	return OK;
	}
    else return ERROR;//增加失败	
}

/***************************************************************
*函数名称：RemoveGraph
*函数功能：Graphs中删除一个名称为GraphName的图
*函数参数：图集合Graphs，字符数组GraphName
*注释：初始条件是有Graphs图集合 
*返回值类型：status类型
*时间复杂度: O(n)
****************************************************************/
status RemoveGraph(GRAPHS &Graphs,char GraphName[])
{
	if(Graphs.length == 0) return ERROR;//如果有0个，没法删 
    int flag = 0;//判断是否删除成功 
    for(int i = 0; i < Graphs.length; i++){
        if(strcmp(GraphName,Graphs.elem[i].name) == 0){//找到名字叫 GraphName的图 
            for(int j = i; j < Graphs.length-1; j++){//移动图，结构可以直接赋值 
                Graphs.elem[j] = Graphs.elem[j+1];
            }
            Graphs.length -- ;//图数量-1
            flag = 1;//删除成功 
            break;
        }
        else continue;//继续找 
    }
    if(flag) return OK;//成功删除 
    else return ERROR;//没找到 
}

/***************************************************************
*函数名称：LocateGraph
*函数功能：Graphs中查找一个名称为GraphName的二叉树 
*函数参数：树集合Graphs，字符数组GraphName
*注释：初始条件是有Graphs树集合 
*返回值类型：status类型
*时间复杂度: O(n)
****************************************************************/
status LocateGraph(GRAPHS &Graphs,char GraphName[])
// 在Graphs中查找一个名称为GraphName的图，成功返回逻辑序号，否则返回0
{
    int loc = -1,flag = 0;//loc记录位置，flag记录是否有 GraphName图
    for(int i = 0; i < Graphs.length; i++){
        if(strcmp(GraphName,Graphs.elem[i].name) == 0){//找到 GraphName图
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
*函数名称：Change
*函数功能：将邻接表图G转换成邻接矩阵 
*函数参数：图G 
*注释：初始条件是有图G存在
*返回值类型：status类型
*时间复杂度: O(n)
****************************************************************/
void Change(ALGraph G){
//将邻接表转换成邻接矩阵 
	memset(map, INF, sizeof(map));
	for(int i = 0; i < G.vexnum; i++) 
		map[i][i] = 0;//初始化 
	ArcNode *p;
	for(int i = 0; i < G.vexnum; i++){
		p = G.vertices[i].firstarc;
		while(p){
			map[i][p->adjvex] = map[p->adjvex][i] = 1;//无向图 边的权值是1 
			p=p->nextarc;
		}
	}
}
/***************************************************************
*函数名称：Floyd
*函数功能：求任意两个顶点之间的最短路 
*函数参数：顶点关键字 
*注释：初始条件是关键字合法 
*返回值类型：void
*时间复杂度: O(n3)
****************************************************************/
void Floyd(int v, int u){
//多源最短路 
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
*函数名称：printfpath
*函数功能：打印最短路径的长度 
*函数参数：顶点关键字 路径数组path 
*注释：初始条件是关键字合法 
*返回值类型：void
*时间复杂度: O(n)
****************************************************************/
void printfpath(int u, int v, int path[][N]){//打印路径 
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





