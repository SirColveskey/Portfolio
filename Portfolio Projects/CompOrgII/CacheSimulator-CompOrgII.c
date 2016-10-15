/* Name: Benjamin Cooper
   FSUID: BJC12B
   Date: 4/22/2016
   Project Description: Implementing a cache simulator in C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[])
{
/*collecting line arguments*/
 int i;
 char* flag1;
 int val1;
 char* flag2;
 int val2;
 char* flag3;
 int val3;
 
 flag1 = argv[1];
 val1 = atoi(argv[2]);
 flag2 = argv[3];
 val2 = atoi(argv[4]);
 flag3 = argv[5];
 val3 = atoi(argv[6]);

/*parsing line arguments*/
 int blocksize;
 int sets;
 int associativity;

 if(!strcmp(flag1,"-b"))
  blocksize = val1;
 else if(!strcmp(flag1,"-s"))
  sets = val1;
 else if(!strcmp(flag1,"-n"))
  associativity = val1;

 if(!strcmp(flag2,"-b"))
  blocksize = val2;
 else if(!strcmp(flag2,"-s"))
  sets = val2;
 else if(!strcmp(flag2,"-n"))
  associativity = val2;

 if(!strcmp(flag3,"-b"))
  blocksize = val3;
 else if(!strcmp(flag3,"-s"))
  sets = val3;
 else if(!strcmp(flag3,"-n"))
  associativity = val3;

/*reading input*/
 int LineNumber = 1;
 int value;
 char reader;
 char blank;
 char* oldRW = NULL;
 char* RW = NULL;
 int* oldValues = NULL;
 int* values = NULL; 
 char* line;

while(fgets(line, 30, stdin)!=NULL)
{
 sscanf(line,"%c%*c%d%c",&reader ,&value ,&blank);
 values = (int*)malloc(LineNumber * sizeof(int));
 RW = (char*)malloc(LineNumber * sizeof(char));
 for(i = 0; i<LineNumber-1; i++)
 {
  RW[i] = oldRW[i];
  values[i] = oldValues[i];
 }
 free(oldRW);
 free(oldValues);
 RW[LineNumber-1] = reader;
 values[LineNumber-1] = value;
 oldRW = RW;
 oldValues = values;
 LineNumber++;
}

/*confirmation printing*/
/*
for(i = 0; i<LineNumber-1; i++)
{
 printf("Line: %c %d\n",RW[i],values[i]);
}
*/

/*Calculating offset, index, and tag*/
int offset = log(blocksize)/log(2);
int index = log(sets)/log(2);
int tag = 32 - offset - index;

/*bitwise mask calculation*/
int maskOffset=0;
int maskIndex=0;
int maskTag=1;

for(i = 0; i<tag-1; i++)
{
 maskTag = maskTag << 1;
 maskTag++;
}

for(i = 0; i<index; i++)
{
 maskIndex = maskIndex << 1;
 maskIndex++;
 maskTag = maskTag << 1;
}

for(i = 0; i<offset; i++)
{
 maskOffset = maskOffset << 1;
 maskOffset++;
 maskIndex = maskIndex << 1;
 maskTag = maskTag << 1;
}

/*Write-Through with no Write Allocate*/
int cache[sets*associativity];
int priority[sets*associativity];
int active[sets*associativity];

int wtMiss=0;
int wtHit=0;
int wtMem=0;

int thisOffset;
int thisIndex;
int thisTag;

int id;
int ided;
int j;
int LRU;
int k;
/*initialize active:*/
for(i=0; i<sets*associativity; i++)
{
	active[i] = 0;
}

for(i = 0; i<LineNumber-1; i++)
{
	thisOffset = values[i] & maskOffset;
	thisIndex = (values[i] & maskIndex) >> offset;
	thisTag = (values[i] & maskTag) >> (index + offset);
	if(RW[i] == 'W')
	{
		k = thisIndex*associativity;
		id = k;
		ided = 0;
		for(j = 0; j<associativity; j++)
		{
			if(cache[k+j]==thisTag && active[k+j] != 0)
			{
				id = k+j;
				ided = 1;
				break;
			}
		}
		if(ided && active[id])
		{
			wtHit++;
			wtMem++;
			priority[id]=i;
		}
		else
		{
			wtMiss++;
			wtMem++;
		}
	}
	if(RW[i] == 'R')
	{
		k = thisIndex*associativity;
		id = thisIndex*associativity;
		ided = 0;
		for(j = 0; j<associativity; j++)
		{
			if(cache[k+j]==thisTag && active[k+j])
			{
				id = k+j;
				ided = 1;
				break;
			}
		}
		if(ided && active[id])
		{
			wtHit++;
			priority[id]=i;
		}
 		else
 		{
  			wtMiss++;
  			wtMem++;
  			LRU = id;
  			for(j=0;j<associativity;j++)
  			{
   				if(priority[k+j] < priority[LRU])
      				LRU = k+j;
   				if(!active[k+j])
   				{
      					LRU = k + j;
      					break;
   				}
  			}
  			cache[LRU] = thisTag;
  			active[LRU] = 1;
/*			printf("one active: %d %d %d | %d %d\n",thisTag,thisIndex,i,cache[thisIndex*associativity],cache[thisIndex*associativity+1]);*/
	         }
	}
/*	printf("Running: %d %d %d %c | %d %d %d\n",thisTag,thisIndex,i,RW[i],wtHit,wtMiss,wtMem);*/
};


