#include<stdio.h>
#include<stdlib.h>
#include<time.h>


struct lst_node_s {
	int data;
	struct lst_node_s* next;
};
typedef struct lst_node_s Node;

struct tsk_node_s {
	int task_num; //starting from 0
	int task_type; // insert:0, delete:1, search:2
	int value; //randomly created value
	struct tsk_node_s* next;
};
typedef struct tsk_node_s Node2;

Node *root=NULL;
Node2 *head= NULL;
Node2 * tail=NULL;

int search(int count,Node*r,int value){      //search wheter a value exist or not
	Node *temp;
	temp=r; //temp shows the first node 
	if(temp==NULL){ //if the first node is empty,print according to it.
		printf("Task %d-search %d : %d  List is empty \n",count,value,value);	
	}
	else{
		while(temp!=NULL){  //if it is not empty search till find the value and print it
			if(temp->data==value){
				printf("Task %d-search %d : %d is found \n",count,value,value);
				return 1;	
			}
			temp=temp->next;
		}
	printf("Task %d-search %d : %d is not found \n",count,value,value); //if it cannot be found ,print it
	return 0;	
	}
	
}

int search2(int count,Node*r,int value){  //This search just checks for a value and return a value to use is inside of it ,so it prints nothing
	Node *temp;
	temp=r; //hold the root node in temp
	while(temp!=NULL){
		if(temp->data==value){
			return 1;	
		}
	temp=temp->next;
	}
	return 0;		
}

Node* insert(int count,Node * r,int value){//It is  in lst_node_s type and inserts a new node to our linked list.
	if(search2(count,r,value)==1){ //it checks for dublicated element
		printf("Task %d-insert %d : %d Dublicated can not be inserted \n",count,value,value); 
		return r;
	}
	if(r==NULL){  //If it is empty ,insert it to beginning of linked list.
		r=malloc(sizeof(Node));
		r->data=value;
		r->next=NULL;
		printf("Task %d-insert %d : %d is inserted \n",count,value,value);
		return r; //return the first node pointer
	}
	if(r->data>value){ //If the element that will be added is smaller then the first element in the list .
			Node*temp=malloc(sizeof(Node));
			temp->data=value;
			temp->next=r;
			printf("Task %d-insert %d : %d is inserted \n",count,value,value);  
			return temp;
	}
	Node * iter=r; //create an iterator and assign it to first Nodes
	while(iter->next !=NULL && iter->next->data <value){ //first possiblity is end of the linked list 2.possiblity is finding a bigger value during iterating.
		iter=iter->next;
	}
	Node*temp=malloc(sizeof(Node));
	temp->next=iter->next;
	iter->next =temp;
	temp->data=value;
	printf("Task %d-insert %d : %d is inserted \n",count,value,value); //insert the value according to position.
	return r;

}


Node* Delete(int count,Node*r,int value){ //search for a certain value and deletes it from memory
	Node *temp;
	Node *iter=r; //to iterate from the first node
	if(r==NULL){ //if the list is empty ,nothing will be deleted
		printf("Task %d-delete %d : %d can not be deleted \n",count,value,value);
		return r;
	}	
	if(r->data ==value){ // if the first element is the searched element ,delete it 
		temp=r;
		r =r->next;
		printf("Task %d-delete %d : %d is deleted \n",count,value,value);
		free(temp);
		return r; 
	}
	while(iter->next !=NULL && iter->next->data!=value ){ //iterate till find the value 
		iter=iter->next;
	}
	if(iter->next==NULL){ //The value can not be found..
		printf("Task %d-delete %d : %d can not be deleted \n",count,value,value);
		return r;
	}
	temp = iter->next; //if we are that part ,it means we found the value
	iter->next=iter->next->next; 
	free (temp);// so delete it 
	printf("Task %d-delete %d : %d is deleted \n",count,value,value);
	return r;
}


void print(Node * r){ //printing the list
	Node* temp =r;
	while(temp!=NULL){
		printf("%d ",temp->data);
		temp=temp->next;
		}
}

void Task_enqueue(int task_num, int task_type, int value){ //inserts a new task into task queue with linked list.)
	if(head==NULL){ //If the queue is empty,insert to beginning
		head = malloc(sizeof(Node2));
		head ->value =value;
		head->task_num=task_num;
		head->task_type=task_type;
		tail = head; //it means one element queue
	}
	else{
		tail->next = malloc(sizeof(Node2)); //adds end of the queue
		tail->next->value =value;
		tail->next->task_num=task_num;
		tail->next->task_type=task_type;
		tail = tail->next; //move the tail
	}

}


Node2* Task_dequeue(){ //It gives us the node in the head of the queue so we can use it for operations
	if(head==NULL){ //if the queue is empty
		printf("The queue is empty");
		return head; 
	}
	else{
		Node2 *temp=head; //Take the first element and return it ,move the head for new first element.
		head = head->next;
		return temp;
	} 
}		
void Task_queue(int n){ //it creates tasks and do the necessarily operations according to numbers.
int count=0;
Node2 *temp=NULL;
Node* iter=NULL;
srand(time(NULL));
	while(count<n){
		int random1 = rand() % 3 + 0;
		int random2=rand() % 10 +1;
		Task_enqueue(count,random1,random2); // 2 randomly value created for using to create tasks
		count+=1;
	} 
	for(count=0;count<n;count++){
		temp=Task_dequeue(); //so take the first node of queue 
		if(temp->task_type==0){ //if task type is 0 ,insert a value to linked list.
			iter=insert(count,iter,temp->value);
			
			
		}
		if(temp->task_type==1){ //if task type is 1 ,delete a value from linked list.
			iter=Delete(count,iter,temp->value);
		}
		if(temp->task_type==2){ //if task type is 2 ,search a value from linked list.
			search(count,iter,temp->value);
		}	
		free(temp); //remove the node that we took with dequeue() from memory
			
	} 
	printf("Final list : \n");
	print(iter);
}
int main(int argc, char **argv){
	int num = atoi(argv[1]);
	printf("Generated %d random list tasks.. \n",num);
	Task_queue(num);
}
