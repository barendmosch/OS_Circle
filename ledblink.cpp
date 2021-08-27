#include "ledblink.h"
#include <circle/sched/scheduler.h>
#include <circle/string.h>

#define FREQUENCY_DELAYS_IN_MS_2        200 // the task delay that the task must wait until continueing the led blink process
#define FREQUENCY_DELAYS_IN_MS_3        300
#define FREQUENCY_DELAYS_IN_MS_4        400 // 235

/* CLEDBlink task constructor. Take the task number, the output pin and screen as arguments */
CLEDBlink::CLEDBlink (unsigned int n_task_id, CGPIOPin *pOutLED, CScreenDevice *pScreen) 
	: task_id(n_task_id), m_pOutLED(pOutLED), m_pScreen (pScreen) {
}

CLEDBlink::~CLEDBlink (void) {
}

void CLEDBlink::Run (void) {
	/* Forever loop */
	while (1) {
		/* Define a message, for logging purposes, and a delay integer. The delay is used to let the LEDs blink with a different frequency */
		CString Message;
		unsigned int ms_delay = 0;

		/* Check which task is currenly executing and set the delay variable to the corresponding task */
		switch (task_id) {
			case 1:
				Message.Format("#%u   ", task_id);
				ms_delay = FREQUENCY_DELAYS_IN_MS_2;
				break;
			case 2:
				Message.Format("#%u   ", task_id);
				ms_delay = FREQUENCY_DELAYS_IN_MS_3;
				break;
			case 3:
				Message.Format("#%u   ", task_id);
				ms_delay = FREQUENCY_DELAYS_IN_MS_4;
				break;
		}
		/* This returns 1, meaning that we created valid tasks */
		// bool is_task = CScheduler::Get()->IsValidTask(CScheduler::Get()->GetCurrentTask()); 

		/* returns 1, meaning that the schedular is in the system and is available */
		// bool sched_available = CScheduler::Get()->IsActive(); 

		Message.Append("\n");
		m_pScreen->Write(Message, Message.GetLength());

		/* Blink the LED that corresponds with the tasks that is currently executing */
		m_pOutLED->Invert();
		/* Delay the task */
		CScheduler::Get()->MsSleep(ms_delay);
	}
}
