/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*          MIPS BASIC ASSEMBLER	      */
/*          By: Benjamin Cooper - bjc12b      */
/*          Class: CDA3101                    */
/*          Date: 2/12/16                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
 * Purpose: To create a program in C to directly assemble sample mips code
 * Method: By using input redirection a mips file is read in through stdio
 *         the addresses of the labels are determined, and it is parsed for
 *         instructions. The instructions are then stored in an array where
 *         they are parsed using relevant references.
 * Potential: 
 *         This product could be improved by adding more extensive MIPS
 *         support, and is designed in such a way to allow for the easy addition
 *         of future MIPS commands.
 */


#include <stdio.h>
#include <string.h>
/* union is used to parse the outputs in a bitwise manner */
union { 
  float f;
  unsigned int x;
  struct { 
  unsigned int imm:16;
  unsigned int rt:5;
  unsigned int rs:5;
  unsigned int op:6;
  } addi;
  struct {
  unsigned int func:6;
  unsigned int shift:5;
  unsigned int rd:5;
  unsigned int rt:5;
  unsigned int rs:5;
  unsigned int op:6;
  } rtype;
  struct {
  unsigned int targ:26;
  unsigned int op:6;
  } jtype;
} u;

int main()
{
  struct pair{
  char label[80];
  int lineNumber;
  };
  int i = 0;
  int j = 0;
  int numlines;
  int address=0;
  int value;
  int op;
  char str[80];
  char indicator;
  struct pair directory[100];
  char file[100][100];
  char mode[80];
  char label[80];
  char rs[80];
  char rt[80];
  char rd[80];
  int s;
  int t;
  int d;
  char command[80];
  char checkme = 'A';
  int k = 0;
  int spaced;
  char checkme2;
  char flag;

  while(checkme != EOF) /* GRABS LABELS AND LOADS PROGRAM TO ARRAY */
  {
   checkme = getchar(); /*initial character preparation*/
   ungetc(checkme, stdin); /*the combination of get and unget is equivalent to peek in c++ */
   if(scanf("%[^\t]",directory[j].label)) /*if there is a label grabs the label and address, else eats the tab */
   {
   	directory[j].lineNumber = address;
	j++;
	getchar();
   }
   else
   {
   	getchar();
   }
   checkme = getchar(); /*peeks twice to get the information needed to calculate instructions */
   checkme2 = getchar();
   ungetc(checkme2, stdin);
   ungetc(checkme, stdin);
   /*instruction length calculations */
   if(checkme == '.' || checkme2 == '.')
   {
    scanf("%s",mode);
    if(!strcmp(mode,".space"))
    {
     scanf("%i", &spaced);
     address = address+spaced;
    }
    else if(!strcmp(mode,".word"))
    {
     scanf("%s", str);
     address = address + strlen(str) * 4;
    }
    scanf("%*[^\n]");
    getchar();
   }
   else if(checkme == 'l' && checkme2 == 'a')
   {
    address = address + 8;
    scanf("%[^\n]",file[i]);
    i++;
    getchar();
   }
   else
   {
    address = address + 4;
    scanf("%[^\n]",file[i]);
    i++;
    getchar();
   };
  /* printf("%i %s\n",address,file[i-1]);*/
   checkme = getchar();/*EOF check */
   ungetc(checkme, stdin);
  }
  /*record keeping*/
  numlines = i;
  i = 0;
  address = 0;
  /* now processes the instructions */
  for( i=0; i<numlines; i++) /*SECOND RUN THROUGH*/
  {
   rt[0] = '\0';
   rs[0] = '\0';
   rd[0] = '\0';
   value = 0;
   s = 0;
   t = 0;
   d = 0;
   /*spacing offset due to removed code*/
    sscanf(file[i],"%s",label);
    /*gets the instructen then performs required action*/
    if( !strcmp(label,"add"))
    {
     sscanf(file[i],"add\t%[^,],%[^,],%s",rd,rs,rt);
     op = 32;
     
    }
    else if( !strcmp(label,"addi"))
    {
     sscanf(file[i],"addi\t%[^,],%[^,],%d",rt,rs,&value);
     op = 8;
    
    }
    else if(!strcmp(label,"nor"))
    {
     sscanf(file[i],"nor\t%[^,],%[^,],%s",rd,rs,rt);
     op = 39;
     
    }
    else if(!strcmp(label,"ori"))
    {
     sscanf(file[i],"ori\t%[^,],%[^,],%d",rt,rs,&value);
     op = 13;
     
    }
    else if(!strcmp(label,"sll"))
    {
     sscanf(file[i],"sll\t%[^,],%[^,],%d",rd,rt,&value);
     op = 0;

    }
    else if(!strcmp(label,"lui"))
    {
     sscanf(file[i],"lui\t%[^,],%d",rt,&value);
     op = 15;
    }
    else if(!strcmp(label,"sw"))
    {
     sscanf(file[i],"sw\t%[^,],%d(%[^)])",rt,&value,rs);
     op = 43;
     
    }
    else if(!strcmp(label,"lw"))
    {
     sscanf(file[i],"lw\t%[^,],%d(%[^)])",rt,&value,rs);
     op = 35;
    }
    else if(!strcmp(label,"bne"))
    {
     sscanf(file[i],"bne\t%[^,],%[^,],%s",rs,rt,str);
     op = 5;
    }
    else if(!strcmp(label,"j"))
    {
     sscanf(file[i],"j\t%s",str);
     op = 2;
    }
    else if(!strcmp(label,"la"))
    {
     sscanf(file[i],"la\t%[^,],%s",rd,str);
     op = 1;
    
    }
    else/*indicator to allow for further development*/
    {
     printf("The command %s is not supported.\n",label);
    }
   /*if statement to convert register strings to reg values*/
   int offset;
   if(strcmp(rs,"$0"))
   {
    if( rs[1] == 's' )
    {
	offset = 16;
    }
    else
    {
        offset = 8;
    };
    s = offset + rs[2] - 48;
    /*printf("%s    %d\n", rs, s);*/
   }
   else
   {
    s = 0;
   };
   if(strcmp(rt,"$0"))
   {
    if( rt[1] == 's' )
        offset = 16;
    else
        offset = 8;
    t = offset + rt[2] - 48;
   }
   else
   {
    t = 0;
   };
   if(rd != "$0")
   {
    if( rd[1] == 's' )
        offset = 16;
    else
        offset = 8;
    d = offset + rd[2] - 48;
   }
   else
   {
    d = 0;
   };
   /*switch to process types of output*/
   switch (op)
   {
   /*r-type*/
    case 0: s = 0;
    case 39:
    case 32: u.rtype.func = op;
             u.rtype.op = 0;
	     u.rtype.shift = value;
	     u.rtype.rd = d;
	     u.rtype.rt = t;
	     u.rtype.rs = s;
	     printf("0x%08X: 0x%08X\n",address, u.x);
	     address = address + 4;
             break;
    /*I-type*/
    case 5: str[strlen(str)+1] = '\0';
            str[strlen(str)] = ':';
	    for(k = 0; k<j+1; k++)
	    {
	     if(!strcmp(str,directory[k].label))
	     {
	      value = directory[k].lineNumber - address;
	      break;
	     }
	    }
	    value = value/4; 
    case 15:
    case 13:
    case 43:
    case 35:
    case 8: u.addi.op = op;
            u.addi.rs = s;
	    u.addi.rt = t;
	    u.addi.imm = value;
	    printf("0x%08X: 0x%08X\n",address,  u.x);
	    address = address + 4;
	   /*printf("registers: %d %d %d",s, t, d);
	   printf("---op: %i\n", op);*/
	    break;
    /*case 5: printf("Not there yet....\n");
            address = address + 4;
	    break;
    J-type*/case 2: str[strlen(str)+1] = '\0';
              str[strlen(str)] = ':';
	      for(k=0; k<j+1; k++)
	      {
	        if(!strcmp(str,directory[k].label))
		{
		 value = directory[k].lineNumber;
		 break;
		}
	      }
              u.jtype.targ = value/4;
	      u.jtype.op = op;
	      printf("0x%08X: 0x%08X\n",address, u.x);
    	    address = address + 4;
	    break;
    /*assigned op code for pseudo instruction*/
    case 1: op = 15;
            str[strlen(str)+1] = '\0';
	    str[strlen(str)] = ':';
	   /* printf("The string is: %s\n",str);*/
	    for(k = 0; k<j+1; k++)
	    {
             if(!strcmp(str,directory[k].label))
	     {
	      value = directory[k].lineNumber;
	      break;
	     }
	    }
	   /* printf("the string has been found at: %i equal to %s\n", k, directory[k].label);
            printf("The address of the label is: %d\n", value);
	   */ u.addi.op = op;
	    u.addi.rs = 0;
	    u.addi.rt= d;
	    u.addi.imm = value >> 16;
	    printf("0x%08X: 0x%08X\n",address, u.x);
	    address = address + 4;
	    op = 13;
	    u.addi.op = op;
	    u.addi.rs = d;
	    u.addi.rt = d;
	    u.addi.imm = value;
	    printf("0x%08X: 0x%08X\n",address, u.x);
	    address = address + 4;
	    
	    
	    break;
   /*NOTE: for loops are to access label addresses in the above statements.
    * switches are used for cascading compatibility. */
  /* rs = "";
   rt = "";
   rd = "";*/
   value = 0;
  }
  }
  /*
  k = 0;
  for(k; k<7; k++)
  {
   printf("address: %s %d\n",directory[k].label, directory[k].lineNumber);
  }*/
  return 0;
}
