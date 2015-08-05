/* calc_a_s.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#define PI 3.1415926

/* add */
double calc_add( double a1, double a2)
{
    double result = 0.0;
    
    result = a1 + a2;
    
    return result;
}

/* sub */
double calc_sub(double b1, double b2)
{
    double result = 0.0;
    
    result = b1 - b2;
    
    return (result);
}

/* mul */
double calc_mul(double c1, double c2)
{
    double result = 0.0;

    result = c1 * c2;

    return (result);
}

/* div */
double calc_div(double d1, double d2)
{
    double result = 0.0;
    
    if (0.0 == d2){
        printf("the divisor cannot be 0.0 !\n");
        exit(1);
    }
    result = d1 / d2;

    return (result);
}

/* PI */
double calc_PI(void)
{
    return PI;
}

/* sin */
double calc_sin(double f)
{
    double result = 0.0;

    result = sin(f);

    return (result);
}

/* cos */
double calc_cos(double g)
{
    double result = 0.0;

    result = cos(g);

    return (result);
}

/* tan */
double calc_tan(double h)
{
    double result = 0.0;

    result = tan(h);

    return (result);
}

/* fabs */
double calc_fabs(double i)
{
    double result = 0.0;

    result = fabs(i);

    return (result);
}

/* exp */
double calc_exp(double j)
{
    double result = 0.0;

    result = exp(j);

    return (result);
}

/* log */
double calc_log(double k)
{
    double result = 0.0;

    assert(k > 0.0);
    result = log(k);

    return (result);
}

/* log10 */
double calc_log10(double l)
{
    assert(l > 0.0);

    return (log10(l));
}

/* pow */
double calc_pow(double m1,double m2)
{
    return (pow(m1, m2));
}

/* rand */
long calc_rand(void)
{
    long result = 0;

    srand(time(0));
    result = rand();
    return (result);
}

/* print_func */
void print_func(void)
{
    printf("Please input commonds as follows:\n");
    printf("./calc_sim 1 xxx xxx   : add\n");
    printf("./calc_sim 2 xxx xxx   : sub\n");
    printf("./calc_sim 3 xxx xxx   : mul\n");
    printf("./calc_sim 4 xxx xxx   : div\n");
    printf("./calc_sim 5           : PI\n");
    printf("./calc_sim 6 xxx       : sin\n");
    printf("./calc_sim 7 xxx       : cos\n");
    printf("./calc_sim 8 xxx       : tan\n");
    printf("./calc_sim 9 xxx       : fabs\n");
    printf("./calc_sim 10 xxx      : exp\n");
    printf("./calc_sim 11 xxx      : ln\n");
    printf("./calc_sim 12 xxx      : lg\n");
    printf("./calc_sim 13 xxx xxx  : pow\n");
    printf("./calc_sim 14          : rand\n");
}

/* main */
int main (int argc, char** argv)    
{
    unsigned int calc_mod = 0;
    double idata  = 0.0;
    double kdata  = 0.0;
    double result = 0.0;
    
    switch (argc){
    case 2:
        argv++;
        calc_mod = atoi(*argv);
        if ((calc_mod != 5) && (calc_mod != 14)){ 
            print_func();
            return -1;
        }
        break;

    case 3:
        argv ++;
        calc_mod = atoi(*argv);
        if ((calc_mod < 6) || (calc_mod > 12)){ 
            print_func();
            return -1;
        }
        argv ++;    
        idata = atof(*argv);
        printf("Enter is mod<%d> data_f<%lf> \n", calc_mod, idata);
        break;

    case 4:
        argv ++;
        calc_mod = atoi(*argv);
        if ((calc_mod < 1) || (calc_mod > 4 && calc_mod != 13)){ 
            print_func();
            return -1;
        }
        argv ++;    
        idata = atof(*argv);
        argv ++;    
        kdata = atof(*argv);    
        printf("Enter is mod<%d> data_f<%lf> data_b<%lf> \n", calc_mod, idata, kdata);
        break;

    default :
        print_func();
        return -1;
    }

    switch(calc_mod){
    case 1:
        result = calc_add(idata, kdata);   
        printf("Calc add (%lf + %lf) result is %lf\n", idata, kdata, (double)result);  	    	
        break;
    
    case 2:
        result = calc_sub(idata, kdata);
        printf("Calc sub (%lf - %lf) result is %lf\n", idata, kdata, (double)result);
        break;
               
    case 3:
        result = calc_mul(idata, kdata);
        printf("Calc mul (%lf * %lf) result is %lf\n", idata, kdata, (double)result);
        break;

    case 4:
        result = calc_div(idata, kdata);
        printf("Calc div (%lf / %lf) result is %lf\n", idata, kdata, (double)result);
        break;

    case 5:
        result = calc_PI();
        printf("Calc PI result is %lf\n", (double)result);
        break;

    case 6:
        result = calc_sin(idata);
        printf("Calc sin (%lf) result is %lf\n", idata, (double)result);
        break;

    case 7:
        result = calc_cos(idata);
        printf("Calc cos (%lf) result is %lf\n", idata, (double)result);
        break;

    case 8:
        result = calc_tan(idata);
        printf("Calc tan (%lf) result is %lf\n", idata, (double)result);
        break;

    case 9:
        result = calc_fabs(idata);
        printf("Calc fabs (%lf) result is %lf\n", idata, (double)result);
        break;

    case 10:
        result = calc_exp(idata);
        printf("Calc exp (%lf) result is %lf\n", idata, (double)result);
        break;

    case 11:
        result = calc_log(idata);
        printf("Calc log (%lf) result is %lf\n", idata, (double)result);
        break;

    case 12:
        result = calc_log10(idata);
        printf("Calc log10 (%lf) result is %lf\n", idata, (double)result);
        break;

    case 13:
        result = calc_pow(idata, kdata);
        printf("Calc pow (%lf , %lf) result is %lf\n", idata, kdata, (double)result);
        break;

    case 14:
        printf("Calc rand result is %ld\n",(long)calc_rand());
        break;

    default:
        printf("Enter calc mod error!!!\n");
        break;
    }
    
    return 0;
}
