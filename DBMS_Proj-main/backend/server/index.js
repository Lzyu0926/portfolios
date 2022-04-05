const express = require("express");
const cors = require("cors");
const { pool } = require("./db");
const path = require("path");
const app = express();
app.use(express.json());
app.use(cors());
app.use(express.static(path.join(__dirname, "build")));

const port = 60000;

//Person Functions
async function queryPerson(identity_card_id) {
  try {
    const res = await pool.query(
      "SELECT * FROM Person WHERE identity_card_id=$1",
      [identity_card_id]
    );
    return res.rows;
  } catch (error) {
    console.error(error);
  }
}
async function insertPerson(identity_card_id, name) {
  try {
    const res = await pool.query(
      "INSERT INTO Person (identity_card_id, name) VALUES ($1, $2)",
      [identity_card_id, name]
    );
    console.log(`Added a person with the name ${name}`);
  } catch (error) {
    throw new Error(error);
  }
}
function verifyId(id) {
  id = id.trim();
  verification = id.match("^[A-Z][12]\\d{8}$");
  if (!verification) {
    return false;
  }
  let conver = "ABCDEFGHJKLMNPQRSTUVXYWZIO";
  let weights = [1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1];

  id = String(conver.indexOf(id[0]) + 10) + id.slice(1);

  checkSum = 0;
  for (let i = 0; i < id.length; i++) {
    c = parseInt(id[i]);
    w = weights[i];
    checkSum += c * w;
  }
  return checkSum % 10 == 0;
}
app.post("/api/person", async (req, res) => {
  /*
  input: { 
    "id": "string",
    "name": "string",
  }
  output: {
    data: null
    success: boolean
    error: "string"
  }
  */
  const data = req.body;
  let result = { data: {}, success: false, error: "" };
  if (data === undefined) {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
  if (data["id"] != null && data["name"] != null) {
    //data check
    if (!verifyId(data["id"])) {
      result["error"] = "Error, wrong identit card id.";
      res.send(result);
      return;
    }
    if (data["name"] === "") {
      result["error"] = "Error, person name can not be empty.";
      res.send(result);
      return;
    }
    const person = await queryPerson(data["id"]);
    if (person.length > 0) {
      result["error"] = "Error, person id exist.";
      res.send(result);
      return;
    }
    //insert person
    try {
      insertPerson(data["id"], data["name"]);
    } catch (error) {
      res.send(error);
      return;
    }
    result["success"] = true;
    res.send(result);
  } else {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
});

//Phone Functions
async function queryPhone(phone_number) {
  try {
    const res = await pool.query("SELECT * FROM Phone WHERE phone_number=$1", [
      phone_number,
    ]);
    return res.rows;
  } catch (error) {
    throw new Error(error);
  }
}
async function insertPhone(phone_number, id) {
  try {
    const res = await pool.query(
      "INSERT INTO Phone (phone_number, identity_card_id) VALUES ($1, $2)",
      [phone_number, id]
    );
  } catch (error) {
    throw new Error(error);
  }
}
function verifyPhone(phone_num) {
  phone_num = phone_num.trim();
  verification = phone_num.match("^[0][9]\\d{8}$");
  return verification;
}

app.post("/api/phone", async (req, res) => {
  /*
  input: { 
    "id": "string",
    "phone_number": "string",
  }
  output: {
    data: null
    success: boolean
    error: "string"
  }
  */
  const data = req.body;
  let result = { data: {}, success: false, error: "" };
  if (data === undefined) {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
  if (data["id"] != null && data["phone_number"] != null) {
    //data check
    if (!verifyId(data["id"])) {
      result["error"] = "Error, wrong id.";
      res.send(result);
      return;
    }
    if (!verifyPhone(data["phone_number"])) {
      result["error"] = "Error, wrong phone_number.";
      res.send(result);
      return;
    }
    if (data["phone_number"] === "") {
      result["error"] = "Error, phone_number can not be empty.";
      res.send(result);
      return;
    }
    const person = await queryPerson(data["id"]);
    if (person.length <= 0) {
      result["error"] = "Error, person id does not exist.";
      res.send(result);
      return;
    }
    const phone = await queryPhone(data["phone_number"]);
    if (phone.length > 0) {
      result["error"] = "Error, phone_number exist.";
      res.send(result);
      return;
    }
    //insert phone
    try {
      insertPhone(data["phone_number"], data["id"]);
    } catch (error) {
      res.send(error);
      return;
    }
    result["success"] = true;
    res.send(result);
  } else {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
});

//Place Functions
async function queryPlace(name, address, phone_number) {
  try {
    const res = await pool.query(
      "SELECT * FROM Place WHERE name=$1 AND address=$2 AND phone_number=$3",
      [name, address, phone_number]
    );
    return res.rows;
  } catch (error) {
    throw new Error(error);
  }
}
async function insertPlace(place_id, name, address, phone_number) {
  try {
    const res = await pool.query(
      "INSERT INTO Place (place_id, name, address, phone_number) VALUES ($1, $2, $3, $4)",
      [place_id, name, address, phone_number]
    );
  } catch (error) {
    throw new Error(error);
  }
}
async function generateAddressId() {
  while (1) {
    try {
      let id = "2";
      let characters = "0123456789";
      let charactersLength = characters.length;
      for (var i = 0; i < 15; i++) {
        id += characters.charAt(Math.floor(Math.random() * charactersLength));
      }
      const res = await pool.query("SELECT * FROM Place WHERE place_id=$1", [id]);
      if (res.rows.length == 0) {
        return id;
      }
    } catch (error) {
      throw new Error(error);
    }
  }
}
app.post("/api/place", async (req, res) => {
  /*
  input: { 
    "name": "string",
    "address": "string",
    "phone_number": "string",
  }
  output: {
    data: "string, address id"
    success: boolean
    error: "string"
  }
  */
  const data = req.body;
  let result = { data: {}, success: false, error: "" };
  if (data === undefined) {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
  if (
    data["name"] != null &&
    data["address"] != null &&
    data["phone_number"] != null
  ) {
    //data check
    if (data["name"] === "") {
      result["error"] = "Error, place name can not be empty.";
      res.send(result);
      return;
    }
    if (data["address"] === "") {
      result["error"] = "Error, place address can not be empty.";
      res.send(result);
      return;
    }
    if (!verifyPhone(data["phone_number"])) {
      result["error"] = "Error, wrong phone_number.";
      res.send(result);
      return;
    }
    const place = await queryPlace(
      data["name"],
      data["address"],
      data["phone_number"]
    );
    if (place.length > 0) {
      result["error"] = "Error, place exist.";
      res.send(result);
      return;
    }
    const phone = await queryPhone(data["phone_number"]);
    if (phone.length <= 0) {
      result["error"] = "Error, phone_number does not exist.";
      res.send(result);
      return;
    }
    //insert place
    try {
      const id = await generateAddressId();
      result["data"] = id;
      insertPlace(id, data["name"], data["address"], data["phone_number"]);
    } catch (error) {
      res.send(error);
      return;
    }
    result["success"] = true;
    res.send(result);
  } else {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
});

//Record Functions
async function insertRecord(place_id, phone_number, time) {
  try {
    const res = await pool.query(
      "INSERT INTO Record (place_id, phone_number, time) VALUES ($1, $2, $3)",
      [place_id, phone_number, time]
    );
  } catch (error) {
    throw new Error(error);
  }
}
function verifyPlaceId(place_id) {
  place_id = place_id.trim();
  verification = place_id.match("^[2]\\d{15}$");
  return verification;
}
app.post("/api/reg", async (req, res) => {
  /*
  input: { 
    "place_id": "string",
    "phone_number": "string",
  }
  output: {
    data: "time"
    success: boolean
    error: "string"
  }
  */
  const data = req.body;
  let result = { data: {}, success: false, error: "" };
  if (data === undefined) {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
  if (data["place_id"] != null && data["phone_number"] != null) {
    //data check
    if (data["place_id"] === "") {
      result["error"] = "Error, place id can not be empty.";
      res.send(result);
      return;
    }
    if (data["phone_number"] === "") {
      result["error"] = "Error, place address can not be empty.";
      res.send(result);
      return;
    }
    if (!verifyPlaceId(data["place_id"])) {
      result["error"] = "Error, wrong place id.";
      res.send(result);
      return;
    }
    if (!verifyPhone(data["phone_number"])) {
      result["error"] = "Error, wrong phone_number.";
      res.send(result);
      return;
    }
    const phone = await queryPhone(data["phone_number"]);
    if (phone.length <= 0) {
      result["error"] = "Error, phone_number does not exist.";
      res.send(result);
      return;
    }
    //insert record
    try {
      const nowTime = new Date();
      insertRecord(data["place_id"], data["phone_number"], nowTime);
      result["data"] = nowTime;
    } catch (error) {
      res.send(error);
      return;
    }
    result["success"] = true;
    res.send(result);
  } else {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
});

//QueryById
async function queryById(identity_card_id) {
  try {
    const res = await pool.query(
      `/*過去14天到過的地方*/
      with place_list as (
          select
              *
          from
              record
          where
              phone_number in (
                  select
                      phone_number
                  from
                      (
                          /*這個人全部的電話*/
                          select
                              *
                          from
                              person
                              inner join phone on person.identity_card_id = phone.identity_card_id
                              and person.identity_card_id = $1
                      ) as phone_numbers
              )
              and time > NOW() - INTERVAL '14 DAYS'
      )
      select
          person.name,
          person.identity_card_id,
          place.address,
          record.time
      from
          record
          inner join place_list on place_list.place_id = record.place_id
          and record.time < place_list.time + INTERVAL '3 HOUR'
          and record.time > place_list.time - INTERVAL '3 HOUR'
          inner join phone on record.phone_number = phone.phone_number
          inner join person on phone.identity_card_id = person.identity_card_id
          inner join place on record.place_id = place.place_id
      order by record.time`,
      [identity_card_id]
    );
    return res.rows;
  } catch (error) {
    throw new Error(error);
  }
}
app.post("/api/query", async (req, res) => {
  /*
  input: { 
    "id": "string",
  }
  output: {
    data: [{},{}]
    success: boolean
    error: "string"
  }
  */
  const data = req.body;
  let result = { data: {}, success: false, error: "" };
  if (data === undefined) {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
  if (data["id"] != null) {
    //data check
    if (!verifyId(data["id"])) {
      result["error"] = "Error, wrong id.";
      res.send(result);
      return;
    }
    const person = await queryPerson(data["id"]);
    if (person.length <= 0) {
      result["error"] = "Error, person id does not exist.";
      res.send(result);
      return;
    }
    //query record
    try {
      result["data"] = await queryById(data["id"]);
    } catch (error) {
      console.log(error);
      res.send(error);
      return;
    }
    result["success"] = true;
    res.send(result);
  } else {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
});

//Query Place id
async function queryByPhone(phone_number) {
  try {
    const res = await pool.query("SELECT * FROM Place WHERE phone_number=$1", [
      phone_number,
    ]);
    return res.rows;
  } catch (error) {
    throw new Error(error);
  }
}
app.post("/api/queryPlace", async (req, res) => {
  /*
    input: { 
      "phone_number": "string",
    }
    output: {
      data: [{}]
      success: boolean
      error: "string"
    }
    */
  const data = req.body;
  let result = { data: {}, success: false, error: "" };
  if (data === undefined) {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
  if (data["phone_number"] != null) {
    //data check
    if (!verifyPhone(data["phone_number"])) {
      result["error"] = "Error, wrong phone number.";
      res.send(result);
      return;
    }
    //query record
    try {
      result["data"] = await queryByPhone(data["phone_number"]);
    } catch (error) {
      console.log(error);
      res.send(error);
      return;
    }
    result["success"] = true;
    res.send(result);
  } else {
    result["error"] = "POST Body Error";
    res.send(result);
    return;
  }
});

app.listen(port, () => {
  console.log(`App listening at http://localhost:${port}`);
});

app.get("*", (req, res) => {
  res.sendFile(path.join(__dirname + "/build/index.html"));
});
