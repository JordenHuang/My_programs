#include <stdio.h>
#include <stdlib.h>

enum move_type {up, down, left, right};
enum Bool_type {t, f};

struct node_struct
 {
  int                  state[17][17];
  int                  hole[2];
  enum move_type       move;
  int                  depth;
  int                  heuristic;
  int                  proj_cost;
  struct node_struct  *parent;
  struct node_struct  *next_in_leaf_list;
 };
 
typedef struct node_struct node_type;
typedef enum Bool_type     Boolean;

char       buf[2];
int   	   size,row=1,column=1;
unsigned int  count;
node_type *head_leaf_list;
Boolean    solved;
int        goal_state[17][17];


void goal(){
	int i, j, z=0;
	FILE *gfptr;
	if((gfptr=fopen("goal.txt","w"))==NULL){
		printf("Fail.\n");
	}
	else{
		fprintf(gfptr,"%d\n",size);
		for(i = 0; i < size; i++){
 			for(j = 0; j < size; j++){
 				if(z < (size*size)-1){
 					z=z+1;
 					goal_state[i][j] = z;
 					fprintf(gfptr,"%5d",goal_state[i][j]);
				}
				else{
					goal_state[i][j] = 0;
					fprintf(gfptr,"%5d",goal_state[i][j]);
				}
			}
			fprintf(gfptr,"\n");
    	}
    	fclose(gfptr);
	}
} 

int heuristic_first (node_type *node){
	int x, i, j, z = 0;
	
 	for(i = (row-1); i < size; i++){
 		for(j = (column-1); j < size; j++){
 			if(row<(size-1)){
 				for(x = 0;x < size;x++){
	 				if (node->state[i][j] == (size*row-x)){
			   			z = z + abs(i - ((node->state[i][j] - 1) / size)) + abs(j - ((node->state[i][j] - 1) % size));
				 	}
				}
			}
			else{
			 	for(x = 0;x < 2;x++){
	 				if (node->state[i][j] == size*(row-x)+column){
			   			z = z + abs(i - ((node->state[i][j] - 1) / size)) + abs(j - ((node->state[i][j] - 1) % size));
				 	}
				}
			}  
    	}
	 }
	 		 
 return(z);
}

int heuristic_child (node_type *node,int k,int l,int i,int j){
	int a=0,x;
	if(row<(size-1)) {
		for(x = 0;x < size;x++){
			if(i!=k && node->state[i][j] == (size*row-x)){
				a=abs(i - ((node->state[i][j] - 1) / size)) - abs(k - ((node->state[i][j] - 1) / size));
			}
			else if(node->state[i][j] == (size*row-x)){
				a=abs(j - ((node->state[i][j] - 1) % size)) - abs(l - ((node->state[i][j] - 1) % size));
			}
		}
	}
	else{
		for(x = 0;x < 2;x++){
			if(i!=k && node->state[i][j] == (size*(row-x)+column)){
				a=abs(i - ((node->state[i][j] - 1) / size)) - abs(k - ((node->state[i][j] - 1) / size));
			}
			else if(node->state[i][j] == (size*(row-x)+column)){
				a=abs(j - ((node->state[i][j] - 1) % size)) - abs(l - ((node->state[i][j] - 1) % size));
			}
		}
	}
	return(a);
}

node_type * get_start_state ()
{
 int  i, j;
 char c;
 node_type *node;
 FILE *ifptr; 
 
 printf("\n     Improved N-Puzzle Solver    \n\n");
 
 node = (node_type *) malloc(sizeof(node_type));
 do {
 	scanf("%d%c",&size,&c);
    for (i = 0; i < size; i++)
     {
      for (j = 0; j < size; j++){
      	scanf("%d%c",&(node->state[i][j]),&c);
		if (node->state[i][j] == 0)
		  {
		   node->hole[0] = i;
		   node->hole[1] = j;
		  }
	  }
      printf("\n");
     } 
    printf("\nStarting configuration is: \n");
    if((ifptr=fopen("ini.txt","w"))==NULL){
		printf("Fail.\n");
	}
	else{
		fprintf(ifptr,"%d\n",size);
		for (i = 0; i < size; i++)
     {
    	printf("     ");
    	for (j = 0; j < size; j++){
    		printf("%3d ", node->state[i][j]);
    		fprintf(ifptr,"%5d",node->state[i][j]);
		}
    	printf("\n");
    	fprintf(ifptr,"\n");
     }
     fclose(ifptr);
	}
    printf("\nIs that correct? (Y/N): ");
    gets(buf);
  } while((buf[0] != 'Y') && (buf[0] != 'y'));
 node->parent = NULL;
 node->heuristic = heuristic_first(node);
 node->depth = 0;
 node->proj_cost = node->heuristic;
 return(node);
} 


