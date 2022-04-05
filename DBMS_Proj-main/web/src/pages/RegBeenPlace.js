import * as React from 'react';
import CssBaseline from '@mui/material/CssBaseline';
import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Container from '@mui/material/Container';
import Toolbar from '@mui/material/Toolbar';
import Paper from '@mui/material/Paper';
import Stepper from '@mui/material/Stepper';
import Step from '@mui/material/Step';
import StepLabel from '@mui/material/StepLabel';
import Button from '@mui/material/Button';
import Typography from '@mui/material/Typography';
import { createTheme, ThemeProvider } from '@mui/material/styles';
import RegisterForm from './RegisterComponents/RegisterForm';
import Review from './RegisterComponents/Review';
import { useSearchParams } from "react-router-dom";
const steps = ['疫調資訊', '資料確認'];

var placeid = ""
var phonenum = ""

function getStepContent(step) {
  switch (step) {
    case 0:
      return <RegisterForm />;
    case 1:
      return <Review />;
    default:
      throw new Error('Unknown step');
  }
}

const theme = createTheme();

function App() {
  const [complete_message, setMessage]= React.useState("")
  const [activeStep, setActiveStep] = React.useState(0);
  const [searchParams, setSearchParams] = useSearchParams();
  placeid = searchParams.get("placeId");

  
  const requestput = (putplaceid,putphonenum) => {
    fetch("https://cnr.ebg.tw/api/reg", {
      method: 'POST',
      body: JSON.stringify({place_id: putplaceid , phone_number: putphonenum}),
      headers: {
        'Content-Type': 'application/json'
      },
    })
    .then(response => {
      return response.json();
    })
    .then(data => {
      console.log('success:', data);
      if(data.success){
        setMessage("登錄成功")
      }
      else{
        setMessage("登錄資料有誤，請重新輸入")
      }
    })
    .catch(err => {
      console.log('error:', err);
    })
  };

  const handleNext = () => {
    if(activeStep === steps.length - 2) {
      placeid = document.getElementById("PlaceID").value
      phonenum = document.getElementById("PhoneNum").value
    }
    else if(activeStep === steps.length - 1) {
      requestput(placeid,phonenum)
    }
    setActiveStep(activeStep + 1);
  };

  const handleBack = () => {
    setActiveStep(activeStep - 1);
  };
  return (
    <ThemeProvider theme={theme}>
      <CssBaseline />
      <AppBar
        position="absolute"
        color="default"
        elevation={0}
        sx={{
          position: 'relative',
          borderBottom: (t) => `1px solid ${t.palette.divider}`,
        }}
      >
        <Toolbar>
          <Typography variant="h6" color="inherit" noWrap>
            實聯登記系統 - 疫調登記
          </Typography>
        </Toolbar>
      </AppBar>
      <Container component="main" maxWidth="sm" sx={{ mb: 4 }}>
        <Paper variant="outlined" sx={{ my: { xs: 3, md: 6 }, p: { xs: 2, md: 3 } }}>
          <Typography component="h1" variant="h4" align="center">
            疫調登記
          </Typography>
          <Stepper activeStep={activeStep} sx={{ pt: 3, pb: 5 }}>
            {steps.map((label) => (
              <Step key={label}>
                <StepLabel>{label}</StepLabel>
              </Step>
            ))}
          </Stepper>
          <React.Fragment>
            {activeStep === steps.length ? (
              <React.Fragment>
                <Typography variant="h5" gutterBottom>
                  {complete_message}
                </Typography>
                <a href="/reg">重新登記</a>
              </React.Fragment>
            ) : (
              <React.Fragment>
                {getStepContent(activeStep)}
                <Box sx={{ display: 'flex', justifyContent: 'flex-end' }}>
                  {activeStep !== 0 && (
                    <Button onClick={handleBack} sx={{ mt: 3, ml: 1 }}>
                      上一步
                    </Button>
                  )}
                  <Button
                    variant="contained"
                    onClick={handleNext}
                    sx={{ mt: 3, ml: 1 }}
                  >
                    {activeStep === steps.length - 1 ? '完成' : '下一步'}
                  </Button>
                </Box>
              </React.Fragment>
            )}
          </React.Fragment>
        </Paper>
        <a href="./home">Home page</a>
      </Container>
    </ThemeProvider>
  );
}

export default App;
export {placeid};
export {phonenum};