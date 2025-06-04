#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep()
#include <stdbool.h>

#define POOL_SIZE 4        // Number of worker threads
#define QUEUE_CAPACITY 10  // Max number of tasks in the queue
#define NUM_TASKS 20       // Total number of tasks to submit

// --- Task Structure ---
typedef struct {
    int id;
    // In a real app, this could be a function pointer and arguments,
    // or data needed for processing.
} Task;

// --- Task Queue (Simple Circular Buffer) ---
typedef struct {
    Task tasks[QUEUE_CAPACITY];
    int head;
    int tail;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty; // Signaled when a task is added
    pthread_cond_t not_full;  // Signaled when a task is removed (optional for bounded queue)
} TaskQueue;

// --- Thread Pool Structure ---
typedef struct {
    pthread_t threads[POOL_SIZE];
    TaskQueue task_queue;
    bool shutdown; // Flag to signal threads to exit
} ThreadPool;

// --- Function Prototypes ---
void *worker_thread_function(void *arg);
bool task_queue_init(TaskQueue *queue);
void task_queue_destroy(TaskQueue *queue);
bool task_queue_add(TaskQueue *queue, Task task);
bool task_queue_get(TaskQueue *queue, Task *task);
bool thread_pool_init(ThreadPool *pool);
void thread_pool_add_task(ThreadPool *pool, Task task);
void thread_pool_shutdown(ThreadPool *pool);
void process_task(Task task, int thread_id); // Function to simulate work

// --- Worker Thread ---
void *worker_thread_function(void *arg) {
    ThreadPool *pool = (ThreadPool *)arg;
    TaskQueue *queue = &pool->task_queue;
    int thread_id = (int)(long)pthread_self(); // Simple way to get a unique-ish ID for demo

    printf("Worker thread %lu started.\n", (unsigned long)pthread_self());

    while (true) {
        Task task;

        // --- CRITICAL SECTION START (Accessing Queue) ---
        pthread_mutex_lock(&queue->mutex);

        // Wait condition: Wait if queue is empty AND shutdown is not requested
        // The loop handles spurious wakeups.
        while (queue->count == 0 && !pool->shutdown) {
            printf("Thread %lu waiting as queue is empty...\n", (unsigned long)pthread_self());
            // pthread_cond_wait atomically unlocks the mutex and waits.
            // When woken, it re-acquires the mutex before returning.
            pthread_cond_wait(&queue->not_empty, &queue->mutex);
        }

        // If shutdown is requested and queue is empty, exit the loop
        if (pool->shutdown && queue->count == 0) {
            pthread_mutex_unlock(&queue->mutex);
            break; // Exit the worker loop
        }

        // Get a task from the queue
        if (!task_queue_get(queue, &task)) {
            // Should not happen if logic is correct, but good practice
            fprintf(stderr, "Error: Failed to get task when queue should not be empty.\n");
            pthread_mutex_unlock(&queue->mutex);
            continue; // Or handle error appropriately
        }

        // Signal that the queue might not be full anymore (if we had bounded adding)
        // pthread_cond_signal(&queue->not_full); // Uncomment if task_queue_add waits on not_full

        // --- CRITICAL SECTION END (Accessing Queue) ---
        pthread_mutex_unlock(&queue->mutex);

        // Process the task (outside the critical section)
        process_task(task, thread_id);
    }

    printf("Worker thread %lu exiting.\n", (unsigned long)pthread_self());
    return NULL;
}

// --- Task Processing Simulation ---
void process_task(Task task, int thread_id) {
    printf("Thread %lu processing task %d...\n", (unsigned long)pthread_self(), task.id);
    // Simulate work - replace with actual task processing
    sleep(1); // Simulate 1 second of work
    printf("Thread %lu finished task %d.\n", (unsigned long)pthread_self(), task.id);
}

// --- Task Queue Implementation ---
bool task_queue_init(TaskQueue *queue) {
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    if (pthread_mutex_init(&queue->mutex, NULL) != 0) {
        perror("Mutex init failed");
        return false;
    }
    if (pthread_cond_init(&queue->not_empty, NULL) != 0) {
        perror("Cond 'not_empty' init failed");
        pthread_mutex_destroy(&queue->mutex); // Clean up mutex
        return false;
    }
    // if (pthread_cond_init(&queue->not_full, NULL) != 0) { // Optional
    //     perror("Cond 'not_full' init failed");
    //     pthread_mutex_destroy(&queue->mutex);
    //     pthread_cond_destroy(&queue->not_empty);
    //     return false;
    // }
    return true;
}

void task_queue_destroy(TaskQueue *queue) {
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->not_empty);
    // pthread_cond_destroy(&queue->not_full); // Optional
}

