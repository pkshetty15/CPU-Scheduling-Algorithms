#include <stdio.h>

void insertBetween(int ready[], int k, int index)
{
    int t;
    int temp = ready[index];
    for(t=index;t< k;t++)
    {
        ready[t] = ready[t+1];
    }
    ready[k] = temp;
}

void ready_q(int at[], int NOP, int ready[])
{
    int i, j, temp, temp_a[10];
    for (int i = 0; i < NOP; i++)
    {
        temp_a[i] = at[i];
    }
    for (i = 0; i < NOP - 1; i++)
    {
        for (j = 0; j < NOP - i - 1; j++)
        {
            if (temp_a[j] > temp_a[j + 1])
            {
                temp = temp_a[j];
                temp_a[j] = temp_a[j + 1];
                temp_a[j + 1] = temp;
                temp = ready[j];
                ready[j] = ready[j + 1];
                ready[j + 1] = temp;
            }
        }
    }
}

void main()
{
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10], ready[10],last;
    float avg_wt, avg_tat;
    printf(" Total number of process in the system: ");
    scanf("%d", &NOP);
    y = NOP;

    for (i = 0; i < NOP; i++)
    {
        printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i + 1);
        printf(" Arrival time is: \t");
        scanf("%d", &at[i]);
        ready[i] = i;
        printf(" \nBurst time is: \t");
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
    }

    printf("Enter the Time Quantum for the process: \t");
    scanf("%d", &quant);
    ready_q(at, NOP, ready);
    last=ready[NOP-1];
    printf("\n Process No \t\t Burst Time \t\t CT \t\t TAT \t\t Waiting Time ");
    int flag = 0, index = 0;
    for (sum = 0, i = ready[0]; y != 0;)
    {
        while (flag != 1)
        {
            if (at[i] <= sum)
            {
                break;
            }
            sum = sum + 1;
        }

        if (temp[i] <= quant && temp[i] > 0)
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }
        if (temp[i] == 0 && count == 1)
        {
            y--;
            printf("\nProcess No[%d] \t\t\t %d\t\t %d\t\t %d\t\t %d", i + 1, bt[i],sum, sum - at[i], sum - at[i] - bt[i]);
            wt = wt + sum - at[i] - bt[i];
            tat = tat + sum - at[i];
            count = 0;
        }
        if (temp[i] != 0 && flag != 1 && sum<last )
        {
            for (int k = index; k < NOP-1; k++)
            {
                if (at[ready[k + 1]] > sum)
                {
                    insertBetween(ready, k, index);
                    index--;
                    break;
                }
            }
        }
        if (index == NOP - 1)
        {
            index = 0;
            flag = 1;
            i = ready[index];
        }
        else if (at[ready[index + 1]] <= sum)
        {
            index++;
            i = ready[index];
        }
        else
        {
            index = 0;
            i = ready[index];
        }
    }
    avg_wt = wt * 1.0 / NOP;
    avg_tat = tat * 1.0 / NOP;
    printf("\n Average Turn Around Time: \t%f", avg_tat);
    printf("\n Average Waiting Time: \t%f", avg_wt);
}
