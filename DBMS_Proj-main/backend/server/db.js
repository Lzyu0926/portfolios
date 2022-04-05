const { Pool} = require('pg')

const pool = new Pool({
  user: 'postgres',
  database: '1101DBMS_Final_DB',
  password: '1101DBMS-Final',
  port: 60999,
  host: '140.119.159.243',
})
module.exports = { pool };