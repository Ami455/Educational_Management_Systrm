

#include "helper.h"
#include "student.h"

namespace Faculty {


vector<tuple<string, int, float,int>> Student::ComputeGradesStatics()
{
    vector<tuple<string, int, float,int>> return_vector;
    /***
    * create 3 maps to map from course code to:
    * 1.Total number of assignments of the course.
    * 2.Total grades of the student of all assignments.
    * 3.Sum of max grades of all assignments.
    ***/
    map<string, int> courseCode_numberOfAssignments;
    map<string, float> courseCode_studentGrades;
    map<string, int> courseCode_totalGrades;

    for(auto solution : assignments_solutions_)
    {
        string code = solution->assignment_->course_->code_;
        courseCode_numberOfAssignments[code]++;
        courseCode_totalGrades[code] += solution->assignment_->max_grade_;
        if(solution->is_graded_)
        {
            courseCode_studentGrades[code]+= solution->grade_;
        }
    }

    for (auto courseCode : courseCode_numberOfAssignments)
    {
        string code = courseCode.first;
        tuple<string, int, float,int> t(code,courseCode_numberOfAssignments[code],courseCode_studentGrades[code],courseCode_totalGrades[code]);
        return_vector.push_back(t);
    }
    return return_vector;
}


bool Student::IsMyDataCorrect(string user_name, string password)
{
    return (user_name_ == user_name) && (password_ == password);
}


shared_ptr<AssignmentSolution> Student:: GetAssignmentSolution(shared_ptr<Assignment> assignment)
{
    for(auto solution : assignments_solutions_)
    {
        if(assignment==solution->assignment_) /*compare memory addresses*/
            return solution;
    }
    return nullptr;
}


int Student::StudentSubmissionsForCourse(shared_ptr<Course> course)
{
    bool found=false;
    int submissionsNum=0;
    //check if registered in course
    for(auto course_p : registered_courses_)
    {
        if (course_p == course)
        {
            found=true;
            break;
        }
    }
    if(!found)
    {
        return submissionsNum;
    }

    /**is course ass has solution**/
    for(auto assignment : course->assignments_)
    {
        shared_ptr<AssignmentSolution> solution=GetAssignmentSolution(assignment);
       if(solution != nullptr)
       {
           submissionsNum++;
       }
    }
    return submissionsNum;
}

}
