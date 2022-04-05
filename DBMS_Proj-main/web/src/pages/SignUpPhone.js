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
import PhoneForm from './phoneComponents/PhoneForm';
import Review from './phoneComponents/Review';


const steps = ['註冊資料', '資料確認'];
let phone = ""
let peopleID = ""

function getStepContent(step) {
  
  switch (step) {
    case 0:
      return <PhoneForm />;
    case 1:
      return <Review />;
    default:
      throw new Error('Unknown step');
  }
}

const theme = createTheme();

function App() {
  const [activeStep, setActiveStep] = React.useState(0);

  const [complete_message, setMessage] = React.useState("註冊中...")

  const [err, setTips] = React.useState("")

  const requestput = (putID,putNum) => {
    fetch("https://cnr.ebg.tw/api/phone", {
      method: 'POST',
      body: JSON.stringify({id: putID , phone_number: putNum}),
      headers: {
        'Content-Type': 'application/json'
      },
    })
    .then(response => {
      return response.json();
    })
    .then(data => {
      console.log('success:', data);
      if (data.success) {
        setMessage("註冊成功🎉")
        
      }
      else {
        setMessage("註冊失敗")
        setTips(data.error)
      }
    })
    .catch(err => {
      console.log('error:', err);
    })
  };
  
  const handleNext = () => {
    if(activeStep === steps.length - 2) {
      phone = document.getElementById("PhoneNum").value;
      peopleID = document.getElementById("PeopleID").value;
    }
    else if(activeStep === steps.length - 1) {
      requestput(peopleID,phone)
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
            實聯登記系統 - 手機註冊
          </Typography>
        </Toolbar>
      </AppBar>
      <Container component="main" maxWidth="sm" sx={{ mb: 4 }}>
        <Paper variant="outlined" sx={{ my: { xs: 3, md: 6 }, p: { xs: 2, md: 3 } }}>
          <Typography component="h1" variant="h4" align="center">
            手機註冊
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
                  {<br/>}
                  {err}
                </Typography>
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
export {phone};
export {peopleID};
