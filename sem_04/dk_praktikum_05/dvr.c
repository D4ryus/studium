/*
 * author: d4ryus - https://github.com/d4ryus/
 * file: dvr.c
 * vim:foldmethod=syntax:foldcolumn=7:
 */
#include <stdio.h>

typedef struct table_def          table;
typedef struct dest_dist_gate_def dest_dist_gate;

struct
dest_dist_gate_def
{
    char dest;
    int  dist;
    char gate;
};

struct
table_def
{
    char id;
    int  round;
    char learn[6];
    dest_dist_gate ddg[6];
};

void
init(table* t, int size)
{
    int i;
    int ii;
    for (i = 0; i < size; i++)
    {
        t[i].id    = 65 + i;
        t[i].round = 0;
        for (ii = 0; ii < size; ii++)
            t[i].learn[ii] = '-';
        for(ii = 0; ii < sizeof(t[i].ddg) / sizeof(dest_dist_gate); ii++)
        {
            t[i].ddg[ii].dest = 65 + ii;
            t[i].ddg[ii].dist = 999;
            t[i].ddg[ii].gate = '-';
        }
    }
}

void
init_adjanz(table* t)
{
    //TABLE A       //A
    t[0].ddg[0].dist = 0;
    t[0].ddg[0].gate = 'A';
                    //B
    t[0].ddg[1].dist = 2;
    t[0].ddg[1].gate = 'B';
    t[0].learn[1] = 'B';
                    //C
    t[0].ddg[2].dist = 5;
    t[0].ddg[2].gate = 'C';
    t[0].learn[2] = 'C';
                    //D
    t[0].ddg[3].dist = 1;
    t[0].ddg[3].gate = 'D';
    t[0].learn[3] = 'D';


    //TABLE B       //A
    t[1].ddg[0].dist = 2;
    t[1].ddg[0].gate = 'A';
    t[1].learn[0] = 'A';
                    //B
    t[1].ddg[1].dist = 0;
    t[1].ddg[1].gate = 'B';
                    //C
    t[1].ddg[2].dist = 3;
    t[1].ddg[2].gate = 'C';
    t[1].learn[2] = 'C';
                    //D
    t[1].ddg[3].dist = 2;
    t[1].ddg[3].gate = 'D';
    t[1].learn[3] = 'D';

    //TABLE C       //A
    t[2].ddg[0].dist = 5;
    t[2].ddg[0].gate = 'A';
    t[2].learn[0] = 'A';
                    //B
    t[2].ddg[1].dist = 3;
    t[2].ddg[1].gate = 'B';
    t[2].learn[1] = 'B';
                    //C
    t[2].ddg[2].dist = 0;
    t[2].ddg[2].gate = 'C';
                    //D
    t[2].ddg[3].dist = 3;
    t[2].ddg[3].gate = 'D';
    t[2].learn[3] = 'D';
                    //E
    t[2].ddg[4].dist = 1;
    t[2].ddg[4].gate = 'E';
    t[2].learn[4] = 'E';
                    //F
    t[2].ddg[5].dist = 5;
    t[2].ddg[5].gate = 'F';
    t[2].learn[5] = 'F';

    //TABLE D       //A
    t[3].ddg[0].dist = 1;
    t[3].ddg[0].gate = 'A';
    t[3].learn[0] = 'A';
                    //B
    t[3].ddg[1].dist = 2;
    t[3].ddg[1].gate = 'B';
    t[3].learn[1] = 'B';
                    //C
    t[3].ddg[2].dist = 3;
    t[3].ddg[2].gate = 'C';
    t[3].learn[2] = 'C';
                    //D
    t[3].ddg[3].dist = 0;
    t[3].ddg[3].gate = 'D';
                    //E
    t[3].ddg[4].dist = 1;
    t[3].ddg[4].gate = 'E';
    t[3].learn[4] = 'E';

    //TABLE E       //C
    t[4].ddg[2].dist = 1;
    t[4].ddg[2].gate = 'C';
    t[4].learn[2] = 'C';
                    //D
    t[4].ddg[3].dist = 1;
    t[4].ddg[3].gate = 'D';
    t[4].learn[3] = 'D';
                    //E
    t[4].ddg[4].dist = 0;
    t[4].ddg[4].gate = 'E';
                    //F
    t[4].ddg[5].dist = 2;
    t[4].ddg[5].gate = 'F';
    t[4].learn[5] = 'F';

    //TABLE F       //C
    t[5].ddg[2].dist = 5;
    t[5].ddg[2].gate = 'C';
    t[5].learn[2] = 'C';
                    //E
    t[5].ddg[4].dist = 2;
    t[5].ddg[4].gate = 'E';
    t[5].learn[4] = 'E';
                    //F
    t[5].ddg[5].dist = 0;
    t[5].ddg[5].gate = 'F';
}

