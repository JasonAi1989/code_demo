/*---------------------------------------------------------------------------
 * Modification History:
 * 07/24/2015 Jason Ai     Created
 *---------------------------------------------------------------------------
 */
#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

typedef unsigned int Element;
typedef struct _node Node;

struct _node
{
	Node* parent_p;
	Node* left;
	Node* right;
	
	Element data;
};

typedef Node* Tree;

int insert_node(Tree *tree, Element data);
int delete_node(Tree *tree, Element data);
void traversal_tree(Tree tree, unsigned int *num);
void print_tree(Tree tree);

#endif