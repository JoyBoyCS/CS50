#include <stdio.h>

void merge(int arr[], int l, int m, int r)
{

    int n1 = m - l + 1;
    int n2 = r - m;

    int i = 0;
    int j = 0;
    int k = l;

    int L[n1];
    int R[n2];

    for (int d = 0; d < n1; d++)
    {
        L[d] = arr[l + d];  // 修改为从 arr[l] 开始复制
    }
    for (int d = 0; d < n2; d++)
    {
        R[d] = arr[m + 1 + d]; // 修改为从 arr[m+1] 开始复制
    }

    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
        {
            arr[k] = R[j];
            j++;
        }
        else
        {
            arr[k] = L[i];
            i++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        k++;
        i++;
    }
    while(j < n2)
    {
        arr[k] = R[j];
        k++;
        j++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (r-l+1 == 1)
    {
        return;
    }
        int m = l + (r - l) / 2; // 修改这里计算中点的方式
        mergeSort(arr, l , m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);

}

int main(void)
{
    int arr[9] = {434,12,53,65,88,342,123,65476,21};

    mergeSort(arr, 0, 8);
    for (int i = 0; i < 8; i++)
    {
        printf("%i,",arr[i]);
    }
}