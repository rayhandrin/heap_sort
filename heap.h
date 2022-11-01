/*
Nama 		: Devina Lusiana
NIM 		: 211511011
Tanggal 	: 18 Mei 2022
Mata Kuliah : Struktur Data & Algoritma
*/

#ifndef heap_h
#define heap_h
#include "list.h"

#include <stdio.h>

typedef struct TreeNode *TreeAddr;
typedef struct TreeNode
{
    int data;
    TreeAddr left;
    TreeAddr right;
    TreeAddr parent;
} ElmtTreeNode;

void menuHeapSort();
void deleteBinaryTree(TreeAddr root);
void SwapValue(TreeAddr a, TreeAddr b);
void inorder(TreeAddr root);
void heapify(TreeAddr node);
void HeapSort(List L_data);
int height(TreeAddr root);
TreeAddr CreateNodeHeap(int X);
TreeAddr BuildMaxHeap(List *L);
TreeAddr getLastNodeAndItsParent(TreeAddr root, int level, TreeAddr parent);
TreeAddr getLastNode(TreeAddr root);

#endif