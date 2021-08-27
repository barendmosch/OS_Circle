#ifndef _ledblink_h
#define _ledblink_h

#include <circle/sched/task.h>
#include <circle/gpiopin.h>
#include <circle/screen.h>

class CLEDBlink : public CTask {
	public:
		CLEDBlink (unsigned int n_task_id, CGPIOPin *pOutLED, CScreenDevice *pScreen);
		~CLEDBlink (void);

		void Run (void);

	private:
		unsigned int 		task_id;
		CGPIOPin		*m_pOutLED;
                CScreenDevice           *m_pScreen;
};

#endif