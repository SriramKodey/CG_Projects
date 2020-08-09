#include<vector>
#include<array>
using namespace std; 
#define MINSEP 60
/* A binary tree node has data, pointer to left 
child and a pointer to right child */
struct Node;
struct extreme
{
	Node* addr;
	int off;
	int level;
};
struct Node 
{ 
	int val; 
	Node *llink, *rlink; 
	int x,y;
	int offset;
	bool thread;

		/* Helper function that allocates a new node */
	Node(int val) 
	{ 
		//Node* node = (Node*)malloc(sizeof(Node)); 
		this->val = val; 
		this->llink = this->rlink = NULL; 
		this->x=this->y=0;
		this->thread=false;  
	} 

	void func(int level,extreme &rmost,extreme &lmost)
	{
		cout<<"in func"<<this->val<<endl;

		
		this->y=level;
		Node* L=this->llink;
		Node* R=this->rlink;
		int CURsep, ROOTsep, LOffsum, ROffsum;
		extreme LL,LR,RL,RR;
		// cout<<LR.level<<LL.level<<this->val<<"\n";
		// 	cout<<RR.level<<RL.level<<this->val<<"\n";
		if(L != NULL){
			// LL.level=-1;
			RL.level=-1;
			// LR.level=-1;
			RR.level=-1;
			rmost.level=-1;
			lmost.level=-1;
			L->func(level+1,LR,LL);

		}
		cout<<LR.level<<LL.level<<this->val<<"\n";
		if(R != NULL){
			LL.level=-1;
			// RL.level=-1;
			LR.level=-1;
			// RR.level=-1;
			rmost.level=-1;
			lmost.level=-1;
			R->func(level+1,RR,RL);
		}
cout<<RR.level<<RL.level<<this->val<<"\n";
		if(L==NULL && R==NULL)
		{
			cout<<endl;
			 // cout<<LR.level<<" "<<LL.level<<this->val<<"\n";
			 // cout<<RR.level<<" "<<RL.level<<this->val<<"\n";
			LL.level=-1;
			RL.level=-1;
			LR.level=-1;
			RR.level=-1;
			// cout<<LR.level<<" "<<LL.level<<this->val<<"\n";
			//  cout<<RR.level<<" "<<RL.level<<this->val<<"\n";
			rmost.addr=lmost.addr=this;
			rmost.level=lmost.level=level;
			rmost.off=lmost.off=0;
			this->offset=0;
		}
		else
		{

			CURsep = MINSEP;
			ROOTsep = MINSEP;
			LOffsum = 0;
			ROffsum = 0;
			/*Now consider each level  in turn until one subtree is exhausted
			pushing the subtrees apart when neccessary.*/
			// cout<<LR.level<<LL.level<<this->val<<"\n";
			// cout<<RR.level<<RL.level<<this->val<<"\n";
			while (L != NULL && R != NULL) {
				if (CURsep < MINSEP) {
					ROOTsep = ROOTsep + (MINSEP - CURsep);
					CURsep = MINSEP;
				}
				//Advance left 
				if (L->rlink != NULL) {
					LOffsum = LOffsum + L->offset;
					CURsep = CURsep - L->offset;
					L = L->rlink;
				}
				else {
					LOffsum = LOffsum - L->offset;
					CURsep = CURsep + L->offset;
					L = L->llink;
				}				//Advance right
				if (R->llink != NULL) {
					ROffsum = ROffsum - R->offset;
					CURsep = CURsep - R->offset;
					R =R->llink;
				}
				else {
					ROffsum = ROffsum + R->offset;
					CURsep = CURsep + R->offset;
					R= R->rlink;
				}
			}
			/*Set the offset in node root and include it in accumulated offsets in right and left*/
			this->offset = (ROOTsep + 1) / 2;
			LOffsum = LOffsum - this->offset;
			ROffsum = ROffsum + this->offset;
			/*Update extreme descendents information*/
			cout<<LR.level<<LL.level<<this->val<<"\n";
			 cout<<RR.level<<RL.level<<this->val<<"\n";
			if (RL.level > LL.level || this->llink == NULL) {
				lmost = RL;
				lmost.off = lmost.off + this->offset;
			}
			else {
				lmost = LL;
				lmost.off = lmost.off - this->offset;
			}
			if (LR.level > RR.level ||this->rlink == NULL) {
				rmost = LR;
				rmost.off = rmost.off - this->offset;
			}
			else {
				rmost = RR;
				rmost.off = rmost.off + this->offset;
			}
			/*If subtrees of root were of uneven heights,check to see if threadng is necessary
			At most one thread needs to be inserted*/
			if (L != NULL && L != this->llink) {
				(RR.addr)->thread = true;
				(RR.addr)->offset = abs((RR.off + this->offset) - LOffsum);
				if ((LOffsum - this->offset) <= RR.off) {
					(RR.addr)->llink = L;
				}
				else {
					(RR.addr)->rlink = L;
				}
			}
			else if (R != NULL && R != this->rlink) {
				(LL.addr)->thread = true;
				(LL.addr)->offset = abs((LL.off - this->offset) - ROffsum);
				if ((ROffsum + this->offset) >= LL.off) {
					(LL.addr)->rlink = R;
				}
				else {
					(LL.addr)->llink = R;
				}
			}
		}

	}

/*!This procedures forms the pre-order traversal of the tree
converting the relative coordinates to absolute coordinates*/
void petrify(int col) {
	/*This procedures forms the pre-order traversal of the tree
	converting the relative coordinates to absolute coordinates*/

		this->x = col;
		if (this->thread==true) 
		{
			this->thread = false;
			this->llink = NULL;
			this->rlink = NULL;
		}
		Node* L=this->llink;
		Node* R=this->rlink;
		if(L != NULL)
			L->petrify( col - this->offset);
		if(R !=NULL)
			R->petrify( col + this->offset);
	}
}; 

