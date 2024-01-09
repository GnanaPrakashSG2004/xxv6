#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"

#ifdef MLFQ_SCHED
extern struct Queue queues[NQUEUES];

void remove_from_queue(struct proc *p)
{
  acquire(&p->lock);
  p->isQueued = 0;
  if (p->queue_next == 0)
  {   // only element in the queue.
    queues[p->Queue_Num].back=0;
    queues[p->Queue_Num].front = 0;
    p->queue_next = 0;
    p->queue_prev=0;
  }
  else
  {
    p->queue_next->queue_prev=0;
    queues[p->Queue_Num].front = p->queue_next;
    p->queue_next = 0;
    p->queue_prev=0;
  }
  queues[p->Queue_Num].no_of_processes--;
  release(&p->lock);
  return;
}

void add_to_queue(struct proc *p, int queue_num)
{
  acquire(&p->lock);
  p->wtime_queue = 0;
  p->Queue_Num = queue_num;
  p->isQueued = 1;
  if (queues[queue_num].front == 0)
  { // no elements in queue
    p->queue_next = 0;
    p->queue_prev = 0;
    queues[queue_num].front = p;
    queues[queue_num].back = p;
  }
  else
  {
    p->queue_next = 0;
    p->queue_prev = queues[queue_num].back;
    queues[queue_num].back->queue_next = p;
    queues[queue_num].back = p;
  }
  queues[p->Queue_Num].no_of_processes++;
  release(&p->lock);
}
#endif