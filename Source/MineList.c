#include "MineInclude.h"
#include "MineList.h"

#include <stdlib.h>
#include <string.h>

List * MineList_Create( void (*destroy)(void*) ) {
	List *list = (List *)malloc(sizeof(List));
	if( list ) {
		memset(list, 0, sizeof(List));
		list->first = NULL;
		list->last = NULL;
		list->size = 0;
		list->destroy = destroy;
		return list;
	}
	return NULL;
}

void MineList_Delete( List *list ) {
	if( list ) {
		ListNode *next_node = list->first;
		ListNode *current_node = NULL;
		while( next_node ) {
			current_node = next_node;
			next_node = current_node->next;
			if( list->destroy AND current_node->data ) {
				list->destroy(current_node->data);
			}
			free(current_node);
		}
		free(list);
	}
}

void MineList_Append( List *list, void *data ) {
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	if( node ) {
		memset(node, 0, sizeof(ListNode));
		node->previous = NULL;
		node->next = NULL;
		node->data = data;
		if( list->last ) {
			list->last->next = node;
			node->previous = list->last;
			list->last = node;
		} else {
			list->first = node;
			list->last = node;
		}
		list->size++;
	}
}

void MineList_AddAtStart( List *list, void *data ) {
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	if( node ) {
		node->previous = NULL;
		node->next = NULL;
		node->data = data;
		if( list->first ) {
			node->next = list->first;
			list->first->previous = node;
			list->first = node;
		} else {
			list->first = node;
			list->last = node;
		}
		list->size++;
	}
}

void MineList_Remove( List *list, ListNode *node ) {
	ListNode *previous_node = node->previous;
	ListNode *next_node = node->next;
	if( previous_node ) {
		previous_node->next = next_node;
	}
	if( next_node ) {
		next_node->previous = previous_node;
	}
	if( node == list->first ) {
		list->first = next_node;
	}
	if( node == list->last ) {
		list->last = previous_node;
	}
	if( list->destroy ) {
		list->destroy(node->data);
		node->data = NULL;
	}
	free(node);
	list->size--;
}

ListNode * MineList_Find( List *list, void *data ) {
	FOREACH(list, void, node_data)
		if( node_data == data ) {
			return current_node;
		}
	ENDFOREACH
	return NULL;
}

