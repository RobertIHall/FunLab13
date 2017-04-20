#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
  //DO THIS

	if(left->isEmpty()) //If left is empty return right.
	{
		return right;
	}
	else if (right->isEmpty()) //If right is empty return left.
	{
		return left;
	}
	else
	{
		T* itemLeft = left->getRootItem(); // get the items from the roots of both parameters.
		T* itemRight = right->getRootItem();
		
		int comp = (*compare_items) (itemLeft, itemRight);
		if (comp < 0) //If left is less than right, swap merge parameters.
		{
			merge(right, left);
		}
		else
		{
			BinaryTree<T>* LeftLeftSubtree = left->detachLeftSubtree(); //Left's left subtree.
			BinaryTree<T>* LeftRightSubtree = left->detachRightSubtree(); //Left's right subtree.
			left->attachRightSubtree(LeftLeftSubtree); //Attach LLS to left's right.
			if (LeftRightSubtree->isEmpty()) //If LR is empty, attach right to left's left side.
			{
				left->attachLeftSubtree(right);
				return left;
			}
			else //if LR is not empty..
			{
				left->attachLeftSubtree(merge(LeftRightSubtree, right)); //Attach the merge to the left's left side.
				return left; //return left.
			}
		}
	}
}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
	BinaryTree<T>* newTree = new BinaryTree<T>(item); //Create a new binary tree with the parameter item as the root.
	bt = merge(bt, newTree); //Merge the two trees now.
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
	T* item = bt->getRootItem();
	
    BinaryTree<T>* leftSubtree = bt->detachLeftSubtree(); //Get left subtree and right subtree.
	BinaryTree<T>* rightSubtree = bt->detachRightSubtree();
	
	delete bt; //Delete old one.
	
	merge(leftSubtree, rightSubtree); //Merge the two.
	
	sze--; //Decrease size and return item.

	return item;
}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
