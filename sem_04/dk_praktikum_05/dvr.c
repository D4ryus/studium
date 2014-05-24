/*
 * author: d4ryus - https://github.com/d4ryus/
 * file: dvr.c
 * vim:foldmethod=syntax:foldcolumn=7:
 */
#include <stdio.h>

typedef struct table_def          table;
typedef struct dest_dist_gate_def dest_dist_gate;
#define SIZE 6

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
    char learn[SIZE];
    dest_dist_gate ddg[SIZE];
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

int
insert(table* tbl, char id, char dest, int dist)
{
    int ID   = id   - 65;
    int DEST = dest - 65;
    tbl[ID].ddg[DEST].dist = dist;
    tbl[ID].ddg[DEST].gate = dest;
}

void
init_adjanz(table* t, int size)
{
    insert(t, 'A',   'B', 2);
    insert(t, 'A',   'C', 5);
    insert(t, 'A',   'D', 1);

    insert(t, 'B',   'A', 2);
    insert(t, 'B',   'C', 3);
    insert(t, 'B',   'D', 2);

    insert(t, 'C',   'A', 5);
    insert(t, 'C',   'B', 3);
    insert(t, 'C',   'D', 3);
    insert(t, 'C',   'E', 1);
    insert(t, 'C',   'F', 5);

    insert(t, 'D',   'A', 1);
    insert(t, 'D',   'B', 2);
    insert(t, 'D',   'C', 3);
    insert(t, 'D',   'E', 1);

    insert(t, 'E',   'C', 1);
    insert(t, 'E',   'D', 1);
    insert(t, 'E',   'F', 2);

    insert(t, 'F',   'C', 5);
    insert(t, 'F',   'E', 2);

    int i;
    int ii;
    for(i = 0; i < size; i++)
    {
        for(ii = 0; ii < size; ii++)
        {
            if(i == ii)
                insert(t, 65 + i, 65 + ii, 0);
        }
    }
}

void
set_neighbor(table* t, int size)
{
    int i;
    int ii;
    for (i = 0; i < size; i++)
    {
        for (ii = 0; ii < size; ii++)
        {
            if(    (t[i].ddg[ii].gate != '-')
                && (                i != ii ) )
                t[i].learn[ii] = t[i].ddg[ii].gate;
        }
    }
}

void
print_tables(table* t, int size)
{
    printf("\n");
    int i;
    int ii;
    int iii;
    for (i = 0; i < size; i++)
    {
        printf("Table:      ");
        if(size >= 9)
        {
            for(ii = 0; ii < size-9; ii++)
            printf(" ");
        }
        printf("%c%2d  ", t[i].id,t[i].round);
    }
    printf("\n");

    for (i = 0; i < size; i++)
    {
        printf("%-6s", "Neig:");
        for(ii = 0; ii < 15-6-size; ii++)
                printf(" ");
        for (ii = 0; ii < size; ii++)
            printf("%c", t[i].learn[ii]);
        printf("  ");
    }
    printf("\n");

    for (i = 0; i < size; i++)
    {
        if(size >= 9)
        {
            for(ii = 0; ii < size-9; ii++)
            printf("-");
        }
        printf("---------------  ");
    }
    printf("\n");

    for (ii = 0; ii < size; ii++)
    {
        for (i = 0; i < size; i++)
        {
            printf("|");
            if(size >= 9)
            {
                for(iii = 0; iii < size-9; iii++)
                {
                    if((iii % 2) == 0)
                        printf(" ");
                }
            }
            printf(" %c "           , t[i].ddg[ii].dest);
            printf(    "| %3d |"    , t[i].ddg[ii].dist);
            printf(           " %c ", t[i].ddg[ii].gate);
            if(size >= 9)
            {
                for(iii = 0; iii < size-9; iii++)
                {
                    if((iii % 2) == 1)
                        printf(" ");
                }
            }
            printf("|  ");
        }
        printf("\n");
    }

    for (i = 0; i < size; i++)
    {
        if(size >= 9)
        {
            for(ii = 0; ii < size-9; ii++)
            printf("-");
        }
        printf("---------------  ");
    }
    printf("\n");
}

void
copy_table(table* t1, table* t2, int size)
{
    int i;
    int ii;
    for (i = 0; i < size; i++)
    {
        t2[i].id = t1[i].id;
        t2[i].round = t1[i].round;
        for (ii = 0; ii < size; ii++)
        {
            t2[i].ddg[ii].dest = t1[i].ddg[ii].dest;
            t2[i].ddg[ii].dist = t1[i].ddg[ii].dist;
            t2[i].ddg[ii].gate = t1[i].ddg[ii].gate;
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
    int size    = SIZE;
    int changes = 1;

    table tbl1[size];
    table tbl2[size];

    printf("\ninit default tables...");
    init(tbl1, size);
    print_tables(tbl1, size);

    printf("\ninit adjanz tables...");
    init_adjanz(tbl1, size);
    print_tables(tbl1, size);

    printf("\nsetting neighbors ...");
    set_neighbor(tbl1, size);
    print_tables(tbl1, size);

    printf("\nstart learn algorithm...");
    copy_table(tbl1, tbl2, size);
    int i;
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
