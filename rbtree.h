#include <stdlib.h>

struct rbnode {
  struct {
    struct rbnode *rbe_left;
    struct rbnode *rbe_right;
    struct rbnode *rbe_parent;
    int rbe_color;
  } entry;
  char content[];
};

struct rbtree {
  struct rbnode *rbh_root;
  int (*cmp)(void *k1, void *k2);
};

void rbtree_remove(struct rbtree *, struct rbnode *);
struct rbnode *rbtree_insert(struct rbtree *, struct rbnode *);
struct rbnode *rbtree_find(struct rbtree *, void *);
struct rbnode *rbtree_next(struct rbtree *, struct rbnode *);
struct rbnode *rbtree_min(struct rbtree *);
struct rbnode *rbtree_max(struct rbtree *);
void rbtree_free(struct rbtree *, void (*free_cb)(void*));
