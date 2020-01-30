#ifndef JOB_STDINPUT_H_
#define JOB_STDINPUT_H_

#include "Job.h"

namespace cefpdf {
namespace job {

class StdInput : public Job
{

public:
    virtual void accept(CefRefPtr<Visitor> visitor) override {
        visitor->visit(this);
    }

private:
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(StdInput); //Fixed in 0.3.4a
};

} // namespace job
} // namespace cefpdf

#endif // JOB_STDINPUT_H_
