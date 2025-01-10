#ifndef ASSIGNMENT_H_INCLUDED
#define ASSIGNMENT_H_INCLUDED



namespace Faculty {

struct Student;
struct Course;
struct Doctor;
struct AssignmentSolution;

struct Assignment{
string content_;
int max_grade_;
shared_ptr<Course> course_;
vector<shared_ptr<AssignmentSolution>> assignment_solutions_;

};
}

#endif // ASSIGNMENT_H_INCLUDED
