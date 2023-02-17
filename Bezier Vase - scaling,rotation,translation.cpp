#include <iostream>
#include <math.h>
#include <graphics.h>

#define N 12
#define PI 3.1415

using namespace std;

void bezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
    double t;
    int x, y;

    for (t = 0.0; t <= 1.0; t += 0.0005) {
        x = pow(1-t,3)*x0 + 3*t*pow(1-t,2)*x1 + 3*pow(t,2)*(1-t)*x2 + pow(t,3)*x3;
        y = pow(1-t,3)*y0 + 3*t*pow(1-t,2)*y1 + 3*pow(t,2)*(1-t)*y2 + pow(t,3)*y3;
        putpixel(x, y, GREEN);
    }
}

int main()
{
    initwindow(900,700);

    int poli[]={200,100,250,175,80,250,200,400,200,100,300,100,300,100,250,175,420,250,300,400,200,400,300,400};
    //int poliO[]={300,100,250,175,420,250,300,400};

    //pentru prima curba
    int x0=poli[0],y0=poli[1];
    int x1=poli[2],y1=poli[3];
    int x2=poli[4],y2=poli[5];
    int x3=poli[6],y3=poli[7];

    //linia de sus
    int x4=poli[8],y4=poli[9];
    int x5=poli[10],y5=poli[11];

    //pentru curba oglindita
    int x6=poli[12],y6=poli[13];
    int x7=poli[14],y7=poli[15];
    int x8=poli[16],y8=poli[17];
    int x9=poli[18],y9=poli[19];

    //linia de jos
    int x10=poli[20],y10=poli[21];
    int x11=poli[22],y11=poli[23];


    setcolor(GREEN);
    bezier(x0,y0,x1,y1,x2,y2,x3,y3);
    line(x4,y4,x5,y5);
    bezier(x6,y6,x7,y7,x8,y8,x9,y9);
    line(x10,y10,x11,y11);

    //DE AICI INCEP TRANSFORMARILE ASUPRA FORMEI

    // TRANSLATATIA POLIGONULUI
    int tx =200, ty = 100;
    for(int i=0;i<N+1;i++){
            poli[2*i] = poli[2*i] + tx;
            poli[2*i+1]= poli[2*i+1] + ty;
    }

    //pentru prima curba
    x0=poli[0],y0=poli[1];
    x1=poli[2],y1=poli[3];
    x2=poli[4],y2=poli[5];
    x3=poli[6],y3=poli[7];

    //linia de sus
    x4=poli[8],y4=poli[9];
    x5=poli[10],y5=poli[11];

    //pentru curba oglindita
    x6=poli[12],y6=poli[13];
    x7=poli[14],y7=poli[15];
    x8=poli[16],y8=poli[17];
    x9=poli[18],y9=poli[19];

    //linia de jos
    x10=poli[20],y10=poli[21];
    x11=poli[22],y11=poli[23];

    bezier(x0,y0,x1,y1,x2,y2,x3,y3);
    line(x4,y4,x5,y5);
    bezier(x6,y6,x7,y7,x8,y8,x9,y9);
    line(x10,y10,x11,y11);

    double xc=0, yc=0;
    for(int i=0;i<N;i++){
            xc += poli[2*i];
            yc += poli[2*i+1];
    }
    xc/=N;yc/=N;
    //circle(xc,yc,5);

    //TRANSLATARILE(coordonatele) se aduna intre ele deoarece poligonul e construit doar dupa SCALARE
    //insa daca a doua ar fi (0,0) prima n ar avea sens ca nu are ce translata inca (Oarecum)
    //pratic a doua TRANSLATARE porneste in continuarea primei

    tx =200;
    ty = 0;

    //Avem doua TRANSLATARI, prima are loc inainte de ROTATIE si SCALARE, iar a doua TRANSLATATIE are rol dupa
    // indiferent ca sunt scrise una dupa alta

    double Xc = xc+tx, Yc=yc+ty;
    //circle((int)Xc, (int)Yc, 4);//face un cerc in centrul de greutate
    //TRANSLATATIE 2
    for(int i=0;i<N+1;i++){
            poli[2*i] = poli[2*i] + tx;
            poli[2*i+1]= poli[2*i+1] + ty;
    }

    // scalare
    double Sx=.5, Sy=.5;
    for(int i=0;i<N+1;i++){
            poli[2*i]   = Xc + (-Xc+poli[2*i])   * Sx;
            poli[2*i+1] = Yc + (-Yc+poli[2*i+1]) * Sy;
    }

    //pentru prima curba
    x0=poli[0],y0=poli[1];
    x1=poli[2],y1=poli[3];
    x2=poli[4],y2=poli[5];
    x3=poli[6],y3=poli[7];

    //linia de sus
    x4=poli[8],y4=poli[9];
    x5=poli[10],y5=poli[11];

    //pentru curba oglindita
    x6=poli[12],y6=poli[13];
    x7=poli[14],y7=poli[15];
    x8=poli[16],y8=poli[17];
    x9=poli[18],y9=poli[19];

    //linia de jos
    x10=poli[20],y10=poli[21];
    x11=poli[22],y11=poli[23];

    /*
    bezier(x0,y0,x1,y1,x2,y2,x3,y3);
    line(x4,y4,x5,y5);
    bezier(x6,y6,x7,y7,x8,y8,x9,y9);
    line(x10,y10,x11,y11);
    */

    //ROTATIA FATA DE CENTRUL (XC,YC)
    double cosa = cos(2*PI/5), sina = sin(2*PI/5);
    for(int i=0;i<N+1;i++){
            double xi,yi;
            xi = poli[2*i];
            yi = poli[2*i+1];
            poli[2*i]   = Xc + (xi-Xc)*cosa - (yi-Yc)*sina;
            poli[2*i+1] = Yc + (xi-Xc)*sina + (yi-Yc)*cosa;
    }

    //pentru prima curba
    x0=poli[0],y0=poli[1];
    x1=poli[2],y1=poli[3];
    x2=poli[4],y2=poli[5];
    x3=poli[6],y3=poli[7];

    //linia de sus
    x4=poli[8],y4=poli[9];
    x5=poli[10],y5=poli[11];

    //pentru curba oglindita
    x6=poli[12],y6=poli[13];
    x7=poli[14],y7=poli[15];
    x8=poli[16],y8=poli[17];
    x9=poli[18],y9=poli[19];

    //linia de jos
    x10=poli[20],y10=poli[21];
    x11=poli[22],y11=poli[23];

    bezier(x0,y0,x1,y1,x2,y2,x3,y3);
    line(x4,y4,x5,y5);
    bezier(x6,y6,x7,y7,x8,y8,x9,y9);
    line(x10,y10,x11,y11);


    getch();
    closegraph();
    return 0;
}
