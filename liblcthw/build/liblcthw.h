#if !defined(_lcthw_BSTree_h)
#define _lcthw_BSTree_h
typedef int(*BSTree_compare)(void *a,void *b);
typedef struct BSTreeNode BSTreeNode;
struct BSTreeNode {
    void *key;
    void *data;

    struct BSTreeNode *left;
    struct BSTreeNode *right;
    struct BSTreeNode *parent;
};
typedef struct BSTree BSTree;
struct BSTree {
    int count;
    BSTree_compare compare;
    BSTreeNode *root;
};
typedef int(BSTree_traverse_cb)(BSTreeNode *node);
BSTree *BSTree_create(BSTree_compare compare);
void BSTree_destroy(BSTree *map);
int BSTree_set(BSTree *map,void *key,void *data);
void *BSTree_get(BSTree *map,void *key);
int BSTree_traverse(BSTree *map,BSTree_traverse_cb traverse_cb);
void *BSTree_delete(BSTree *map,void *key);
#endif
#if !defined(_DArray_h)
#define _DArray_h
typedef struct DArray DArray;
#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>
struct DArray {
    int end;
    int max;
    size_t element_size;
    size_t expand_rate;
    void **contents;
};
DArray *DArray_create(size_t element_size,size_t initial_max);
void DArray_destroy(DArray *array);
void DArray_clear(DArray *array);
int DArray_expand(DArray *array);
int DArray_contract(DArray *array);
int DArray_push(DArray *array,void *el);
void *DArray_pop(DArray *array);
void DArray_clear_destroy(DArray *array);
#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)
#define DEFAULT_EXPAND_RATE 300
#define DArray_free(E) free((E))
#endif
#if !defined(darray_algos_h)
#define darray_algos_h
#include <lcthw/darray.h>
typedef int(*DArray_compare)(const void *a,const void *b);
int DArray_qsort(DArray *array,DArray_compare cmp);
int DArray_heapsort(DArray *array,DArray_compare cmp);
int DArray_mergesort(DArray *array,DArray_compare cmp);
#endif
#if !defined(_lcthw_Hashmap_h)
#define _lcthw_Hashmap_h
#include <stdint.h>
#include <lcthw/darray.h>
#define DEFAULT_NUMBER_OF_BUCKETS 100
typedef int(*Hashmap_compare)(void *a,void *b);
typedef uint32_t(*Hashmap_hash)(void *key);
typedef struct Hashmap Hashmap;
struct Hashmap {
    DArray *buckets;
    Hashmap_compare compare;
    Hashmap_hash hash;
};
typedef struct HashmapNode HashmapNode;
struct HashmapNode {
    void *key;
    void *data;
    uint32_t hash;
};
typedef int(*Hashmap_traverse_cb)(HashmapNode *node);
Hashmap *Hashmap_create(Hashmap_compare compare,Hashmap_hash);
void Hashmap_destroy(Hashmap *map);
int Hashmap_set(Hashmap *map,void *key,void *data);
void *Hashmap_get(Hashmap *map,void *key);
int Hashmap_traverse(Hashmap *map,Hashmap_traverse_cb traverse_cb);
void *Hashmap_delete(Hashmap *map,void *key);
#endif
#if !defined(hashmap_algos_h)
#define hashmap_algos_h
#include <stdint.h>
uint32_t Hashmap_fnv1a_hash(void *data);
uint32_t Hashmap_adler32_hash(void *data);
uint32_t Hashmap_djb_hash(void *data);
#endif
#if !defined(lcthw_List_h)
#define lcthw_List_h
typedef struct ListNode ListNode;
#include <stdlib.h>
struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
};
typedef struct List List;
struct List {
    int count;
    ListNode *first;
    ListNode *last;
};
List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);
#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)
void List_push(List *list,void *value);
void *List_pop(List *list);
void List_unshift(List *list,void *value);
void *List_shift(List *list);
void *List_remove(List *list,ListNode *node);
List *List_copy(List *list);
void List_join(List *left,List *right);
void List_split(List *list,ListNode *splitter,List **remainder,int recount);
void ListNode_swap(ListNode *a,ListNode *b);
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL; \
    ListNode *V = NULL; \
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)
#endif
#if !defined(lcthw_list_algos_h)
#define lcthw_list_algos_h
#include "list.h"
typedef int(*List_compare)(void *a,void *b);
int List_bubble_sort(List *list,List_compare comparator);
List *List_merge_sort(List *list,List_compare comparator);
#endif
#if !defined(_radixmap_h)
#define _radixmap_h
typedef union RMElement RMElement;
#include <stdint.h>
union RMElement {
    uint64_t raw;
    struct {
        uint32_t key;
        uint32_t value;
    } data;
};
typedef struct RadixMap RadixMap;
struct RadixMap {
    size_t max;
    size_t end;
    uint32_t counter;
    RMElement *contents;
    RMElement *temp;
};
RadixMap *RadixMap_create(size_t max);
void RadixMap_destroy(RadixMap *map);
void RadixMap_sort(RadixMap *map);
RMElement *RadixMap_find(RadixMap *map,uint32_t key);
int RadixMap_add(RadixMap *map,uint32_t key,uint32_t value);
int RadixMap_delete(RadixMap *map,RMElement *el);
#endif
#if !defined(string_algos_h)
#define string_algos_h
typedef struct StringScanner StringScanner;
#include <lcthw/bstrlib.h>
#include <lcthw/darray.h>
struct StringScanner {
    bstring in;
    const unsigned char *haystack;
    ssize_t hlen;
    const unsigned char *needle;
    ssize_t nlen;
    size_t skip_chars[UCHAR_MAX + 1];
};
int String_find(bstring in,bstring what);
StringScanner *StringScanner_create(bstring in);
int StringScanner_scan(StringScanner *scan,bstring tofind);
void StringScanner_destroy(StringScanner *scan);
#endif
#define INTERFACE 0
#define EXPORT_INTERFACE 0
#define LOCAL_INTERFACE 0
#define EXPORT
#define LOCAL static
#define PUBLIC
#define PRIVATE
#define PROTECTED
/*
 * This source file is part of the bstring string library.  This code was
 * written by Paul Hsieh in 2002-2010, and is covered by either the 3-clause
 * BSD open source license or GPL v2.0. Refer to the accompanying documentation
 * for details on usage and license.
 */

