const express = require("express");
const app = express();
const mysql = require("mysql");
const PORT = process.env.port || 8000;

// import 하는 부분
const bodyParser = require("body-parser");

// 아랫부분 적당한 위치에 추가
app.use(express.json());
app.use(bodyParser.urlencoded({ extended: true }));


const cors = require('cors');

let corsOptions = {
  origin: "*", // 출처 허용 옵션
  credential: true, // 사용자 인증이 필요한 리소스(쿠키 ..등) 접근
};

app.use(cors(corsOptions));
//

const db = mysql.createPool({
  host: "localhost",
  user: "",
  password: "",
  database: "",
});
/*
app.get("/", (req, res) => {
  const sqlQuery = "INSERT INTO mboard (idx) VALUES (15)";
  db.query(sqlQuery, (err, result) => {
    res.send("success!");
  });
});
*/
app.get("/list", (req, res) => {
  //const sqlQuery = "SELECT *FROM mboard;";
  const sqlQuery = "SELECT idx, subject, name, DATE_FORMAT(rdate, '%Y-%m-%d') AS rdate FROM mboard;";
  db.query(sqlQuery, (err, result) => {
    res.send(result);
  });
});
app.post("/insert", (req, res) => {
  var title = req.body.title;
  var content = req.body.content;
 
  const sqlQuery =
    "INSERT INTO mboard (subject, content, name) VALUES (?,?,'matthew');";
  db.query(sqlQuery, [title, content], (err, result) => {
    res.send(result);
  });
});

app.post("/update", (req, res) => {
  var title = req.body.title;
  var content = req.body.content;

  const sqlQuery =
    "UPDATE mboard SET subject = ?, content = ?, name) VALUES (?,?,'artistJay');";
  db.query(sqlQuery, [title, content], (err, result) => {
    res.send(result);
  });
});

app.get("/detail", (req, res) => {
  var id = req.query.id;
  //var content = req.body.content;
  //console.log(id);

  const sqlQuery =
    "SELECT * from mboard WHERE idx =?";
  db.query(sqlQuery, [id], (err, result) => {
    res.send(result);
  });
});

app.listen(PORT, () => {
  console.log(`running on port ${PORT}`);
});
