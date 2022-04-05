# -*- coding: UTF-8 -*-
import random
import csv


def genePlaceCode():
    placeCode = "2"
    for j in range(15):
        placeCode = placeCode + random.choice("0123456789")
    return placeCode


if __name__ == "__main__":
    usedNum = list()
    print("id,name,address,phone")
    with open("../csv/202112.csv", newline="") as csvfile:
        rows = csv.DictReader(csvfile)
        for row in rows:

            placeCode = genePlaceCode()
            while placeCode in usedNum:
                placeCode = genePlaceCode()
            else:
                phone = "09"
                print(placeCode, end=",")
                for j in range(8, 0, -1):
                    num = random.randint(0, 9)
                    phone = phone + str(num)
                print(row["公司名稱"], end=",")
                print(row["公司所在地"], end=",")
                print("\"", end="")
                print(phone, end="\"\n")
                usedNum.append(placeCode)