/*
 * bstrlib.h
 *
 * This file is the header file for the core module for implementing the
 * bstring functions.
 */

#ifndef BSTRLIB_INCLUDE
#define BSTRLIB_INCLUDE

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#if !defined (BSTRLIB_VSNP_OK) && !defined (BSTRLIB_NOVSNP)
# if defined (__TURBOC__) && !defined (__BORLANDC__)
#  define BSTRLIB_NOVSNP
# endif
#endif

#define BSTR_ERR (-1)
#define BSTR_OK (0)
#define BSTR_BS_BUFF_LENGTH_GET (0)

typedef struct tagbstring * bstring;
typedef const struct tagbstring * const_bstring;

/* Copy functions */
#define cstr2bstr bfromcstr
extern bstring bfromcstr (const char * str);
extern bstring bfromcstralloc (int mlen, const char * str);
extern bstring blk2bstr (const void * blk, int len);
extern char * bstr2cstr (const_bstring s, char z);
extern int bcstrfree (char * s);
extern bstring bstrcpy (const_bstring b1);
extern int bassign (bstring a, const_bstring b);
extern int bassignmidstr (bstring a, const_bstring b, int left, int len);
extern int bassigncstr (bstring a, const char * str);
extern int bassignblk (bstring a, const void * s, int len);

/* Destroy function */
extern int bdestroy (bstring b);

/* Space allocation hinting functions */
extern int balloc (bstring s, int len);
extern int ballocmin (bstring b, int len);

/* Substring extraction */
extern bstring bmidstr (const_bstring b, int left, int len);

