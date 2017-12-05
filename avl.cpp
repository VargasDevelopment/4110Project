#include <stdio.h>
#include <iostream>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
AvlNode* balance(AvlNode * & root);

void print(AvlNode *root);

AvlNode* insert( const int & info, AvlNode * & root )
{
  if (root == NULL)
  {
	root = new AvlNode (info, nullptr, nullptr);
	return root;
  }

  int leftH=0, rightH = 0;

  if(root->left != NULL)
  {
          leftH = root->left->height;
  }
  if(root->right != NULL)
  {
  	  rightH = root->right->height;
  }
  
  if (info < root->element)
  {
    // if current node is less than the root, insert left
    root->left = insert( info, root->left );
    root->left->height = 1 + (leftH > rightH ? leftH : rightH);
  }
  else if (info > root->element)
  {
    // if current node is equal or bigger, insert to the right
    root->right = insert( info, root->right );
    root->right->height = 1 + (leftH > rightH ? leftH : rightH);

  }
  else
  {
	return root;

  }
	
  
  return balance(root);
}

int heightDiff(AvlNode * & root)
{
	if(root == NULL)
		return 0;
	
	int left=0, right=0;
        if(root->left != NULL)
        {
                left = root->left->height;
        }
        if(root->right != NULL)
        {
                right = root->right->height;
        }
	
	return (left - right);
}

AvlNode * rotateLeft(AvlNode * & root)
{
	int rootLeftH=0, rootRightH = 0, leftH = 0, rightH = 0;

        if(root->left != NULL)
        {
                rootLeftH = root->left->height;
        }
        if(root->right != NULL)
        {
                rootRightH = root->right->height;
        }

        AvlNode *temp = root->right;
        AvlNode *temp2 = temp->left;

        temp->left = root;
        root->right = temp2;

        if(temp->left != NULL)
        {
                leftH = temp->left->height;
        }
        if(temp->right != NULL)
        {
                rightH = temp->right->height;
        }

	
        return temp;
}

AvlNode * rotateRight(AvlNode * & root)
{
	int rootLeftH=0, rootRightH = 0, leftH = 0, rightH = 0;

  	if(root->left != NULL)
  	{
      		rootLeftH = root->left->height;
  	}
  	if(root->right != NULL)
  	{
          	rootRightH = root->right->height;
  	}

  AvlNode *temp = root->left;
	AvlNode *temp2 = temp->right;
        
	temp->right = root;
        root->left = temp2;
	
	if(temp->left != NULL)
        {
                leftH = temp->left->height;
        }
        if(temp->right != NULL)
        {
                rightH = temp->right->height;
        }
	
	
        return temp;
}

AvlNode* balance(AvlNode * & root)
{
	
	int diff = heightDiff(root);
	int rightDiff = heightDiff(root->right);
	int leftDiff = heightDiff(root->left);
			
	if(diff > 1 && leftDiff >= 0)
	{
		return rotateRight(root);
	}
	
	if(diff > 1 && leftDiff < 0)
        {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
        }
	
	if(diff < -1 && rightDiff <= 0)
	{
		return rotateLeft(root);
	}
	
        if(diff < -1 && rightDiff > 0)
        {
        	root->right =  rotateRight(root->right);
                return rotateLeft(root);
        }

        return root;
}

AvlNode * findMin(AvlNode * & root)
{
	if(root->left)
	{
		return findMin(root->left);
	}
	else
	{
		return root;
	}
}

AvlNode * removeMin(AvlNode * & root)
{
	if(root->left == 0)
	{
		return root->right;
	}
	else
	{
		root->left = removeMin(root->left);
		balance(root);
		return root;
	}
}

/**
 * Internal method to remove from a subtree.
 * info is the item to remove.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
AvlNode* remove( const int & info, AvlNode * & root ) {
	printf("deleting\n");
	
	if(!root)
	{
		return NULL;
	}
	
	if(info < root->element)
	{
		printf("going left\n");
		root->left = remove(info, root->left);
	}
	else if(info > root->element)
	{
		printf("going rightt\n");
		root->right = remove(info, root->right);
	}
	else
	{
		if((root->left == NULL) || (root->right == NULL))
		{
			AvlNode* tmp = root->left ? root->left : root->right;
			
			if(tmp == NULL)
			{
				tmp = root;
				root = NULL;
			}
			else
			{
				root = tmp;
			}

			delete tmp;
		}
		else
		{
			AvlNode * tmp = findMin(root->right);
			root->element = tmp->element;
			
			root->right = remove(tmp->element, root->right);
		}
		
	}

	if (root == NULL)
        	return root;
		
	int leftH=0, rightH = 0;
	
	if(root->left)
	{
		leftH = root->left->height;
	}
	if(root->right)
	{
		rightH = root->right->height;
	}
	
	root->height = 1 + (leftH > rightH ? leftH : rightH);
	
	return balance(root);
}

/*
 * You will probably neesd auxiliary mathods to
 *  - find the minimum of tree
 *  - rotate (single and double, in both directions
 *  - balance am AVL  tree
 */

/*
 * Print methods, do not change
 */
void print(AvlNode *root, int level, int type) {
  if (root == NULL) {
    	printf("can't print\n");
	return;
  }
  if (type == IS_ROOT) {
    std::cout << root -> element << "\n";
  } else {
    for (int i = 1; i < level; i++) {
      std::cout << "| ";
    }
    if (type == IS_LEFT) {
      std::cout << "|l_" << root -> element << "\n";
    } else {
      std::cout << "|r_" << root -> element << "\n";
    }
  }
  if (root -> left != NULL) {
    print(root -> left, level + 1, IS_LEFT);
  }
  if (root -> right != NULL) {
    print(root -> right, level + 1, IS_RIGHT);
  }
}
void print(AvlNode *root) {
  print(root, 0, IS_ROOT);
}
/*
 * END Print methods, do not change
 */


/*
 * Main method, do not change
 */
int main(int argc, const char * argv[]) {
  AvlNode *root = NULL;
  std::string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);
  std::string input;
  int data;
  while(std::cin >> input){
    if (input == "insert"){
      std::cin>>data;
      root = insert(data, root);
    } else if(input == "delete"){
      std::cin>>data;
      root = remove(data, root);
    } else if(input == "print"){
      print(root);
      std::cout << "\n";
    } else{
      std::cout<<"Data not consistent in file";
      break;
    }
  }
  return 0;
}
/*
 * END main method
 */

