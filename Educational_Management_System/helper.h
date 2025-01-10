#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <iostream>
#include<bits/stdc++.h>
#include<string>
#include <algorithm>
#include <cmath>
#include <utility>
#include <memory>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

#include "assignment.h"
#include "student.h"
#include "course.h"
#include "doctor.h"
#include "assignment_solution.h"

#include "user_flow_controller.h"
#include "student_flow_controller.h"
#include "doctor_flow_controller.h"

namespace Faculty {

struct Helper {
    static double Probability();
    /***
    * Read an integer from the stream, and check validations.
    * @param low: the min expected value
    * @param high: the max expected value
    * @return int: the validated value
    ***/
    static int ReadInt(int low, int high);
    /***
    * Convert integer to string, and append zeros to reach the given length
    ***/
    static string ToString(int value, int length);
    static int RunMenu(vector<string> &menu);

    // Declare/implement template methods here
    /***
    * Return random subset of a given vector
    ***/
    template<typename T>
    static vector<T> GetRandomSubset(const vector<T> &vec)
    {
        vector<T> retVec;
        for(auto element : vec)
        {
            /*store element when probability is over 70%*/
            if(1.0 * rand() /RAND_MAX >0.7)
            {
                retVec.push_back(element);
            }
            return retVec;
        }
    }

    /***
    * Return a random subset of a given vector with minimum length
    ***/
    template<typename T>
    static vector<T> GetRandomSubset(const vector<T> &vec, int min_length)
    {
        assert((int)vec.size() >= min_length);
        vector<int> indices;
        for(size_t i =0; i<vec.size(); ++i)
        {
            indices.push_back(i); // indices 0:n-1
        }
        //random sorting
        std::random_shuffle(indices.begin(),indices.end());

        vector<T> retVec;
        for(int i=0; i<min_length; ++i)
        {
            retVec.push_back(vec[indices[i]]);
        }
        return retVec;
    }

    template<typename T>
    static void RemoveElement(vector<shared_ptr<T>> &vec, shared_ptr<T> element)
    {
        for(int i = 0; i < (int) vec.size(); ++i)
        {
            if(vec[i]==element)
            {
                vec.erase(vec.begin()+i);
                --i;
            }
        }
    }

};

}

#endif // HELPER_H_INCLUDED
