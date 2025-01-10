#ifndef COURSES_MANAGER_H_INCLUDED
#define COURSES_MANAGER_H_INCLUDED


namespace Faculty {

struct CoursesManager {
    shared_ptr<Course> AddCourse();
    void AddDummyData();
    void ShowCourses();

    /***
	 * There are circular relationships (course has students and students has course...we can't add all dummy data in same time).
	 * So we build them in a way that breaks the cycle...we also fix through that the dependent data
	 ***/
    void AddDummyDataRelationships();

    /***
    * Return compliment courses( all courses except the given ones).
    ***/
    vector<shared_ptr<Course>> GetUnregisteredCourses(vector<shared_ptr<Course>> registered_courses);

    vector<shared_ptr<Course>> courses_list_;

};

extern shared_ptr<CoursesManager> gCoursesManager;

}

#endif // COURSES_MANAGER_H_INCLUDED
