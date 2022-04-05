import React from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import "./App.css";
const Home = React.lazy(() => import("./pages/Home"));
const SignUpPhone = React.lazy(() => import("./pages/SignUpPhone"));
const SignUpPeopleID = React.lazy(()=>import("./pages/SignUpPeopleID"));
const SignUpAddress = React.lazy(() => import("./pages/SignUpAddress"));
const QueryPhone = React.lazy(() => import("./pages/QueryPhone"));
const QueryPlace = React.lazy(() => import("./pages/QueryPlace"));
const RegBeenPlace = React.lazy(() => import("./pages/RegBeenPlace"));
const QRinfo = React.lazy(() => import("./pages/QRcode"));
function App() {
  const loading = (
    <div
      style={{
        fontSize: "30px",
        color: "#ffffff",
      }}
    >
      loading...
    </div>
  );
  return (
    <React.Suspense fallback={loading}>
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="home" element={<Home />} />
          <Route path="phone" element={<SignUpPhone />} />
          <Route path="people" element={<SignUpPeopleID />} />
          <Route path="address" element={<SignUpAddress />} />
          <Route path="query" element={<QueryPhone />} />
          <Route path="reg" element={<RegBeenPlace />} />
          <Route path="qr" element={<QRinfo />} />
          <Route path="queryplace" element={<QueryPlace />} />
        </Routes>
      </BrowserRouter>
    </React.Suspense>
  );
}

export default App;