int a=0;

struct graph
{
	 int graph_size;
	 vector<int> pre;
	 Node* root=NULL;
	 
	Node* constructTreeUtil(  int* preIndex, int key,int min, int max ) 
	{ 
		cout << pre.size() << endl;
		// Base case 
		if( *preIndex >= graph_size ) 
			return NULL; 

		Node* temp=NULL;

		// If current element of pre[] is in range, then only it is part of current subtree 
		if( key > min && key < max ) 
		{ 
			// Allocate memory for root of this subtree and increment *preIndex 
			temp = new Node(key); 
			*preIndex = *preIndex + 1; 
			a++;cout<<"in function"<<a<<endl;
			if (*preIndex < graph_size) 
			{
				pre.resize(5);
				cout << *preIndex << endl;
				// Construct the subtree under root All nodes which are in range {min .. key} will go in left subtree, and first such node will be root of left subtree. 
				temp->llink=constructTreeUtil(  preIndex, pre[*preIndex],min, key); 
				// All nodes which are in range {key..max} will go in right subtree, and first such node will be root of right subtree. 
				temp->rlink=constructTreeUtil(  preIndex, pre[*preIndex],key, max); 
			} 
		} 

		return temp; 
	} 

	// The main function to construct BST 
	// from given preorder traversal. 
	Node *constructTree() 
	{ 
		int preIndex = 0; 
		return constructTreeUtil ( &preIndex, pre[0], INT_MIN, INT_MAX ); 
	} 


	graph(int n,vector<int> pres)
	{
		this->graph_size=n;
		this->pre=pres;
		for(int i=0;i<n;i++)
			this->pre[i]=pres[i];
		this->root=constructTree();
		//printInorder(this->root);
		// extreme lmost,rmost;
		// root->func(0,lmost,rmost);
		// root->petrify(30);
	}
	void printInorder (Node* node)  
	{  //cout<<"hi  ";
	    if (node == NULL)  
	        return; 
	    cout<<node->val<<" "; 
	    printInorder(node->llink);  
	    // cout<<node->val<<" ";  
	    printInorder(node->rlink);  
	} 


};


