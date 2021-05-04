#include <iostream>

struct Node
{
	int value;
	Node* ptr;
	
	Node(int new_value = 0, Node* new_ptr = nullptr)
	{
		value = new_value;
		ptr = new_ptr;
	}
	
	~Node()
	{
		value = 0;
		ptr = nullptr;
	}
};

Node* NodeXOR (Node* a, Node* b)
{
	return (Node*)((long long int)(a) ^ (long long int)(b));
}

struct DList
{
	Node* first;
	Node* last;
	
	int len;
	
	DList()
	{
		first = nullptr;
		last = nullptr;
		len = 0;
	}
};

int PrintDList(DList* d_list)
{
	if (d_list == nullptr)
	{
		return -1;
	}
		
	Node* buffer_node = d_list->first;
	Node* buffer_prev = nullptr;
	Node* buffer_next = nullptr;
	
	while(buffer_node != nullptr)
	{
		std::cout << buffer_node->value << std::endl;
		
		buffer_next = NodeXOR(buffer_node->ptr, buffer_prev);
		
		buffer_prev = buffer_node;
		buffer_node = buffer_next;
	}
};

Node* add_to_end (DList* d_list, int n)
{
	if (d_list == nullptr)
	{
		return nullptr;
	}
	
	Node* sec_last_element = new Node(n, NodeXOR(d_list->last, nullptr));

	if (d_list->len == 1)
	{
		d_list->last = sec_last_element;
		d_list->first->ptr = d_list->last;
		
		d_list->len += 1;		
				
		return d_list->last;
	}
	
	if (d_list->len == 0)
	{
		Node* new_last_element = new Node(n);
		d_list->first = new_last_element;
		d_list->last = new_last_element;
		
		d_list->len = 1;
		
		return d_list->last;
	} 
	else
	{
		d_list->last->ptr = NodeXOR(d_list->last->ptr, sec_last_element);
		d_list->last = sec_last_element;
			
		d_list->len += 1;
	}
	
	return sec_last_element;
};

DList* CreateDList(int* data, int size)
{
	DList* ret = new DList();
	
	for (int cnt = 0; cnt < size; cnt++)
	{
		add_to_end(ret, data[cnt]);
	}
	
	return ret;
}

Node* add_to_begin (DList* d_list, int n)
{
	if (d_list == nullptr)
	{
		return nullptr;
	}
	
	Node* sec_first_element = new Node(n, NodeXOR(d_list->first, nullptr));

	if (d_list->len == 1)
	{
		d_list->first = sec_first_element;
		d_list->last->ptr = d_list->first;
		
		d_list->len += 1;		
				
		return d_list->first;
	}
	
	if (d_list->len == 0)
	{
		Node* new_first_element = new Node(n);
		d_list->first = new_first_element;
		d_list->last = new_first_element;
		
		d_list->len = 1;
		
		return d_list->first;
	} 
	else
	{
		d_list->first->ptr = NodeXOR(d_list->first->ptr, sec_first_element);
		d_list->first = sec_first_element;
			
		d_list->len += 1;
	}
	
	return sec_first_element;
};

Node* find_by_index(DList* d_list, int index)
{
	if (d_list == nullptr)
	{
		return nullptr;
	}
	
	int cnt = 0;
	Node* buffer_prev = nullptr;
	Node* buffer_node = d_list->first;
	Node* buffer_next = nullptr;
	
	while (cnt < index && buffer_node != nullptr)
	{
		buffer_next = NodeXOR(buffer_prev, buffer_node->ptr);
		buffer_prev = buffer_node;
		buffer_node = buffer_next;
		
		cnt++;
	}
	
	return buffer_node;
}

Node* add_i (DList* d_list, int index, int new_value)
{
	if (d_list == nullptr)
	{
		return nullptr;
	}
	
	if (index > d_list->len)
	{
		return nullptr;
	}
	
	if (d_list->len == 0)
	{		
		return add_to_begin(d_list, new_value);
	}
	
	if (index == d_list->len)
	{
		return nullptr;
	}
	
	if (index == 0)
	{
		return add_to_begin(d_list, new_value);
	}
	
	if (index == d_list->len-1)
	{
		return add_to_end(d_list, new_value);
	}
	
	Node* new_element = new Node(new_value);
	
	Node* buffer = find_by_index(d_list, index-1);
	Node* buffer_next = find_by_index(d_list, index);
	
	Node* buffer_prev = NodeXOR(buffer->ptr, buffer_next);
	Node* buffer_next_next = NodeXOR(buffer_next->ptr, buffer);
	
	buffer->ptr = NodeXOR(buffer_prev, new_element);
	buffer_next->ptr = NodeXOR(new_element, buffer_next_next);
	
	new_element->ptr = NodeXOR(buffer, buffer_next);
	
	d_list->len += 1;
	return new_element;
};

