#include "hash.h"
#include "common.h"
#include<assert.h>//assert if false then abor

typedef struct hash_node
{
	void *key;
	void *value;
	struct hash_node *prev;
	struct hash_node *next;
}hash_node_t;

struct hash
{
	unsigned int buckets;
	hashfunc_t hash_func;
	hash_node_t **nodes;//**, 
};

hash_node_t** hash_get_bucket(hash_t *hash, void *key);
hash_node_t* hash_get_node_by_key(hash_t *hash, void *key, unsigned int key_size);


hash_t* hash_alloc(unsigned int buckets, hashfunc_t hash_func)
{
	hash_t *hash = (hash_t*) malloc(sizeof(hash_t));//initial hash, first is a hash node
	hash->buckets = buckets;// node hang on the buckets
	hash->hash_func = hash_func;
	int size = buckets * sizeof(hash_node_t);//need this size so far
	hash->nodes = (hash_node_t **) malloc(size);	
	memset(hash->nodes, 0, size);
	return hash;
}

void* hash_lookup_entry(hash_t *hash, void* key, unsigned int key_size)
{//lookup
	hash_node_t *node = hash_get_node_by_key(hash, key, key_size);
	if(node == NULL)
		return NULL;
	return node->value;
//key in buckets
}

//what's the relation of key and value
void hash_add_entry(hash_t *hash, void *key, unsigned int key_size,void *value, unsigned int value_size)
{
	if(hash_lookup_entry(hash, key, key_size))
	{
		fprintf(stderr, "duplicate has key\n");
		return;
	}
	
	//add: malloc a node size,find the bucket, insert the node (headpinsert)
	hash_node_t *node = malloc(sizeof(hash_node_t));
	node->prev = NULL;
	node->next = NULL;//init
	
	//why node has key and value?
	node->key = malloc(key_size);
	memcpy(node->key, key, key_size);
	node->value = malloc(value_size);
	memcpy(node->value, value, value_size);

	hash_node_t **bucket = hash_get_bucket(hash, key);
	if(*bucket == NULL)
	{	
		*bucket = node;
	}
	else
	{
		node->next = *bucket;
		(*bucket)->prev = node;
		*bucket = node;
	}	
}



void hash_free_entry(hash_t *hash, void *key, unsigned int key_size)
{
	//del a node from list
	hash_node_t *node = hash_get_node_by_key(hash, key, key_size);
	if (node == NULL)
	{
		return;
	}

	free(node->key);
	free(node->value);

	if (node->prev)
		node->prev->next = node->next;
	else
	{
		hash_node_t **bucket = hash_get_bucket(hash, key);
		*bucket = node->next;
	}
	if (node->next)
		node->next->prev = node->prev;

	free(node);
}

hash_node_t** hash_get_bucket(hash_t *hash, void *key)
{
	unsigned int bucket = hash->hash_func(hash->buckets, key);
	if (bucket >= hash->buckets)
	{
		fprintf(stderr, "bad bucket lookup\n");
		exit(EXIT_FAILURE);
	}

	return &(hash->nodes[bucket]);//**
}

hash_node_t* hash_get_node_by_key(hash_t *hash, void *key, unsigned int key_size)
{//fine bucket then find node in list
	hash_node_t **bucket = hash_get_bucket(hash, key);
	hash_node_t *node = *bucket;
	if (node == NULL)
	{
		return NULL;
	}

	while (node != NULL && memcmp(node->key, key, key_size) != 0)
	{
		node = node->next;
	}

	return node;
}