Boolean at_goal(node_type *node)
{
 int i, j;
 Boolean at_goal = f;
     if ((node->heuristic) == 0){
     	at_goal = t;		
	 }
 return(at_goal);
} 


void insert (node_type *new_node)
{
 node_type *last, *next;
 Boolean found;

 if (head_leaf_list == NULL)
  {
   head_leaf_list = new_node;
   new_node->next_in_leaf_list = NULL;
  }
 else
  {
   if (new_node->proj_cost < head_leaf_list->proj_cost)
    {
     new_node->next_in_leaf_list = head_leaf_list;
     head_leaf_list = new_node;
    }
   else
    {
     last = head_leaf_list;
     next = head_leaf_list->next_in_leaf_list;
     found = f;
     while ((next != NULL) && (found == f))
       {if (new_node->proj_cost < next->proj_cost)
	  found = t;
			else
	  		{
				last = next;
	  			next = next->next_in_leaf_list;
			  }
       }
     new_node->next_in_leaf_list = next;
     last->next_in_leaf_list = new_node;
    }
  }
} 

Boolean cut(node_type *node){
	int i=0;
	Boolean a = f;
	node_type *n=node;
	node_type *p=node->parent;
	while(i<5 && p!=NULL){
		if(n->heuristic != p->heuristic){
			break;
		}
		n=p;
		p=n->parent;
		i++;
		if(i==5){
			a=t;
		}
	}	
	return (a);
}


void expand (node_type *node, node_type **final_node)
{
 node_type *child;
 enum move_type tr1;
 int i, j, k, l, x, y, prev1, prev2,tr;
 Boolean a=f;

 if (node->parent == NULL)
   {
    prev1 = -1;
    prev2 = -1;
   }
 else
  {
   prev1 = node->parent->hole[0];
   prev2 = node->parent->hole[1];
   if(count>10000){
   	a=cut(node);
   }
  }
 i = node->hole[0];
 j = node->hole[1];
 for (tr = up; tr <= right; tr++)
   {
    switch (tr)
	   {
	    case up: k = i - 1;
		     l = j;
		     break;
	    case down: k = i + 1;
		       l = j;
		       break;
	    case left: k = i;
		       l = j - 1;
		       break;
	    case right: k = i;
			l = j + 1;
			break;
	  }
    if (((row-1) <= k) && (k < size) && ((column-1) <= l) && (l < size) &&
	  ((prev1 != k) || (prev2 != l)) && solved == f && a==f)
      {
       child = (node_type *) malloc(sizeof(node_type));
       child->parent = node;
       for (x = 0; x < size; x++)
			for (y = 0; y < size; y++)
	 	 		child->state[x][y] = node->state[x][y];
       child->hole[0] = k;
       child->hole[1] = l;
       child->state[i][j] = child->state[k][l];
       child->state[k][l] = 0;
       child->move = tr;
       child->heuristic = node->heuristic + heuristic_child(child,k,l,i,j);
       child->depth = node->depth + 1;
       child->proj_cost = child->heuristic + child->depth;
       insert(child);
       solved = at_goal(child);
       if (solved == t) *final_node = child;
      } 
   } 
}

void run(node_type *node,FILE *mfptr){
	if (node->parent != NULL)
   {
    run(node->parent,mfptr);
    switch (node->move)
     {
      case up:    fprintf(mfptr,"D\n"); break;
      case down:  fprintf(mfptr,"U\n"); break;
      case left:  fprintf(mfptr,"R\n"); break;
      case right: fprintf(mfptr,"L\n"); break;
     }
    }
} 
  
void write(node_type *node){
	FILE *mfptr;
	if((mfptr=fopen("move.txt","a"))==NULL){
		printf("Fail.\n");
	}
	else{
		run(node,mfptr);
		fclose(mfptr);
    }
}

