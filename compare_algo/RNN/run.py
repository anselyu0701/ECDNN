import subprocess
import time
import csv
import os

run_times = 1
dataset = ['iris', 'wine', 'breastcancer', 'ecoli', 'satimage', 'abalone']
number_cluster = ['3', '3', '2', '8', '7', '3']

def run_script(arg_1, r, idx):
    print(["./RNN", arg_1, r, number_cluster])
    process = subprocess.Popen(["./RNN", arg_1, str(r), number_cluster[idx]])
    process.wait()
   
def running(dataset_name, r, idx):
    exec_time = []    
    arg_1 = "./dataset/" + dataset_name + "/"
    # print(arg_1)
    with open (arg_1 + "Result.txt", "w") as File:
        pass
    run_script (arg_1, r, idx)

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
        

def writeFile (dataset_name, r, ave_f1):
    with open("./dataset/" + dataset_name + "/r_result.csv", 'a', newline='') as csv_file:
        # 創建CSV寫入器
        csv_writer = csv.writer(csv_file)        
        data = [str(r), str(ave_f1)]
        csv_writer.writerow(data)

        
            

if __name__ == "__main__":
    ave_f1 = 0.0
    idx = 0

    print('Start')
    for dataset_name in dataset:
        with open("./dataset/" + dataset_name + "/r_result.csv", 'w', newline='') as csv_file:
            csv_writer = csv.writer(csv_file)
            data = ['r', 'F1 Score']
            csv_writer.writerow(data)    
        r = 0.5     
        while (r <= 30):
            running(dataset_name, r, idx)    
            ave_f1 = calculate_f1(dataset_name)        
            writeFile(dataset_name, r, ave_f1)
            r += 0.5
        print('Dataset: ' + dataset_name)
        idx += 1

    print('Finish')
