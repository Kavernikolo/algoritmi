#define LEVELS 5

typedef struct _SkipList
{
    SkipNode *head;
    unsigned int max_level;

}SkipList;

typedef struct _SkipNode
{
    SkipNode **next;
    unsigned int level;

    void *data;

    int(*compare)(void*, void*);
}SkipNode;