node_type * copy(node_type *node){
	node_type *copy;
	int x,y;
	copy = (node_type *) malloc(sizeof(node_type));	
    for (x = 0; x < size; x++){
    	for (y = 0; y < size; y++){
			copy->state[x][y] = node->state[x][y];
			printf("%5d",copy->state[x][y]);
			if(node->state[x][y] == 0){
				copy->hole[0] = x;
   				copy->hole[1] = y;
			}
		}
		printf("\n");
	}	
    copy->move = node->move;
    copy->heuristic = node->heuristic;
    copy->depth = node->depth;
    copy->proj_cost = node->proj_cost;
    copy->parent = NULL;
    copy->next_in_leaf_list = NULL;
    return (copy);
}

void del(node_type *node){
	node_type *cptr;
	while(node!=NULL){
		cptr=node;
		node=node->next_in_leaf_list;
		free(cptr);
	} 
} 

void get(node_type **node,node_type *current){
	while(*node!=NULL){
		*node = (*node)->next_in_leaf_list;    
	}
	if((*node) == NULL){
		(*node)= current;
	}
}

int site(node_type *node){
	int x=size-1, i, j, z = 0;	
 	if(row<(size-1)){
 		for(j = 0; j < size; j++){
			if (node->state[row-1][j] != (size*row-x)){
		  		z = z+1;
			}
			x=x-1;
		}
  	}
	else{
		x=1;
		for(i = row-1; i < size; i++){
	 		if (node->state[i][column-1] != size*(row-x)+column){
				z = z+1;
			}
			x=x-1;
		}
	}  		 
 	return(z);
}

void find(node_type *node){
	int x=0, y=0, k=size-1, i, j, z=size*2-row-column+1,a,b,c;
	FILE *mfptr;
	for(i = row-1; i < size; i++){
 		for(j = column-1; j < size; j++){
 			if(row<(size-1)){
 				if(i<row){
 					for(c = 0;c < size;c++){
	 					if (node->state[i][j] != (size*row-k) && node->state[i][j] == (size*row-c) && z > (abs(node->hole[0] - i)+abs(node->hole[1] - j))){
			  				x = node->hole[0] - i;
					   		y = node->hole[1] - j;
					   		a = i;
					   		b = j;
					   		z = abs(x)+abs(y);
						}
					}
					k=k-1;
				 }
				 if(i>=row){
	 				for(k = 0;k < size;k++){
		 				if (node->state[i][j] == (size*row-k) && z > (abs(node->hole[0] - i)+abs(node->hole[1] - j))){
				   			x = node->hole[0] - i;
				   			y = node->hole[1] - j;
				   			a = i;
				   			b = j;
				   			z = abs(x)+abs(y);
					 	}
					}
				}
			}
			else{
			 	for(k = 0;k < 2;k++){
	 				if (node->state[i][j+1] == size*(row-k)+column && z > (abs(node->hole[0] - i)+abs(node->hole[1] - j-1))){
			   			x = node->hole[0] - i;
			   			y = node->hole[1] - j-1;
			   			a = i;
			   			b = j+1;
			   			z = abs(x)+abs(y);
				 	}
				}
			} 
    	}
	 }
	 i = node->hole[0];
	 j = node->hole[1];
	 if(i<a && (i != row-1 || j==b)){
	 	x=x+1;
	 }
	 else if(j<b){
	 	y=y+1;
	 }
	 else if(j>b){
	 	y=y-1;
	 }
	 else{
	 	x=x-1;
	 }
	if((mfptr=fopen("move.txt","a"))==NULL){
		printf("Fail.\n");
	}
	else{
		while(x!=0 || y!=0){
		 	if(x>0){
		 		node->state[i][j] = node->state[i-1][j];
		 		node->state[i-1][j] = 0;
		 		i=i-1;
		 		x=x-1;
		 		node->depth=node->depth+1;
		 		fprintf(mfptr,"D\n");
		 	}
		 	else if(x<0){
		 		node->state[i][j] = node->state[i+1][j];
		 		node->state[i+1][j] = 0;
		 		i=i+1;
		 		x=x+1;
		 		node->depth=node->depth+1;
		 		fprintf(mfptr,"U\n");
			}
			if(y>0){
				node->state[i][j] = node->state[i][j-1];
		 		node->state[i][j-1] = 0;
		 		j=j-1;
		 		y=y-1;
		 		node->depth=node->depth+1;
		 		fprintf(mfptr,"R\n");
			}
			else if(y<0){
				node->state[i][j] = node->state[i][j+1];
		 		node->state[i][j+1] = 0;
		 		j=j+1;
		 		y=y+1;
		 		node->depth=node->depth+1;
				fprintf(mfptr,"L\n");
			}
		}
		fclose(mfptr);
    }
	node->hole[0] = i;
	node->hole[1] = j;
	node->heuristic = heuristic_first(node);
	node->proj_cost = node->heuristic + node->depth;
	for(i=0;i < size;i++){
		for(j=0;j < size;j++){
			printf("%5d",node->state[i][j]);
		}
		printf("\n");
	}
}