// Adds a task. Blocks if queue is full (if not_full condition is used).
// Simplified version: assumes queue won't overfill in this demo.
bool task_queue_add(TaskQueue *queue, Task task) {
    pthread_mutex_lock(&queue->mutex);

    // Optional: Wait if queue is full (for a strictly bounded queue)
    // while (queue->count == QUEUE_CAPACITY) {
    //     printf("Queue full, waiting...\n");
    //     pthread_cond_wait(&queue->not_full, &queue->mutex);
    // }

    if (queue->count >= QUEUE_CAPACITY) {
        fprintf(stderr, "Error: Task queue is full! Task %d dropped.\n", task.id);
        pthread_mutex_unlock(&queue->mutex);
        return false; // Indicate failure (or block using the wait above)
    }

    queue->tasks[queue->tail] = task;
    queue->tail = (queue->tail + 1) % QUEUE_CAPACITY;
    queue->count++;

    // Signal *one* waiting worker thread that the queue is not empty
    pthread_cond_signal(&queue->not_empty);

    pthread_mutex_unlock(&queue->mutex);
    return true;
}

// Gets a task. Assumes mutex is already locked by caller.
bool task_queue_get(TaskQueue *queue, Task *task) {
    if (queue->count == 0) {
        return false; // Should be checked by caller with the wait condition
    }

    *task = queue->tasks[queue->head];
    queue->head = (queue->head + 1) % QUEUE_CAPACITY;
    queue->count--;
    return true;
}


// --- Thread Pool Implementation ---
bool thread_pool_init(ThreadPool *pool) {
    pool->shutdown = false;
    if (!task_queue_init(&pool->task_queue)) {
        return false;
    }

    for (int i = 0; i < POOL_SIZE; ++i) {
        if (pthread_create(&pool->threads[i], NULL, worker_thread_function, pool) != 0) {
            perror("Thread creation failed");
            // Cleanup already created threads and queue before failing
            pool->shutdown = true; // Signal any created threads to exit
            pthread_cond_broadcast(&pool->task_queue.not_empty); // Wake them up
            for(int j = 0; j < i; ++j) {
                pthread_join(pool->threads[j], NULL);
            }
            task_queue_destroy(&pool->task_queue);
            return false;
        }
    }
    printf("Thread pool initialized with %d threads.\n", POOL_SIZE);
    return true;
}

void thread_pool_add_task(ThreadPool *pool, Task task) {
    if (!task_queue_add(&pool->task_queue, task)) {
        // Handle task submission failure if necessary
        fprintf(stderr, "Failed to add task %d to queue.\n", task.id);
    }
}

void thread_pool_shutdown(ThreadPool *pool) {
    printf("Shutting down thread pool...\n");

    // --- CRITICAL SECTION START (Accessing shutdown flag and signaling) ---
    pthread_mutex_lock(&pool->task_queue.mutex);
    pool->shutdown = true;
    // Wake up all waiting threads so they can check the shutdown flag
    pthread_cond_broadcast(&pool->task_queue.not_empty);
    // If using not_full condition, broadcast on it too in case threads are waiting there
    // pthread_cond_broadcast(&pool->task_queue.not_full);
    pthread_mutex_unlock(&pool->task_queue.mutex);
    // --- CRITICAL SECTION END ---


    // Wait for all worker threads to finish
    for (int i = 0; i < POOL_SIZE; ++i) {
        if (pthread_join(pool->threads[i], NULL) != 0) {
            perror("Failed to join thread");
            // Continue trying to join others
        }
         printf("Joined thread %d.\n", i);
    }

    // Cleanup resources
    task_queue_destroy(&pool->task_queue);
    printf("Thread pool shutdown complete.\n");
}


// --- Main Function ---
int main() {
    ThreadPool pool;

    // Initialize the thread pool
    if (!thread_pool_init(&pool)) {
        fprintf(stderr, "Failed to initialize thread pool.\n");
        return 1;
    }

    // Submit tasks to the pool
    printf("Submitting %d tasks...\n", NUM_TASKS);
    for (int i = 0; i < NUM_TASKS; ++i) {
        Task t = { .id = i };
        thread_pool_add_task(&pool, t);
        // Optional: Add a small delay to simulate tasks arriving over time
        // usleep(10000); // 10ms
    }
    printf("All tasks submitted.\n");

    // Give threads some time to process before initiating shutdown
    // In a real app, shutdown might be triggered by an event or signal
    printf("Waiting a bit before shutdown...\n");
    sleep(5); // Wait for 5 seconds

    // Shutdown the pool and wait for threads to finish
    thread_pool_shutdown(&pool);

    return 0;
}
