#ifndef __F1_SCORE_H__
#define __F1_SCORE_H__

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

class F1ClassTable
{
    public:
        int n;
        float TP;
        float FP;
        float FN;
        float f1;

        F1ClassTable();
};

class F1ClassManager
{
    private:
        std::vector<F1ClassTable*> class_vector;
        int number_cluster;

    public:

        F1ClassManager(int number_cluster);

        void calculateTP_FP_FN (int real_label, int prediction_label);

        float calculateMacroF1 ();

};

float calculateF1Score (std::vector<int> test_label_data, std::vector<int> prediction, int number_cluster);


#endif