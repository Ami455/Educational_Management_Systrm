#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <tuple>
#include <map>

namespace Faculty {

struct Student {
    string id_;
    string user_name_;
    string password_;
    string full_name_;
    string email_;

    /***
    * Return vector of student grades.
    * vector length is the number of registered courses, each element in vector is a tuple.
    * the tuple consists of 4 values: course code, number of assignments, sum of student grades, total assignment grades.
    ***/
    vector<tuple<string, int, float,int>>ComputeGradesStatics();

    /***
    * check if the user name and password are correct
    ***/
    bool IsMyDataCorrect(string user_name, string password);

    /***
    * check if the given assignment has a solution and return it.
    ***/
    shared_ptr<AssignmentSolution> GetAssignmentSolution(shared_ptr<Assignment> assignment);

    /**calculate how many submitted ass for one course**/
    int StudentSubmissionsForCourse(shared_ptr<Course> course);

    vector <shared_ptr<Course>> registered_courses_;
    vector <shared_ptr<AssignmentSolution>> assignments_solutions_;

};

}

#endif // STUDENT_H_INCLUDED
