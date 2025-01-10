#ifndef DOCTORS_MANAGER_H_INCLUDED
#define DOCTORS_MANAGER_H_INCLUDED

namespace Faculty {

struct DoctorsManager{
    shared_ptr<Doctor> GetUser(string user_name, string password);

    int GetTotalSystemDoctors();
    void AddDummyData();
    void ShowDoctors();

    vector<shared_ptr<Doctor>> doctors_list_;
};

extern shared_ptr<DoctorsManager> gDoctorsManager;

}

#endif // CDOCTORS_MANAGER_H_INCLUDED
