//C语言Vector实现
//index从0开始
#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

//BASE_SIZE只可以是偶数
#define VECTOR_BASE_SIZE										64

typedef struct tagVector
{
	void **pArray;												//指针数组
	int nMemorySize;											//内存大小
	int nCount;
} Vector;

Vector 			*vtCreate();									//创建向量
void				vtDestory(Vector *pVt);
void				vtAddBack(Vector *pVt,void *pNode);		//添加
void 				*vtRemove(Vector *pVt,int index);		//删除
void				*vtGet(Vector *pVt,int index);			//检索
int					vtCount(Vector *pVt);						//元素数量

#endif // VECTOR_H_INCLUDED