Node* del_i (DList* d_list, int index)
{
	if (d_list == nullptr)
	{
		return nullptr;
	}
	
	if (index >= d_list->len)
	{
		return nullptr;
	}
	
	if (index == 0)
	{
		Node* del_element = d_list->first;
		
		if (d_list->len == 1)
		{
			d_list->first = nullptr;
		}
		else
		{	
			d_list->first = d_list->first->ptr;
			
			d_list->first->ptr = NodeXOR(d_list->first->ptr, del_element);
		}
		
		d_list->len -= 1;
		
		return del_element;
	}
	
	if (index == d_list->len-1)
	{
		Node* del_element = d_list->last;
	
		if (d_list->len == 1)
		{
			d_list->first = nullptr;
		}
		else
		{
			Node* prev_last = del_element->ptr;
			
			prev_last->ptr = NodeXOR(prev_last->ptr, del_element);
		}
		
		d_list->len -= 1;
		
		return del_element;
	}
	
	Node* buffer_prev = find_by_index(d_list, index - 1);
	Node* buffer_del = find_by_index(d_list, index);
	
	if(buffer_del == nullptr)
	{	
		return nullptr;
	}
	
	Node* buffer_next = NodeXOR(buffer_del->ptr, buffer_prev);
	
	buffer_prev->ptr = NodeXOR(NodeXOR(buffer_prev->ptr, buffer_del), buffer_next);
	buffer_next->ptr = NodeXOR(buffer_prev, NodeXOR(buffer_next->ptr, buffer_del));
	
	d_list->len -= 1;
	
	return buffer_del;	
};

Node* find_by_value(DList* d_list, int value)
{
	if (d_list == nullptr)
	{
		return nullptr;
	}
	
	Node* buffer_prev = nullptr;
	Node* buffer_node = d_list->first;
	Node* buffer_next = nullptr;

	while(buffer_node->value != value && buffer_node != nullptr)
	{
		buffer_next = NodeXOR(buffer_node->ptr, buffer_prev);
		
		buffer_prev = buffer_node;
		buffer_node = buffer_next;
	}
	
	return buffer_node;
}

int get_index_by_value(DList* d_list, int value)
{
	if (d_list == nullptr)
	{
		return -1;
	}
	
	Node* buffer_prev = nullptr;
	Node* buffer_node = d_list->first;
	Node* buffer_next = nullptr;

	int cnt = 0;
	while(buffer_node != nullptr && buffer_node->value != value)
	{
		buffer_next = NodeXOR(buffer_node->ptr, buffer_prev);
		
		buffer_prev = buffer_node;
		buffer_node = buffer_next;
	
		cnt++;
	}
	
	return (buffer_node == nullptr ? -1 : cnt);
}

Node* remove_value(DList* d_list, int value)
{
	if (d_list == nullptr)
	{
		return nullptr;
	}
	
	return del_i(d_list, get_index_by_value(d_list, value));
}

DList* copy_dlist (DList* d_list)
{
	if (d_list == nullptr)
	{
		return nullptr;
	}
	
	DList* new_dlist = new DList();
	
	Node* buffer_prev = nullptr;
	Node* buffer_node = d_list->first;
	Node* buffer_next = nullptr;
	
	while (buffer_node != nullptr)
	{
		add_to_end(new_dlist, buffer_node->value);
		
		buffer_next = NodeXOR(buffer_node->ptr, buffer_prev);
		
		buffer_prev = buffer_node;
		buffer_node = buffer_next;
	}
	
	return new_dlist;
}

DList* reverse_dlist(DList* d_list)
{
	if (d_list == nullptr)
	{
		return nullptr;
	}
	
	DList* new_dlist = new DList();
	
	Node* buffer_prev = nullptr;
	Node* buffer_node = d_list->first;
	Node* buffer_next = nullptr;
	
	while (buffer_node != nullptr)
	{
		add_to_begin(new_dlist, buffer_node->value);
		
		buffer_next = NodeXOR(buffer_node->ptr, buffer_prev);
		
		buffer_prev = buffer_node;
		buffer_node = buffer_next;
	}
	
	return new_dlist;
}

DList* merge_dlist(DList* a_dlist, DList* b_dlist)
{
	if (a_dlist == nullptr || b_dlist == nullptr)
	{
		return nullptr;
	}

	DList* new_dlist = new DList();
	
	Node* buffer_prev = nullptr;
	Node* buffer_node = a_dlist->first;
	Node* buffer_next = nullptr;
	
	while (buffer_node != nullptr)
	{
		add_to_end(new_dlist, buffer_node->value);
		
		buffer_next = NodeXOR(buffer_node->ptr, buffer_prev);
		
		buffer_prev = buffer_node;
		buffer_node = buffer_next;
	}
	
	buffer_prev = nullptr;
	buffer_node = b_dlist->first;
	
	while (buffer_node != nullptr)
	{
		add_to_end(new_dlist, buffer_node->value);
		
		buffer_next = NodeXOR(buffer_node->ptr, buffer_prev);
		
		buffer_prev = buffer_node;
		buffer_node = buffer_next;
	}
	
	return new_dlist;
}

int delete_dlist (DList* d_list)
{
	if (d_list == nullptr)
	{
		return -1;
	}
	
	Node* buffer_prev = nullptr;
	Node* buffer_node = d_list->first;
	Node* buffer_next = nullptr;
	Node* temp_buffer = nullptr;
	
	while (buffer_node != nullptr)
	{
		temp_buffer = buffer_node;
		
		buffer_next = NodeXOR(buffer_node->ptr, buffer_prev);
		
		buffer_prev = buffer_node;
		buffer_node = buffer_next;
		
		delete temp_buffer;
	}
	
	d_list->len = 0;
	d_list->first = nullptr;
	d_list->last = nullptr;
	
	d_list = nullptr;
	
	return 0;
}

int main ()
{
	
}