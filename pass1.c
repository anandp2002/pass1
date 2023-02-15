#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    char label[10],opcode[10],operand[10],mnemonic[10],code[10];
    int locctr,start,length;
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1=fopen("input.txt","r");
    fp2=fopen("optab.txt","r");
    fp3=fopen("symtab.txt","w");
    fp4=fopen("intermediate.txt","w");
    fp5=fopen("length.txt","w");
    fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        start=locctr=atoi(operand);
        fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
    }
    else
    {
        start=locctr=0;
    }
    while(strcmp(opcode,"END")!=0)
    {
        fprintf(fp4,"%d\t",locctr);
        if(strcmp(label,"**")!=0)
        {
            fprintf(fp3,"%s\t%d\n",label,locctr);
        }
        fscanf(fp2,"%s\t%s",mnemonic,code);
        while(strcmp(mnemonic,"END")!=0)
        {
            if(strcmp(mnemonic,opcode)==0)
            {
                locctr+=3;
                rewind(fp2);
                break;
            }
            fscanf(fp2,"%s\t%s",mnemonic,code);
        }
        if(strcmp(opcode,"WORD")==0)
        {
            locctr+=3;
        }
        else if(strcmp(opcode,"RESW")==0)
        {
            locctr+=(3*atoi(operand));
        }
        else if(strcmp(opcode,"BYTE")==0)
        {
            locctr+=1;
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            locctr+=(atoi(operand));
        }
        fprintf(fp4,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
    }
    fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    length=locctr-start;
    printf("Program length is %d",length);
    fprintf(fp5,"%d",length);
    fclose(fp5);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}