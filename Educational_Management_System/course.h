#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED

namespace Faculty {

struct Course{
    string code_;
    string name_;

    shared_ptr <Doctor> doctor_;
    vector <shared_ptr<Assignment>> assignments_;
    vector <shared_ptr<Student>> registered_students_;

    /***
    *Return sum of assignments grades
    ***/
    int GetTotalAssignmentsGradesSum();

    /***
    *Return num of registered students
    ***/
    int GetTotalRegisteredStudentsNum();

};

}

#endif // COURSE_H_INCLUDED
