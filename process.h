#ifndef PROCESS_H
#define PROCESS_H
typedef enum{ready,running,terminated}state;
typedef struct {
    unsigned int process_id;
    state process_state;
    unsigned int bursttime;
    unsigned int reamaing_time;
    unsigned int arrival_time;
    unsigned int periority;
    int serve_time;
    int finish_time;
}process;

#endif // PROCESS_H
