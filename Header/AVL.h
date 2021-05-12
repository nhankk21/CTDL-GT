#include<string>
#include<string.h>
#include<fstream>
#include<stdlib>

using namespace std;

struct Material {
	
};

struct materialNode {
	Material data;
	materialNode* left;
	materialNode* right;
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
	return getNodeHeight(node->left) - getNodeHeight(node->right);
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
	materialNode* nextRoot = root->right;
	root->right = nextRoot->left;
	nextRoot->left = root;
	
	// Cap nhat lai do cao
	root->height = max(getNodeHeight(root->left), getNodeHeight(root->right)) + 1;
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
		if (root->left == NULL || root->right == NULL) {
			materialNode *tmp = root->left ? root->left : root->right;
			// Neu la node la (khong co con) 
			if (tmp == NULL) {
				tmp = root;
				root = NULL;
			}
			else {
				*root = *tmp;
				delete(tmp);
			}
		}
		// Node 2 con
		else {
			// Lay succesor node (la node nho nhat cua cay ben phai hoac node lon nhat cua cay ben trai)
			materialNode *tmp = getMinNode(root->right);
			// Copy data cua succesor node (node the mang) cho node can xoa
			root->data = tmp->data;
			// Xoa succesor node
			root->right = deleteNode(root->right, tmp->data);
		}
		
	}
	// Sau khi xoa, neu cay chi co 1 node thi return
	if (root == NULL) return root;
	
	// Cap nhat lai do cao cua node hien tai
	root->height = max(getNodeHeight(root->left), getNodeHeight(root->right)) + 1;
	
	// Can bang lai cay
	int balance = getNodeBalanceFactor(root);
	// Co 4 truong hop can bang cay
	// L - L
	if (balance > 1 && getNodeBalanceFactor(root->left) >= 0) return rightRotate(root);
	// L - R
	if (balance > 1 && getNodeBalanceFactor(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	// R - R
	if (balance < -1 && getNodeBalanceFactor(root->right) <= 0) return leftRotate(root);
	// R - L
	if (balance < -1 && getNodeBalanceFactor(root->right > 0)) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
}


