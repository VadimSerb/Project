#include <stdio.h>
#include <tommath.h>

struct Point{
    mp_int X, Y, Z;
};

struct Parameters{
    mp_int a, d, p, q, u, v;
};

void ToText(mp_int arg){ //Работает корректно
    char stroka[4096];
    mp_toradix(&arg, stroka, 10);
    printf("%s",stroka);
    printf("\n");
}

void Transform (struct Point *P, struct Parameters *PR){ //Работает корректно

    mp_int zero, temp;

    int result;
    if ((result = mp_init_multi(&zero, &temp, NULL)) != MP_OKAY) {
        printf("Error initializing the numbers. %s",
               mp_error_to_string(result));
    }

    mp_read_radix(&zero, "0", 10);

    if (mp_cmp_mag(&P->Z, &zero) != MP_EQ){

        mp_invmod(&P->Z, &PR->p, &temp); //вычисляется корректно

        //x = X/Z
        mp_mulmod(&P->X, &temp, &PR->p, &P->X);

        //y = Y/Z
        mp_mulmod(&P->Y, &temp, &PR->p, &P->Y);

        P->Z = zero;
        //mp_clear_multi(&zero, &temp, NULL);
    }
}

void AddPoints(struct Point *P1, struct Point *P2, struct Parameters *PR){ //Работает корректно

    mp_int C, D, E, temp, sqrE, one, sumXY1, sumXY2, Em1, mulsum;

    int result;
    if ((result = mp_init_multi(&C, &D, &E, &temp, &sqrE, &one, &sumXY1, &sumXY2, &Em1, &mulsum,  NULL)) != MP_OKAY) {
        printf("Error initializing the numbers. %s",
               mp_error_to_string(result));
    }
    mp_read_radix(&temp, "1", 10);
    mp_read_radix(&one, "1", 10);


    mp_mulmod (&P1->X, &P2->X, &PR->p, &C);     //C = X1*X2

    mp_mulmod (&P1->Y, &P2->Y, &PR->p, &D);     //D = Y1*Y2

    mp_mulmod (&PR->d, &C, &PR->p, &temp); //d*C
    mp_mulmod (&temp, &D, &PR->p, &E);          // E = d*C*D

    mp_addmod(&P1->X, &P1->Y, &PR->p, &sumXY1); // X1 + Y1
    mp_addmod(&P2->X, &P2->Y, &PR->p, &sumXY2); // X2 + Y2
    mp_submod(&one, &E, &PR->p, &Em1); // E-1
    mp_mulmod(&sumXY1, &sumXY2, &PR->p, &mulsum); // (X1+Y1)*(X2+Y2)
    mp_submod(&mulsum, &C, &PR->p, &mulsum); // (X1+Y1)*(X2+Y2) - C
    mp_submod(&mulsum, &D, &PR->p, &mulsum); // (X1+Y1)*(X2+Y2) - C - D
    mp_mulmod(&Em1, &mulsum, &PR->p, &P1->X);// Результирующая координата X: (E-1) * ((X1+Y1)*(X2+Y2) - C - D)

    //используем имеющиеся переменные для получения результирующей Y координаты, чтобы не объявлять новые

    mp_addmod(&one, &E, &PR->p, &Em1); // Em1 = 1+E
    mp_mulmod(&PR->a, &C, &PR->p, &sumXY1); //sumXY1 = a*C
    mp_submod(&D, &sumXY1, &PR->p, &sumXY2); //sumXY2 = D - a*C

    mp_mulmod(&Em1, &sumXY2, &PR->p, &P1->Y); //результирующая координата Y: (D - a*C)*(E+1)


    mp_sqrmod(&E, &PR->p, &sqrE); // E^2
    mp_submod(&one, &sqrE, &PR->p, &P1->Z); // Результирующая координата Z: 1 - E^2
}

