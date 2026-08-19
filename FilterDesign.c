#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846           //PI defined till 20 digits for precision

//FILTER CODE SECTION
void LowPassFilter(float omega_c,float H_d[],int N,int Tau)             //Low Pass Filter H_d[n] computation
{
    for(int i=0;i<N;i++)
    {
        if(i!=Tau)
        {
            H_d[i]=(sin(omega_c*(i-Tau)))/(PI*(i-Tau));                 
        }else{
            H_d[i]= omega_c/PI;
        }
    }
}

void HighPassFilter(float omega_c,float H_d[],int N,int Tau)            //High pass Filter H_d[n] computation
{
    for(int i=0;i<N;i++)
    {
        if(i!=Tau)
        {
            H_d[i]=(sin(PI*(i-Tau))-sin(omega_c*(i-Tau)))/(PI*(i-Tau));
        }else{
            H_d[i]= 1-(omega_c/PI);
        }
    }
}

void BandPassFilter(float omega_c_upper,float omega_c_lower,float H_d[],int N,int Tau)          //Band Pass Filter H_d[n] computation
{
    for(int i=0;i<N;i++)
    {
        if(i!=Tau)
        {
            H_d[i]=(sin(omega_c_upper*(i-Tau))-sin(omega_c_lower*(i-Tau)))/(PI*(i-Tau));
        }else{
            H_d[i]=(omega_c_upper-omega_c_lower)/PI;
        }
    }
}

void FilterChoice(int filteroptions,float omega_c,float omega_c_upper,float omega_c_lower,float H_d[],int N,int Tau)
{
    if(filteroptions==1)
    {
        LowPassFilter(omega_c,H_d,N,Tau);
    }else if(filteroptions==2)
    {
        HighPassFilter(omega_c,H_d,N,Tau);
    }else if(filteroptions==3)
    {
        BandPassFilter(omega_c_upper,omega_c_lower,H_d,N,Tau);
    }else
    {
        printf("Invalid Choice, returning to ");
        exit(0);
    }
}

//WINDOW CODE SECTION
void RectangularWindow(float W_n[],int N)
{
    for(int i=0;i<N;i++)
    {
        W_n[i]=1;
    }
}

void HanningWindow(float W_n[],int N)
{
    for(int i=0;i<N;i++)
    {
        W_n[i]= 0.5 - 0.5*cos((2*PI*i)/(N-1));
    }
}

void HammingWindow(float W_n[],int N)
{
    for(int i=0;i<N;i++)
    {
        W_n[i]= 0.54 - 0.46*cos((2*PI*i)/(N-1));
    }
}

void BartlettWindow(float W_n[],int N,int Tau)
{
    for(int i=0;i<N;i++)
    {
        W_n[i]= 1 - (2*abs(i-Tau))/(N-1);
    }
}

void BlackmannWindow(float W_n[],int N)
{
    for(int i=0;i<N;i++)
    {
        W_n[i]= 0.42 - 0.5*cos((2*PI*i)/(N-1)) + 0.08*cos((4*PI*i)/(N-1));
    }
}

void WindowChoice(int windowoptions, float W_n[], int N, int Tau)
{
    if(windowoptions==1)
    {
        RectangularWindow(W_n,N);
    }else if(windowoptions==2)
    {
        HanningWindow(W_n,N);
    }else if(windowoptions==3)
    {
        HammingWindow(W_n,N);
    }else if(windowoptions==4)
    {
        BartlettWindow(W_n,N,Tau);
    }else if(windowoptions==5)
    {
        BlackmannWindow(W_n,N);
    }else
    {
        printf("Invalid Choice, returning back....");
        exit(0);
    }
}

void FilterCoefficient(float H_d[],float W_n[],int N,float H[])
{
    for(int n=0;n<N;n++)
    {
        H[n]=H_d[n]*W_n[n];
    }
    printf("Filter Coefficients h_d[n] = {");
    for(int i=0;i<N;i++)
    {
        printf("%f",H[i]);
        if (i < N- 1){
            printf(", ");
        }
    }
    printf("}\n");
}

void DisplayH_z(float H[],int N)
{
    printf("H[z] = ");
    for(int i=0;i<N;i++)
    {
        printf("%fz^-%d",H[i],i);
        if (i < N - 1){
            printf(" + ");
        }
    }
    printf("\n");
}

int main()
{
    int filteroptions,N,Tau,windowoptions;
    float omega_c,omega_c_upper,omega_c_lower;
    printf("Please Specify the Type of Filter(Press the Number assigned to the filter)\n");
    printf("1. Low Pass Filter\n");
    printf("2. High Pass Filter\n");
    printf("3. Band Pass Filter\n");
    printf("Your Filter Choice: \n");
    scanf("%d",&filteroptions);
    if(filteroptions==1 || filteroptions==2)
    {
        printf("Provide cutoff frequency: ");
        scanf("%f",&omega_c);
    }
    else if(filteroptions==3)
    {
        printf("Provide cutoff frequencies: [Lower] [Upper]: ");
        scanf("%f",&omega_c_lower);
        scanf("%f",&omega_c_upper);
    }
    printf("Enter Number of samples to analyse(N): \n");
    scanf("%d",&N);
    Tau=(N-1)/2;
    float H_d[N],W_n[N],H[N];
    printf("Please specify the Window(Press the Number assigned to the window)\n");
    printf("1. Rectangular Window\n");
    printf("2. Hanning Window\n");
    printf("3. Hamming Window\n");
    printf("4. Bartlett Window\n");
    printf("5. Blackmann Window\n");
    printf("Your Window Choice: \n");
    scanf("%d",&windowoptions);
    FilterChoice(filteroptions, omega_c, omega_c_upper,omega_c_lower, H_d, N, Tau);
    WindowChoice(windowoptions, W_n, N, Tau);
    FilterCoefficient(H_d,W_n,N,H);
    DisplayH_z(H,N);
    return 0;
}