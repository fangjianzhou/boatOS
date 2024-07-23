
#ifndef _LIST_H
#define _LIST_H

KLINE void list_init(list_h_t* list)
{
	list->prev=list;
	list->next=list;
	return;
}

KLINE void __list_del(list_h_t* prev, list_h_t* next)
{
	next->prev = prev;
	prev->next = next;
	return;
}

KLINE void __list_add(list_h_t *new,list_h_t *prev,list_h_t *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
	return;
}

KLINE void list_add(list_h_t *new, list_h_t *head)
{
         __list_add(new, head, head->next);
	return;
}

KLINE void list_add_tail(list_h_t* new,list_h_t* head)
{
        __list_add(new, head->prev, head);
	return;	
}


KLINE void __list_del_entry(list_h_t* entry)
{
	__list_del(entry->prev, entry->next);
	return;
}

KLINE void list_del(list_h_t* entry)
{
	__list_del(entry->prev, entry->next);
	list_init(entry);
	return;
}

KLINE void list_move(list_h_t* list,list_h_t* head)
{
         list_del(list);
         list_add(list, head);
         return;
}
KLINE void list_move_tail(list_h_t* list,list_h_t* head)
{
         list_del(list);
         list_add_tail(list, head);
         return;
}


KLINE bool_t list_is_empty(const list_h_t* head)
{
	if(head->next == head)
	{
		return TRUE;
	}
	return FALSE;
}

KLINE bool_t list_is_empty_careful(const list_h_t* head)
{
	list_h_t* next = head->next;
	if(next == head && next == head->prev)
	{
		return TRUE;
	}
	return FALSE;
}


#define list_for_each(pos, head) for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_head_dell(pos, head) for (pos = (head)->next; pos != (head); pos = (head)->next)

#define list_entry(ptr, type, member) \
((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
#endif
