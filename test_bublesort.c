/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bublesort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:26:17 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/09/05 18:16:07 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
void ft_swap(int *prim, int *seg)
{
    int swap;
    
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
    primer = 10;
    index_seg = 0;
    index_prim = 0;
    while(primer --)
    {
        index_seg = 0;
        seg = 10;
        while(seg)
        {
            if (nums[index_seg] > nums[index_seg + 1])
            {
                ft_swap(&(nums[index_seg]), &(nums[index_seg + 1]));
            }
            
            index_seg ++;
            seg --;
        }
        index_prim ++;
    }
    int print;

    print = 10;
    int i = 0;
    while(print --)
    {
        printf("order = %d\n", nums[i]);
        i++;

    }
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