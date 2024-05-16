/**
 * @author  Anselyu <m11202117@mail.ntust.edu.tw>
 * @brief   Calculate the Macro-F1 Score
 * @see     https://blog.csdn.net/qq_43190189/article/details/105778058
 *          Macro-F1 Score
*/

#include "f1_score.h"

F1ClassTable::F1ClassTable ()
{
    this->n  = 0;
    this->TP = 0;
    this->FP = 0;
    this->FN = 0;
}

/*  F1ClassManager function */
F1ClassManager::F1ClassManager (int number_cluster)
{
    this->number_cluster = number_cluster;
    for (int idx = 0; idx < number_cluster; idx++)
    {
        F1ClassTable* new_table = new F1ClassTable();
        this->class_vector.push_back(new_table);
    }
}

void F1ClassManager::calculateTP_FP_FN (int real_label, int prediction_label)
{
    if (real_label == prediction_label) // TP
    {
        class_vector[real_label]->TP++;
    }
    else // FP, FN
    {
        class_vector[prediction_label]->FP++; // FP
        class_vector[real_label]->FN++; // FN
    }
    class_vector[real_label]->n++;
}

float F1ClassManager::calculateMacroF1 ()
{
    float average_f1 = 0;
    for (int class_idx = 0; class_idx < number_cluster; class_idx++)
    {
        class_vector[class_idx]->f1 = 2*class_vector[class_idx]->TP / 
            (2*class_vector[class_idx]->TP + class_vector[class_idx]->FP + class_vector[class_idx]->FN);
        if (std::isnan(class_vector[class_idx]->f1))
        {
            // if denominator is 0
            class_vector[class_idx]->f1 = 0;
        }
        average_f1 += class_vector[class_idx]->f1;
        // std::cout<<"------------"<<std::endl;
        // std::cout << class_vector[class_idx]->precision << " " << class_vector[class_idx]->recall << " " << class_vector[class_idx]->f1 << " " << std::endl;
        // std::cout<<"------------"<<std::endl<<std::endl;
    }
    average_f1 /= number_cluster;
    return average_f1;
}

/*------------------------------------------------------------------*/



float calculateF1Score (std::vector<int> test_label_data, std::vector<int> prediction, int number_cluster)
{
    F1ClassManager *f1_classes = new F1ClassManager(number_cluster);
    float result;
    std::cout<< "Test Size: " << test_label_data.size()<<std::endl;
    std::cout<< "Prediction Size: " << prediction.size()<<std::endl;
    
    for (int label_idx = 0; label_idx < prediction.size(); label_idx++)
    {   
        f1_classes->calculateTP_FP_FN(test_label_data[label_idx%test_label_data.size()], prediction[label_idx]);
    }

    result = f1_classes->calculateMacroF1();

    std::cout << "Macro-F1 Score: " << result << std::endl;
    
    return result;
}