# -*- coding: UTF-8 -*-
import random
import csv
if __name__ == "__main__":
    with open("../csv/person.csv", newline="") as csvfile:
        reader = csv.reader(csvfile)
        data_list = list(reader)
        n = int(input())
        used = list()
        for i in range(n):
            phone = "09"
            for j in range(8, 0, -1):
                num = random.randint(0, 9)
                phone = phone + str(num)
            if phone in used:
                i -= 1
            else:
                print("\"", end="")
                print(phone, end="\",")
                print(random.choice(data_list)[0])
                used.append(phone)