void report_solution (){
	FILE *fptr;
	char str[2];
	if((fptr=fopen("move.txt","r"))==NULL){
		printf("Fail.\n");
	}
	else{
		while(!feof(fptr)){
			fscanf(fptr,"%s\n",str);
			printf("     %s\n",str);
		}
    	fclose(fptr);
    }
} 

int main(void)
{
  unsigned int  total,s,x;
  node_type *current,
	    *final_node,*small;
  	FILE *fptr;
  	node_type *first;
	if((fptr=fopen("move.txt","w"))==NULL){
		printf("Fail.\n");
	}
	else{
    	fclose(fptr);
    }
  current = get_start_state();
  goal();
  x=size;
  s = site(current);
  small = current;
  printf("\nSearch has begun.\n");
  solved = at_goal(current);
  head_leaf_list = current;
  current->next_in_leaf_list = NULL;
  first = head_leaf_list;
  count = 0;
  total = 0;
  while(row < size && column <= size){
	  	while (solved == f)
	    {
	      current = head_leaf_list;
	      head_leaf_list = head_leaf_list->next_in_leaf_list;
	      expand (current, &final_node);
	      get(&first,head_leaf_list);
	      if (solved == t) current = final_node;
		  count++;
	      if ((small->heuristic > current->heuristic) && solved == f && s > x)
		{
		  	small = current;
	      	printf("%d\n",small->heuristic);
		  	total = total + count;
		  	count = 0;
		  	printf("%d nodes have been expanded without reaching the goal.\n", total);
			write(small);
			head_leaf_list = copy(small);
			del(first);
			s = site(head_leaf_list);
			first = head_leaf_list;
		}
		else if((x>0 && s <= x && solved == f )|| count==60000){
		  	count = 0;
		  	printf("%d nodes have been expanded without reaching the goal.\n", total);
			head_leaf_list = copy(small);
			del(first);
			find(head_leaf_list);
			small = head_leaf_list;
			first = head_leaf_list;
			x=x-1;
		}
	    }
	    total = total + count;
	    printf("%d nodes have been expanded ", total);
		printf("without reaching the goal.\n");
	    count = 0;
	    if(row<(size-1)){
	    	write(current);
			head_leaf_list = copy(current);
			del(first);
			first = head_leaf_list;
			current =  head_leaf_list;
			printf("   %d  h    \n",row);
		    row=row+1;
		    head_leaf_list->heuristic = heuristic_first(head_leaf_list);
		    small = head_leaf_list;
		    head_leaf_list->proj_cost = head_leaf_list->heuristic + head_leaf_list->depth;
		    solved = at_goal(head_leaf_list);
		    s = site(head_leaf_list);
		    x=size;
		    if(row == (size-2)){
		    	x=2;
			}
		}
		else{
			write(current);
			head_leaf_list = copy(current);
			del(first);
			first = head_leaf_list;
			current =  head_leaf_list;
			printf("   %d  Ƨ   \n",column);
		    column=column+1;
		    head_leaf_list->heuristic = heuristic_first(head_leaf_list);
		    small = head_leaf_list;
		    head_leaf_list->proj_cost = head_leaf_list->heuristic + head_leaf_list->depth;
		    solved = at_goal(head_leaf_list);
		    s = site(head_leaf_list);
		    x=2;
		    
		}
  }
  if (solved == t){	
    printf("\n");
	printf("depth:%d\n",current->depth);
  	printf("Solution found.\n");
   	printf("Steps are as follows:\n");
	report_solution ();
    }
  else
    {
      printf("Execution terminated without reaching goal.\n\n");
      printf("Press <Enter> to continue.");
      gets(buf);
    }
    return 0;
}

