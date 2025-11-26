#include <stdio.h>
#include <string.h>

struct production {
    char lf;
    char rt[10];
    int prod_rear;
    int fl;
};

struct production prodn[20], prodn_new[20];

int main() {
    int b = -1, d, f, q, n, m = 0, c = 0;
    char terminal[20], nonterm[20], alpha[10], extra[10];
    char epsilon = '^';

    /* Input special characters */
    printf("\nEnter the number of Special characters (except non-terminals): ");
    scanf("%d", &q);

    printf("Enter the special characters for your production: ");
    for (int cnt = 0; cnt < q; cnt++) {
        scanf(" %c", &alpha[cnt]);
    }

    /* Input productions */
    printf("\nEnter the number of productions: ");
    scanf("%d", &n);

    for (int cnt = 0; cnt < n; cnt++) {
        printf("Enter production %d (format A alpha): ", cnt + 1);
        scanf(" %c %s", &prodn[cnt].lf, prodn[cnt].rt);
        prodn[cnt].prod_rear = strlen(prodn[cnt].rt);
        prodn[cnt].fl = 0;
    }

    /* Left factoring */
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            if (prodn[i].lf == prodn[j].lf) {

                int idx = 0, p = -1;
                m = 0;

                while (prodn[i].rt[idx] != '\0' && prodn[j].rt[idx] != '\0') {

                    if (prodn[i].rt[idx] == prodn[j].rt[idx]) {
                        extra[++p] = prodn[i].rt[idx];
                        prodn[i].fl = 1;
                        prodn[j].fl = 1;
                    } else {
                        if (p == -1) break;

                        int h = 0, u = 0;

                        prodn_new[++b].lf = prodn[i].lf;
                        strcpy(prodn_new[b].rt, extra);
                        prodn_new[b].rt[p + 1] = alpha[c];

                        prodn_new[++b].lf = alpha[c];
                        for (int g = idx; g < prodn[j].prod_rear; g++)
                            prodn_new[b].rt[h++] = prodn[j].rt[g];

                        prodn_new[++b].lf = alpha[c];
                        for (int g = idx; g < prodn[i].prod_rear; g++)
                            prodn_new[b].rt[u++] = prodn[i].rt[g];

                        m = 1;
                        break;
                    }
                    idx++;
                }

                if (prodn[i].rt[idx] == '\0' && m == 0) {
                    int h = 0;
                    prodn_new[++b].lf = prodn[i].lf;
                    strcpy(prodn_new[b].rt, extra);
                    prodn_new[b].rt[p + 1] = alpha[c];

                    prodn_new[++b].lf = alpha[c];
                    prodn_new[b].rt[0] = epsilon;

                    prodn_new[++b].lf = alpha[c];
                    for (int g = idx; g < prodn[j].prod_rear; g++)
                        prodn_new[b].rt[h++] = prodn[j].rt[g];
                }

                if (prodn[j].rt[idx] == '\0' && m == 0) {
                    int h = 0;
                    prodn_new[++b].lf = prodn[i].lf;
                    strcpy(prodn_new[b].rt, extra);
                    prodn_new[b].rt[p + 1] = alpha[c];

                    prodn_new[++b].lf = alpha[c];
                    prodn_new[b].rt[0] = epsilon;

                    prodn_new[++b].lf = alpha[c];
                    for (int g = idx; g < prodn[i].prod_rear; g++)
                        prodn_new[b].rt[h++] = prodn[i].rt[g];
                }

                c++;
            }
        }
    }

    /* Output */
    printf("\n\n********************************");
    printf("\n AFTER LEFT FACTORING");
    printf("\n********************************\n\n");

    int count = 1;

    for (int i = 0; i <= b; i++) {
        printf("Production %d: %c -> %s\n", count++, prodn_new[i].lf, prodn_new[i].rt);
    }

    for (int i = 0; i < n; i++) {
        if (prodn[i].fl == 0) {
            printf("Production %d: %c -> %s\n", count++, prodn[i].lf, prodn[i].rt);
        }
    }

    return 0;
}