/* Various standard manipulations */
extern int bconcat (bstring b0, const_bstring b1);
extern int bconchar (bstring b0, char c);
extern int bcatcstr (bstring b, const char * s);
extern int bcatblk (bstring b, const void * s, int len);
extern int binsert (bstring s1, int pos, const_bstring s2, unsigned char fill);
extern int binsertch (bstring s1, int pos, int len, unsigned char fill);
extern int breplace (bstring b1, int pos, int len, const_bstring b2, unsigned char fill);
extern int bdelete (bstring s1, int pos, int len);
extern int bsetstr (bstring b0, int pos, const_bstring b1, unsigned char fill);
extern int btrunc (bstring b, int n);

/* Scan/search functions */
extern int bstricmp (const_bstring b0, const_bstring b1);
extern int bstrnicmp (const_bstring b0, const_bstring b1, int n);
extern int biseqcaseless (const_bstring b0, const_bstring b1);
extern int bisstemeqcaselessblk (const_bstring b0, const void * blk, int len);
extern int biseq (const_bstring b0, const_bstring b1);
extern int bisstemeqblk (const_bstring b0, const void * blk, int len);
extern int biseqcstr (const_bstring b, const char * s);
extern int biseqcstrcaseless (const_bstring b, const char * s);
extern int bstrcmp (const_bstring b0, const_bstring b1);
extern int bstrncmp (const_bstring b0, const_bstring b1, int n);
extern int binstr (const_bstring s1, int pos, const_bstring s2);
extern int binstrr (const_bstring s1, int pos, const_bstring s2);
extern int binstrcaseless (const_bstring s1, int pos, const_bstring s2);
extern int binstrrcaseless (const_bstring s1, int pos, const_bstring s2);
extern int bstrchrp (const_bstring b, int c, int pos);
extern int bstrrchrp (const_bstring b, int c, int pos);
#define bstrchr(b,c) bstrchrp ((b), (c), 0)
#define bstrrchr(b,c) bstrrchrp ((b), (c), blength(b)-1)
extern int binchr (const_bstring b0, int pos, const_bstring b1);
extern int binchrr (const_bstring b0, int pos, const_bstring b1);
extern int bninchr (const_bstring b0, int pos, const_bstring b1);
extern int bninchrr (const_bstring b0, int pos, const_bstring b1);
extern int bfindreplace (bstring b, const_bstring find, const_bstring repl, int pos);
extern int bfindreplacecaseless (bstring b, const_bstring find, const_bstring repl, int pos);

/* List of string container functions */
struct bstrList {
    int qty, mlen;
    bstring * entry;
};
extern struct bstrList * bstrListCreate (void);
extern int bstrListDestroy (struct bstrList * sl);
extern int bstrListAlloc (struct bstrList * sl, int msz);
extern int bstrListAllocMin (struct bstrList * sl, int msz);

/* String split and join functions */
extern struct bstrList * bsplit (const_bstring str, unsigned char splitChar);
extern struct bstrList * bsplits (const_bstring str, const_bstring splitStr);
extern struct bstrList * bsplitstr (const_bstring str, const_bstring splitStr);
extern bstring bjoin (const struct bstrList * bl, const_bstring sep);
extern int bsplitcb (const_bstring str, unsigned char splitChar, int pos,
	int (* cb) (void * parm, int ofs, int len), void * parm);
extern int bsplitscb (const_bstring str, const_bstring splitStr, int pos,
	int (* cb) (void * parm, int ofs, int len), void * parm);
extern int bsplitstrcb (const_bstring str, const_bstring splitStr, int pos,
	int (* cb) (void * parm, int ofs, int len), void * parm);

/* Miscellaneous functions */
extern int bpattern (bstring b, int len);
extern int btoupper (bstring b);
extern int btolower (bstring b);
extern int bltrimws (bstring b);
extern int brtrimws (bstring b);
extern int btrimws (bstring b);

/* <*>printf format functions */
#if !defined (BSTRLIB_NOVSNP)
extern bstring bformat (const char * fmt, ...);
extern int bformata (bstring b, const char * fmt, ...);
extern int bassignformat (bstring b, const char * fmt, ...);
extern int bvcformata (bstring b, int count, const char * fmt, va_list arglist);

