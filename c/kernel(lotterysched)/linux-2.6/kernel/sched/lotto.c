#include <linux/random.h>
#include "sched.h"

//#include <list.h>
/*
#define TOO_SOON 2
#define TOO_LONG 25
*/
static struct task_struct
*lotto_pick_next_task(struct rq *rq, struct task_struct *prev, struct rq_flags *rf) {
  unsigned long total_tickets = 0;

  struct task_struct *next = NULL;
  struct list_head *temp;

  uint i;
  unsigned long r;

  if(rq->lrq.nr_running <= 0) return NULL;
  
  // Count # tickets
  list_for_each(temp, &rq->lrq.lotto_lh) {
    next = list_entry(temp, struct task_struct, lotto_rl);
    total_tickets += next->numTickets;
  }   
  // Select winning 'ticket'
  do {
    get_random_bytes(&r, sizeof(unsigned long));
    r = (r%total_tickets)+1;
  } while(r < 0);

  // Find process with winning 'ticket'
  i = 0;
  list_for_each(temp, &rq->lrq.lotto_lh) {
    next = list_entry(temp, struct task_struct, lotto_rl);
    i += next->numTickets;
    if(i >= r) break;
    
    list_del(&next->lotto_rl);
    list_add_tail(&next->lotto_rl, &rq->lrq.lotto_lh);
  }
  return next;
}


static void
lotto_enqueue_task(struct rq *rq, struct task_struct *p, int wakeup) {
  printk(KERN_NOTICE "*****ENQUEUE TASK LOTTO*****");

  list_add_tail(&p->lotto_rl, &rq->lrq.lotto_lh);
  rq->lrq.nr_running++;
  
}

static void
lotto_dequeue_task(struct rq *rq, struct task_struct *p, int sleep) {
  list_del(&p->lotto_rl);
  rq->lrq.nr_running--;
}

static void
lotto_update_curr(struct rq *rq) {
  struct task_struct *p = rq->curr;
  p->se.sum_exec_runtime += (rq->clock - p->se.exec_start);
  p->se.exec_start = rq->clock;
}

static void
lotto_requeue_task(struct rq *rq, struct task_struct *p) {
  list_move_tail(&p->lotto_rl, &rq->lrq.lotto_lh);
}

static void
lotto_yield_task(struct rq *rq) {
  lotto_requeue_task(rq, rq->curr);
}

static void
lotto_check_preempt_curr(struct rq *rq, struct task_struct *p, int wakeflags) {
  
}
 
static void
lotto_task_tick(struct rq *rq, struct task_struct *p, int queued) {
  lotto_update_curr(rq);
}

static void
lotto_set_curr_task(struct rq *rq) {
  (rq->curr)->se.exec_start = rq->clock;
}

const struct sched_class
lotto_sched_class = {
  .next                 = &rt_sched_class,
  .pick_next_task	= lotto_pick_next_task,

  .enqueue_task         = lotto_enqueue_task,
  .dequeue_task         = lotto_dequeue_task,
  
  .yield_task	        = lotto_yield_task,

  .check_preempt_curr	= lotto_check_preempt_curr,
  
  .task_tick		= lotto_task_tick,
  .update_curr	        = lotto_update_curr,
 
  //.put_prev_task	= put_prev_task_fair,
  //.task_fork		= task_fork_fair,
  .set_curr_task        = lotto_set_curr_task,
};
