#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define G_MOON 1.6
#define V_MAX 1.0
#define DT 0.01 //krok symulacji [s]
#define PRINT_FREQ 0.25 //co ile wypisac [s]


 int pilot(double m, double h, double v, double Fc) {
     double a = Fc / m - G_MOON; //hamowanie z włączonym silnikiem
     double h_next = h - v * DT - 0.5 * G_MOON * DT * DT; //wysokość w następnym kroku symulacji
     double v_next = v + G_MOON * DT; //prędkość w następnym kroku
     double v_end = v_next * v_next - 2.0 * a * h_next; //v_końc^2 = v^2 − 2*a*h

     return v > 0 && v_end >= V_MAX * V_MAX;
 }

int main(int argc, char *argv[]) {
    double m = (argc > 1 ? atof(argv[1]) : 2000.0);
    double H  = (argc > 2) ? atof(argv[2]) : 500.0;
    double v  = (argc > 3) ? atof(argv[3]) : 10.0;
    double Fc = (argc > 4) ? atof(argv[4]) : 4500.0;
    const char *fname = (argc > 5) ? argv[5] : "przebieg.csv";

    if (m <= 0.0 || H <= 0.0 || Fc < 0.0 || v < 0.0) {
        printf("Bledne dane wejsciowe.");
        return 1;
    }
     FILE *f = fopen(fname, "w");
     fprintf(f, "czas_s,wysokosc_m,predkosc_ms,silnik\n");

     double t = 0.0;
     double next_print = 0.0;
     int engine = 0;

    while (1) {
        engine = pilot(m, H, v, Fc);

        fprintf(f, "%.2f,%.3f,%.3f,%d\n", t, H, v, engine);

        if (t >= next_print) {
            printf("H=%.1fm, V=%.1fm/s, %s\n", H, v, engine ? "ON" : "OFF");
            next_print += PRINT_FREQ;
        }

        double a_down = G_MOON - (engine? Fc/m : 0.0); //przyspiesenie grawitacja - ciąg silnika
        double H_new = H - v * DT - 0.5 * a_down * DT * DT;
        double v_new = v + a_down * DT;

        if (H_new <= 0.0) {
            double s;
            if (fabs(a_down) == 0) {
                s = (v > 0.0) ? H / v : DT;
            }else {
                double disc = v * v + 2.0 * a_down * H;
                s = (-v + sqrt(disc)) / a_down;
            }
            if (s < 0.0 || s > DT) s = DT;
            double v_touch = v + a_down * s;
            t += s;
            fprintf(f, "%.2f,%.3f,%.3f,%d\n", t, 0.0, v_touch, engine);
            printf("H=0.0m, V=%.1fm/s, %s\n", v_touch, engine ? "ON" : "OFF");
            printf("\nDotkniecie Ksiezyca po %.2f s z predkoscia %.2f m/s.\n", t, v_touch);

            if (v_touch < V_MAX)
                printf("LADOWANIE UDANE.\n");
            else
                printf("LADOWANIE NIEUDANE - ladownik rozbity (limit %.0f m/s).\n",
                       V_MAX);
            break;

        }
        H = H_new;
        v = v_new;
        t += DT;

    }
     fclose(f);
     return 0;
}