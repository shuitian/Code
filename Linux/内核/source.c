// linux-2.6.0
// include/linux/sched.h

#define __set_task_state(tsk, state_value)		\
	do { (tsk)->state = (state_value); } while (0)
#define __set_current_state(state_value)			\
	do { current->state = (state_value); } while (0)
#define next_task(p)	list_entry((p)->tasks.next, struct task_struct, tasks)
#define prev_task(p)	list_entry((p)->tasks.prev, struct task_struct, tasks)
#define for_each_process(p) \
	for (p = &init_task ; (p = next_task(p)) != &init_task ; )

// include/linux/list.h
#define list_for_each(pos, head) \
	for (pos = (head)->next, prefetch(pos->next); pos != (head); \
        	pos = pos->next, prefetch(pos->next))

// kernel/fork.c
long do_fork(unsigned long clone_flags,
	      unsigned long stack_start,
	      struct pt_regs *regs,
	      unsigned long stack_size,
	      int __user *parent_tidptr,
	      int __user *child_tidptr)
{
	copy_process(clone_flags, stack_start, regs, stack_size, parent_tidptr, child_tidptr);
	//...
	{//vfork_done
		struct completion vfork;
		if (clone_flags & CLONE_VFORK) {
			p->vfork_done = &vfork;
			init_completion(&vfork);
		}
	}
	//...
	if (clone_flags & CLONE_VFORK) {
		wait_for_completion(&vfork);
		if (unlikely (current->ptrace & PT_TRACE_VFORK_DONE))
			ptrace_notify ((PTRACE_EVENT_VFORK_DONE << 8) | SIGTRAP);
	}	
	//...
	return pid;
}

struct task_struct *copy_process(unsigned long clone_flags,
				 unsigned long stack_start,
				 struct pt_regs *regs,
				 unsigned long stack_size,
				 int __user *parent_tidptr,
				 int __user *child_tidptr)
{
	//...
	struct task_struct *p = NULL;
	p = dup_task_struct(current);
	//...
	if (nr_threads >= max_threads)
		goto bad_fork_cleanup_count;
	//...
#ifdef CONFIG_PREEMPT
	p->thread_info->preempt_count = 1;
#endif
	p->did_exec = 0;
	p->state = TASK_UNINTERRUPTIBLE;
	copy_flags(clone_flags, p);
	p->pid = alloc_pidmap();
	//...
	copy_semundo(clone_flags, p);
	copy_signal(clone_flags, p);
	//copy_xxx(clone_flags, p);
	copy_namespace(clone_flags, p);
	copy_thread(0, clone_flags, stack_start, stack_size, p, regs);
	//...
	local_irq_disable();
     	p->time_slice = (current->time_slice + 1) >> 1;
     	p->first_time_slice = 1;
	current->time_slice >>= 1;
	local_irq_enable();

	return p;
}

// arch/um/include/kern.h
extern int clone(int (*proc)(void *), void *sp, int flags, void *data);

//  arch/i386/kernel/process.c
int kernel_thread(int (*fn)(void *), void * arg, unsigned long flags)
{
	struct pt_regs regs;
	//...
	/* Ok, create the new process.. */
	return do_fork(flags | CLONE_VM | CLONE_UNTRACED, 0, &regs, 0, NULL, NULL);
}

// kernel/exit.c
asmlinkage long sys_exit(int error_code)
{
	do_exit((error_code&0xff)<<8);
}

asmlinkage long sys_waitpid(pid_t pid,unsigned int * stat_addr, int options)
{
	return sys_wait4(pid, stat_addr, options, NULL);
}

NORET_TYPE void do_exit(long code)
{
	//...
	__exit_mm(tsk);
	exit_sem(tsk);
	__exit_files(tsk);
	__exit_fs(tsk);
	exit_namespace(tsk);
	exit_itimers(tsk);
	exit_thread();
	//...
	tsk->exit_code = code;
	exit_notify(tsk);
	schedule();
}