void DoublePoint(struct Point *P, struct Parameters PR){ //Работает корректно

    mp_int B, C, D, E, F, temp, term1, term2, two;

    int result;
    if ((result = mp_init_multi(&B, &C, &D, &E, &F, &temp, &term1, &term2, &two, NULL)) != MP_OKAY) {
        printf("Error initializing the numbers. %s",
               mp_error_to_string(result));
    }

    mp_addmod(&P->X, &P->Y, &PR.p, &temp); // temp = X+Y
    mp_sqrmod(&temp, &PR.p, &B); //B = (X+Y)^2
    mp_sqrmod(&P->X, &PR.p, &C); //C = X^2
    mp_sqrmod(&P->Y, &PR.p, &D); //D = Y^2
    mp_mulmod(&PR.a, &C, &PR.p, &E); //E = a*C
    mp_addmod(&E, &D, &PR.p, &F); //F = E+D

    mp_read_radix(&two, "2", 10);
    mp_submod(&F, &two, &PR.p, &term1); //term1 = F-2
    mp_submod(&B, &C, &PR.p, &term2); //term2 = B-C
    mp_submod(&term2, &D, &PR.p, &term2); //term2 = B-C-D
    mp_mulmod(&term1, &term2, &PR.p, &P->X); //результирующая координата X: (F-2)*(B-C-D)

    mp_submod(&E, &D, &PR.p, &term1); //term1 = E-D
    mp_mulmod(&term1, &F, &PR.p, &P->Y); //результирующая координата Y: F*(E-D)

    mp_sqrmod(&F, &PR.p, &term1); //term1 = F^2
    mp_mulmod(&two, &F, &PR.p, &term2); //term2 = 2*F
    mp_submod(&term1, &term2, &PR.p, &P->Z); //результирующая координата Z: F^2 - 2*F
}

struct Point BinaryMethod(struct Point *P, mp_int k, struct Parameters PR){ //Работает корректно

    mp_int zero, one;
    int result;
    if ((result = mp_init_multi(&zero, &one, NULL)) != MP_OKAY) {
        printf("Error initializing the numbers. %s",
               mp_error_to_string(result));
    }
    mp_read_radix(&zero, "0", 10);
    mp_read_radix(&one, "1", 10);

    struct Point P1;
    P1.X = zero;
    P1.Y = one;
    P1.Z = zero;

    struct Point P2;
    P2.X = P->X;
    P2.Y = P->Y;
    P2.Z = P->Z;

    for(long i = mp_count_bits(&k) - 1; i>=0; --i ){
        DoublePoint(&P1, PR);
        Transform(&P1, &PR);
        //printf("%lu ", i);
        if(mp_get_bit(&k, i)){
            AddPoints(&P1, &P2, &PR);
            Transform(&P1, &PR);
            //printf("%lu ", i);
        }
    }
    return P1;
}


void IfOnCurve(struct Point *P, struct Parameters PR){ //Работает корректно
    mp_int A, B, temp1, temp2, one;

    int result;
    if ((result = mp_init_multi(&A, &B, &temp1, &temp2, &one, NULL)) != MP_OKAY) {
        printf("Error initializing the numbers. %s",
               mp_error_to_string(result));
    }
    mp_read_radix(&one, "1", 10);

    mp_sqrmod(&P->X, &PR.p, &A); //X^2
    mp_sqrmod(&P->Y, &PR.p, &B); //Y^2
    mp_mulmod(&PR.a, &A, &PR.p, &temp1); //a*X^2
    mp_addmod(&temp1, &B, &PR.p, &temp1); //a*X^2 + Y^2

    mp_mulmod(&PR.d, &A, &PR.p, &temp2); //d*X^2
    mp_mulmod(&temp2, &B, &PR.p, &temp2); //d*X^2 * Y^2
    mp_addmod(&temp2, &one, &PR.p, &temp2); // d*X^2 * Y^2 + 1

    if (mp_cmp_mag(&temp1, &temp2) == MP_EQ){
        printf("%s\n", "Yes");
    }
    else printf("%s\n", "No");
}

void IfIdentical(struct Point *P, struct Parameters PR){ //Работает корректно
    mp_int zero, one;

    int result;
    if ((result = mp_init_multi(&zero, &one, NULL)) != MP_OKAY) {
        printf("Error initializing the numbers. %s",
               mp_error_to_string(result));
    }

    mp_read_radix(&one, "1", 10);
    mp_read_radix(&zero, "0", 10);

    if ((mp_cmp_mag(&P->X, &zero) == MP_EQ) && (mp_cmp_mag(&P->Y, &one) == MP_EQ) && (mp_cmp_mag(&P->Z, &zero) == MP_EQ)){
        printf("%s\n", "Yes");
    }
    else printf("%s\n", "No");
}



