

#include "helper.h"
#include "students_manager.h"

namespace Faculty {

shared_ptr<StudentsManager> gStudentsManager(new StudentsManager());

shared_ptr<Student> StudentsManager::GetUser(string user_name, string password)
{
    for(auto student : students_list_)
    {
        if(student->IsMyDataCorrect(user_name,password))
        {
            return student;
        }
    }
    return nullptr;
}
shared_ptr<Student> StudentsManager::GetStudent(string student_id)
{
    for(auto student : students_list_)
    {
        if(student->id_ == student_id)
        {
            return student;
        }
    }
    return nullptr;
}

int StudentsManager::GetTotalSystemStudents()
{
    return students_list_.size();
}
void StudentsManager::AddDummyData()
{
    vector <string> names = { "Ali", "Mostafa", "Hani", "Mohamed", "Ashraf", "Samy", "Morad", "Sayed", "Hussien" };
    for(int i=1; i<=20; i++)
    {
        shared_ptr<Student> student (new Student());

        student->user_name_ = "s" + Helper::ToString(i, 3);
        student->password_ = "sp" + Helper::ToString(i, 3);
        student->full_name_ = names[rand()%(names.size())] + " " + names[rand()%(names.size())];
        student->email_ = Helper::ToString(i, 3) + "@gmail.com";
        student->id_ = Helper::ToString(i, 3) +  Helper::ToString((i * 12345) %10000, 5);

        students_list_.push_back(student);

    }

}
void StudentsManager::ShowStudents()
{
    for(auto student : students_list_)
    {
        printf("Student %-15s with ID %s registered in %d courses.\n",student->full_name_.c_str(),student->id_.c_str(), (int)student->registered_courses_.size());
        if(student->registered_courses_.size() > 0)
        {
            cout<<("\tCourses list:");
            for(auto course : student->registered_courses_)
            {
                cout<< " " << course->code_;
            }
        }
        cout<<"\n";
    }
    cout<<"\n*******************************\n";
}


}