static void exit_notify(struct task_struct *tsk)
{
	//...
	if (state == TASK_DEAD)
		release_task(tsk);
}

void release_task(struct task_struct * p)
{
	//...
	atomic_dec(&p->user->processes);
	proc_dentry = proc_pid_unhash(p);
	//...
	put_task_struct(p);
}

asmlinkage long sys_wait4(pid_t pid,unsigned int * stat_addr, int options, struct rusage * ru)
{
	//...
}

static inline void forget_original_parent(struct task_struct * father)
{
	//...
}

// kernel/sched.c
#define cpu_rq(cpu)		(&per_cpu(runqueues, (cpu)))
#define this_rq()		(&__get_cpu_var(runqueues))
#define task_rq(p)		cpu_rq(task_cpu(p))
#define cpu_curr(cpu)		(cpu_rq(cpu)->curr)

static inline runqueue_t *task_rq_lock(task_t *p, unsigned long *flags)
{
	struct runqueue *rq;

repeat_lock_task:
	local_irq_save(*flags);
	rq = task_rq(p);
	spin_lock(&rq->lock);
	if (unlikely(rq != task_rq(p))) {
		spin_unlock_irqrestore(&rq->lock, *flags);
		goto repeat_lock_task;
	}
	return rq;
}

static inline void task_rq_unlock(runqueue_t *rq, unsigned long *flags)
{
	spin_unlock_irqrestore(&rq->lock, *flags);
}

static inline runqueue_t *this_rq_lock(void)
{
	runqueue_t *rq;

	local_irq_disable();
	rq = this_rq();
	spin_lock(&rq->lock);

	return rq;
}

static inline void rq_unlock(runqueue_t *rq)
{
	spin_unlock_irq(&rq->lock);
}

static inline void double_rq_lock(runqueue_t *rq1, runqueue_t *rq2)
{
	if (rq1 == rq2)
		spin_lock(&rq1->lock);
	else {
		if (rq1 < rq2) {
			spin_lock(&rq1->lock);
			spin_lock(&rq2->lock);
		} else {
			spin_lock(&rq2->lock);
			spin_lock(&rq1->lock);
		}
	}
}

static inline void double_rq_unlock(runqueue_t *rq1, runqueue_t *rq2)
{
	spin_unlock(&rq1->lock);
	if (rq1 != rq2)
		spin_unlock(&rq2->lock);
}

static inline void resched_task(task_t *p)
{
#ifdef CONFIG_SMP
	preempt_disable();
	if (/* balabala */ && (task_cpu(p) != smp_processor_id()))
		smp_send_reschedule(task_cpu(p));
	preempt_enable();
#else
	set_tsk_need_resched(p);
#endif
}

asmlinkage void schedule(void)
{
	//...
	array = rq->active;
	if (unlikely(!array->nr_active)) {
		/*
		 * Switch the active and expired arrays.
		 */
		rq->active = rq->expired;
		rq->expired = array;
		array = rq->active;
		rq->expired_timestamp = 0;
	}

	idx = sched_find_first_bit(array->bitmap);
	queue = array->queue + idx;
	next = list_entry(queue->next, task_t, run_list);
	//...
	if (likely(prev != next)) {
		next->timestamp = now;
		rq->nr_switches++;
		rq->curr = next;

		prepare_arch_switch(rq, next);
		prev = context_switch(rq, prev, next);
		barrier();

		finish_task_switch(prev);
	}
	//...
}

void scheduler_tick(int user_ticks, int sys_ticks)
{
	//...
	if (p->array != rq->active) {
		set_tsk_need_resched(p);
		goto out;
	}
	//...
	if (!--p->time_slice) {
		if (!TASK_INTERACTIVE(p) || EXPIRED_STARVING(rq)) {
			enqueue_task(p, rq->expired);
		} else
			enqueue_task(p, rq->active);
	} else {
		/* Prevent a too long timeslice allowing a task to monopolize
		 * the CPU. We do this by splitting up the timeslice into smaller pieces.
		 * */
	}
}

