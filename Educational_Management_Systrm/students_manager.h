#ifndef STUDENTS_MANAGER_H_INCLUDED
#define STUDENTS_MANAGER_H_INCLUDED


namespace Faculty {

struct StudentsManager {
    shared_ptr<Student> GetUser(string user_name, string password);
    shared_ptr<Student> GetStudent(string student_id);

    int GetTotalSystemStudents();
    void AddDummyData();
    void ShowStudents();

    vector<shared_ptr<Student>> students_list_;

};

extern shared_ptr<StudentsManager> gStudentsManager;
}

#endif // STUDENTS_MANAGER_H_INCLUDED
