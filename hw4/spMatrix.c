#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 50

//data type declaration
typedef enum {head,entry} tagfield;
typedef struct matrixNode *matrixPtr;
typedef struct entryNode{
		int row;
		int col;
		int value;
} ;
typedef struct matrixNode{
		matrixPtr down;
		matrixPtr right;
		tagfield tag;
		union {
			matrixPtr next;
			entryNode entry;
		} u;
} ;
matrixPtr  hdnode[MAX_SIZE];
//function prototype
matrixPtr mread();
matrixPtr mread(matrixPtr,int,int,int);
matrixPtr newNode(int,int,int);
void mwrite_(matrixPtr);
void mwrite(matrixPtr);
matrixPtr mmult(matrixPtr , matrixPtr);
void insert(int,int,int);
matrixPtr mtranspose(matrixPtr);
int main(void){
		matrixPtr a,b,c,d,t;
	printf("(input first matrix)\n");
	a = mread();
	printf("(input second matrix)\n");
	b = mread();
	
	c = mtranspose(b);
	c = mread(c,b->u.entry.col,b->u.entry.row,b->u.entry.value);
	d = mmult(a,c);
	printf("b transpose:\n");
	printf("numRows = %d,numCols = %d\n",c->u.entry.row,c->u.entry.col);
	printf("The matrix by row, column and value:\n");
	mwrite(c);
	printf("a * b transpose:\n");
	printf("numRows = %d,numCols = %d\n",d->u.entry.row,d->u.entry.col);
	printf("The matrix by row, column and value:\n");
	mwrite(d);	
	return 0;


}

matrixPtr newNode(int row,int col ,int value){
	matrixPtr temp;
	temp = (matrixNode*)malloc(sizeof(matrixNode));
	temp->right = temp;
	temp->down = temp;
	if(row == -1){
		temp->tag = head;
		temp->u.next = temp;
		return temp;
	}else{
		temp->tag = entry;
		temp->u.entry.row = row;
		temp->u.entry.col = col;
		temp->u.entry.value = value;
		return temp;
	}
}

void insert(int row,int col,int value){
	matrixPtr temp,cur,pre;
			temp = newNode(row,col,value);
			if(hdnode[row]->right != hdnode[row]){
				cur = hdnode[row]->right;
				pre = hdnode[row];
				while(temp->u.entry.col > cur->u.entry.col && cur != hdnode[row]){
					pre = cur; cur = cur->right;
				}
				temp->right = cur;
				pre->right = temp;
			}else{
				hdnode[row]->right = temp;
				temp->right = hdnode[row];
			}

			if(hdnode[col]->down != hdnode[col]){
				cur = hdnode[col]->down;
				pre = hdnode[col];
				while(temp->u.entry.row > cur->u.entry.row && cur != hdnode[col]){
					pre = cur; cur = cur -> down;
				}
				temp -> down = cur;
				pre -> down = temp;
			}else{
				hdnode[col] -> down = temp;
				temp->down = hdnode[col];
			}	
}
	

