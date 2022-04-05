# -*- coding: UTF-8 -*-
import random
import csv
from datetime import datetime


start_time = 1640966400
end_time = 1643644799
if __name__ == "__main__":
    n = int(input())
    usedAll = list()

    with open("../csvphone.csv", newline="") as phoneFile:
        phoneReader = csv.reader(phoneFile)
        phoneList = list(phoneReader)

        with open("../place.csv", newline="") as placeFile:
            placeReader = csv.reader(placeFile)
            placeList = list(placeReader)

            for i in range(n):
                phone = random.choice(phoneList)[0]
                place = random.choice(placeList)[0]
                rtime = random.randint(start_time, end_time)
                rtime = datetime.fromtimestamp(
                    rtime).strftime("%Y/%m/%d %H:%M:%S")
                if phone+str(rtime) in usedAll:
                    i -= 1
                else:
                    print(phone+","+place+","+str(rtime))
                    usedAll.append(phone+str(rtime))
