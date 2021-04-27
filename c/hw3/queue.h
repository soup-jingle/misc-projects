typedef struct elt {
	struct elt *next;
	struct elt *prev;
	struct queue *queue;
	void *value;
} Elt;

typedef struct queue {
	struct elt *first;
	struct elt *last;
	int size;
} Queue;

inline void qNewElt(Elt *e, void *val) {
	e = malloc(sizeof(Elt));
	e->next = NULL;
	e->value = val;
}

inline Elt* qNext(Elt *e) {
	return e->next;
}

inline Elt* qPrev(Elt *e) {
	return e->prev;
}

inline Elt* qFirst(Queue *q) {
	return q->first;
}

inline Elt* qLast(Queue *q) {
	return q->last;
}

inline void qInsertAt(Queue *q, Elt *prev, Elt *new) {
	new->queue = q;
	new->prev = prev;
	new->next = prev->next;
	new->next->prev = new;
	prev->next = e;
	q->size += 1;
}

inline void qInsertLast(Queue *q, Elt *e) {
	qInsertAt(q, qLast(q), e);
}

inline void qRemove(Elt *e) {
	if(e->queue->size > 0) {
		e->next->prev = e->prev;
		e->prev->next = e->next;
		e->queue->size -= 1;
	}
	e->next = NULL;
}

inline int qEmpty(Queue *q) {
	return (q->size == 0);
}

inline void qInit(Queue *q) {
	q->first = (Elt *)q;
	q->last = (Elt *)q;
	q->size = 0;
}