#define bvformata(ret, b, fmt, lastarg) { \
bstring bstrtmp_b = (b); \
const char * bstrtmp_fmt = (fmt); \
int bstrtmp_r = BSTR_ERR, bstrtmp_sz = 16; \
	for (;;) { \
		va_list bstrtmp_arglist; \
		va_start (bstrtmp_arglist, lastarg); \
		bstrtmp_r = bvcformata (bstrtmp_b, bstrtmp_sz, bstrtmp_fmt, bstrtmp_arglist); \
		va_end (bstrtmp_arglist); \
		if (bstrtmp_r >= 0) { /* Everything went ok */ \
			bstrtmp_r = BSTR_OK; \
			break; \
		} else if (-bstrtmp_r <= bstrtmp_sz) { /* A real error? */ \
			bstrtmp_r = BSTR_ERR; \
			break; \
		} \
		bstrtmp_sz = -bstrtmp_r; /* Doubled or target size */ \
	} \
	ret = bstrtmp_r; \
}

#endif

typedef int (*bNgetc) (void *parm);
typedef size_t (* bNread) (void *buff, size_t elsize, size_t nelem, void *parm);

/* Input functions */
extern bstring bgets (bNgetc getcPtr, void * parm, char terminator);
extern bstring bread (bNread readPtr, void * parm);
extern int bgetsa (bstring b, bNgetc getcPtr, void * parm, char terminator);
extern int bassigngets (bstring b, bNgetc getcPtr, void * parm, char terminator);
extern int breada (bstring b, bNread readPtr, void * parm);

/* Stream functions */
extern struct bStream * bsopen (bNread readPtr, void * parm);
extern void * bsclose (struct bStream * s);
extern int bsbufflength (struct bStream * s, int sz);
extern int bsreadln (bstring b, struct bStream * s, char terminator);
extern int bsreadlns (bstring r, struct bStream * s, const_bstring term);
extern int bsread (bstring b, struct bStream * s, int n);
extern int bsreadlna (bstring b, struct bStream * s, char terminator);
extern int bsreadlnsa (bstring r, struct bStream * s, const_bstring term);
extern int bsreada (bstring b, struct bStream * s, int n);
extern int bsunread (struct bStream * s, const_bstring b);
extern int bspeek (bstring r, const struct bStream * s);
extern int bssplitscb (struct bStream * s, const_bstring splitStr,
	int (* cb) (void * parm, int ofs, const_bstring entry), void * parm);
extern int bssplitstrcb (struct bStream * s, const_bstring splitStr,
	int (* cb) (void * parm, int ofs, const_bstring entry), void * parm);
extern int bseof (const struct bStream * s);

struct tagbstring {
	int mlen;
	int slen;
	unsigned char * data;
};

/* Accessor macros */
#define blengthe(b, e)	    (((b) == (void *)0 || (b)->slen < 0) ? (int)(e) : ((b)->slen))
#define blength(b)	    (blengthe ((b), 0))
#define bdataofse(b, o, e)  (((b) == (void *)0 || (b)->data == (void*)0) ? (char *)(e) : ((char *)(b)->data) + (o))
#define bdataofs(b, o)	    (bdataofse ((b), (o), (void *)0))
#define bdatae(b, e)	    (bdataofse (b, 0, e))
#define bdata(b)	    (bdataofs (b, 0))
#define bchare(b, p, e)     ((((unsigned)(p)) < (unsigned)blength(b)) ? ((b)->data[(p)]) : (e))
#define bchar(b, p)	    bchare ((b), (p), '\0')

/* Static constant string initialization macro */
#define bsStaticMlen(q,m)   {(m), (int) sizeof(q)-1, (unsigned char *) ("" q "")}
#if defined(_MSC_VER)
/* There are many versions of MSVC which emit __LINE__ as a non-constant. */
# define bsStatic(q)	    bsStaticMlen(q,-32)
#endif
#ifndef bsStatic
# define bsStatic(q)	    bsStaticMlen(q,-__LINE__)
#endif

/* Static constant block parameter pair */
#define bsStaticBlkParms(q) ((void *)("" q "")), ((int) sizeof(q)-1)

