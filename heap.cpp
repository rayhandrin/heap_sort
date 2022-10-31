/* 
Nama 		: Devina Lusiana
NIM 		: 211511011
Tanggal 	: 18 Mei 2022
Mata Kuliah : Struktur Data & Algoritma
*/ 

#include <iostream>
#include <queue>
#include "heap.h"
using namespace std;

TreeAddr lastNode, parentOfLastNode;

/* dibuat oleh Devina Lusiana*/
void menuHeapSort()
{
    cout<<"==================================================================="<<endl;
    cout<<"||                       INTEGER HEAP SORT                       ||"<<endl;
    cout<<"==================================================================="<<endl;
    cout<<"Catatan: Masukkan angka 00 jika sudah selesai memasukkan angka"<<endl<<endl;
}

/*Sumber :https://www.techiedelight.com/delete-given-binary-tree-iterative-recursive/ */
void deleteBinaryTree(TreeAddr root)
{
    if (root == nullptr)
    {
        return;
    }

    deleteBinaryTree(root->left);
    deleteBinaryTree(root->right);

    delete root;

    root = nullptr;
}

/* dibuat oleh Devina Lusiana*/
TreeAddr CreateNodeHeap(int X)
{
    TreeAddr newNode;
    newNode = (TreeAddr )malloc(sizeof(TreeNode));
    if (newNode != NULL)
    {
        newNode->data = X;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
    }
    return newNode;
}

/* dibuat oleh Devina Lusiana*/
void SwapValue(TreeAddr a, TreeAddr b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

/* dibuat oleh Devina Lusiana*/
void inorder(TreeAddr root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

/* dibuat oleh Devina Lusiana*/
void heapify(TreeAddr node)
{
    if (node->parent != NULL)
    {

        if (node->data > node->parent->data)
        {
            swap(node->data, node->parent->data);
            heapify(node->parent);
        }
    }
    else
    {
        return;
    }
}

/* 
    Sumber https://www.techiedelight.com/construct-complete-binary-tree-from-linked-list/
    dimodifikasi oleh Devina Lusiana. Modifikasinya yaitu membuat complete binary tree menjadi max heap
*/

TreeAddr BuildMaxHeap(List *L)
{

    address P = First(*L);

    TreeAddr root = CreateNodeHeap(Info(P));

    P = Next(P);
    
    queue<TreeAddr > q;

    q.push(root);

    while (P != NULL)
    {

        TreeAddr front = q.front();
        
        q.pop();
        
        TreeAddr leftChild = CreateNodeHeap(Info(P));

        front->left = leftChild;

        leftChild->parent = front;

        q.push(leftChild);

        heapify(leftChild);

        P = Next(P);

            if (P != NULL)
            {

                TreeAddr rightChild = CreateNodeHeap(Info(P));

                front->right = rightChild;

                rightChild->parent = front;

                q.push(rightChild);

                heapify(rightChild);
                
                P = Next(P);
            }
    }

    return root;
}

/* Sumber : https://www.geeksforgeeks.org/delete-the-last-leaf-node-in-a-binary-tree/ */
int height(TreeAddr root)
{
    if (root == NULL)
        return 0;

    int left = height(root->left) + 1;
    int right = height(root->right) + 1;

    return max(left, right);
}

/* Sumber : https://www.geeksforgeeks.org/delete-the-last-leaf-node-in-a-binary-tree/ */
TreeAddr getLastNodeAndItsParent(TreeAddr root, int level, TreeAddr parent)
{
    TreeAddr temp;
    if (root == NULL)
        return temp;

    if (level == 1)
    {
        lastNode = root;
        parentOfLastNode = parent;
    }
    temp = getLastNodeAndItsParent(root->left, level - 1, root);
    temp = getLastNodeAndItsParent(root->right, level - 1, root);
    return temp;
}

/* 
    Sumber : https://www.geeksforgeeks.org/delete-the-last-leaf-node-in-a-binary-tree/
    dimodifikasi oleh : Devina Lusiana. Pada awalnya modul getLastNode ini digunakan untuk menghapus
    last element pada binary tree, kemudian dimodifikasi menjadi mengirimkan address dari last element 
*/
TreeAddr getLastNode(TreeAddr root)
{
    TreeAddr temp;
    int levelOfLastNode = height(root);
    temp = getLastNodeAndItsParent(root, levelOfLastNode, NULL);

    if (lastNode!=NULL && parentOfLastNode!=NULL)
    {
        if (parentOfLastNode->right !=NULL )
            return parentOfLastNode->right;
        else
            return parentOfLastNode->left;
    }

    return root;
}

/* Dibuat oleh : Devina Lusiana */
void HeapSort(List L_data)
{
    List L_ascending;
    List L_descending;
    CreateList(&L_ascending);
    CreateList(&L_descending);
    TreeAddr root;
    TreeAddr temp;
    int jumlah = NbElmt(L_data);

    do
    {
        root = BuildMaxHeap(&L_data);
        temp = getLastNode(root);
        SwapValue(temp, root);

        InsVFirst(&L_ascending, temp->data);
        InsVLast(&L_descending, temp->data);
        DelP(&L_data, temp->data);
        
        jumlah = NbElmt(L_data);
        if (jumlah == 1)
        {
            cout<<"Data setelah di sort secara ascending: ";
            InsVFirst(&L_ascending, root->data);
            PrintInfo(L_ascending);
            cout<<endl;
            
            cout<<"Data setelah di sort secara descending: ";
            InsVLast(&L_descending, root->data);
            PrintInfo(L_descending);
            cout<<endl;
        }

        deleteBinaryTree(root);

    } while (!ListEmpty(L_data));
    
    return;
}
