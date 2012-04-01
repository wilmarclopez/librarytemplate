#ifndef PROCESSEXECUTOR_H
#define PROCESSEXECUTOR_H
#include "Process.h"

/**
 * Process Executor class. This class managae the process object.
 */

class ProcessExecutor
{
    public:
        ProcessExecutor();
        /**
        *Process Executor constructor
        * @param poolSize an integer that sets the pool size
        */
        ProcessExecutor(int poolSize);
        virtual ~ProcessExecutor();

        /**
        *Method to execute the processing of the message
        * @param proc the  process to be executed
        */
        void submit (Process* proc) const;
    protected:
    private:
};

#endif // PROCESSEXECUTOR_H
