#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct StackNode {
    ElementType data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    int size;
} LinkStack;

typedef enum { OK = 1, ERROR = 0 } Status;

/* ???????? */
//创建新链栈
LinkStack* InitStack(void){
	LinkStack* S = (LinkStack*)malloc(sizeof(LinkStack));
	if(S==NULL) return NULL;
	S->top = NULL;
	S->size = 0;
	return S;
};
//判空
int IsEmpty(const LinkStack* S){
	if(S==NULL||S->top==NULL) return 1;
	if(S->top!=NULL) return 0;
};
//获取链栈长度
int GetSize(const LinkStack* S){
	if(S==NULL) return 0;
	return S->size;
};
//压入新数据
Status Push(LinkStack* S, ElementType x){
	if(S==NULL) return ERROR;
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if(newNode==NULL) return ERROR;
	newNode->data = x;
	newNode->next = S->top;
	S->top = newNode;
	S->size++; 
	return OK;
};
//删除顶数据
Status Pop(LinkStack* S, ElementType* x){
	if(S==NULL||x==NULL) return ERROR;
	if(IsEmpty(S)) return ERROR;
	StackNode* Del = S->top;
	S->top = S->top->next;
	*x = Del->data;
	free(Del);
	S->size--;
	return OK;
};
//读取顶数据
Status GetTop(const LinkStack* S, ElementType* x){
	if(S==NULL||x==NULL) return ERROR;
	if(IsEmpty(S)) return ERROR;
	*x = S->top->data;
	return OK;
};
//清空链栈（保留S,S->top=NULL）
void Clear(LinkStack* S){
	if(S==NULL||S->size==0) return;
	StackNode* Del = S->top;
	StackNode* next = NULL;
	while(Del!=NULL){
		next = Del->next;
		free(Del);
		Del = next;
	}
	S->size = 0;
	S->top = NULL;
};
//摧毁链栈
void DestroyStack(LinkStack** pS){
	if(pS==NULL||*pS==NULL) return;
	StackNode* Del = (*pS)->top;
	StackNode* next = NULL;
	while(Del){
		next = Del->next;
		free(Del);
		Del = next;
	}
	*pS = NULL;
	return;
};
//打印链栈
void PrintStack(const LinkStack* S){
	if(S==NULL||S->size==0){
		printf("NULL\n");
		return;
	}
	int lst[S->size];
	StackNode* temp = S->top;
	for(int i=0;i<S->size;i++){
		lst[i] = temp->data;
		temp = temp->next;
	}
	for(int i=S->size-1;i>=0;i--){
		printf("%d",lst[i]);
		if(i!=0) printf(" ");
	}
	printf("\n");
	return;
}
//赋值链栈
Status CopyStack(const LinkStack* S,LinkStack* T){
	if(S==NULL||T==NULL) return ERROR;
	int lst[S->size];
	StackNode* temp = S->top;
	for(int i=0;i<S->size;i++){
		lst[i] = temp->data;
		temp = temp->next;
	}
	StackNode* head = NULL;
	for(int i=S->size-1;i>=0;i--){
		StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
		if(newNode==NULL) return ERROR;
		newNode->data = lst[i];
		newNode->next = head;
		head = newNode;
	}
	Clear(T);
	T->top = head;
	T->size = S->size;
	return OK;
}
//逆置链栈
Status ReverseStack(LinkStack* S){
	if(S==NULL) return ERROR;
	if(S->size==0||S->size==1) return OK;
	int lst[S->size];
	StackNode* temp = S->top;
	StackNode* pre = NULL;
	StackNode* next = NULL;
	while(temp!=NULL){
		next = temp->next;
		temp->next = pre;
		pre = temp;
		temp = next;
	}
	S->top = pre;
	return OK;
}
//获取链栈中最小值
Status GetMin(const LinkStack* S,ElementType* min){
	if(S==NULL||min==NULL||S->top==NULL) return ERROR;
	*min = S->top->data;
	StackNode* temp = S->top;
	while(temp){
		if(*min>temp->data){
			*min = temp->data;
		}
		temp =temp->next;
	}
	return OK;
}
//判断对称
Status IsSymmetric(const LinkStack* S){
	if(S==NULL) return ERROR;
	if(S->top==NULL||S->top->next==NULL) return OK;
	int lst[S->size];
	StackNode* temp = S->top;
	for(int i=0;i<S->size;i++){
		lst[i] = temp->data;
		temp = temp->next;
	}
	int head = 0,tail = S->size-1;
	bool ifs = true;
	while(head<tail){
		if(lst[head]!=lst[tail]){
			ifs = false;
			break;
		}
		head++;tail--;
	}
	if(ifs) return OK;
	return ERROR;
}
//删除指定值的数据
Status DeleteElem(LinkStack* S,ElementType e){
	if(S==NULL) return ERROR;
	StackNode* pre = NULL;
	StackNode* temp = S->top;
	StackNode* next = NULL;
	StackNode* Del = NULL;
	while(temp){
		next = temp->next;
		if(temp->data==e){
			Del = temp;
			if(pre==NULL){
				S->top = next;
			}else{
				pre->next = next;
			}
			free(Del);
			S->size--;
		}else{
			pre = temp;
		}
		temp = next;
	}
	return OK;
}
//合并链栈（先S1后S2）
Status MergeStack(const LinkStack* S1,const LinkStack* S2,LinkStack* S3){
	if(S1==NULL||S2==NULL||S3==NULL) return ERROR;
	StackNode* head = NULL;
	StackNode* temp3 = NULL;
	StackNode* tempa = S2->top;
	while(tempa){
		StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
		if(newNode==NULL){
			StackNode* tempb = head;
			StackNode* next = NULL;
			while(tempb){
				next = tempb->next;
				free(tempb);
				tempb = next;
			}
			return ERROR;
		}
		newNode->data = tempa->data;
		newNode->next = NULL;
		if(temp3==NULL){
			temp3 = newNode;
		}else{
			temp3->next = newNode;
			temp3 = temp3->next;
		}
		if(head==NULL){
			head = temp3;
		}
		tempa = tempa->next;
	}
	tempa = S1->top;
	while(tempa){
		StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
		if(newNode==NULL){
			StackNode* tempb = head;
			StackNode* next = NULL;
			while(tempb){
				next = tempb->next;
				free(tempb);
				tempb = next;
			}
			return ERROR;
		}
		newNode->data = tempa->data;
		newNode->next = NULL;
		if(temp3==NULL){
			temp3 = newNode;
		}else{
			temp3->next = newNode;
			temp3 = temp3->next;
		}
		if(head==NULL){
			head = temp3;
		}
		tempa = tempa->next;
	}
	Clear(S3);
	S3->size = S1->size+S2->size;
	S3->top = head;
	return OK;
}
//去重
Status RemoveDuplicate(LinkStack* S){
	if(S==NULL) return ERROR;
	StackNode* temp = S->top;
	int lst[S->size];
	for(int i=0;i<S->size;i++){
		lst[i] = temp->data;
		temp = temp->next;
	}
	for(int i=0;i<S->size/2;i++){
		int a = lst[i];
		lst[i] = lst[S->size-1-i];
		lst[S->size-1-i] = a;
	}
	int uniq[S->size];
    int un = 0;
    for (int i = 0; i < S->size; i++) {
        int had = 0;
        for (int j = 0; j < un; j++) {
            if (uniq[j] == lst[i]) {
                had = 1;
                break;
            }
        }
        if (!had) uniq[un++] = lst[i];
    }
    Clear(S);
    for (int i = 0; i < un; i++) {
        Push(S, uniq[i]);
    }
	return OK;
}
//逆置栈顶k个元素
Status ReverseTop(LinkStack* S,int k){
	if(S==NULL||k<0||k>S->size) return ERROR;
	if(k==0||k==1) return OK;
	StackNode* temp = S->top;
	int lst[k];
	for(int i=0;i<k;i++){
		Pop(S,&lst[i]);
	}
	for(int i=0;i<k;i++){
		Push(S,lst[i]);
	}
	return OK;
}
//计算范围内数据和
Status GetRangeSum(const LinkStack* S,int low,int high,int* sum){
	if(S==NULL||sum==NULL||low<1||high<low||high>S->size) return ERROR;
	StackNode* temp = S->top;
	int lst[S->size];
	int summ = 0;
	for(int i=0;i<S->size;i++){
		lst[i] = temp->data;
		temp = temp->next;
	}
	for(int i=S->size-low;i>=S->size-high;i--){
		summ+=lst[i];
	}
	*sum = summ;
	return OK;
}
//合并链栈（S1，S2交替）
Status InterleaveStack(const LinkStack* S1, const LinkStack* S2,LinkStack* S3){
	if(S1==NULL||S2==NULL||S3==NULL) return ERROR;
	StackNode* temp1 = S1->top;StackNode* temp2 = S2->top;
	int lst[S1->size+S2->size];
	int lst1[S1->size];
	int lst2[S2->size]; 
	int p = 0;
	for(int i=0;i<S1->size;i++){
		lst1[i] = temp1->data;
		temp1 = temp1->next;
	}
	for(int i=0;i<S2->size;i++){
		lst2[i] = temp2->data;
		temp2 = temp2->next;
	}
	for(int i=0;i<S1->size/2;i++){
		int a = lst1[i];
		lst1[i] = lst1[S1->size-1-i];
		lst1[S1->size-1-i] = a;
	}
	for(int i=0;i<S2->size/2;i++){
		int a = lst2[i];
		lst2[i] = lst2[S2->size-1-i];
		lst2[S2->size-1-i] = a;
	}
	int p1 = 0,p2 =0;
	while(p1<S1->size||p2<S2->size){
		if(p1<S1->size){
			lst[p] = lst1[p1];
			p1++;p++;
		}
		if(p2<S2->size){
			lst[p] = lst2[p2];
			p2++;p++;
		}
	}
	StackNode* head = NULL;
	StackNode* cur = NULL;
	for(int i=0;i<S1->size+S2->size;i++){
		StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
		if(newNode==NULL){
			StackNode* temp = head;
			StackNode* next = NULL;
			while(temp){
				next = temp->next;
				free(temp);
				temp = next;
			}
			return ERROR;
		}
		newNode->data = lst[i];
		newNode->next = NULL;
		if(head==NULL){
			head = newNode;
			cur = head;
		}else{
			cur->next = newNode;
			cur = cur->next;
		}
	}
	Clear(S3);
	S3->top = head;
	S3->size = S1->size+S2->size;
	return OK;
}
/* ????????(???????) */








int main()
{
    /*
     * ??????????????
     * ?????????????
     */
    return 0;
}

/******************** ?????"????"??????? ********************/
/*
???? InitStack ?,?????:
LinkStack* InitStack(void) { ... }
*/