void
print_tables(table* t, int size)
{
    printf("\n");
    int i;
    for (i = 0; i < size; i++)
        printf("Table:       %c%d    ", t[i].id,t[i].round);
    printf("\n");

    for (i = 0; i < size; i++)
    {
        printf("Learning ");
        int ii;
        for (ii = 0; ii < size; ii++)
            printf("%c", t[i].learn[ii]);
        printf("    ");
    }
    printf("\n");

    for (i = 0; i < size; i++)
        printf("---------------    ");
    printf("\n");

    int ii;
    for (ii = 0; ii < sizeof(t[i].ddg) / sizeof(dest_dist_gate); ii++)
    {
        for (i = 0; i < size; i++)
            printf("| %c | %3d | %c |    ", t[i].ddg[ii].dest,
                    t[i].ddg[ii].dist,
                    t[i].ddg[ii].gate);
        printf("\n");
    }

    for (i = 0; i < size; i++)
        printf("---------------    ");
    printf("\n");
}

void
copy_table(table* t1, table* t2, int size)
{
    int i;
    int ii;
    for (i = 0; i < size; i++)
    {
        t2[i].round = t1[i].round;
        for (ii = 0; ii < size; ii++)
        {
            t2[i].ddg[ii].dest = t1[i].ddg[ii].dest;
            t2[i].ddg[ii].dist = t1[i].ddg[ii].dist;
            t2[i].ddg[ii].gate = t1[i].ddg[ii].gate;
            t2[i].learn[ii]    = t1[i].learn[ii];
            t2[i].learn[ii]    = t1[i].learn[ii];
            t2[i].learn[ii]    = t1[i].learn[ii];
        }
    }
}

int
learn_round(table* t1, table* t2, int size)
{
    int i;
    int ii;
    int iii;
    int count = 0;
    for(i = 0; i < size; i++)
    {
        t2[i].round += 1;
        for(ii = 0; ii < size; ii++)
        {
            for(iii = 0; iii < size; iii++)
            {
                if(    (                    i != ii  )
                    && (     t1[i].learn[iii] != '-' ) )
                {
                    if( t1[i].ddg[ii].dist > (t1[iii].ddg[ii].dist + t1[i].ddg[iii].dist) )
                    {
                        t2[i].ddg[ii].dist = t1[iii].ddg[ii].dist + t1[i].ddg[iii].dist;
                        t2[i].ddg[ii].gate = t1[iii].id;
                        count++;
                        continue;
                    }
                    continue;
                }
            }
        }
    }
    return count;
}

int
learn_something(table* t, int size)
{
    int i;
    int ii;
    int iii;
    int count = 0;
    for(i = 0; i < size; i++)
    {
        t[i].round += 1;
        for(ii = 0; ii < size; ii++)
        {
            for(iii = 0; iii < size; iii++)
            {
                if(    (                   i != ii  )
                    && (     t[i].learn[iii] != '-' ) )
                {
                    if( t[i].ddg[ii].dist > (t[iii].ddg[ii].dist + t[i].ddg[iii].dist) )
                    {
                        t[i].ddg[ii].dist = t[iii].ddg[ii].dist + t[i].ddg[iii].dist;
                        t[i].ddg[ii].gate = t[iii].id;
                        count++;
                        continue;
                    }
                    continue;
                }
            }
        }
    }
    return count;
}

int
main()
{
    int size    = 6;
    int changes = 1;

    table tbl1[size];
    table tbl2[size];

    printf("\ninit default tables...");
    init(tbl1, size);
    init(tbl2, size);
    print_tables(tbl1, size);

    printf("\ninit adjanz tables...");
    init_adjanz(tbl1);
    init_adjanz(tbl2);
    print_tables(tbl1, size);

    printf("\nstart learn algorithm...");
    while(changes != 0)
    {
        changes = learn_round(tbl1, tbl2, size);
        print_tables(tbl2, size);
        printf("%d changes.\n", changes);
        copy_table(tbl2, tbl1, size);
    }
    /*
    while(changes != 0)
    {
        changes = learn_something(tbl1, size);
        print_tables(tbl1, size);
        printf("%d changes.\n", changes);
    }
    */
}
