

#include "helper.h"
#include "courses_manager.h"
#include "students_manager.h"
#include "doctors_manager.h"

namespace Faculty {

shared_ptr<CoursesManager> gCoursesManager(new CoursesManager());

shared_ptr<Course> CoursesManager::AddCourse()
{
    shared_ptr<Course> course(new Course());
    cout<<"Enter course name: ";
    cin>>course->name_;

    cout<<"Enter course code: ";
    cin>>course->code_;

    courses_list_.push_back(course);
    return course;
}

void CoursesManager::AddDummyData()
{
    vector<string> names ={"Math 1", "Math 2", "Math 3", "Prog 1", "Prog 2", "Prog 3", "Stat 1", "Stat 2"};
    for(int i=0; i< (int)names.size(); ++i)
    {
        shared_ptr<Course> course (new Course());
        course->name_ = names[i];
        course->code_ = "CS"+ Helper::ToString(rand()%1000,3);
        courses_list_.push_back(course);
    }
}

void CoursesManager::ShowCourses()
{
    for(auto course : courses_list_)
    {
        cout<<"Course "<<left<<setw(5)<<course->name_
        <<"\tCode "<< course->code_<<" - taught by DR."
        <<course->doctor_->name_<<"\n";
        cout<<"\tRegistered students ID:";

        for(auto student : course->registered_students_)
        {
            cout<<" "<<student->id_;
        }
        cout<<"\n";
    }
        cout<<"\n*******************************\n";


}
void CoursesManager::AddDummyDataRelationships()
{
    for(auto course : courses_list_)
    {// Generate 75% of students per course
        int registered_students_p= gStudentsManager->students_list_.size() * 75.0 / 100.0;
        course->registered_students_= Helper::GetRandomSubset(gStudentsManager->students_list_,registered_students_p);
        course->doctor_ = Helper::GetRandomSubset(gDoctorsManager->doctors_list_,1)[0];

        //add random assignments
        for(int r= 1 + rand() % 5 ; r; r--)
        {
            //create ass and fill its data
            shared_ptr<Assignment> ass (new Assignment());
            course->assignments_.push_back(ass);
            ass->content_ = "Assign " + Helper::ToString(r,3);
            ass->max_grade_ = 10 +rand()%50;
            ass->course_ = course; //fix ass - course

            //some registered students assign solutions
            int registered_stu_p= gStudentsManager->students_list_.size() * 60.0 / 100.0;
            vector<shared_ptr<Student>> someRegesteredStudents = Helper::GetRandomSubset(course->registered_students_, registered_stu_p);

            for(auto student_p: someRegesteredStudents)
            {
                //create solution for the assignment for each student
                shared_ptr<AssignmentSolution> assign_sol(new AssignmentSolution());
                ass->assignment_solutions_.push_back(assign_sol); //fix assign - assign solution

                //fill assign sol data
                assign_sol->student_=student_p;
                assign_sol->answer_ = Helper::ToString(rand() % 10000, 4) + Helper::ToString(rand() % 10000, 4) + Helper::ToString(rand() % 10000, 4);
                assign_sol->assignment_=ass; //connect assign sol - ass
                assign_sol->doctor_comments_="No comments";
                if(Helper::Probability() > 0.5)
                {
                    assign_sol->is_graded_ = true;
                    assign_sol->grade_ = rand() % (1 + ass->max_grade_);


                }
                //fix student - assign sol
                assign_sol->student_->assignments_solutions_.push_back(assign_sol);
            }




        }


        //fix doctor courses data
        course->doctor_->teaching_courses_.push_back(course);
        for(auto student : course->registered_students_)
        {
            student->registered_courses_.push_back(course);
        }
    }
}


vector<shared_ptr<Course>> CoursesManager::GetUnregisteredCourses(vector<shared_ptr<Course>> registered_courses)
{
    vector<shared_ptr<Course>> complimentCourses;
    /*for each course in the courses list if the course is not in the given courses it is not registered so add it*/
    for(auto course : courses_list_)
    {
        bool isRegistered = false;
        for(auto registered : registered_courses)
        {
            if(course == registered)
            {
                isRegistered = true;
                break;
            }
        }
        if(!isRegistered)
        {
            complimentCourses.push_back(course);
        }
    }

    return complimentCourses;

}

}
