/**
 * Represents a binary tree
 *
 * @file mainBinTree.c
 * @author Stephanie Scholl
 * @note Matrikelnummer: 979993
 * @note Hochschule RheinMain
 *
 * @note Fach: Programmiermethoden- und Techniken
 * @note 2. Semester
 * @note Projektarbeit
 *
 * @note Professor: Sven Eric Panitz
 * @note Praktikumsleiter: Christian Lassmann
 */

#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"
#include "ArrayList.h"
#include "Reimwoerterbuch.h"

/**
 * Checks if a given tree is empty
 *
 * @param this tree* - tree which is going to be checked
 *
 * @return Boolean TRUE if tree is empty, else FALSE
 */
bool isEmpty(Tree* this) {
	return this->head == NULL && this->left == NULL && this->right == NULL;
}

/**
 * Creates a new empty tree
 *
 * @param kleinerGleich le Functionpointer to function which checks if an element is smaller oder bigger/equal to another
 *
 * @return new leaf tree without a leaf
 */
Tree* newEmptyTree(le kleinerGleich) {
	return newLeafTree(kleinerGleich, NULL);
}

/**
 * Creates a new tree with a root element
 *
 * @param kleinerGleich le - Functionpointer to function which checks if an element is smaller oder bigger/equal to another
 * @param elem void* - element which is the new root
 *
 * @return new leaf tree with a leaf
 */
Tree* newLeafTree(le kleinerGleich, void* elem) {
	Tree* newTree = malloc(sizeof(Tree));
	newTree->head = elem;
	newTree->left = NULL;
	newTree->right = NULL;
	newTree->kleinerGleich = kleinerGleich;
	return newTree;
}

/**
 * Function for deleting every node of the tree, but not the elements
 *
 * @param this tree* - tree which is going to be deleted
 */
void deleteTree(Tree* this) {
	if (this != NULL) {
		deleteTree(this->left);
		deleteTree(this->right);
		/*you allocated space, so you need to free it now*/
		free(this);
	}
}

/**
 * Function for calculating the size of a tree
 *
 * @param this tree* - tree where the nodes are going to be counted
 *
 * @return size of tree as unsigned int
 */
/*unsigned int*/nat length(Tree* this) {
	if (this->head == NULL) {
		return 0;
	} else if (this->left == NULL && this->right == NULL) {
		return 1;
	} else {
		return length(this->left) + length(this->right) + 1;
	}
}

/**
 * Function for adding an element to a given tree
 *
 * @param this tree* - tree where the element is going to be added
 * @param el void* - Object which is going to be added
 */
void add(Tree* this, void* el) {
	/*if this is empty, put root*/
	if (isEmpty(this)) {
		this->head = el;
	} else {
		/*left tree*/
		if (this->kleinerGleich(el, this->head)) {
			if (this->kleinerGleich(this->head, el)) {
				return;
			} else {
				if (this->left != NULL) {
					add(this->left, el);
				} else {
					this->left = newLeafTree(this->kleinerGleich, el);
				}
			}
			/*right tree*/
		} else {
			if (this->kleinerGleich(this->head, el)) {
				if (this->right != NULL) {
					add(this->right, el);
				} else {
					this->right = newLeafTree(this->kleinerGleich, el);
				}
			}
		}
	}
}

/**
 * Copies tree but not the elements
 *
 * @param this tree* - tree which is going to be copied
 *
 * @return copied tree
 */
Tree* copyTree(Tree* this) {
	if (this == NULL) {
		return NULL;
	}
	Tree* l = copyTree(this->left);
	Tree* r = copyTree(this->right);
	Tree* n = newLeafTree(this->kleinerGleich, this->head);
	n->left = l;
	n->right = r;
	return n;
}

/* enthält der Baum ein bestimmtes Element. Hierzu wird die Ordnungsrelation des Baumes genommen.
 x==y bedeutet: kleinerGleich(x,y) && kleinerGleich(y,x).
 */

/**
 * Function for checking if there's a particular object in the tree
 *
 * @param this tree* - tree which is going to be checked
 * @param elem void* - object to search for
 *
 * @return TRUE if the object is in the tree, else FALSE
 */
bool contains(Tree* this, void* elem) {

	if (this != NULL) {
		if ((this->kleinerGleich(this->head, elem))
				&& (this->kleinerGleich(elem, this->head))) {
			return true;
		}

		return contains(this->right, elem) || contains(this->left, elem);
	}
	return false;
}

/**
 * Function for applying a consumer to every single element inorder of the tree
 *
 * @param this tree* - tree to go through
 * @param consumer void - Function which is going to be applied
 */
void macheFuerAlle(Tree* this, void consumer(void*)) {
	if (isEmpty(this)) {
		return;
	}
	if (this != NULL) {
		macheFuerAlle(this->left, consumer);
		macheFuerAlle(this->right, consumer);
		consumer(this->head);
	}
}

/**
 * Function for applying a consumer to every single element postorder of the tree
 *
 * @param this tree* - tree to go through
 * @param list ArrayList* - list
 * @param consumer void - Function which is going to be applied
 */
void macheFuerAllePost(Tree* this, ArrayList* list, void consumer(void*, void*)) {
	if (this != NULL) {
		macheFuerAllePost(this->left, list, consumer);
		consumer(list, this->head);
		macheFuerAllePost(this->right, list, consumer);
	}
}

/**
 * Function for applying a consumer to every single element preorder of the tree
 *
 * @param this tree* - tree to go through
 * @param consumer void - Function which is going to be applied
 *
 */
void macheFuerAllePre(Tree* this, void consumer(void*)) {
	if (this != NULL) {
		consumer(this->head);
		macheFuerAllePre(this->left, consumer);
		macheFuerAllePre(this->right, consumer);
	}
}

/**
 * Function for testing if a object is smaller/equal as another
 *
 * @param w1 void* - first object
 * @param w2 void* - second object
 *
 * @return 1 if the first element is smaller or equals the other, else 0
 */
bool klGlChar(void* w1, void* w2) {
	int i = 0;
	while (stringCharAt(w1, i) == stringCharAt(w2, i) && i < stringLength(w1)
			&& i < stringLength(w2)) {
		i++;
	}
	if (stringCharAt(w1, i) <= stringCharAt(w2, i)) {
		return 1;
	}
	return 0;

}