static inline task_t * context_switch(runqueue_t *rq, task_t *prev, task_t *next)
{
	//...
	switch_to(prev, next, prev);
	return prev;
}

// include/linux/interrupt.h
struct irqaction {
	irqreturn_t (*handler)(int, void *, struct pt_regs *);
	unsigned long flags;
	unsigned long mask;
	const char *name;
	void *dev_id;
	struct irqaction *next;
};

extern int request_irq(unsigned int,
		       irqreturn_t (*handler)(int, void *, struct pt_regs *),
		       unsigned long, const char *, void *);
extern void free_irq(unsigned int, void *);

// kernel/softirq.c
asmlinkage void do_softirq(void)
{
	//balabala see aslo in Linux Kernel Development v1 p71
}

void open_softirq(int nr, void (*action)(struct softirq_action*), void *data)
{
	softirq_vec[nr].data = data;
	softirq_vec[nr].action = action;
}

void __tasklet_schedule(struct tasklet_struct *t)
{
	if (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
	{
		unsigned long flags;
		local_irq_save(flags);
		t->next = __get_cpu_var(tasklet_vec).list;
		__get_cpu_var(tasklet_vec).list = t;
		raise_softirq_irqoff(TASKLET_SOFTIRQ);
		local_irq_restore(flags);
	}
}

static void tasklet_action(struct softirq_action *a)
{
	struct tasklet_struct *list;

	local_irq_disable();
	list = __get_cpu_var(tasklet_vec).list;
	__get_cpu_var(tasklet_vec).list = NULL;
	local_irq_enable();

	while (list) {
		struct tasklet_struct *t = list;

		list = list->next;

		if (tasklet_trylock(t)) {
			if (!atomic_read(&t->count)) {
				if (!test_and_clear_bit(TASKLET_STATE_SCHED, &t->state))
					BUG();
				t->func(t->data);
				tasklet_unlock(t);
				continue;
			}
			tasklet_unlock(t);
		}

		local_irq_disable();
		t->next = __get_cpu_var(tasklet_vec).list;
		__get_cpu_var(tasklet_vec).list = t;
		__raise_softirq_irqoff(TASKLET_SOFTIRQ);
		local_irq_enable();
	}
}

void tasklet_init(struct tasklet_struct *t,
		  void (*func)(unsigned long), unsigned long data)
{
	t->next = NULL;
	t->state = 0;
	atomic_set(&t->count, 0);
	t->func = func;
	t->data = data;
}

static int ksoftirqd(void * __bind_cpu)
{
	daemonize("ksoftirqd/%d", (int) (long) __bind_cpu);
	set_user_nice(current, 19);

	__set_current_state(TASK_INTERRUPTIBLE);
	mb();
	__get_cpu_var(ksoftirqd) = current;

	for (;;) {
		if (!local_softirq_pending())
			schedule();
		__set_current_state(TASK_RUNNING);
		while (local_softirq_pending()) {
			do_softirq();
			if(need_resched())
				schedule();
		}
		__set_current_state(TASK_INTERRUPTIBLE);
	}
}

// kernel/workqueue.c
static inline void run_workqueue(struct cpu_workqueue_struct *cwq)
{
	unsigned long flags;
	spin_lock_irqsave(&cwq->lock, flags);
	//balabla see alse in LKD p82
	spin_unlock_irqrestore(&cwq->lock, flags);
}

// include/asm-ppc/highmem.h
static inline void *kmap(struct page *page)
{
	might_sleep();
	if (page < highmem_start_page)
		return page_address(page);
	return kmap_high(page);
}

static inline void kunmap(struct page *page)
{
	if (in_interrupt())
		BUG();
	if (page < highmem_start_page)
		return;
	kunmap_high(page);
}