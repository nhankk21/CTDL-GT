#include<string>
#include<string.h>
#include<fstream>
#include<stdlib>

using namespace std;

struct Material {
	
};

struct materialNode {
	Material data;
	Tree* left;
	Tree* right;
	int height;
};

void createMaterialList(materialNode* &root) {
	root = NULL;
}

int getNodeHeight(materialNode* node) {
	if (node == NULL) return 0;
	return node->height;
}

materialNode* createNode(const Material &data) {
	materialNode* node = new materialNode;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}
int getNodeBalanceFactor(materialNode* node) {
	if (node == NULL) return 0;
	return getNodeHeight(materialNode->left) - getNodeHeight(materialNode->right);
}

// Cay bi lech trai -> xoay ve ben phai
materialNode* rightRotate(materialNode* root) {
	// Xoay
	materialNode* nextRoot = root->left;
	root->left = nextRoot->right;
	nextRoot->right = root;
	
	// Cap nhat lai do cao
	root->height = max(getNodeHeight(root->left), getNodeHeight(root->right)) + 1;
	nextRoot->height = max(getNodeHeight(nextRoot->left), getNodeHeight(nextRoot->right)) + 1;
	return nextRoot;
}

materialNode* leftRotate(materialNode* root) {
	// Xoay
	materialNode* nextRoot = root-data>right;
	root->right = nextRoot->left;
	nextRoot->left = root;
	
	// Cap nhat lai do cao
	root->height = max(getNodeHeight(root->next), getNodeHeight(root->right)) + 1;
	nextRoot->height = max(getNodeHeight(nextRoot->left), getNodeHeight(nextRoot->right)) + 1;
	return nextRoot;
}

// Node nho nhat luon nam o phia ben trai cay
materialNode* getMinNode(materialNode* root) {
	materialNode* cur = root;
	while (cur->left != NULL) cur = cur->left;
	return cur; 
}

materialNode* insertNode(materialNode* &root, Material &data) {
	if (root == NULL) {
		root = createNode(data);
		return root;
	}
	if (data < root->data) root->left = insertNode(root->left, data); // Data can them nho hon root->data thi them vao ben trai
	else if( data > root->data) root->right = insertNode(root->right, data);// // Data can them lon hon root->data thi them vao ben phai
	else return root; 
	
	// Cap nhat lai chieu cao cua root
	root->height = max(getNodeHeight(root->left), getNodeHeight(root->right)) + 1;
	
	// Kiem tra cay co mat can bang hay khong
	int balance = getNodeBalanceFactor(root);
	
	// Co 4 truong hop cay bi mat can bang:
	
	// Truong hop L - L
	if (balance > 1 && data < root->left->data) return rightRotate(root);
	
	// Truong hop R - R
	if (balance < -1 && data > root->right->data) return leftRotate(root);
	
	// Truong hop L - R
	if (balance > 1 && data > root->left->data) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	
	// Truong hop R - L
	if (balance < -1 && data < root->right->data) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	} 
	return root;
}

materialNode* deleteNode(materialNode * &root, Material &data) {
	
}