void IfNeighbors(struct Point *P, struct Point *Q, struct Parameters PR){ //Работает корректно
    if ((mp_cmp_mag(&P->X, &Q->X) == MP_EQ) && (mp_cmp_mag(&P->Y, &Q->Y) == MP_EQ)){
        printf("%s\n", "Yes");
    }
    else printf("%s\n", "No");
}


int main()
{
    mp_int a, d, p, q, u, v, t, t1;
    int result;


    if ((result = mp_init_multi(&a,
                                &d,
                                &p,
                                &q,
                                &u,
                                &v,
                                &t,
                                &t1, NULL)) != MP_OKAY) {
        printf("Error initializing the numbers. %s",
               mp_error_to_string(result));
        return 1;
    }


    mp_read_radix(&a, "1", 10);
    mp_read_radix(&d, "2724414110474605931834268501164757645998726878473076809432604223414351675387", 10);
    mp_read_radix(&p, "115792089237316195423570985008687907853269984665640564039457584007913129639319", 10);
    mp_read_radix(&q, "28948022309329048855892746252171976963338560298092253442512153408785530358887", 10);
    mp_read_radix(&u, "13", 10);
    mp_read_radix(&v, "43779144989398987843428779166090436406934195821915183574454224403186176950503", 10);

    mp_read_radix(&t, "512", 10);
    mp_read_radix(&t1, "783", 10);


    struct Parameters params = {a, d, p, q, u, v};

    struct Point P;
    P.X = u;
    P.Y = v;
    P.Z = a;


//ПЕРВЫЕ ДВА ТЕСТА
/*
    struct Point P1;
    P1 = BinaryMethod(&P, q, params);
    printf("%s", "TEST 1: ");
    IfOnCurve(&P1, params);
    printf("%s", "TEST 2: ");
    IfIdentical(&P1, params);
*/

//ТРЕТИЙ ТЕСТ 3.1
    /*struct Point P1;
    mp_addmod(&q, &a, &p, &q);
    P1 = BinaryMethod(&P, q, params);
    printf("%s", "TEST 3.1: ");
    IfNeighbors(&P1, &P, params);*/

//ТРЕТИЙ ТЕСТ 3.2

    /*
    struct Point P1;
    mp_submod(&q, &a, &p, &q);
    P1 = BinaryMethod(&P, q, params);
    printf("%s", "TEST 3.2: ");
    mp_neg(&P.X, &P.X);
    mp_neg(&P.Z, &P.Z);
    mp_mod(&P.X, &p, &P.X);
    mp_mod(&P.Z, &p, &P.Z);
    IfNeighbors(&P1, &P, params);
*/




//ЧЕТВЕРТЫЙ ТЕСТ
 /*   printf("%s", "TEST 4: ");
    struct Point P1;
    mp_addmod(&t, &t1, &p, &t);
    P1 = BinaryMethod(&P, t, params);
    ToText(P1.X);
    ToText(P1.Y);
    ToText(P1.Z);

    mp_int x4,y4,z4, a4, b4, c4;
    mp_init_multi(&x4, &y4, &z4, &a4, &b4, &c4, NULL);
    mp_read_radix(&x4, "72044294942874046977222924124655700724349196941677802073801936404244642176522", 10);
    mp_read_radix(&y4, "90873943441692278212453548254847993556900622188125177514980435162063934989635", 10);
    mp_read_radix(&z4, "0", 10);

    mp_read_radix(&a4, "66349702245150253999391046487116098928770330087329907499559175930326860401959", 10);
    mp_read_radix(&b4, "106197119342637702326435514873280640920772982677795516566958134913965717816646", 10);
    mp_read_radix(&c4, "0", 10);

    struct Point A, B;
    A.X = x4;
    A.Y = y4;
    A.Z = z4;
    B.X = a4;
    B.Y = b4;
    B.Z = c4;

    AddPoints(&A, &B, &params);
    Transform(&A, &params);
    ToText(A.X);
    ToText(A.Y);
    ToText(A.Z);
*/

    //mp_clear_multi(&a, &d, &p, &q, &u, &v, NULL);


    return 0;
}
