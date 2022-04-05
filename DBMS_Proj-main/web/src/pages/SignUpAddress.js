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
import AddressForm from './addressComponents/AddressForm';
import Review from './addressComponents/Review';

// const steps = ['店家資訊', '負責人聯絡方式', '資料確認'];
const steps = ['店家資訊', '資料確認'];
const theme = createTheme();

export const ThemeContext = React.createContext()

function App() {
  const [activeStep, setActiveStep] = React.useState(0);
  const [storeName, setStoreName] = React.useState("政治大學店");
  const [address, setAddress] = React.useState("dfdsfs");
  const [phone_number, setPhone] = React.useState("0800921000");
  const [address_id, setID] = React.useState("")
  const [complete_message, setMessage] = React.useState("登錄中...")


  function handleNext() {

    var url = 'https://cnr.ebg.tw/api/place';
    if (activeStep === steps.length - 1) {
      console.log("post:")
      // console.log(storeName + " " + address + " " + phone_number)
      fetch(url, {
        method: "POST",
        body: JSON.stringify({ name: storeName, address: address, phone_number: phone_number }),
        headers: new Headers({ 'content-type': 'application/json' }),
      })
        .then(function (response) {
          console.log(response);
          console.log(response.body)
          return response.json();
        })
        .then(function (data) {
          console.log(data);
          if (data.success) {
            setID("場所代碼：" + data.data)
            setMessage("登錄成功🎉")
          }
          else {
            setMessage("登錄失敗😞")
            setID(data.error)
          }

        })
        .catch(error => console.error(error))
    }
    setActiveStep(activeStep + 1);

  };

  const handleBack = () => {
    setActiveStep(activeStep - 1);
  };

  function getStepContent(step) {
    switch (step) {
      case 0:
        return <AddressForm setName={setStoreName} setPhone={setPhone} setAddress={setAddress} />;
      case 1:
        return <Review name={storeName} address={address} phone={phone_number} />;
      default:
        throw new Error('Unknown step');
    }
  };



  return (
    <ThemeContext.Provider value={storeName}>
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
            實聯登記系統 - 場所登記
          </Typography>
        </Toolbar>
      </AppBar>
      <Container component="main" maxWidth="sm" sx={{ mb: 4 }}>
        <Paper variant="outlined" sx={{ my: { xs: 3, md: 6 }, p: { xs: 2, md: 3 } }}>
          <Typography component="h1" variant="h4" align="center">
            場所登記
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
                <Typography variant="subtitle1">
                    {address_id}
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
    </ThemeContext.Provider>
  );
}

export default App;
