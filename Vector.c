#include <stdlib.h>
#include "Vector.h"

Vector *vtCreate()
{
	Vector *pVt=calloc(1,sizeof(Vector));

    return pVt;
}

void vtDestory(Vector *pVt)
{
    free(pVt);
}

void vtAddBack(Vector *pVt,void *pNode)
{
	if(pVt->nCount<pVt->nMemorySize)
	{
        pVt->pArray[pVt->nCount]=pNode;
        pVt->nCount++;

        return;
	}
	else
	{
        void **pMem;

        if(pVt->nMemorySize)
			pMem=malloc(sizeof(void *)*pVt->nMemorySize*2);
		else
		{
			pMem=malloc(sizeof(void *)*VECTOR_BASE_SIZE);
			pVt->nMemorySize=VECTOR_BASE_SIZE/2;
		}

        if(!pMem)
		{
			printf("Memory out of!\n");
			return;
		}

		for(int i=0;i<pVt->nCount;i++)
			pMem[i]=pVt->pArray[i];

		free(pVt->pArray);
		pVt->pArray=pMem;

		pVt->pArray[pVt->nCount]=pNode;
        pVt->nCount++;

        pVt->nMemorySize<<=1;
	}
}

void *vtRemove(Vector *pVt,int index)
{
	void *pDel=vtGet(pVt,index);

	if(!pDel) return NULL;

	for(int i=index;i<pVt->nCount;i++)
	{
		pVt->pArray[i]=pVt->pArray[i+1];
	}

	pVt->nCount--;

	if(pVt->nCount<pVt->nMemorySize/2 &&
		pVt->nCount>=VECTOR_BASE_SIZE*2)
	{
        void **pMem;

        if(pVt->nMemorySize)
			pMem=malloc(sizeof(void *)*pVt->nMemorySize*2);
		else
		{
			pMem=malloc(sizeof(void *)*VECTOR_BASE_SIZE);
			pVt->nMemorySize=VECTOR_BASE_SIZE/2;
		}

        if(!pMem)
		{
			printf("Memory out of!\n");
			return NULL;
		}

		for(int i=0;i<pVt->nCount;i++)
			pMem[i]=pVt->pArray[i];

		free(pVt->pArray);
		pVt->pArray=pMem;

        pVt->nMemorySize<<=1;
	}

	return pDel;
}

void *vtGet(Vector *pVt,int index)
{
	if(index<0 || index>=pVt->nCount) return NULL;

	return pVt->pArray[index];
}

int vtCount(Vector *pVt)
{
	return pVt->nCount;
}
