#include "kernel.h"
#include <circle/startup.h>

/* The main loop, this is not altered in any way shape or form */
int main (void) {
        CKernel Kernel;
        if (!Kernel.Initialize ()) {
                halt ();
                return EXIT_HALT;
        }

        TShutdownMode ShutdownMode = Kernel.Run();

        switch (ShutdownMode) {
            case ShutdownReboot:
                    reboot ();
                    return EXIT_REBOOT;

            case ShutdownHalt:
            default:
                    halt ();
                    return EXIT_HALT;
        }
}