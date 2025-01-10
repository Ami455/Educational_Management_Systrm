#include "helper.h"

namespace Faculty {


int Course::GetTotalAssignmentsGradesSum()
{
    int sum=0;
    for(auto assignment: assignments_)
    {
        for(auto solution : assignment->assignment_solutions_)
        {
            sum+=solution->grade_;
        }
    }
    return sum;
}

int Course::GetTotalRegisteredStudentsNum()
{
    return registered_students_.size();
}

}
