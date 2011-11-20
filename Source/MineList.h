#ifndef MINE_LIST_H
#define MINE_LIST_H

typedef struct __mine_list      List;
typedef struct __mine_list_node ListNode;

struct __mine_list
{
	ListNode      *first;
	ListNode      *last;
	unsigned int   size;
	void           (*destroy)( void *data );
};

struct __mine_list_node
{
	ListNode *previous;
	ListNode *next;
	void     *data;
};

List * MineList_Create( void (*destroy)(void*) );
void MineList_Destroy( List *list);

void MineList_Append( List *list, void *data );
void MineList_AddAtStart( List *list, void *data );

void MineList_Remove( List *list, ListNode *node );

ListNode * MineList_Find( List *list, void *data );

#define FOREACH( LIST, TYPE, NAME ) \
	if( LIST->first ) { \
		ListNode *current_node = NULL; \
		ListNode *next_node = LIST->first; \
		TYPE *NAME = NULL; \
		while( next_node ) { \
			current_node = next_node; \
			next_node = current_node->next; \
			NAME = (TYPE *)current_node->data;

#define ENDFOREACH \
		} \
	}

#define CONTINUE \
	node = node->next; \
	continue;

#endif /* MINE_LIST_H */
