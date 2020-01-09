// Justin Rodriguez
// Assignment 4
// 2/17/16
// main function, LCS function, and Helper max function

#include "stdheader.h"



void LCS(char * S1, char * S2, char * S3){
    int L1 = strlen(S1);
    int L2 = strlen(S2);
    
    int **A = (int**)malloc(sizeof(int*) * (L1+1));
    
    int i;
    for(i = 0; i <= L1; i++)
        A[i] = (int*)malloc(sizeof(int) * (L2+1));
        
    for(i=0; i<=L2; i++)
        A[L1][0] = 0;
        
    for(i=0;i<=L1;i++)
        A[0][L2] = 0;
        
    
    int j;
    
    for(i = L1 - 1; i >= 0; i--){
        for(j = L2 - 1; j >=0; j--){
            if(S1[i] == S2[j])
                A[i][j] = 1 + A[i+1][j+1];
            
            else{
                A[i][j] = max(A[i+1][j], A[i][j+1]);
            }
        }
    }

    i = 0;
    j = 0;
    int k = 0;
    
    while(true){
        
        if (i > L1 || j > L2 || A[i][j] == 0){
            break;
        }
        
        if(S1[i] == S2[j]){
            S3[k] = S1[i];
            i ++;
            j ++;
            k ++;
        }
        else if(A[i][j + 1] >= A[i + 1][j]){
            j++;
        }
        else{
            i++;
        }
    }
     
    for(i = 0; i <= L1; i++)
        free(A[i]);
    
    free(A);
    S3[k] = '\0';
    return;
}


int max(int a,int b){
    return (a > b)? a : b;
}

int main(int argc, char ** argv){
    char S1[80];
    char S2[80];
    char S3[80];
    
    while(scanf("%s", S1) > 0){
        scanf("%s", S2);
        LCS(S1, S2, S3);
        printf("%s\n", S3);
    }
    return 0;
    
}