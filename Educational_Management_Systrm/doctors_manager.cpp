

#include "helper.h"
#include "doctors_manager.h"

namespace Faculty {

shared_ptr<DoctorsManager> gDoctorsManager(new DoctorsManager());

shared_ptr<Doctor> DoctorsManager::GetUser(string user_name, string password)
{
    for(auto doctor : doctors_list_)
    {
        if(doctor->user_name_ ==user_name && doctor->password_ == password)
        {
            return doctor;
        }
    }

    return nullptr;
}

int DoctorsManager::GetTotalSystemDoctors()
{
    return doctors_list_.size();
}
void DoctorsManager::AddDummyData()
{
    vector <string> names = { "Ali", "Mostafa", "Hani", "Mohamed", "Ashraf", "Samy", "Morad", "Sayed", "Hussien" };
    for(int i=1; i<= (int)names.size() ; i++)
    {
        shared_ptr<Doctor> doctor (new Doctor());

        doctor->user_name_ = "d" + Helper::ToString(i, 3);
        doctor->password_ = "dp" + Helper::ToString(i, 3);
        doctor->name_ = names[i-1];

        doctors_list_.push_back(doctor);

    }

    /*Teaching courses will be filled at CoursesManager::AddDummyDataRelationships*/
}
void DoctorsManager::ShowDoctors()
{
    for(auto doctor : doctors_list_)
    {
        cout << "Doctor " << doctor->name_ << " is teaching " << doctor->teaching_courses_.size() << " courses.";
        if (doctor->teaching_courses_.size()>0)
        {
            cout<<"\tCourses codes:";
            for(auto course : doctor->teaching_courses_)
            {
                cout<<" "<<course->code_;
            }
        }
        cout<<"\n";
    }
    cout<<"\n*******************************\n";

}

}
