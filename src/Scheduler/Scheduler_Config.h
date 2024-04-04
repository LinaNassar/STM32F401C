/***********************************************************************************************/
/* File Name:	Scheduler_Config.h                                                             */
/* Module	: 	Scheduler						                                               */
/* Layer	:	Scheduler										                               */
/* AUTHOR   :   Lina Nassar                                                                    */
/***********************************************************************************************/

#ifndef SCHEDULER_CONFIG_H
#define SCHEDULER_CONFIG_H


/*Configure the tick rime of the scheduler in Milliseconds */
#define Sched_TickTime_Ms       2000


/*Add the names of the required runnables to the list before Runnables_Num*/
typedef enum
{
    //Run_1, /*Example*/
    Traffic_Light,
    _Runnables_Num,

}RunnableList_t;

#endif