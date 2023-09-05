/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bublesort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:26:17 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/05 15:49:45 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
void ft_swap(void **prim, void **seg)
{
    void *swap;
    
    // printf("swap?\n");
    swap = *prim;
    *prim = *seg;
    *seg = swap;
}

void ft_order(int *nums)
{
    int primer;
    int seg;
    int index_prim;
    int index_seg;

    seg = 10;
    index_seg = 0;
    primer = 10;
    index_prim = 0;
    while(primer --)
    {
        index_seg  = 0;
        while(seg)
        {
              printf("ANTEEES BUCLEEEEEEE == %d     INDEX SSEEEEEG == %d\n", nums[index_seg], index_seg);
            if (nums[index_seg] > nums[index_seg + 1])
            {
                ft_swap((void *)&nums[index_seg], (void *) &nums[index_seg + 1]);
            }
            
            index_seg ++;
            seg --;
            //  printf("BUCLEEEEEEE == %d     INDEX SSEEEEEG == %d\n", nums[index_seg], index_seg);
        }
        index_prim ++;
    }
    // int print;

    // print = 10;
    // int i = 0;
    // while(print --)
    // {
    //     printf("order = %d\n", nums[i]);
    //     i++;

    // }
}

int main(void)
{
    int nums[10];

    nums [0] = 7;
    nums [1] = 4;
    nums [2] = 1;
    nums [3] = 65;
    nums [4] = -8;
    nums [5] = 5;
    nums [6] = 98;
    nums [7] = -76;
    nums [8] = 2;
    nums [9] = 13;
    
    ft_order(nums);
}