matrixPtr mread(){
	int numRows,numCols, numTerms, numHeads,i;
	int row,col,value,currentRow;
	matrixPtr temp,last,node,cur,pre;
	//printf("Enter the number of rows, columns and number of nonzero terms:\n");
	scanf("%d %d %d",&numRows,&numCols,&numTerms);
	numHeads = (numRows > numCols)? numRows:numCols;
	
	node = newNode(numRows,numCols,numTerms); 
	if(!numHeads) node->right = node;
	else{
		for(i=0;i<numHeads;i++){
			temp = newNode(-1,0,0);
			hdnode[i] = temp;
		}
		for(i=0;i<numTerms;i++){
			//printf("Enter row, column and value:\n");
			scanf("%d %d %d",&row,&col,&value);
			temp = newNode(row,col,value);
			if(hdnode[row]->right != hdnode[row]){
				cur = hdnode[row]->right;
				pre = hdnode[row];
				while(temp->u.entry.col > cur->u.entry.col && cur != hdnode[row]){
					pre = cur; cur = cur->right;
				}
				temp->right = cur;
				pre->right = temp;
			}else{
				hdnode[row]->right = temp;
				temp->right = hdnode[row];
			}

			if(hdnode[col]->down != hdnode[col]){
				cur = hdnode[col]->down;
				pre = hdnode[col];
				while(temp->u.entry.row > cur->u.entry.row && cur != hdnode[col]){
					pre = cur; cur = cur -> down;
				}
				temp -> down = cur;
				pre -> down = temp;
			}else{
				hdnode[col] -> down = temp;
				temp->down = hdnode[col];
			}	
		}
	}
	for(i=0;i<numHeads;i++ )
		hdnode[i]->u.next = hdnode[i+1];
	hdnode[numHeads - 1]->u.next = node;
	node->right = hdnode[0];

	return node;
}
void mwrite(matrixPtr node){
	matrixPtr row,col;
	for(row = node->right;row != node;row = row->u.next){
		for(col = row -> right;col != row;col = col -> right){
			printf("%2d %2d %2d\n",col->u.entry.row,col->u.entry.col,col->u.entry.value);
		}
	}
}
void mwrite_(matrixPtr node){
	int i,j,zero =0;
	matrixPtr row,col;
	for(row = node->right; row != node; row = row->u.next){
		for(col = row -> right,i=0; col != row;col = col -> right){	
			for(j=i;j<col->u.entry.col;j++)
				printf("%3d",zero);
			printf("%3d",col->u.entry.value);
			i = j+1;
		}
		for(j=i;j<node->u.entry.col;j++)
			printf("%3d",zero);
		printf("\n");
	}
	printf("\n");
}
//mread overloading
matrixPtr mread(matrixPtr arr,int numRows,int numCols,int numTerms){
	int numHeads,i;
	int row,col,value;
	matrixPtr node,last,temp;
	numHeads = (numRows > numCols)? numRows:numCols;

	node = newNode(numRows,numCols,numTerms); 
	if(!numHeads) node->right = node;
	else{
		for(i=0;i<numHeads;i++){
			temp = newNode(-1,0,0);
			hdnode[i] = temp;
		}

		for(i = 0; i < numTerms ;arr = arr->right,i++){
			row = arr->u.entry.row;
			col = arr->u.entry.col;
			value = arr->u.entry.value;
			insert(row,col,value);	
		}	
			
	}
	for(i=0;i<numHeads;i++ )
		hdnode[i]->u.next = hdnode[i+1];
	hdnode[numHeads - 1]->u.next = node;
	node->right = hdnode[0];
	
	return node;
}
matrixPtr mmult(matrixPtr a,matrixPtr b){
	int i,j,sum = 0;;
	matrixPtr plus,superPlus,temp,newMatrix;
	int num=0;
	
	for(plus = a->right,i=0; plus != a ;plus = plus->u.next,i++){
		for(superPlus = b->right,j=0;superPlus != b;superPlus = superPlus->u.next,j++){
			sum = 0;
			plus = plus->right;
			superPlus = superPlus -> down;
			while(plus->tag != 0 && superPlus->tag != 0 ){
				while(plus->u.entry.col > superPlus->u.entry.row && superPlus->tag != 0){
					superPlus = superPlus->down;
				}
				while(plus->u.entry.col < superPlus->u.entry.row && plus->tag != 0){
					plus = plus->right;
				}
				if(superPlus->u.entry.row == plus->u.entry.col && plus->tag != 0 && superPlus->tag != 0){
					sum+= (superPlus->u.entry.value)*(plus->u.entry.value);
				}
				if(plus->tag != 0 && superPlus ->tag!= 0){
					plus = plus->right;
					superPlus = superPlus->down;
				}
			}
			while(plus->tag != 0){
				plus = plus->right;
			}
			while(superPlus->tag != 0){
				superPlus = superPlus->down;
			}
			
			if(sum != 0){
				num++;
				temp = newNode(i,j,sum);
				if(newMatrix == 0){
					newMatrix = temp;
				}
				else{
					temp->right = newMatrix;
					newMatrix = temp;
				}
		    }
		}
	}	
	return mread(newMatrix,a->u.entry.row,b->u.entry.col,num);
}
	
matrixPtr mtranspose(matrixPtr node){
	int i,j,zero =0;
	matrixPtr row,col,newMatrix,temp;
	for(row = node->right; row != node; row = row->u.next){
		for(col = row -> right,i=0;col != row;col = col -> right){	
			temp = newNode(col->u.entry.col,col->u.entry.row,col->u.entry.value);
			temp->right = newMatrix;
			newMatrix = temp;
		}
	}
	return newMatrix;
}