/*Write-back with Write Allocate*/
/*
int cache[sets*associativity];
int priority[sets*associativity];
int active[sets*associativity];
*/
int dirty[sets*associativity];

int wbMiss=0;
int wbHit=0;
int wbMem=0;
/*
int thisOffset;
int thisIndex;
int thisTag;

int id;
int ided;
int j;
int LRU;
*/
ided = 0;
/*initialize active:*/
for(i=0; i<sets*associativity; i++)
{
	active[i] = 0;
}

/*initialize dirty:*/
for(i=0; i<sets*associativity; i++)
{
	dirty[i] = 0;
	priority[i] = 0;
	cache[i] = 0;
}
/*printf("ROUND TWO...FIGHT!\n")i;*/
for(i = 0; i<LineNumber-1; i++)
{
	thisOffset = values[i] & maskOffset;
	thisIndex = (values[i] & maskIndex) >> offset;
	thisTag = (values[i] & maskTag) >> (index + offset);
	if(RW[i] == 'W')
	{
		k = thisIndex*associativity;
			id = thisIndex*associativity;
			ided = 0;
		for(j = 0; j<associativity; j++)
		{
			if(cache[k+j]==thisTag && active[k+j])
			{
				id = k+j;
				ided = 1;
				break;
			}
		}
		if(ided && active[id])
		{
			wbHit++;
			priority[id]=i;
			dirty[id]=1;
		}
		else
		{
			wbMiss++;
			LRU = id;
			wbMem++;  			
			for(j=0;j<associativity;j++)
  			{
   				if(priority[k+j] < priority[LRU])
      				LRU = k+j;
   				if(!active[k+j])
   				{
      					LRU = k+j;
      					break;
   				}
  			}
  			cache[LRU] = thisTag;
  			active[LRU] = 1;
		/*	printf("Initializing: %d %d %d\n",thisIndex,thisTag,i);*/
			if(dirty[LRU])
				wbMem++;
			dirty[LRU] = 1;
		}
	}
	if(RW[i] == 'R')
	{
		k = thisIndex*associativity;
		id = thisIndex*associativity;
		ided = 0;
		for(j = 0; j<associativity; j++)
		{
			if(cache[k+j]==thisTag && active[k+j] != 0)
			{
				id = k+j;
				ided = 1;
				break;
			}
		}
		if(ided && active[id])
		{
			wbHit++;
			priority[id]=i;
		}
 		else
 		{
  			wbMiss++;
			wbMem++;
  			LRU = id;
  			for(j=0;j<associativity;j++)
  			{
   				if(priority[k+j] < priority[LRU])
      					LRU = k+j;
   				if(!active[k+j])
   				{
      					LRU = k+j;
      					break;
   				}
  			}
  			cache[LRU] = thisTag;
  			active[LRU] = 1;
			if(dirty[LRU])
				wbMem++;
			dirty[LRU] = 0;
/*			printf("Initializing through read: %d %d %d\n",thisIndex,thisTag,i);*/
 		}
	}
/*	printf("Running: %d %d %d\n",thisIndex,thisTag,i);
	printf("Here are the stats: %d %d | %d %d\n", active[thisIndex*associativity], active[thisIndex*associativity+1], cache[thisIndex*associativity], cache[thisIndex*associativity+1]);*/
};
/*printing results*/
 printf("Block size: %d \nNumber of Sets: %d \nAssociativity: %d \nNumber of Offset bits: %d\nNumber of Index bits: %d\nNumber of Tag bits: %d\n\n****************************************\nWrite-through with No Write Allocate\n****************************************\nTotal number of references: %d\nHits: %d\nMisses: %d\nMemory References:%d\n\n****************************************\nWrite-back with Write Allocate\n****************************************\nTotal number of references: %d\nHits: %d\nMisses: %d\nMemory References:%d\n", blocksize, sets, associativity,offset,index,tag,LineNumber-1,wtHit,wtMiss,wtMem,LineNumber-1,wbHit,wbMiss,wbMem);


 return 0;
}
  
