#include<iostream>
#include<random>

using namespace std;

struct Node {
	int val;
	int height;
	Node* left;
	Node* right;
	Node* up;
	Node(int key) {
		val = key;
		height = 1;
		left = right = up = nullptr;
	}
};

int height_func(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	else {
		return root->height;
	}
}

int get_balance(Node* root) {

	if (root == nullptr) {
		return 0;
	}
	int balance = height_func(root->left) - height_func(root->right);
	cout << "balance dla: " << root->val <<  " to: " << balance << endl;
	return balance;
}



Node* rotacja_w_lewo(Node* root) {
	if (root == nullptr || root->right == nullptr) {
		return root;  // jak nie ma prawego dziecka, rotacja w lewo nie jest mo¿liwa
	}
	Node* new_root = root->right;
	root->right = new_root->left;

	if (new_root->left != nullptr) {
		new_root->left->up = root;
	}

	new_root->left = root;  
	new_root->up = root->up; 

	root->up = new_root;

	return new_root;  
}

Node* rotacja_w_prawo(Node* root) {
	if (root == nullptr || root->left == nullptr) {
		return root;
	}
	Node* root_temp = root->left;
	root->left = root_temp->right;;

	if (root_temp->right != nullptr) {
		root_temp->right->up = root;
	}

	root_temp->right = root;  
	root_temp->up = root->up; 

	root->up = root_temp;

	return root_temp;
}


Node* insert_num(Node* root, int val, Node* parent = nullptr) {
	if (root == nullptr) {
		Node* newNode = new Node(val);
		newNode->up = parent;
		return newNode;
	}

	if (root->val <= val) {
		cout << "PRZECHODZE root->right: " << root->val << endl;
		root->right = insert_num(root->right, val, root);
	}
	else {
		cout << "PRZECHODZE root->left: " << root->val << endl;
		root->left = insert_num(root->left, val, root);
	}
	cout << "PRZECHODZE root->height: " << root->val << endl;
	root->height = 1 + max(height_func(root->left), height_func(root->right));
	cout << "HEIGHT DLA: " << root->val << " TO: " << root->height << endl;

	int balance = get_balance(root);

	if (balance > 1 && val < root->left->val)
		return rotacja_w_prawo(root);

	if (balance < -1 && val > root->right->val)
		return rotacja_w_lewo(root);

	if (balance > 1 && val > root->left->val) {
		root->left = rotacja_w_lewo(root->left);
		return rotacja_w_prawo(root);
	}

	if (balance < -1 && val < root->right->val) {
		root->right = rotacja_w_prawo(root->right);
		return rotacja_w_lewo(root);
	}

	return root;

}

Node* find_num(Node* root, int val) {
	if (root == nullptr || root->val == val) {
		return root;
	}
	if (root->val <= val) {
		cout << root->val << " ";
		return find_num(root->right, val);
	}
	else {
		cout << root->val << " ";
		return find_num(root->left, val);
	}
}

void preorder_print(Node* root) {
	if (root == nullptr) {
		return;
	}
	cout << root->val << " ";
	preorder_print(root->left);
	preorder_print(root->right);
}



int main() {
	int poczatek = 20;
	Node* root = new Node(poczatek);
	const int ROZMIAR = 10;
	int tab[ROZMIAR];
	tab[0] = poczatek;

	// Wstawianie losowych liczb do drzewa
	for (int i = 0; i < ROZMIAR - 1; i++) {
		random_device rd;   // Ÿród³o losowe
		mt19937 gen(rd());  // generator Mersenne Twister
		uniform_int_distribution<> dis(1, 50); 
		int num = dis(gen);
		cout << "\nWstawiam liczbe: " << num << endl;
		root = insert_num(root, num);
		cout << "sciezka wyszukiwania liczby: ";
		find_num(root, num);
		cout << endl;
		tab[i + 1] = num;
	}

	preorder_print(root);
}