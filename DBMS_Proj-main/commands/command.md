---
marp: true
title: 1101-DBMS-Final-Step1
date: 2021-12-12
paginate: true
---

# 1101-DBMS-Final

## Commands

---

# Build Container

```
docker run -d --name 1101DBMS-Final -p 60999:5432 -restart always -e POSTGRES_PASSWORD=1101DBMS-Final postgres

```

- -d ：後台執行 Container ，並返回 ID
- --name 1101DBMS-Final ：將 Container 取名為 1101DBMS-Final
- -p 609999:5432 ：將 Container 的 5432 Port 映射到主機的 60999 Port (前面代表主機，後面代表容器)
- -restart always ：如果 container 遇到例外的情況被 stop 掉，例如是重新開機，docker 會試著重新啟動此 container
- postgres ：指定安裝的鏡像 postgres

---

# 建立資料庫

利用pgAdmin4

---

# 製作模擬資料-Person
- 使用 IdGenerator 產生假身分證資料
- 利用 http://www.richyli.com/name/index.asp 姓名產生器產生中文姓名
- 結合兩者產生person的table，共5000筆

---

# 製作模擬資料-Phone
- 利用前述產生的Person資料
- 亂數產生電話號碼，並且一定屬於前者
- 共產生10000筆

---
# 製作模擬資料-Place
- 利用經濟部商業司提供的公司變更清冊開放資料，2021年12月版
- 結合前述的電話產生器產生Place資料
- 共16096筆
ref:
https://data.gov.tw/license
https://data.gcis.nat.gov.tw/od/detail?oid=75353060-3C3D-453E-8E5C-4ADDEAA8260F

---
# 製作模擬資料-Record
- 利用前述的Phone及Place，與隨機的時間（2022/1/1~2022/1/31）
- 組合產生Record資料，共500,000筆
