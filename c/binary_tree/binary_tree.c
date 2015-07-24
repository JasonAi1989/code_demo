/*---------------------------------------------------------------------------
 * Modification History:
 * 07/24/2015 Jason Ai     Created
**     	   A
**         B     C
**      D   E F   G
**  the left data <= the right data, so
**  D < E < B < A < F < C < G
 *---------------------------------------------------------------------------
 */

#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*
args:
	tree [in & out] : the node
	data [in] : the data, element
return:
	-1:error
	0: insert the data
*/
int insert_node(Tree *tree, Element data)
{
	if(tree == NULL)
		return -1;

	Tree T = *tree;
	Tree node_p;

	//when the tree is the null root, we should malloc the space
	if(T == NULL)
	{
		node_p = malloc(sizeof(Node));
		bzero(node_p, sizeof(Node));
		node_p->data = data;
		*tree = node_p;  //we can't use T to instead of *tree here
		return 0;
	}

	//distribute the data to left or right kid
	if(T->data >= data)
	{
		if(T->left != NULL)
			insert_node(&T->left, data);
		else
		{
			node_p = malloc(sizeof(Node));
			bzero(node_p, sizeof(Node));
			node_p->data = data;
			T->left = node_p;
			node_p->parent_p = T;
		}
	}
	else
	{
		if(T->right != NULL)
			insert_node(&T->right, data);
		else
		{
			node_p = malloc(sizeof(Node));
			bzero(node_p, sizeof(Node));
			node_p->data = data;
			T->right = node_p;
			node_p->parent_p = T;
		}			
	}	

	return 0;
}

/*
args:
	tree [in & out]: the node
	data [in]: the data, element
return:
	-1:error
	0: don't find the data
	1: find out the data and delete successfully
*/
int delete_node(Tree *tree, Element data)
{
	if (tree == NULL)
		return -1;

	if (*tree == NULL)
		return -1;

	Tree T = *tree;

	/*bingo, we find it, but this node has two kids, 
	    we have to find out an another node to instead of it,
	    the another node's data shoud be similar to current node,
	    so the right kid's left kid or the left kid's right kid is the good option,
	    here, we choose the right kid's left kid to instead of current node ^0^
	*/
	if(T->data == data && T->left != NULL && T->right != NULL) 
	{
		Tree temp_node = T->right;
		Tree temp_parent=NULL;

		//to get the final left kid
		while(temp_node->left)
		{
			temp_parent = temp_node;
			temp_node = temp_node->left;
		}

		T->data = temp_node->data; //get the best data

		if(temp_parent)
			temp_parent->left = temp_node->right; 

		free(temp_node);		
	}
	else if(T->data == data && T->left != NULL)
	{
		Tree temp_node = T;

		*tree = T->left;  //we can't use T to instead of *tree here

		free(temp_node);
	}
	else if(T->data == data && T->right != NULL)
	{
		Tree temp_node = T;

		*tree = T->right;  //we can't use T to instead of *tree here
		
		free(temp_node);
	}
	else if(T->data == data)
	{
		Tree temp_node = T;

		*tree = NULL;

		free(temp_node);
	}
	else if(T->data > data && T->left != NULL) // go ahead
	{
		delete_node(&T->left, data); 
	}
	else if(T->data > data) //we can't find out the data
	{
		return 0;
	}
	else if(T->data < data && T->right != NULL) // go ahead
	{
		delete_node(&T->right, data); 
	}
	else if(T->data < data) //we can't find out the data
	{
		return 0;
	}

	
}
	
void traversal_tree(Tree tree, unsigned int *num)
{
//NLR
	if (!tree)
		return;

	*num ++; //do something by itself firstly

	traversal_tree(tree->left, num); //do something by the left kid secondly

	traversal_tree(tree->right, num); //do something by the right kid finally

//LNR
#if 0
	if (!tree)
		return;

	traversal_tree(tree->left, num); //do something by the left kid firstly

	*num ++; //do something by itself secondly

	traversal_tree(tree->right, num); //do something by the right kid finally
#endif

//LRN
#if 0
	if (!tree)
		return;

	traversal_tree(tree->left, num); //do something by the left kid firstly

	traversal_tree(tree->right, num); //do something by the right kid secondly

	*num ++; //do something by itself finally
#endif
}

void print_tree(Tree tree)
{
	if (!tree)
		return;

	print_tree(tree->left);

	printf("data: %d\n", tree->data);

	print_tree(tree->right);

}

