/* Hi, my name is Perrakis Stylianos R.N.:2401.I managed to do a Convolution Process on C within the course of the subject,
briefly is that it is using 3 files at ".txt" form one of them is impulse response'h.txt' usually is called filter, the
second one is our signal 'signal.txt' and the other is our output 'Output.txt'.I hope you enjoy!!!*/
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
        buffer=calloc(i,sizeof(float)); //Creates free space that our signal will be stored and puts 0 to free spaces
        if( buffer==NULL)               //If it cannot create space in the memory then it ends the task
        {
            printf("Out of Memory");
            fclose(file);
            exit(1);
        }
        i=0;
        rewind(file);
        while(fscanf(file,"%f",&o)==1)     //When it has no elements to scan it will return 0 and stop the loop
        {
            buffer[i]=o;                    //insert our elements into the array we created dynamically
            i++;
        }
        printf("======This is our Signal:=======\n");   //Printing our Signal to be more friendly to user
        for(ip=0; ip<i; ip++)
        {
            printf("%f\n",buffer[ip]);
        }

    }
//==========================Impulse response file Handling==========================//
    FILE* file2=fopen("h.txt","r"); //Creating a pointer who's pointing at the start of our file
    if(file2==NULL) //Checking about input files,if pointer is Null then something goes wrong
    {
        printf("Check files possibly Missing!");
        fclose(file);
        free(buffer);
        return 1;
    }
    else
    {
        while(fscanf(file2,"%f",&o)==1)    //Calculating the Number of the elements in the input file
        {

            j++;
            //  printf("%d",j);
        }
        // printf("==%d==",j);
        if((j)%2==0)                     // This statement in order to continue you had to put in the file odd number of elements in filter file,you have to have a middle element as our Professor told us
        {
            printf("\n\t\t     PROSOXH!!!\n Prepei na balleis perrito arithmo gia thn kroustikh apokrish\n");
            fclose(file);
            fclose(file2);
            free(buffer);
            exit(1);                    //Else exits so changes have to be done&& free the space we allocated
        }
        filter=calloc(j,sizeof(float)); //Creates free space that our signal will be stored and puts 0 to free spaces
        if(filter==NULL)               //If system not allowed to create space in the memory then it ends the task
        {
            printf("Out of Memory");
            fclose(file);
            fclose(file2);
            free(buffer);
            exit(1);                  //So again it Exits,After the user informed what's going on
        }

        rewind(file2); //Opening again the file again to reset the pointer at the Start of the file..
        j=0;                            // Re-declare th j in manage to have Access to the 0 box of the array we created before

        while(fscanf(file2,"%f",&o)==1)   //When it has no elements to scan it will return 0 and stop the loop
        {
            filter[j]=o;                  //Insert our elements into the array we created dynamically
            j++;
        }
        printf("\n======Auto einai to filtro mas:======\n");//Printing our Signal to be more friendly to user
        for(ip=0; ip<j; ip++)
        {
            printf("%f\n",filter[ip]);
        }
    }
    convole (buffer,filter,i,j); //Calling The Function that makes the Convolution it has 4 arguments the arrays and the size of each one
    fclose(file);               //Closing the files as a gentleman :)
    fclose(file2);
    free(filter);              //Free the spaces we created because its our duty to do it and then We are free to go :)
    free(buffer);
    return 0;
}
//==========================Convole-Routine==========================//
int convole(float *x,float *h,int cf,int ch)
{
    int sout,j,i,k;
    float *o,calc;
    sout=cf+ch-1;                  //Calculating the number of output values

    o=calloc(sout,sizeof(float)); //Allocating enough space for the output
    if(o==NULL)                   //If its not allowed then Printing in the screen Message and the returns 0 to end the Function and free the memory we allocated early
    {
        printf("Memory Error!");
        return 0;
    }
    printf("\n========This is our output======"); //Printing message before loop in manage to get when it is finished
    for (i=0; i<sout; i++)
    {
        k=i;
        calc=0;
        for (j=0; j<ch; j++)
        {
            if(k>=0&&k<cf)
            {
                calc=calc+(x[k]*h[j]); //Here it makes the convolution calculations
            }
            k--;
            o[i]=calc;              //Putting values in the array
        }
        printf("\n%f",o[i]);        //Printing our Matrix that contains our output
    }
    WriteResult(o,sout);            //Calling Void WriteResult with arguments the array,length of him because we want to pass it in the output file
    free(o);                        //Freeing o no more needed
    return 0;                        //Return 0, i managed to do it int this function and not void because of line 102 when i cant allocate i have to free the ones i allocated before
}
//==========================Write-Result==========================//
void WriteResult(float *o,int n)
{
    int i;
    FILE *f;
    f=fopen("Output.txt","w");      //Opening the file OR creating it thats the point of "w"
    for(i=0; i<n; i++)
    {
        fprintf(f,"%f\n",o[i]);    //We writing the array into the file
    }
    fclose(f);                      //Last but not least, we closing the file,before exiting
}
