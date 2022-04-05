# -*- coding: UTF-8 -*-
import random
import csv
charList = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
local_table = {"A": 10, "B": 11, "C": 12, "D": 13, "E": 14, "F": 15, "G": 16, "H": 17, "I": 34, "J": 18, "K": 19, "L": 20,
               "M": 21, "N": 22, "O": 35, "P": 23, "Q": 24, "R": 25, "S": 26, "T": 27, "U": 28, "V": 29, "W": 32, "X": 30, "Y": 31, "Z": 33}

if __name__ == "__main__":
    n = int(input())
    usedName = list()
    usedId = list()
    with open("../csv/name.csv", newline="") as csvfile:
        reader = csv.reader(csvfile)
        data_list = list(reader)
        for i in range(n):
            output = ""
            local = random.choice(charList)
            output = output + local
            checkSum = local_table[local]//10+local_table[local] % 10*9

            gender = random.randint(1, 2)
            output = output + str(gender)
            checkSum = checkSum+gender*8
            for j in range(7, 0, -1):
                num = random.randint(0, 9)
                output = output + str(num)
                checkSum = checkSum+num*j
            output = output + str((10-checkSum % 10) % 10)

            name = random.choice(data_list)
            if output in usedId:
                i = i-1
            elif name in usedName:
                i = i-1
            else:
                print(output, end=",")
                print(name)
                usedId.append(output)
