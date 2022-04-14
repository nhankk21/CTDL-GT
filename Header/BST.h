#include<string>
#include<string.h>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct Material {
	string codeMaterial;
	string nameMaterial;
	string unitMaterial;
	float quantity;
	Material(){};
	Material(string code, string name, string unit, float quantity) {
		this->codeMaterial = code;
		this->nameMaterial = name;
		this->unitMaterial = unit;
		this->quantity = quantity;
	}
	void operator = (const Material &material) {
		this->codeMaterial = material.codeMaterial;
		this->nameMaterial = material.nameMaterial;
		this->unitMaterial = material.unitMaterial;
		this->quantity = material.quantity;
	}
	bool operator > (const Material &material) {
		return this->codeMaterial > material.codeMaterial;
	}
	bool operator < (const Material &material) {
		return this->codeMaterial < material.codeMaterial;
	}
};

struct materialNode {
	Material data;
	materialNode* left;
	materialNode* right;
};

void createMaterialList(materialNode* &root) {
	root = NULL;
}


materialNode* createNode(const Material &data) {
	materialNode* node = new materialNode;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// Node nho nhat luon nam o phia ben trai cay
materialNode* getMinNode(materialNode* root) {
	materialNode* cur = root;
	while (cur && cur->left != NULL) cur = cur->left;
	return cur; 
}

struct Node
{
	string code;
	float total;
	Material *data;
	
	struct Node *pLeft;
	struct Node *pRight;
};

typedef struct Node NODE;
typedef NODE* TREE;
void khoitao(TREE &t) {

	t=NULL;
}
void themNODE(TREE &t,string x,float total,Material* data) {
	if(t==NULL)
	{
		NODE *p=new NODE;
		p->code=x;
		p->total=total;
		p->pLeft=NULL;
		p->pRight=NULL;
		p->data=data;
		t=p;
	}
	else
	{
		if(t->code>x)
			themNODE(t->pLeft,x,total,data);
		else if(t->code<x)
			themNODE(t->pRight,x,total,data);
		else
		{
			t->total+=total;
		}
	}
}



materialNode* insertNode(materialNode* &root, Material &data) {
	if (root == NULL) {
		return createNode(data);
		//return root;
	}
	if (data < root->data) root->left = insertNode(root->left, data); // Data can them nho hon root->data thi them vao ben trai
	else root->right = insertNode(root->right, data);// // Data can them lon hon root->data thi them vao ben phai
	return root; 
}

materialNode* deleteNode(materialNode* &root, Material &data) {
	if (root == NULL) return root;
	
	// Neu data < root->data de quy sang trai
	if (data < root->data) {
		root->left = deleteNode(root->left, data);
	}
	// Neu data > root->data de quy sang phai
	else if (data > root->data) {
		root->right = deleteNode(root->right, data);
	}
	// Neu bang
	else {
		// Neu la node la hoac node 1 con
		if (root->left == NULL) {
			materialNode* tmp = root->right;
			delete root;
			return tmp;	
		}
		else if (root->right == NULL) {
			materialNode* tmp = root->left;
			delete root;
			return tmp;	
		}
		
		// Node 2 con
		struct materialNode* tmp = getMinNode(root->right);
		
		root->data = tmp->data;
		root->right = deleteNode(root->right, tmp->data);
	}
	return root;		
			
}

materialNode* searchNode(materialNode* root, const string key) {
	materialNode* re = NULL;
	while (root != NULL) {
		if (key < root->data.codeMaterial) root = root->left;
		else if (key > root->data.codeMaterial) root = root->right;
		else {
			re = root;
			break;
		}
	}
	return re;
}



bool cmpT(Node* a, Node* b) {
	if (a->total > b->total) return true;
	return false;
}

void quickSortTotal(Node* parr[], int l , int r, bool(compare)(Node*, Node*)) {	
	if (l <= r) {
		Node* key = parr[(l+r)/2];
		
		int i = l;
		int j = r;
		while (i <= j) {
			while (compare(parr[i], key))
				i++;
			while (compare(key, parr[j]))
				j--;
 
			if (i <= j) {
				swap(parr[i], parr[j]);
				i++;
				j--;
			}
		}
 
	
		if (l < j)
			quickSortTotal(parr, l, j, cmpT);
		if (r > i)
			quickSortTotal(parr, i, r, cmpT);
	}
}

bool cmpM(materialNode* a, materialNode* b){
	if(a->data.nameMaterial < b->data.nameMaterial){
		return true;
	} else{
		return false;
	}
}

void quickSortMaterial(materialNode* parr[], int l , int r, bool(*compare)(materialNode*, materialNode*)) {	
	if (l <= r) {
		materialNode* key = parr[(l+r)/2];
		
		int i = l;
		int j = r;
		while (i <= j) {
			while (compare(parr[i], key))
				i++;
			while (compare(key, parr[j]))
				j--;
 
			if (i <= j) {
				swap(parr[i], parr[j]);
				i++;
				j--;
			}
		}
 
	
		if (l < j)
			quickSortMaterial(parr, l, j, cmpM);
		if (r > i)
			quickSortMaterial(parr, i, r, cmpM);
	}
}
