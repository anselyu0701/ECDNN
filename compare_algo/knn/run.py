import subprocess
import time
import csv
import os

run_times = 1
dataset = ['iris', 'wine', 'breastcancer', 'ecoli', 'satimage', 'abalone']
number_cluster = ['3', '3', '2', '8', '7', '3']
# dataset = ['iris']
# number_cluster = ['3']

def run_script(arg_1, kth, idx):
    print(["./knn", arg_1, kth, number_cluster])
    process = subprocess.Popen(["./knn", arg_1, str(kth), number_cluster[idx]])
    process.wait()
   
def running(dataset_name, kth, idx):
    exec_time = []    
    arg_1 = "./dataset/" + dataset_name + "/"
    # print(arg_1)
    with open (arg_1 + "Result.txt", "w") as File:
        pass
    run_script (arg_1, kth, idx)

def calculate_f1(dataset_name):
    average_f1 = 0
    arg_1 = "./dataset/" + dataset_name + "/"
    try:
        with open(arg_1 + "Result.txt", 'r') as file:
            for line in file:
                # 將每一行分割成單詞（以空格分隔）
                words = line.strip().split()
                if words:
                    # 將第一個單詞轉換為整數並相加到總和中
                    average_f1 += float(words[0])
                    
    except FileNotFoundError:
        print (os.path.exists(arg_1+ "Result.txt"))
        print("檔案不存在")
            
    average_f1 /= 100.0
    print('Average F1 Score: ', average_f1)
    return average_f1
        

def writeFile (dataset_name, kth, ave_f1):
    with open("./dataset/" + dataset_name + "/k_result.csv", 'a', newline='') as csv_file:
        # 創建CSV寫入器
        csv_writer = csv.writer(csv_file)        
        data = [str(kth), str(ave_f1)]
        csv_writer.writerow(data)

        
            

if __name__ == "__main__":
    ave_f1 = 0.0
    idx = 0

    print('Start')
    for dataset_name in dataset:
        with open("./dataset/" + dataset_name + "/k_result.csv", 'w', newline='') as csv_file:
            csv_writer = csv.writer(csv_file)
            data = ['k', 'F1 Score']
            csv_writer.writerow(data)  
        
        for kth in range (4, 26, 1):
            running(dataset_name, kth, idx)    
            ave_f1 = calculate_f1(dataset_name)        
            writeFile(dataset_name, kth, ave_f1)
        idx += 1

    print('Finish')