/* Reference building macros */
#define cstr2tbstr btfromcstr
#define btfromcstr(t,s) {					     \
    (t).data = (unsigned char *) (s);				     \
    (t).slen = ((t).data) ? ((int) (strlen) ((char *)(t).data)) : 0; \
    (t).mlen = -1;						     \
}
#define blk2tbstr(t,s,l) {	      \
    (t).data = (unsigned char *) (s); \
    (t).slen = l;		      \
    (t).mlen = -1;		      \
}
#define btfromblk(t,s,l) blk2tbstr(t,s,l)
#define bmid2tbstr(t,b,p,l) {						     \
    const_bstring bstrtmp_s = (b);					     \
    if (bstrtmp_s && bstrtmp_s->data && bstrtmp_s->slen >= 0) { 	     \
	int bstrtmp_left = (p); 					     \
	int bstrtmp_len  = (l); 					     \
	if (bstrtmp_left < 0) { 					     \
	    bstrtmp_len += bstrtmp_left;				     \
	    bstrtmp_left = 0;						     \
	}								     \
	if (bstrtmp_len > bstrtmp_s->slen - bstrtmp_left)		     \
	    bstrtmp_len = bstrtmp_s->slen - bstrtmp_left;		     \
	if (bstrtmp_len <= 0) { 					     \
	    (t).data = (unsigned char *)"";				     \
	    (t).slen = 0;						     \
	} else {							     \
	    (t).data = bstrtmp_s->data + bstrtmp_left;			     \
	    (t).slen = bstrtmp_len;					     \
	}								     \
    } else {								     \
	(t).data = (unsigned char *)""; 				     \
	(t).slen = 0;							     \
    }									     \
    (t).mlen = -__LINE__;						     \
}
#define btfromblkltrimws(t,s,l) {					     \
    int bstrtmp_idx = 0, bstrtmp_len = (l);				     \
    unsigned char * bstrtmp_s = (s);					     \
    if (bstrtmp_s && bstrtmp_len >= 0) {				     \
	for (; bstrtmp_idx < bstrtmp_len; bstrtmp_idx++) {		     \
	    if (!isspace (bstrtmp_s[bstrtmp_idx])) break;		     \
	}								     \
    }									     \
    (t).data = bstrtmp_s + bstrtmp_idx; 				     \
    (t).slen = bstrtmp_len - bstrtmp_idx;				     \
    (t).mlen = -__LINE__;						     \
}
#define btfromblkrtrimws(t,s,l) {					     \
    int bstrtmp_len = (l) - 1;						     \
    unsigned char * bstrtmp_s = (s);					     \
    if (bstrtmp_s && bstrtmp_len >= 0) {				     \
	for (; bstrtmp_len >= 0; bstrtmp_len--) {			     \
	    if (!isspace (bstrtmp_s[bstrtmp_len])) break;		     \
	}								     \
    }									     \
    (t).data = bstrtmp_s;						     \
    (t).slen = bstrtmp_len + 1; 					     \
    (t).mlen = -__LINE__;						     \
}
#define btfromblktrimws(t,s,l) {					     \
    int bstrtmp_idx = 0, bstrtmp_len = (l) - 1; 			     \
    unsigned char * bstrtmp_s = (s);					     \
    if (bstrtmp_s && bstrtmp_len >= 0) {				     \
	for (; bstrtmp_idx <= bstrtmp_len; bstrtmp_idx++) {		     \
	    if (!isspace (bstrtmp_s[bstrtmp_idx])) break;		     \
	}								     \
	for (; bstrtmp_len >= bstrtmp_idx; bstrtmp_len--) {		     \
	    if (!isspace (bstrtmp_s[bstrtmp_len])) break;		     \
	}								     \
    }									     \
    (t).data = bstrtmp_s + bstrtmp_idx; 				     \
    (t).slen = bstrtmp_len + 1 - bstrtmp_idx;				     \
    (t).mlen = -__LINE__;						     \
}

/* Write protection macros */
#define bwriteprotect(t)     { if ((t).mlen >=	0) (t).mlen = -1; }
#define bwriteallow(t)	     { if ((t).mlen == -1) (t).mlen = (t).slen + ((t).slen == 0); }
#define biswriteprotected(t) ((t).mlen <= 0)

#ifdef __cplusplus
}
#endif

#endif
