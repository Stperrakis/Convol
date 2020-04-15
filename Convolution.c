
#include <stdio.h>
#include <stdlib.h>
#include "koolplot.h"
int main()
{
    int i=0,j=0,ip;
    float o,*buffer,*filter;
//==========================Signal file Handling==========================//
    FILE* file=fopen("signal.txt","r");
    if(file==NULL)                                //Checking about input files
    {
        printf("Check files possibly Missing!");
        return 1;
    }
    else
    {
        while(fscanf(file,"%f",&o)==1)   //Calculating the Number of the elements in the input file
        {
            i++;
        }
        buffer=calloc(i,sizeof(float));
        if( buffer==NULL)             
        {
            printf("Out of Memory");
            fclose(file);
            exit(1);
        }
        i=0;
        rewind(file);
        while(fscanf(file,"%f",&o)==1)     
        {
            buffer[i]=o;                    
            i++;
        }
        printf("======This is our Signal:=======\n");   //Printing our Signal to be more friendly to user
        for(ip=0; ip<i; ip++)
        {
            printf("%f\n",buffer[ip]);
        }

    }
//==========================Impulse response file Handling==========================//
    FILE* file2=fopen("h.txt","r"); 
    if(file2==NULL) 
    {
        printf("Check files possibly Missing!");
        fclose(file);
        free(buffer);
        return 1;
    }
    else
    {
        while(fscanf(file2,"%f",&o)==1) //Calculating the Number of the elements in the input file
        {

            j++;
            //  printf("%d",j);
        }
        // printf("==%d==",j);
        if((j)%2==0)                     
        {
            printf("\n\t\t     PROSOXH!!!\n Prepei na balleis perrito arithmo gia thn kroustikh apokrish\n");
            fclose(file);
            fclose(file2);
            free(buffer);
            exit(1);                    
        }
        filter=calloc(j,sizeof(float)); 
        if(filter==NULL)               
        {
            printf("Out of Memory");
            fclose(file);
            fclose(file2);
            free(buffer);
            exit(1);                  
        }

        rewind(file2);
        j=0;                            

        while(fscanf(file2,"%f",&o)==1)  
        {
            filter[j]=o;                  
            j++;
        }
        printf("\n======Auto einai to filtro mas:======\n");
        for(ip=0; ip<j; ip++)
        {
            printf("%f\n",filter[ip]);
        }
    }
    convole (buffer,filter,i,j);
    fclose(file);               
    fclose(file2);
    free(filter);             
    free(buffer);
    return 0;
}
//==========================Convole-Routine==========================//
int convole(float *x,float *h,int cf,int ch)
{
    int sout,j,i,k;
    float *o,calc;
    sout=cf+ch-1;                 

    o=calloc(sout,sizeof(float)); 
    if(o==NULL)                 
    {
        printf("Memory Error!");
        return 0;
    }
    printf("\n========This is our output======");
    for (i=0; i<sout; i++)
    {
        k=i;
        calc=0;
        for (j=0; j<ch; j++)
        {
            if(k>=0&&k<cf)
            {
                calc=calc+(x[k]*h[j]); 
            }
            k--;
            o[i]=calc;              
        }
        printf("\n%f",o[i]);        
    }
    WriteResult(o,sout);            
    free(o);                       
    return 0;                       
}
//==========================Write-Result==========================//
void WriteResult(float *o,int n)
{
    int i;
    FILE *f;
    f=fopen("Output.txt","w");      
    for(i=0; i<n; i++)
    {
        fprintf(f,"%f\n",o[i]);   
    }
    fclose(f);                     
}
