//
// Created by Никита on 06.05.2021.
//
#include <stdio.h>
#include <stdlib.h>
double realcodeACP[26501];
double perfectACPvolt[26501];
double LSB=2.56/1024;
double ideal_to_1023=2.5575-2.56/1024/2;
double zero=0.0;
double scale=0.0;
double real_to_1023=0.0;
double integral[26501];
double max=0.0;
double quant_error=0.5;
int up_polka=0.0;
int down_polka=0.0;



void Read_data_from_file(){
    FILE* pFcode;
    FILE* pFvolt;

    pFvolt=fopen("C:\\tmp\\TSANILab3-2\\volt.txt","r"); // real code
    pFcode=fopen("C:\\tmp\\TSANILab3-2\\realcodeACP.txt","r"); // real code

    for (int i=0;i<26501;i++){
        float temp_code;
        float t;
        fscanf(pFcode,"%f",&temp_code);
        realcodeACP[i]=temp_code;
        fscanf(pFvolt,"%f",&t);
        perfectACPvolt[i]=t;
      //printf("%f\n",realcodeACP[i]);
    }

    fclose(pFcode);
    fclose(pFvolt);

}


void Zerroerror(){
    int j=0;
    do{
       j++;
    } while (realcodeACP[j]!=1);
    down_polka=j;
    zero= perfectACPvolt[j] -0.5*LSB;
    //printf("%lf\n",zero/LSB);


}

void without_zero(){
    for (int i=0; i<26501;i++){
        perfectACPvolt[i]=perfectACPvolt[i]- zero;
        //printf("%lf\n",perfectACPvolt[i]);
    }
}

void Scale_error(){
    int j=0;
    do{
        j++;
        //printf("%lf\n",realcodeACP[j]);
    } while (realcodeACP[j]!=1023);
    up_polka=j;
    scale=(ideal_to_1023 - perfectACPvolt[j]);
    real_to_1023 =perfectACPvolt[j];
}

void without_scale(){
    for (int i=574;i<26501;i++){
        perfectACPvolt[i]=perfectACPvolt[i]*(ideal_to_1023/real_to_1023);
       // printf("%f\n",perfectACPvolt[i]);
    }
}
void integral_error(){
    for (int i=down_polka;i<up_polka+1;i++){
        integral[i]=(perfectACPvolt[i]-LSB*realcodeACP[i])/LSB +quant_error;
        if(integral[i]<0){
            integral[i]=(-1)*integral[i];
        }
        if(integral[i]>max){
            max =integral[i];
        }

        //printf("%f\n", integral[i]);
    }
    //printf("%f\n", max);
}



int main (int argc, char *argv[]) {
    Read_data_from_file();
    Zerroerror();
    without_zero();
    Scale_error();
    without_scale();
    integral_error();
    return 0;
}
