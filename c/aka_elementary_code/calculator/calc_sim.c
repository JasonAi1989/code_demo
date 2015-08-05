#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double add_m (double num1,double num2);
double sub_m (double num1,double num2);
double mul_m (double num1,double num2);
double div_m (double num1,double num2);
double pi (void);
double sin_m (double num1);
double cos_m (double num1);
double tan_m (double num1);
double abs_m (double num1);
double exp_m (double num1);
double log_m (double num1);
double log10_m (double num1);
double pow_m (double num1,double num2);
double rand_m (void);
void empty_cache(void);


int main(int argc, const char *argv[])
{
    unsigned int mod;
    int argc_m;
    double num1,num2,result;
    char argv1[1024] = {};
    char argv2[1024] = {};
    char argv0[1024] = {};
	

	
    while (1){


    printf("1.加法运算 commd: ./calc_sim 1 xxx xxx \n");
    printf("2.减法运算 commd: ./calc_sim 2 xxx xxx\n");
    printf("3.乘法运算 commd: ./calc_sim 3 xxx xxx\n");
    printf("4.除法运算 commd: ./calc_sim 4 xxx xxx\n");
    printf("5.PI运算 commd: ./calc_sim 5\n");
    printf("6.sin运算 commd: ./calc_sim 6 xxx\n");
    printf("7.cos运算 commd: ./calc_sim 7 xxx\n");
    printf("8.tan运算 commd: ./calc_sim 8 xxx\n");
    printf("9.绝对值运算 commd: ./calc_sim 9 xxx\n");
    printf("10.幂指数运算(e的n次幂) commd: ./calc_sim 10 xxx\n");
    printf("11.自然对数运算(log) commd: ./calc_sim 11 xxx\n");
    printf("12.常对数运算(log10) commd: ./calc_sim 12 xxx\n");
    printf("13.n次幂运算 commd: ./calc_sim 13 xxx xxx\n");
    printf("14.随机数获取 commd: ./calc_sim 14\n");
    printf("15.exit\n");

	scanf("%s\n",argv0);

    mod = atoi(argv0);

	 switch (mod)
	 {
			case 1:
			case 2:
			case 3:
			case 4:
			case 13:argc_m=scanf("%s %s",argv1,argv2);
					num1 = (double)atof(argv1);
   					num2 = (double)atof(argv2);
					break;
			case 5:
			case 14:break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:argc_m=scanf("%s",argv1);
					num1 = (double)atof(argv1);
					break;
            default :break;
}
 
    	printf("%d\n",mod);
        printf("%f\n",num1);
        printf("%f\n",num2);
    switch (mod)
    {
        case 1:if (argc_m != 2)
                    printf("error\n");
               else{
                    result = add_m(num1,num2);
                    printf("%f\n",result);
               }
                    break;
               
        case 2:if (argc_m != 2)
                    printf("error\n");
               else{
                    result = sub_m(num1,num2);
                    printf("%f\n",result);
               }
                    break;
               
        case 3:if (argc_m != 2)
                    printf("error\n");
               else{
                    result = mul_m(num1,num2);
                    printf("%f\n",result);
               }
                    break;
               
       case 4:if (argc_m != 2)
                    printf("error\n");
			   else if(0 == num2)
					printf("error\n");
               else{
                    result = div_m(num1,num2);
                    printf("%f\n",result);
               }
                    break;
               
       case 5:
                    result = pi();
                    printf("%f\n",result);
                    break;
               
       case 6:if (argc_m != 1)
                    printf("error\n");
               else{
                    result = sin_m(num1);
                    printf("%f\n",result);
               }
                    break;
               
       case 7:if (argc_m != 1)
                    printf("error\n");
               else{
                    result = cos_m(num1);
                    printf("%f\n",result);
               }
                    break;
               
       case 8:if (argc_m != 1)
                    printf("error\n");
               else{
                    result = tan_m(num1);
                    printf("%f\n",result);
               }
                    break;
               
       case 9:if (argc_m != 1)
                    printf("error\n");
               else{
                    result = abs_m(num1);
                    printf("%f\n",result);
               }
                    break;
               
       case 10:if (argc_m != 1)
                    printf("error\n");
               else{
                    result = exp_m(num1);
                    printf("%f\n",result);
               }
                    break;
               
       case 11:if (argc_m != 1)
                    printf("error\n");
			   else if ((0 == num1 )||(num1 < 0))
					printf("error\n");
               else{
                    result =log_m(num1);
                    printf("%f\n",result);
               }
                    break;
               
       case 12:if (argc_m != 1 || num1 <= 0)
                    printf("error\n");
               else{
                    result =log10_m(num1);
                    printf("%f\n",result);
               }
                    break;
               
       case 13:if (argc_m != 2 )
                    printf("error\n");
               else{
                    result =pow_m(num1,num2);
                    printf("%f\n",result);
               }
                    break;
               
       case 14:
                    result =rand_m();
                    printf("%f\n",result);
           
                    break;
               
       case 15:return 0;

       default :printf("error\n");
               break;
    }
		empty_cache();
	
    }

}


double add_m(double num1,double num2)
{
    return (num1 + num2);

}

double sub_m(double num1,double num2)
{
    return (num1 - num2);

}

double mul_m(double num1,double num2)
{
    return (num1 * num2);

}

double div_m(double num1,double num2)
{
   

			
    return (num1/num2);

}

double pi(void)
{
	 double p = 3.1415926;
    return (p) ;


}

double sin_m(double num1)
{
    return (sin(num1));

}

double cos_m(double num1)
{
    return (cos(num1));

}

double tan_m(double num1)
{
    return (tan(num1));

}

double abs_m(double num1)
{
    int a;
    double b;
    a = (int)num1;
    b = (double)(abs(a));
    return b;
}

double exp_m(double num1)
{
    return (exp(num1));

}

double log_m(double num1)
{
    return (log(num1));

}

double log10_m(double num1)
{
    return (log10(num1));

}

double pow_m(double num1,double num2)
{
    return (pow(num1,num2));

}

double rand_m(void)
{
    srand((int)time(0));
    return ((double)rand());

}

void empty_cache(void)
{
char ch;
while ((ch = getchar()) != '\n');
}

